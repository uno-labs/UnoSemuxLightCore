#include "UnoSemuxAddr.hpp"

namespace UnoSemux {

UnoSemuxAddr::UnoSemuxAddr (const KeyPairT& aKeyPair):
iKeyPair(aKeyPair)
{
    RecalcAddr();
}

UnoSemuxAddr::UnoSemuxAddr (KeyPairT&& aKeyPair):
iKeyPair(std::move(aKeyPair))
{
    RecalcAddr();
}

UnoSemuxAddr::~UnoSemuxAddr (void) noexcept
{
    iKeyPair.Clear();
    iAddr.clear();
    iNonce = 0;
}

UnoSemuxTransactionSign UnoSemuxAddr::Sign1 (const UnoSemuxTransaction& aTransaction) const
{
    GpBytesArray                        transactionBytes    = aTransaction.Encode();
    GpCryptoHash_Blake2b::Res256T       hash                = GpCryptoHash_Blake2b::S_256(transactionBytes);
    GpCryptoKeyPair_Ed25519::ResSignT   sign                = iKeyPair.Sign(hash);
    GpRawPtrByteR                       pubKey              = iKeyPair.PublicBytes();

    return UnoSemuxTransactionSign(std::move(transactionBytes),
                                   std::move(GpBytesArrayUtils::SMake(hash)),
                                   std::move(GpBytesArrayUtils::SMake(sign)),
                                   std::move(GpBytesArrayUtils::SMake(pubKey.AsStringView())));
}

UnoSemuxTransactionSign UnoSemuxAddr::Sign2 (const UnoSemuxTransaction& aTransaction) const
{
    GpBytesArray                        transactionBytes    = aTransaction.Encode();
    GpCryptoHash_Blake2b::Res256T       hash                = GpCryptoHash_Blake2b::S_256(transactionBytes, iAddr);
    GpCryptoKeyPair_Ed25519::ResSignT   sign                = iKeyPair.Sign(hash);
    GpRawPtrByteR                       pubKey              = iKeyPair.PublicBytes();

    return UnoSemuxTransactionSign(std::move(transactionBytes),
                                   std::move(GpBytesArrayUtils::SMake(hash)),
                                   std::move(GpBytesArrayUtils::SMake(sign)),
                                   std::move(GpBytesArrayUtils::SMake(pubKey.AsStringView())));
}

void    UnoSemuxAddr::RecalcAddr (void)
{
    const GpBytesArray                      publicBytes     = iKeyPair.ToPublicBytesWithPrefix();
    const GpCryptoHash_Blake2b::Res256T     blake2b_hash    = GpCryptoHash_Blake2b::S_256(publicBytes);
    const GpCryptoHash_Ripemd160::Res160T   ripemd160       = GpCryptoHash_Ripemd160::S_H(blake2b_hash);

    iAddr = GpBytesArrayUtils::SMake(ripemd160);
    iName = AddrStrHex();
}

}//namespace UnoSemux
