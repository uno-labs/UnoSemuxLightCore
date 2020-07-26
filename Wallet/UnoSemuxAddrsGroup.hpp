#pragma once

#include "UnoSemuxAddr.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxAddrsGroup
{
public:
    CLASS_REMOVE_CTRS(UnoSemuxAddrsGroup)
    CLASS_DECLARE_DEFAULTS(UnoSemuxAddrsGroup)

    using AddrListT = UnoSemuxAddr::C::MapStr::SP;

public:
                                UnoSemuxAddrsGroup      (GpCryptoKeyFactory::SP aFactory);
                                ~UnoSemuxAddrsGroup     (void) noexcept;

    UnoSemuxAddr::SP            GenNext                 (void);
    void                        Delete                  (GpRawPtrCharR aAddrStrHex);
    UnoSemuxAddr::SP            Find                    (GpRawPtrCharR aAddrStrHex);
    bool                        IsContainAddr           (GpRawPtrCharR aAddrStrHex) const;
    const AddrListT&            AddrsList               (void) const noexcept {return iAddrsList;}
    const GpCryptoKeyFactory&   Factory                 (void) const {return iFactory.VC();}

private:
    GpCryptoKeyFactory::SP      iFactory;
    AddrListT                   iAddrsList;
};

}//UnoSemux
