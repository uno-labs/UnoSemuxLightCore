#include "UnoSemuxAddrsGroup.hpp"
#include "UnoSemuxWalletUtils.hpp"

namespace UnoSemux {

UnoSemuxAddrsGroup::UnoSemuxAddrsGroup (GpCryptoKeyFactory::SP aFactory):
iFactory(std::move(aFactory))
{
}

UnoSemuxAddrsGroup::~UnoSemuxAddrsGroup (void) noexcept
{
}

UnoSemuxAddr::SP    UnoSemuxAddrsGroup::GenNext (void)
{
    UnoSemuxAddr::SP addr = UnoSemuxWalletUtils::SNewAddrFromFactory(iFactory.V());
    iAddrsList.emplace(addr.VCn().AddrStrHex(), addr);
    return addr;
}

void    UnoSemuxAddrsGroup::Delete (GpRawPtrCharR aAddrStrHex)
{
    std::string key(aAddrStrHex.AsStringView());
    if (iAddrsList.erase(key) == 0)
    {
        THROW_GPE("Addres '"_sv + aAddrStrHex.AsStringView() + "' not found"_sv);
    }
}

UnoSemuxAddr::SP    UnoSemuxAddrsGroup::Find (GpRawPtrCharR aAddrStrHex)
{
    std::string key(aAddrStrHex.AsStringView());
    auto iter = iAddrsList.find(key);

    if (iter == iAddrsList.end())
    {
        THROW_GPE("Addres '"_sv + aAddrStrHex.AsStringView() + "' not found"_sv);
    }

    return iter->second;
}

bool    UnoSemuxAddrsGroup::IsContainAddr (GpRawPtrCharR aAddrStrHex) const
{
    std::string key(aAddrStrHex.AsStringView());
    return iAddrsList.count(key) > 0;
}

}//namespace UnoSemux
