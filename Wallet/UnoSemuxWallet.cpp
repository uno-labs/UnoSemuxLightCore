#include "UnoSemuxWallet.hpp"
#include "UnoSemuxWalletUtils.hpp"

namespace UnoSemux {

UnoSemuxWallet::UnoSemuxWallet (void):
iRndAddrGroup(GpCryptoKeyFactory_Ed25519_Rnd::SP::SNew())
{
}

UnoSemuxWallet::~UnoSemuxWallet (void) noexcept
{
}

UnoSemuxAddr::SP    UnoSemuxWallet::GenRndAddr (void)
{
    return iRndAddrGroup.GenNext();
}

UnoSemuxAddr::SP    UnoSemuxWallet::GenNextHDAddr (const count_t aHDGroupId)
{
    return iHDAddrGroups.at(aHDGroupId).V().GenNext();
}

UnoSemuxAddr::SP    UnoSemuxWallet::GenHDAddr (const count_t aHDGroupId, const count_t aAddrId)
{
    THROW_NOT_IMPLEMENTED();
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
        auto& g = iter.second.V();
        if (g.IsContainAddr(aAddrStrHex))
        {
            g.Delete(aAddrStrHex);
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
        auto& g = iter.second.V();

        if (g.IsContainAddr(aAddrStrHex))
        {
            return g.Find(aAddrStrHex);
        }
    }

    THROW_GPE("Addres '"_sv + aAddrStrHex.AsStringView() + "' not found"_sv);
}

count_t UnoSemuxWallet::AddHDGroup (GpRawPtrCharR aMnemonic, GpRawPtrCharR aPassword)
{
    GpCryptoKeyFactory::SP hdKeyFactory = UnoSemuxWalletUtils::SNewHDKeyFactoryMnemonic(aMnemonic, aPassword);

    iHDAddrGroupLastId++;

    iHDAddrGroups.insert({iHDAddrGroupLastId, UnoSemuxAddrsGroup::SP::SNew(hdKeyFactory)});

    return iHDAddrGroupLastId;
}

void    UnoSemuxWallet::DeleteHDGroup (const count_t aHDGroupId)
{
    iHDAddrGroups.erase(aHDGroupId);
}

GpBytesArray    UnoSemuxWallet::Serialize (GpRawPtrCharR aPassword) const
{
    return UnoSemuxWalletUtils::SWalletSerialize(*this, aPassword);
}

std::string UnoSemuxWallet::SerializeHex (GpRawPtrCharR aPassword) const
{
    GpBytesArray data = Serialize(aPassword);
    return GpStringOps::SFromBytes(data);
}

/*GpBytesArray  UnoSemuxWallet::SerializeBase64 (GpRawPtrCharR aPassword) const
{
    GpBytesArray data = Serialize(aPassword);
    return GpEncoders::SBinToBase64(data);
}*/

void    UnoSemuxWallet::Deserialize (GpRawPtrByteR aData, GpRawPtrCharR aPassword)
{

}

void    UnoSemuxWallet::DeserializeHex (GpRawPtrCharR aDataStrHex, GpRawPtrCharR aPassword)
{
    GpBytesArray data = GpStringOps::SToBytes(aDataStrHex);
    return Deserialize(data, aPassword);
}

/*void  UnoSemuxWallet::DeserializeBase64   (GpRawPtrCharR aDataBase64, GpRawPtrCharR aPassword)
{
    GpBytesArray data = GpEncoders::SBase64ToBin(data);
    return Deserialize(data, aPassword);
}*/

}//UnoSemux
