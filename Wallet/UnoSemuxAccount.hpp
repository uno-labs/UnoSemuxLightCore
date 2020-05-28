#pragma once

#include "UnoSemuxAddr.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxAccount
{
public:
	CLASS_REMOVE_CTRS_EXCEPT_DEFAULT_MOVE(UnoSemuxAccount);
	CLASS_DECLARE_DEFAULTS(UnoSemuxAccount);

	using NamesT = GpMap<std::string/*name*/, std::string/*hex*/>;

public:
								UnoSemuxAccount			(void) noexcept;
								UnoSemuxAccount			(UnoSemuxAccount&& aAccount) noexcept;
	virtual						~UnoSemuxAccount		(void) noexcept;

	UnoSemuxAddr::SP			AddrFindByName			(std::string_view aAddrName);
	UnoSemuxAddr::CSP			AddrFindByName			(std::string_view aAddrName) const;
	UnoSemuxAddr::SP			AddrFindByHexStr		(std::string_view aAddrHex);
	UnoSemuxAddr::CSP			AddrFindByHexStr		(std::string_view aAddrHex) const;
	void						AddrAdd					(UnoSemuxAddr::SP aAddr);
	void						AddrDeleteByName		(std::string_view aAddrName);
	void						AddrDeleteByHexStr		(std::string_view aAddrHex);

	std::string_view			AddrHexStrByName		(std::string_view aAddrName) const;

private:
	auto						_FindAddr				(std::string_view aKey) -> UnoSemuxAddr::C::MapStr::SP::iterator;
	auto						_FindAddr				(std::string_view aKey) const -> UnoSemuxAddr::C::MapStr::SP::const_iterator;

private:
	UnoSemuxAddr::C::MapStr::SP	iAddrsByHex;
	NamesT						iNames;
};

}//namespace UnoSemux
