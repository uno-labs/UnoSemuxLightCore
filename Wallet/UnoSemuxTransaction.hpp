#pragma once

#include "UnoSemuxTransactionType.hpp"
#include "UnoSemuxNetworkType.hpp"
#include "../Utils/UnoSemuxUnits.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxTransaction
{
public:
    CLASS_DECLARE_DEFAULTS(UnoSemuxTransaction)

    using NetworkTypeT          = UnoSemuxNetworkType;
    using NetworkTypeTE         = NetworkTypeT::EnumT;

    using TransactionTypeT      = UnoSemuxTransactionType;
    using TransactionTypeTE     = TransactionTypeT::EnumT;

public:
                            UnoSemuxTransaction     (void) noexcept;
                            UnoSemuxTransaction     (const UnoSemuxTransaction& aTransaction);
                            UnoSemuxTransaction     (UnoSemuxTransaction&& aTransaction) noexcept;
                            UnoSemuxTransaction     (const NetworkTypeTE        aNetworkType,
                                                     const TransactionTypeTE    aType,
                                                     const GpBytesArray&        aAddrTo,
                                                     const nanosem_t            aValue,
                                                     const nanosem_t            aFee,
                                                     const s_int_64             aNonce,
                                                     const unix_ts_ms_t         aTimestamp,
                                                     const GpBytesArray&        aData,
                                                     const semgas_t             aGas,
                                                     const nanosem_t            aGasPrice);
                            UnoSemuxTransaction     (const NetworkTypeTE        aNetworkType,
                                                     const TransactionTypeTE    aType,
                                                     GpBytesArray&&             aAddrTo,
                                                     const nanosem_t            aValue,
                                                     const nanosem_t            aFee,
                                                     const s_int_64             aNonce,
                                                     const unix_ts_ms_t         aTimestamp,
                                                     GpBytesArray&&             aData,
                                                     const semgas_t             aGas,
                                                     const nanosem_t            aGasPrice) noexcept;
                            ~UnoSemuxTransaction    (void) noexcept;

    NetworkTypeTE           NetworkType             (void) const noexcept {return iNetworkType;}
    TransactionTypeTE       Type                    (void) const noexcept {return iType;}
    const GpBytesArray&     AddrTo                  (void) const noexcept {return iAddrTo;}
    nanosem_t               Value                   (void) const noexcept {return iValue;}
    nanosem_t               Fee                     (void) const noexcept {return iFee;}
    s_int_64                Nonce                   (void) const noexcept {return iNonce;}
    unix_ts_ms_t            Timestamp               (void) const noexcept {return iTimestamp;}
    const GpBytesArray&     Data                    (void) const noexcept {return iData;}
    semgas_t                Gas                     (void) const noexcept {return iGas;}
    nanosem_t               GasPrice                (void) const noexcept {return iGasPrice;}

    GpBytesArray            Encode                  (void) const;
    //void                  Decoode                 (GpRawPtrByteR aData) const;

private:
    NetworkTypeTE           iNetworkType;
    TransactionTypeTE       iType;
    GpBytesArray            iAddrTo;
    nanosem_t               iValue      = 0_usem;
    nanosem_t               iFee        = 0_usem;
    s_int_64                iNonce      = 0;
    unix_ts_ms_t            iTimestamp  = 0_unix_ts_s;
    GpBytesArray            iData;
    semgas_t                iGas        = 0_semgas;
    nanosem_t               iGasPrice   = 0_usem;
};

}//namespace UnoSemux
