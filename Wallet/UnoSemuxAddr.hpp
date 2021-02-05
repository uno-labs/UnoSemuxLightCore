#pragma once

#include "UnoSemuxTransaction.hpp"
#include "UnoSemuxTransactionSign.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxAddr
{
public:
	CLASS_DECLARE_DEFAULTS(UnoSemuxAddr)

	using KeyPairT	= GpCryptoKeyPair_Ed25519;

public:
								UnoSemuxAddr		(void);
								UnoSemuxAddr		(const UnoSemuxAddr& aAddr);
								UnoSemuxAddr		(UnoSemuxAddr&& aAddr);
								UnoSemuxAddr		(const KeyPairT& aKeyPair);
								UnoSemuxAddr		(KeyPairT&& aKeyPair);
	virtual						~UnoSemuxAddr		(void) noexcept;

	UnoSemuxAddr&				operator=			(const UnoSemuxAddr& aAddr);
	UnoSemuxAddr&				operator=			(UnoSemuxAddr&& aAddr);

	const KeyPairT&				KeyPair				(void) const noexcept {return iKeyPair;}

	GpSecureStorage				PrivateKey			(void) const {return iKeyPair.ToPrivateBytesWithPrefix();}
	GpSecureStorage				PrivateKeyStrHex	(void) const {return iKeyPair.ToPrivateStrHexWithPrefix();}

	const GpBytesArray&			Addr				(void) const noexcept {return iAddr;}
	std::string					AddrStrHex			(void) const noexcept {return StrOps::SFromBytes(iAddr);}

	std::string_view			Name				(void) const noexcept {return iName;}
	void						SetName				(std::string_view aName) {iName = aName;}

	UnoSemuxTransactionSign		Sign1				(const UnoSemuxTransaction& aTransaction) const;
	UnoSemuxTransactionSign		Sign2				(const UnoSemuxTransaction& aTransaction) const;

private:
	void						RecalcAddr			(void);

private:
	KeyPairT					iKeyPair;
	GpBytesArray				iAddr;
	std::string					iName;
};

}//namespace UnoSemux
