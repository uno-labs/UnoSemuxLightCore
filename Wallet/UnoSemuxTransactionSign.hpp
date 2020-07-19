#pragma once

#include "../UnoSemuxLightCore_global.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxTransactionSign
{
public:
    CLASS_DECLARE_DEFAULTS(UnoSemuxTransactionSign)

public:
                            UnoSemuxTransactionSign     (void) noexcept;
                            UnoSemuxTransactionSign     (GpBytesArray&& aData,
                                                         GpBytesArray&& aHash,
                                                         GpBytesArray&& aSign,
                                                         GpBytesArray&& aPublicKey) noexcept;
                            UnoSemuxTransactionSign     (const UnoSemuxTransactionSign& aSign);
                            UnoSemuxTransactionSign     (UnoSemuxTransactionSign&& aSign) noexcept;
                            ~UnoSemuxTransactionSign    (void) noexcept;

    const GpBytesArray&     Data                        (void) const noexcept {return iData;}
    const GpBytesArray&     Hash                        (void) const noexcept {return iHash;}
    const GpBytesArray&     Sign                        (void) const noexcept {return iSign;}
    const GpBytesArray&     PublicKey                   (void) const noexcept {return iPublicKey;}

    GpBytesArray            Encode                      (void) const;

private:
    GpBytesArray            iData;
    GpBytesArray            iHash;
    GpBytesArray            iSign;
    GpBytesArray            iPublicKey;
};

}//namespace UnoSemux
