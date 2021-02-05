#pragma once

#include "../UnoSemuxLightCore_global.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxTransactionSign
{
public:
	CLASS_DECLARE_DEFAULTS(UnoSemuxTransactionSign)

public:
								UnoSemuxTransactionSign		(void) noexcept;
								UnoSemuxTransactionSign		(GpBytesArray&&	aData,
															 GpBytesArray&& aHash,
															 GpBytesArray&& aSign,
															 GpBytesArray&& aPublicKey) noexcept;
								UnoSemuxTransactionSign		(const UnoSemuxTransactionSign& aSign);
								UnoSemuxTransactionSign		(UnoSemuxTransactionSign&& aSign) noexcept;
								~UnoSemuxTransactionSign	(void) noexcept;

	UnoSemuxTransactionSign&	operator=					(const UnoSemuxTransactionSign& aSign);
	UnoSemuxTransactionSign&	operator=					(UnoSemuxTransactionSign&& aSign) noexcept;

	const GpBytesArray&			Data						(void) const noexcept {return iData;}
	std::string					DataHex						(void) const noexcept {return StrOps::SFromBytes(Data());}
	const GpBytesArray&			Hash						(void) const noexcept {return iHash;}
	std::string					HashHex						(void) const noexcept {return StrOps::SFromBytes(Hash());}
	const GpBytesArray&			Sign						(void) const noexcept {return iSign;}
	std::string					SignHex						(void) const noexcept {return StrOps::SFromBytes(Sign());}
	const GpBytesArray&			PublicKey					(void) const noexcept {return iPublicKey;}
	std::string					PublicKeyHex				(void) const noexcept {return StrOps::SFromBytes(PublicKey());}

	GpBytesArray				Encode						(void) const;
	std::string					EncodeHex					(void) const {return StrOps::SFromBytes(Encode());}

private:
	GpBytesArray				iData;
	GpBytesArray				iHash;
	GpBytesArray				iSign;
	GpBytesArray				iPublicKey;
};

}//namespace UnoSemux
