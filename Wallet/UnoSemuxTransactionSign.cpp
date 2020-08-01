#include "UnoSemuxTransactionSign.hpp"

namespace UnoSemux {

UnoSemuxTransactionSign::UnoSemuxTransactionSign (void) noexcept
{
}

UnoSemuxTransactionSign::UnoSemuxTransactionSign (GpBytesArray&& aData,
                                                  GpBytesArray&& aHash,
                                                  GpBytesArray&& aSign,
                                                  GpBytesArray&& aPublicKey) noexcept:
iData(std::move(aData)),
iHash(std::move(aHash)),
iSign(std::move(aSign)),
iPublicKey(std::move(aPublicKey))
{
}

UnoSemuxTransactionSign::UnoSemuxTransactionSign (const UnoSemuxTransactionSign& aSign):
iData(aSign.iData),
iHash(aSign.iHash),
iSign(aSign.iSign),
iPublicKey(aSign.iPublicKey)
{
}

UnoSemuxTransactionSign::UnoSemuxTransactionSign (UnoSemuxTransactionSign&& aSign) noexcept:
iData(std::move(aSign.iData)),
iHash(std::move(aSign.iHash)),
iSign(std::move(aSign.iSign)),
iPublicKey(std::move(aSign.iPublicKey))
{
}

UnoSemuxTransactionSign::~UnoSemuxTransactionSign (void) noexcept
{
}

GpBytesArray    UnoSemuxTransactionSign::Encode (void) const
{
    GpBytesArray res;
    res.reserve(  iHash.size()
                + iData.size()
                + iSign.size()
                + iPublicKey.size());

    GpByteWriterStorageByteArray    writerStorage(res);
    GpByteWriter                    writer(writerStorage);

    writer.BytesWithLen(iHash);
    writer.BytesWithLen(iData);

    writer.CompactSInt32(NumOps::SConvert<s_int_32>(iSign.size() + iPublicKey.size()));
    writer.Bytes(iSign);
    writer.Bytes(iPublicKey);

    return res;
}

}//namespace UnoSemux
