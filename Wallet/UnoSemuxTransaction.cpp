#include "UnoSemuxTransaction.hpp"

namespace UnoSemux {

UnoSemuxTransaction::UnoSemuxTransaction (void) noexcept
{
}

UnoSemuxTransaction::UnoSemuxTransaction (const UnoSemuxTransaction& aTransaction):
iNetworkType(aTransaction.iNetworkType),
iType(aTransaction.iType),
iAddrTo(aTransaction.iAddrTo),
iValue(aTransaction.iValue),
iFee(aTransaction.iFee),
iNonce(aTransaction.iNonce),
iTimestamp(aTransaction.iTimestamp),
iData(aTransaction.iData),
iGas(aTransaction.iGas),
iGasPrice(aTransaction.iGasPrice)
{
}

UnoSemuxTransaction::UnoSemuxTransaction (UnoSemuxTransaction&& aTransaction) noexcept:
iNetworkType(std::move(aTransaction.iNetworkType)),
iType(std::move(aTransaction.iType)),
iAddrTo(std::move(aTransaction.iAddrTo)),
iValue(std::move(aTransaction.iValue)),
iFee(std::move(aTransaction.iFee)),
iNonce(std::move(aTransaction.iNonce)),
iTimestamp(std::move(aTransaction.iTimestamp)),
iData(std::move(aTransaction.iData)),
iGas(std::move(aTransaction.iGas)),
iGasPrice(std::move(aTransaction.iGasPrice))
{
}

UnoSemuxTransaction::UnoSemuxTransaction (const NetworkTypeTE       aNetworkType,
                                          const TransactionTypeTE   aType,
                                          const GpBytesArray&       aAddrTo,
                                          const nanosem_t           aValue,
                                          const nanosem_t           aFee,
                                          const s_int_64            aNonce,
                                          const unix_ts_ms_t        aTimestamp,
                                          const GpBytesArray&       aData,
                                          const semgas_t            aGas,
                                          const nanosem_t           aGasPrice):
iNetworkType(aNetworkType),
iType(aType),
iAddrTo(aAddrTo),
iValue(aValue),
iFee(aFee),
iNonce(aNonce),
iTimestamp(aTimestamp),
iData(aData),
iGas(aGas),
iGasPrice(aGasPrice)
{
}

UnoSemuxTransaction::UnoSemuxTransaction (const NetworkTypeTE       aNetworkType,
                                          const TransactionTypeTE   aType,
                                          GpBytesArray&&            aAddrTo,
                                          const nanosem_t           aValue,
                                          const nanosem_t           aFee,
                                          const s_int_64            aNonce,
                                          const unix_ts_ms_t        aTimestamp,
                                          GpBytesArray&&            aData,
                                          const semgas_t            aGas,
                                          const nanosem_t           aGasPrice) noexcept:
iNetworkType(aNetworkType),
iType(aType),
iAddrTo(std::move(aAddrTo)),
iValue(aValue),
iFee(aFee),
iNonce(aNonce),
iTimestamp(std::move(aTimestamp)),
iData(aData),
iGas(aGas),
iGasPrice(aGasPrice)
{
}

UnoSemuxTransaction::~UnoSemuxTransaction (void) noexcept
{
}

GpBytesArray    UnoSemuxTransaction::Encode (void) const
{
    GpBytesArray res;
    res.reserve(64 + iData.size());

    GpByteWriterStorageByteArray    writerStorage(res);
    GpByteWriter                    writer(writerStorage);

    writer.UInt8(u_int_8(iNetworkType));
    writer.UInt8(u_int_8(iType));
    writer.BytesWithLen(iAddrTo);
    writer.SInt64(iValue.ValueAs<s_int_64>());
    writer.SInt64(iFee.ValueAs<s_int_64>());
    writer.SInt64(iNonce);
    writer.SInt64(iTimestamp.ValueAs<s_int_64>());
    writer.BytesWithLen(iData);

    if (   (iType == TransactionTypeT::CALL)
        || (iType == TransactionTypeT::CREATE))
    {
        writer.SInt64(iGas.ValueAs<s_int_64>());
        writer.SInt64(iGasPrice.ValueAs<s_int_64>());
    }

    return res;
}

}//namespace UnoSemux
