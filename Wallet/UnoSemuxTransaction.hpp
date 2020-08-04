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
                                                         GpBytesArray&&             aAddrTo,
                                                         const nanosem_t            aValue,
                                                         const nanosem_t            aFee,
                                                         const s_int_64             aNonce,
                                                         const unix_ts_ms_t         aTimestamp,
                                                         GpBytesArray&&             aData,
                                                         const semgas_t             aGas,
                                                         const nanosem_t            aGasPrice) noexcept;
                                ~UnoSemuxTransaction    (void) noexcept;

    static UnoSemuxTransaction  STransfer               (const NetworkTypeTE        aNetworkType,
                                                         GpRawPtrCharR              aAddrToStrHex,
                                                         const nanosem_t            aValue,
                                                         const nanosem_t            aFee,
                                                         const s_int_64             aNonce,
                                                         const unix_ts_ms_t         aTimestamp,
                                                         GpRawPtrByteR              aData);
    static UnoSemuxTransaction  SDelegate               (const NetworkTypeTE        aNetworkType,
                                                         GpRawPtrCharR              aAddrToStrHex,
                                                         const nanosem_t            aValue,
                                                         const nanosem_t            aFee,
                                                         const s_int_64             aNonce,
                                                         const unix_ts_ms_t         aTimestamp,
                                                         GpRawPtrCharR              aName);
    static UnoSemuxTransaction  SVote                   (const NetworkTypeTE        aNetworkType,
                                                         GpRawPtrCharR              aAddrToStrHex,
                                                         const nanosem_t            aValue,
                                                         const nanosem_t            aFee,
                                                         const s_int_64             aNonce,
                                                         const unix_ts_ms_t         aTimestamp,
                                                         GpRawPtrByteR              aData);
    static UnoSemuxTransaction  SUnvote                 (const NetworkTypeTE        aNetworkType,
                                                         GpRawPtrCharR              aAddrToStrHex,
                                                         const nanosem_t            aValue,
                                                         const nanosem_t            aFee,
                                                         const s_int_64             aNonce,
                                                         const unix_ts_ms_t         aTimestamp,
                                                         GpRawPtrByteR              aData);
    static UnoSemuxTransaction  SCreate                 (const NetworkTypeTE        aNetworkType,
                                                         GpRawPtrCharR              aAddrToStrHex,
                                                         const s_int_64             aNonce,
                                                         const unix_ts_ms_t         aTimestamp,
                                                         GpRawPtrByteR              aData,
                                                         const semgas_t             aGas,
                                                         const nanosem_t            aGasPrice);
    static UnoSemuxTransaction  SCall                   (const NetworkTypeTE        aNetworkType,
                                                         GpRawPtrCharR              aAddrToStrHex,
                                                         const nanosem_t            aValue,
                                                         const s_int_64             aNonce,
                                                         const unix_ts_ms_t         aTimestamp,
                                                         GpRawPtrByteR              aData,
                                                         const semgas_t             aGas,
                                                         const nanosem_t            aGasPrice);

    UnoSemuxTransaction&        operator=               (const UnoSemuxTransaction& aTransaction);
    UnoSemuxTransaction&        operator=               (UnoSemuxTransaction&& aTransaction) noexcept;

    NetworkTypeT                NetworkType             (void) const noexcept {return iNetworkType;}
    TransactionTypeT            Type                    (void) const noexcept {return iType;}
    const GpBytesArray&         AddrTo                  (void) const noexcept {return iAddrTo;}
    std::string                 AddrToStrHex            (void) const noexcept {return GpStringOps::SFromBytes(iAddrTo);}
    nanosem_t                   Value                   (void) const noexcept {return iValue;}
    nanosem_t                   Fee                     (void) const noexcept {return iFee;}
    s_int_64                    Nonce                   (void) const noexcept {return iNonce;}
    unix_ts_ms_t                Timestamp               (void) const noexcept {return iTimestamp;}
    const GpBytesArray&         Data                    (void) const noexcept {return iData;}
    std::string                 DataStrHex              (void) const noexcept {return GpStringOps::SFromBytes(iData);}
    semgas_t                    Gas                     (void) const noexcept {return iGas;}
    nanosem_t                   GasPrice                (void) const noexcept {return iGasPrice;}

    GpBytesArray                Encode                  (void) const;
    std::string                 EncodeHex               (void) const;
    //void                      Decoode                 (GpRawPtrByteR aData) const;

private:
    NetworkTypeTE               iNetworkType;
    TransactionTypeTE           iType;
    GpBytesArray                iAddrTo;
    nanosem_t                   iValue      = 0_usem;
    nanosem_t                   iFee        = 0_usem;
    s_int_64                    iNonce      = 0;
    unix_ts_ms_t                iTimestamp  = 0_unix_ts_s;
    GpBytesArray                iData;
    semgas_t                    iGas        = 0_semgas;
    nanosem_t                   iGasPrice   = 0_usem;
};

}//namespace UnoSemux
