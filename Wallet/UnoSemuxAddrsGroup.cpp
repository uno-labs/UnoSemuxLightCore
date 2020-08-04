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
    std::string key(ExtractAddrHex(aAddrStrHex));
    if (iAddrsList.erase(key) == 0)
    {
        THROW_GPE("Addres '"_sv + aAddrStrHex.AsStringView() + "' not found"_sv);
    }
}

UnoSemuxAddr::SP    UnoSemuxAddrsGroup::Find (GpRawPtrCharR aAddrStrHex)
{
    std::string key(ExtractAddrHex(aAddrStrHex));
    auto iter = iAddrsList.find(key);

    if (iter == iAddrsList.end())
    {
        THROW_GPE("Addres '"_sv + aAddrStrHex.AsStringView() + "' not found"_sv);
    }

    return iter->second;
}

bool    UnoSemuxAddrsGroup::IsContainAddr (GpRawPtrCharR aAddrStrHex) const
{
    std::string key(ExtractAddrHex(aAddrStrHex));
    return iAddrsList.count(key) > 0;
}

std::string_view    UnoSemuxAddrsGroup::ExtractAddrHex (GpRawPtrCharR aAddrStrHex) const noexcept
{
    if (aAddrStrHex.IsEqualByArgLen("0x"_sv))
    {
        return aAddrStrHex.SubrangeBeginOffset(2_cnt).AsStringView();
    } else
    {
        return aAddrStrHex.AsStringView();
    }
}

}//namespace UnoSemux
