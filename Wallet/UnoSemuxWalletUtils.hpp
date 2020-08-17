#pragma once

#include "UnoSemuxAddr.hpp"
#include "UnoSemuxWallet.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxWalletUtils
{
public:
    CLASS_REMOVE_CTRS(UnoSemuxWalletUtils)

    static constexpr s_int_8        UNO_SEMUX_WALLET_FORMAT_VERSION (void) noexcept {return 1;}

public:
    static GpSecureStorage          SNewMnemonic                    (void);
    static bool                     SValidateMnemonic               (GpRawPtrCharR aMnemonic);
    static GpSecureStorage          SSeedFromMnemonic               (GpRawPtrCharR aMnemonic,
                                                                     GpRawPtrCharR aPassword);
    static GpCryptoHDKeyStorage     SGenerateBip44                  (GpRawPtrByteR aSeed);
    static GpCryptoKeyFactory::SP   SNewHDKeyFactory                (const GpCryptoHDKeyStorage& aBip44RootHD);
    static GpCryptoKeyFactory::SP   SNewHDKeyFactoryMnemonic        (GpRawPtrCharR aMnemonic, GpRawPtrCharR aPassword);
    static GpCryptoKeyFactory::SP   SNewRndKeyFactory               (void);
    static UnoSemuxAddr::SP         SNewAddrFromFactory             (GpCryptoKeyFactory& aFactory);
    static UnoSemuxAddr::SP         SNewAddrFromPrivateKey          (GpRawPtrByteR aPrivateKey);
    static UnoSemuxAddr::SP         SNewAddrFromPrivateKeyStrHex    (GpRawPtrCharR aPrivateKeyStrHex);

    static UnoSemuxWallet::SP       SWalletDeserialize              (GpRawPtrCharR aPassword);
    static GpBytesArray             SWalletSerialize                (const UnoSemuxWallet&  aWallet,
                                                                     GpRawPtrCharR          aPassword);

private:
    static void                     SAddrGroupSerialize         (GpByteWriter&              aWriter,
                                                                     const UnoSemuxAddrsGroup&  aAddrGroup);

private:
    static const GpMnemonicCodeGen::WordListT   sWordListEN;
};

}//UnoSemux


