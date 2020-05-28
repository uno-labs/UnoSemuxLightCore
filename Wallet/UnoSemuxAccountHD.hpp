#pragma once

#include "UnoSemuxAccount.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxAccountHD final: public UnoSemuxAccount
{
public:
	CLASS_REMOVE_CTRS_EXCEPT_MOVE(UnoSemuxAccountHD);
	CLASS_DECLARE_DEFAULTS(UnoSemuxAccountHD);

	using NetworkTypeT	= GpCryptoHDNetworkType;
	using NetworkTypeTE	= NetworkTypeT::EnumT;

public:
									UnoSemuxAccountHD	(UnoSemuxAccountHD&& aAccountHD) noexcept;
									UnoSemuxAccountHD	(GpCryptoHDKeyPair&& aBip44_changeKey);

	virtual							~UnoSemuxAccountHD	(void) noexcept override final;

	UnoSemuxAccountHD&				operator=			(UnoSemuxAccountHD&& aAccountHD) noexcept;

	UnoSemuxAddr::SP				AddrAddNextHD		(void);

	static UnoSemuxAccountHD::SP	SImportFromMnemonic	(const GpSecureStorage&	aMnemonic,
														 const NetworkTypeTE	aNetworkType);
	static UnoSemuxAccountHD::SP	SImportFromMnemonic	(const GpSecureStorage& aMnemonic,
														const GpSecureStorage& aPassword,
														 const NetworkTypeTE	aNetworkType);
	static UnoSemuxAccountHD::SP	SImportFromMnemonic	(std::string_view		aMnemonic,
														 const NetworkTypeTE	aNetworkType);
	static UnoSemuxAccountHD::SP	SImportFromMnemonic	(std::string_view		aMnemonic,
														 std::string_view		aPassword,
														 const NetworkTypeTE	aNetworkType);
	static GpSecureStorage			SNewMnemonic		(void);

private:
	GpCryptoHDKeyPair				iBip44_changeKey;
	count_t							iCountAddrsHD	= 0_cnt;

	static const GpMnemonicCodeGen::WordListT sWordListEN;
};

}//namespace UnoSemux
