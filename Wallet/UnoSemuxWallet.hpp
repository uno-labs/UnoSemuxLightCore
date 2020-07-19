#pragma once

#include "UnoSemuxAddrsGroup.hpp"
#include "UnoSemuxWalletUtils.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxWallet
{
public:
    CLASS_REMOVE_CTRS_EXCEPT_DEFAULT(UnoSemuxWallet)
    CLASS_DECLARE_DEFAULTS(UnoSemuxWallet)

public:
                                    UnoSemuxWallet      (void);
                                    ~UnoSemuxWallet     (void) noexcept;

    UnoSemuxAddr::SP                GenNextRndAddr      (void);
    UnoSemuxAddr::SP                GenNextHDAddr       (const count_t aHDGroupId);
    void                            DeleteAddr          (GpRawPtrCharR aAddrStrHex);
    UnoSemuxAddr::SP                FindAddr            (GpRawPtrCharR aAddrStrHex);
    count_t                         AddHDGroup          (GpRawPtrCharR aMnemonic, GpRawPtrCharR aPassword);
    //void                          DeleteHDGroup       (const count_t aHDGroupId);

private:
    UnoSemuxAddrsGroup              iRndAddrGroup;
    UnoSemuxAddrsGroup::C::Vec::SP  iHDAddrGroups;
};

}//UnoSemux
