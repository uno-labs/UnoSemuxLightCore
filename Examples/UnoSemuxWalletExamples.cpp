#include "UnoSemuxWalletExamples.hpp"
#include <iostream>

void    UnoSemuxWalletExamples::SExample1 (void)
{
    //Global SemuxLightCore initialization (once after app start)
    UnoSemuxLightCore::SInit();

    //Generate new mnemonic phrase using random generator
    GpSecureStorage     mnemonic    = UnoSemuxWalletUtils::SNewMnemonic();
    std::string         mnemonicStr = std::string(mnemonic.ViewR().R().AsStringView());

    std::cout << "New mnemonic phrase: '" << mnemonicStr << "'\n";

    //Create empty wallet
    UnoSemuxWallet wallet;

    //Import HD group(factory) from mnemonic phrase
    const count_t hdGroupId_1 = wallet.AddHDGroup(mnemonic.ViewR().R(), "123456"_sv/*password can be empty, but this less secure*/);

    //We can store into the wallet more than one HD group
    const count_t hdGroupId_2 = wallet.AddHDGroup("exclude ship then surface reform human easily hip acquire circle wrestle still"_sv, ""_sv);

    //Generate new address from HD group 1
    {
        //Each call GenNextHDAddr will generate next address from HD sequence
        UnoSemuxAddr::SP hd_1_Addr_1 = wallet.GenNextHDAddr(hdGroupId_1);
        std::cout << "New HD_1 address_1 '0x" << hd_1_Addr_1.VC().AddrStrHex() << "'" << std::endl;

        UnoSemuxAddr::SP hd_1_Addr_2 = wallet.GenNextHDAddr(hdGroupId_1);
        std::cout << "New HD_1 address_2 '0x" << hd_1_Addr_2.VC().AddrStrHex() << "'" << std::endl;
    }

    //Generate new address from HD group 2
    UnoSemuxAddr::SP hd_2_Addr_1;//this address will be used for transaction example (0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56)
    {
        hd_2_Addr_1 = wallet.GenNextHDAddr(hdGroupId_2);
        std::cout << "New HD_2 address_1 '0x" << hd_2_Addr_1.VC().AddrStrHex() << "'" << std::endl;
    }

    //Generate new address from random generator (need no mnemonic phrase)
    {
        UnoSemuxAddr::SP rnd_Addr_1 = wallet.GenNextRndAddr();
        std::cout << "New RND address_1 '0x" << rnd_Addr_1.VC().AddrStrHex() << "'" << std::endl;
    }

    //Generate transfer transaction from hd_2_Addr_1 (0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56) to 0x2162745af703d5893877d6e899fe864411c2cbc1
    {
        //You need to know current nonce value for address. Is can be get only from full node server
        //For testnet next URL can be used "http://api.testnet.semux.top/v2.4.0/
        //Get nonce: curl -X GET "http://api.testnet.semux.top/v2.4.0/account?address=0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56" -H "accept: application/json"
        const s_int_64      nonce   = 0;//Set this value see "nonce" value from API json responce
        const unix_ts_ms_t  ts      = GpDateTimeOps::SUnixTS_ms();

        //You can see address information in blockchain explorers (for testnet):
        //https://testnet.semux.top/address/0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56 (if NotFoundError then this is new address with no transactions)
        //Or https://testnet.semux.info/explorer/account/0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56

        //Fill transaction values
        UnoSemuxTransaction tx = UnoSemuxTransaction::STransfer(UnoSemuxNetworkType::TESTNET,
                                                                "0x2162745af703d5893877d6e899fe864411c2cbc1"_sv,//To address
                                                                10000000_usem,                                  //Amount value of nano sem to send
                                                                5000000_usem,                                   //Comission 5000000_usem
                                                                nonce,                                          //Nonce
                                                                ts,                                             //Current unix timestamp (ms)
                                                                GpRawPtrByteR());                               //Data (bytes) optional

        //Sign transaction with address
        UnoSemuxTransactionSign txSign      = hd_2_Addr_1.V().Sign1(tx);

        //Encode transaction sign
        GpBytesArray            txSignBytes = txSign.Encode();

        //Convert transaction sign to hex str
        std::string             txSignHexStr= GpStringOps::SFromBytes(txSignBytes);

        std::cout << "Transaction:\n";
        std::cout << "    From:                0x" << hd_2_Addr_1.VC().AddrStrHex() << "\n";
        std::cout << "    To:                  0x" << tx.AddrToStrHex() << "\n";
        std::cout << "    Value(nano sem):     " << tx.Value().ValueAs<size_t>() << "\n";
        std::cout << "    Fee(nano sem):       " << tx.Fee().ValueAs<size_t>() << "\n";
        std::cout << "    Gas(gas):            " << tx.Gas().ValueAs<size_t>() << "\n";
        std::cout << "    Gas price(nano sem): " << tx.GasPrice().ValueAs<size_t>() << "\n";
        std::cout << "    Network:             " << tx.NetworkType().ToString() << "\n";
        std::cout << "    Type:                " << tx.Type().ToString() << "\n";
        std::cout << "    Unix TS(ms):         " << tx.Timestamp().ValueAs<size_t>() << "\n";
        std::cout << "    Data(hex):           " << tx.DataStrHex() << "\n";
        std::cout << "    Sign hex:            " << txSignHexStr << std::endl;

        //Now you can send transaction to the network using full node server
        //curl -X GET "http://api.testnet.semux.top/v2.4.0/broadcast-raw-transaction?raw=...set_this_to_sign_hex_value..." -H "accept: application/json"
    }

    //Global SemuxLightCore clear (once before app stop)
    UnoSemuxLightCore::SClear();
}
