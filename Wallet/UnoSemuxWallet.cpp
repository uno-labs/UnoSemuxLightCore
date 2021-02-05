#include "UnoSemuxWallet.hpp"
#include "UnoSemuxWalletUtils.hpp"

namespace UnoSemux {

UnoSemuxWallet::UnoSemuxWallet (void):
iRndAddrGroup(MakeSP<GpCryptoKeyFactory_Ed25519_Rnd>())
{
}

UnoSemuxWallet::~UnoSemuxWallet (void) noexcept
{
}

void	UnoSemuxWallet::Clear (void) noexcept
{
	?
	iRndAddrGroup.Clear();
	HDAddrGroupsT		iHDAddrGroups;
	count_t				iHDAddrGroupLastId = 0_cnt;
}

void	UnoSemuxWallet::Set (UnoSemuxWallet&& aWallet) noexcept
{
	Clear();
}

UnoSemuxAddr::SP	UnoSemuxWallet::GenRndAddr (void)
{
	return iRndAddrGroup.GenNext();
}

UnoSemuxAddr::SP	UnoSemuxWallet::GenNextHDAddr (const count_t aHDGroupId)
{
	return iHDAddrGroups.at(aHDGroupId)->GenNext();
}

UnoSemuxAddr::SP	UnoSemuxWallet::GenHDAddr (const count_t aHDGroupId, const count_t aAddrId)
{
	THROW_NOT_IMPLEMENTED();
}

void	UnoSemuxWallet::DeleteAddr (GpRawPtrCharR aAddrStrHex)
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

UnoSemuxAddr::SP	UnoSemuxWallet::FindAddr (GpRawPtrCharR aAddrStrHex)
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

count_t	UnoSemuxWallet::AddHDGroup (GpRawPtrCharR aMnemonic, GpRawPtrCharR aPassword)
{
	GpCryptoKeyFactory::SP hdKeyFactory = UnoSemuxWalletUtils::SNewHDKeyFactoryMnemonic(aMnemonic, aPassword);

	iHDAddrGroupLastId++;

	iHDAddrGroups.insert({iHDAddrGroupLastId, MakeSP<UnoSemuxAddrsGroup>(hdKeyFactory)});

	return iHDAddrGroupLastId;
}

void	UnoSemuxWallet::DeleteHDGroup (const count_t aHDGroupId)
{
	iHDAddrGroups.erase(aHDGroupId);
}

GpBytesArray	UnoSemuxWallet::Serialize (GpRawPtrCharR aPassword) const
{
	return UnoSemuxWalletUtils::SWalletSerialize(*this, aPassword);
}

std::string	UnoSemuxWallet::SerializeHex (GpRawPtrCharR aPassword) const
{
	GpBytesArray data = Serialize(aPassword);
	return StrOps::SFromBytes(data);
}

void	UnoSemuxWallet::Deserialize (GpRawPtrByteR aData, GpRawPtrCharR aPassword)
{
	UnoSemuxWallet::SP wallet = UnoSemuxWalletUtils::SWalletDeserialize(aData, aPassword);

}

void	UnoSemuxWallet::DeserializeHex (GpRawPtrCharR aDataStrHex, GpRawPtrCharR aPassword)
{
	GpBytesArray data = StrOps::SToBytes(aDataStrHex);
	return Deserialize(data, aPassword);
}

}//UnoSemux
