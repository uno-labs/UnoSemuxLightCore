#include "UnoSemuxAccount.hpp"

namespace UnoSemux {

UnoSemuxAccount::UnoSemuxAccount (void) noexcept
{
}

UnoSemuxAccount::UnoSemuxAccount (UnoSemuxAccount&& aAccount) noexcept:
iAddrsByHex(std::move(aAccount.iAddrsByHex)),
iNames(std::move(aAccount.iNames))
{
}

UnoSemuxAccount::~UnoSemuxAccount (void) noexcept
{
}

UnoSemuxAddr::SP	UnoSemuxAccount::AddrFindByName (std::string_view aAddrName)
{
	return _FindAddr(AddrHexStrByName(aAddrName))->second;
}

UnoSemuxAddr::CSP	UnoSemuxAccount::AddrFindByName (std::string_view aAddrName) const
{
	return _FindAddr(AddrHexStrByName(aAddrName))->second;
}

UnoSemuxAddr::SP	UnoSemuxAccount::AddrFindByHexStr (std::string_view aAddrHex)
{
	return _FindAddr(aAddrHex)->second;
}

UnoSemuxAddr::CSP	UnoSemuxAccount::AddrFindByHexStr (std::string_view aAddrHex) const
{
	return _FindAddr(aAddrHex)->second;
}

void	UnoSemuxAccount::AddrAdd (UnoSemuxAddr::SP aAddr)
{
	const UnoSemuxAddr& addr	= aAddr.VC();
	const std::string	addrHex = addr.AddrStrHex();

	THROW_GPE_COND_CHECK_M(iAddrsByHex.find(addrHex) == iAddrsByHex.end(), "Address '"_sv + addrHex + "' not unique"_sv);

	iAddrsByHex.emplace(addrHex, aAddr);
}

void	UnoSemuxAccount::AddrDeleteByName (std::string_view aAddrName)
{
	iAddrsByHex.erase(_FindAddr(AddrHexStrByName(aAddrName)));
}

void	UnoSemuxAccount::AddrDeleteByHexStr (std::string_view aAddrHex)
{
	iAddrsByHex.erase(_FindAddr(aAddrHex));
}

std::string_view	UnoSemuxAccount::AddrHexStrByName (std::string_view aAddrName) const
{
	const auto iter = iNames.find(std::string(aAddrName));

	THROW_GPE_COND_CHECK_M(iter != iNames.end(), "Address not found by name '"_sv + aAddrName + "'"_sv);

	return iter->second;
}

auto	UnoSemuxAccount::_FindAddr (std::string_view aKey) -> UnoSemuxAddr::C::MapStr::SP::iterator
{
	auto iter = iAddrsByHex.find(std::string(aKey));
	if (iter != iAddrsByHex.end())
	{
		return iter;
	} else
	{
		THROW_GPE("Addr not found by '"_sv + aKey + "'");
	}
}

auto	UnoSemuxAccount::_FindAddr (std::string_view aKey) const -> UnoSemuxAddr::C::MapStr::SP::const_iterator
{
	auto iter = iAddrsByHex.find(std::string(aKey));
	if (iter != iAddrsByHex.end())
	{
		return iter;
	} else
	{
		THROW_GPE("Addr not found by '"_sv + aKey + "'");
	}
}

}//namespace UnoSemux
