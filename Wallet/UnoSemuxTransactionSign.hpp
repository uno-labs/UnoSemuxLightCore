#pragma once

#include "../UnoSemuxLightCore_global.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxTransactionSign
{
public:
							UnoSemuxTransactionSign		(void) noexcept;
							UnoSemuxTransactionSign		(GpBytesArray&&	aTxData,
														 GpBytesArray&& aTxHash,
														 GpBytesArray&& aSign,
														 GpBytesArray&& aPubKeyNoPrefix) noexcept;
							UnoSemuxTransactionSign		(const UnoSemuxTransactionSign& aSign);
							UnoSemuxTransactionSign		(UnoSemuxTransactionSign&& aSign) noexcept;
							~UnoSemuxTransactionSign	(void) noexcept;

	const GpBytesArray&		TxData						(void) const noexcept {return iTxData;}
	const GpBytesArray&		TxHash						(void) const noexcept {return iTxHash;}
	const GpBytesArray&		Sign						(void) const noexcept {return iSign;}
	const GpBytesArray&		PubKeyNoPrefix				(void) const noexcept {return iPubKeyNoPrefix;}

	GpBytesArray			Encode						(void) const;

private:
	GpBytesArray			iTxData;
	GpBytesArray			iTxHash;
	GpBytesArray			iSign;
	GpBytesArray			iPubKeyNoPrefix;
};

}//namespace UnoSemux
