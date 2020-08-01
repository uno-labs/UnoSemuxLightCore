#pragma once

#include "UnoSemuxAddrsGroup.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxWallet
{
public:
    CLASS_REMOVE_CTRS_EXCEPT_DEFAULT(UnoSemuxWallet)
    CLASS_DECLARE_DEFAULTS(UnoSemuxWallet)

    using HDAddrGroupsT = UnoSemuxAddrsGroup::C::MapCountT::SP;

public:
                                UnoSemuxWallet      (void);
                                ~UnoSemuxWallet     (void) noexcept;

    UnoSemuxAddr::SP            GenNextRndAddr      (void);
    UnoSemuxAddr::SP            GenNextHDAddr       (const count_t aHDGroupId);
    UnoSemuxAddr::SP            GenHDAddr           (const count_t aHDGroupId, const count_t aAddrId);
    void                        DeleteAddr          (GpRawPtrCharR aAddrStrHex);
    UnoSemuxAddr::SP            FindAddr            (GpRawPtrCharR aAddrStrHex);
    count_t                     AddHDGroup          (GpRawPtrCharR aMnemonic, GpRawPtrCharR aPassword);
    void                        DeleteHDGroup       (const count_t aHDGroupId);

    const UnoSemuxAddrsGroup&   RndAddrGroup        (void) const noexcept {return iRndAddrGroup;}
    const HDAddrGroupsT&        HDAddrGroups        (void) const noexcept {return iHDAddrGroups;}
    count_t                     HDAddrGroupLastId   (void) const noexcept {return iHDAddrGroupLastId;}

    GpBytesArray                Seserialize         (GpRawPtrCharR aPassword) const;
    std::string                 SeserializeHex      (GpRawPtrCharR aPassword) const;
    //GpBytesArray              SeserializeBase64   (GpRawPtrCharR aPassword) const;

    void                        Deseserialize       (GpRawPtrByteR aData, GpRawPtrCharR aPassword);
    void                        DeseserializeHex    (GpRawPtrCharR aDataStrHex, GpRawPtrCharR aPassword);
    void                        DeseserializeBase64 (GpRawPtrCharR aDataBase64, GpRawPtrCharR aPassword);

private:
    UnoSemuxAddrsGroup          iRndAddrGroup;
    HDAddrGroupsT               iHDAddrGroups;
    count_t                     iHDAddrGroupLastId = 0_cnt;
};

}//UnoSemux
