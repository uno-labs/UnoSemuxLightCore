#include "UnoSemuxTransactionSign.hpp"

namespace UnoSemux {

UnoSemuxTransactionSign::UnoSemuxTransactionSign (void) noexcept
{
}

UnoSemuxTransactionSign::UnoSemuxTransactionSign (GpBytesArray&& aTxData,
												  GpBytesArray&& aTxHash,
												  GpBytesArray&& aSign,
												  GpBytesArray&& aPubKeyNoPrefix) noexcept:
iTxData(std::move(aTxData)),
iTxHash(std::move(aTxHash)),
iSign(std::move(aSign)),
iPubKeyNoPrefix(std::move(aPubKeyNoPrefix))
{
}

UnoSemuxTransactionSign::UnoSemuxTransactionSign (const UnoSemuxTransactionSign& aSign):
iTxData(aSign.iTxData),
iTxHash(aSign.iTxHash),
iSign(aSign.iSign),
iPubKeyNoPrefix(aSign.iPubKeyNoPrefix)
{
}

UnoSemuxTransactionSign::UnoSemuxTransactionSign (UnoSemuxTransactionSign&& aSign) noexcept:
iTxData(std::move(aSign.iTxData)),
iTxHash(std::move(aSign.iTxHash)),
iSign(std::move(aSign.iSign)),
iPubKeyNoPrefix(std::move(aSign.iPubKeyNoPrefix))
{
}

UnoSemuxTransactionSign::~UnoSemuxTransactionSign (void) noexcept
{
}

GpBytesArray	UnoSemuxTransactionSign::Encode (void) const
{

	GpBytesArray res;
	res.reserve(  iTxData.size()
				+ iTxHash.size()
				+ iSign.size()
				+ iPubKeyNoPrefix.size());

	GpByteOStreamByteArray ostream(res);

	ostream.CompactSInt32(NumOps::SConvert<s_int_32>(iTxHash.size()));
	ostream.Bytes(iTxHash);
	ostream.CompactSInt32(NumOps::SConvert<s_int_32>(iTxData.size()));
	ostream.Bytes(iTxData);
	ostream.CompactSInt32(NumOps::SConvert<s_int_32>(iSign.size() + iPubKeyNoPrefix.size()));
	ostream.Bytes(iSign);
	ostream.Bytes(iPubKeyNoPrefix);

	return res;
}

}//namespace UnoSemux
