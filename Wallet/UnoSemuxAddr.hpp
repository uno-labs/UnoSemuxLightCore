#pragma once

#include "UnoSemuxTransaction.hpp"
#include "UnoSemuxTransactionSign.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxAddr
{
public:
	CLASS_REMOVE_CTRS(UnoSemuxAddr);
	CLASS_DECLARE_DEFAULTS(UnoSemuxAddr);

	using KeyPairT	= GpCryptoKeyPair_Ed25519;

public:
								UnoSemuxAddr			(KeyPairT::SP aKeyPair);
	virtual						~UnoSemuxAddr			(void) noexcept;

	void						Clear					(void) noexcept;

	const KeyPairT&				KeyPair					(void) const noexcept {return iKeyPair.VC();}

	const GpBytesArray&			Addr					(void) const noexcept {return iAddr;}
	std::string					AddrStrHex				(void) const noexcept {return GpStringOps::SFromBytes(iAddr);}

	s_int_64					Nonce					(void) const noexcept {return iNonce;}
	s_int_64					IncNonce				(void) noexcept {return ++iNonce;}
	void						SetNonce				(const s_int_64 aNonce) noexcept {iNonce = aNonce;}

	UnoSemuxTransactionSign		Sign1					(const UnoSemuxTransaction& aTransaction) const;
	UnoSemuxTransactionSign		Sign2					(const UnoSemuxTransaction& aTransaction) const;

	static UnoSemuxAddr::SP		SGenerateNew			(void);
	static UnoSemuxAddr::SP		SImportPrivateKeyBytes	(const GpSecureStorage& aPrivateBytes);
	static UnoSemuxAddr::SP		SImportPrivateKeyStrHex	(const GpSecureStorage& aPrivateStrHex);
	static UnoSemuxAddr::SP		SImportPrivateKeyStrHex	(std::string_view aPrivateStrHex);

private:
	void						RecalcAddr				(void);

private:
	KeyPairT::SP				iKeyPair;
	GpBytesArray				iAddr;
	s_int_64					iNonce = 0;
};

}//namespace UnoSemux
