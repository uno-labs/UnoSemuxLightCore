#include "UnoSemuxAddr.hpp"

namespace UnoSemux {

UnoSemuxAddr::UnoSemuxAddr (KeyPairT::SP aKeyPair):
iKeyPair(std::move(aKeyPair))
{
	RecalcAddr();
}

UnoSemuxAddr::~UnoSemuxAddr (void) noexcept
{
	Clear();
}

void	UnoSemuxAddr::Clear (void) noexcept
{
	iKeyPair.Clear();
	iAddr.clear();
	iNonce = 0;
}

UnoSemuxTransactionSign	UnoSemuxAddr::Sign1 (const UnoSemuxTransaction&	aTransaction) const
{
	const UnoSemuxAddr::KeyPairT&	keyPair	= iKeyPair.VC();

	GpBytesArray transactionBytes	= aTransaction.Encode();
	GpBytesArray transactionHash	= GpCryptoHash_Blake2b::S_256_Ba(transactionBytes);
	GpBytesArray transactionSign	= keyPair.Sign(transactionHash);
	GpBytesArray pubKey				= keyPair.PublicBytes();

	return UnoSemuxTransactionSign(std::move(transactionBytes),
								   std::move(transactionHash),
								   std::move(transactionSign),
								   std::move(pubKey));
}

UnoSemuxTransactionSign	UnoSemuxAddr::Sign2 (const UnoSemuxTransaction&	aTransaction) const
{
	const UnoSemuxAddr::KeyPairT&	keyPair	= iKeyPair.VC();

	GpBytesArray transactionBytes	= aTransaction.Encode();
	GpBytesArray transactionHash	= GpCryptoHash_Blake2b::S_256_Ba(transactionBytes, iAddr);
	GpBytesArray transactionSign	= keyPair.Sign(transactionHash);
	GpBytesArray pubKey				= keyPair.PublicBytes();

	return UnoSemuxTransactionSign(std::move(transactionBytes),
								   std::move(transactionHash),
								   std::move(transactionSign),
								   std::move(pubKey));
}

UnoSemuxAddr::SP	UnoSemuxAddr::SGenerateNew (void)
{
	KeyPairT::SP keyPair = KeyPairT::SP::SNew();
	keyPair.V().GenerateNew();
	return UnoSemuxAddr::SP::SNew(keyPair);
}

UnoSemuxAddr::SP	UnoSemuxAddr::SImportPrivateKeyBytes (const GpSecureStorage& aPrivateBytes)
{
	KeyPairT::SP keyPair = KeyPairT::SP::SNew();
	keyPair.V().ImportPrivateBytesSS(aPrivateBytes);
	return UnoSemuxAddr::SP::SNew(keyPair);
}

UnoSemuxAddr::SP	UnoSemuxAddr::SImportPrivateKeyStrHex (const GpSecureStorage& aPrivateStrHex)
{
	KeyPairT::SP keyPair = KeyPairT::SP::SNew();
	keyPair.V().ImportPrivateStrHexSS(aPrivateStrHex);
	return UnoSemuxAddr::SP::SNew(keyPair);
}

UnoSemuxAddr::SP	UnoSemuxAddr::SImportPrivateKeyStrHex (std::string_view aPrivateStrHex)
{
	KeyPairT::SP keyPair = KeyPairT::SP::SNew();
	keyPair.V().ImportPrivateStrHexSV(aPrivateStrHex);
	return UnoSemuxAddr::SP::SNew(keyPair);
}

void	UnoSemuxAddr::RecalcAddr (void)
{
	const GpBytesArray publicBytes		= iKeyPair.VC().ToPublicBytesWithPrefix();
	const GpBytesArray pk_blake2b_hash	= GpCryptoHash_Blake2b::S_256_Ba(publicBytes);
	iAddr								= GpCryptoHash_Ripemd160::S_H(pk_blake2b_hash);
}

}//namespace UnoSemux
