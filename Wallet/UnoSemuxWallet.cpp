#include "UnoSemuxWallet.hpp"

namespace UnoSemux {

UnoSemuxWallet::UnoSemuxWallet (void):
iRndAddrGroup(GpCryptoKeyFactory_Ed25519_Rnd::SP::SNew())
{
}

UnoSemuxWallet::~UnoSemuxWallet (void) noexcept
{
}

UnoSemuxAddr::SP    UnoSemuxWallet::GenNextRndAddr (void)
{
    return iRndAddrGroup.GenNext();
}

UnoSemuxAddr::SP    UnoSemuxWallet::GenNextHDAddr (const count_t aHDGroupId)
{
    return iHDAddrGroups.at(aHDGroupId.ValueAs<size_t>()).V().GenNext();
}

void    UnoSemuxWallet::DeleteAddr (GpRawPtrCharR aAddrStrHex)
{
    if (iRndAddrGroup.IsContainAddr(aAddrStrHex))
    {
        iRndAddrGroup.Delete(aAddrStrHex);
        return;
    }

    for (auto& iter: iHDAddrGroups)
    {
        if (iter.VC().IsContainAddr(aAddrStrHex))
        {
            iter.Vn().Delete(aAddrStrHex);
            return;
        }
    }

    THROW_GPE("Addres '"_sv + aAddrStrHex.AsStringView() + "' not found"_sv);
}

UnoSemuxAddr::SP    UnoSemuxWallet::FindAddr (GpRawPtrCharR aAddrStrHex)
{
    if (iRndAddrGroup.IsContainAddr(aAddrStrHex))
    {
        return iRndAddrGroup.Find(aAddrStrHex);
    }

    for (auto& iter: iHDAddrGroups)
    {
        if (iter.VC().IsContainAddr(aAddrStrHex))
        {
            return iter.Vn().Find(aAddrStrHex);
        }
    }

    THROW_GPE("Addres '"_sv + aAddrStrHex.AsStringView() + "' not found"_sv);
}

count_t UnoSemuxWallet::AddHDGroup (GpRawPtrCharR aMnemonic, GpRawPtrCharR aPassword)
{
    GpCryptoKeyFactory::SP hdKeyFactory = UnoSemuxWalletUtils::SNewHDKeyFactoryMnemonic(aMnemonic, aPassword);
    iHDAddrGroups.emplace_back(UnoSemuxAddrsGroup::SP::SNew(hdKeyFactory));

    return count_t::SMake(iHDAddrGroups.size()) - 1_cnt;
}

}//UnoSemux
