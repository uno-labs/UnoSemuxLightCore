#include "UnoSemuxWalletExamples.hpp"
#include <iostream>

void	UnoSemuxWalletExamples::SExample1 (void)
{
	//Global SemuxLightCore initialization (once after app start)
	UnoSemuxLightCore::SInit();

	//Generate new mnemonic phrase using random generator
	GpSecureStorage		mnemonic	= UnoSemuxWalletUtils::SNewMnemonic();

	std::cout << "New mnemonic phrase: '" << mnemonic.ViewR().R().AsStringView() << "'\n";

	//Create empty wallet
	UnoSemuxWallet wallet;

	//Import HD group(factory) from mnemonic phrase
	const count_t hdGroupId_1 = wallet.AddHDGroup(mnemonic.ViewR().R(), "123456"_sv/*password can be empty, but this less secure*/);

	//We can store into the wallet more than one HD group
	const count_t hdGroupId_2 = wallet.AddHDGroup("scout innocent rent portion still tumble curve ketchup term cousin stuff ostrich"_sv, ""_sv);

	//Generate new address from HD group 1
	{
		//Each call GenNextHDAddr will generate next address from HD sequence
		UnoSemuxAddr::SP hd_1_Addr_1 = wallet.GenNextHDAddr(hdGroupId_1);
		std::cout << "New HD_1 address_1 '0x" << hd_1_Addr_1->AddrStrHex() << "'" << std::endl;

		UnoSemuxAddr::SP hd_1_Addr_2 = wallet.GenNextHDAddr(hdGroupId_1);
		std::cout << "New HD_1 address_2 '0x" << hd_1_Addr_2->AddrStrHex() << "'" << std::endl;
	}

	//Generate new address from HD group 2
	UnoSemuxAddr::SP hd_2_Addr_1;//this address will be used for transaction example (0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56)
	{
		hd_2_Addr_1 = wallet.GenNextHDAddr(hdGroupId_2);
		std::cout << "New HD_2 address_1 '0x" << hd_2_Addr_1->AddrStrHex() << "'" << std::endl;
	}

	//Generate new address from random generator (need no mnemonic phrase)
	{
		UnoSemuxAddr::SP rnd_Addr_1 = wallet.GenRndAddr();
		std::cout << "New RND address_1 '0x" << rnd_Addr_1->AddrStrHex() << "'" << std::endl;
	}

	//Generate transfer transaction from hd_2_Addr_1 (0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56) to 0x2162745af703d5893877d6e899fe864411c2cbc1
	{
		//You need to know current nonce value for address. Is can be get only from full node server
		//For testnet next URL can be used "http://api.testnet.semux.top/v2.4.0/
		//Get nonce: curl -X GET "http://api.testnet.semux.top/v2.4.0/account?address=0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56" -H "accept: application/json"
		const s_int_64		nonce	= 0;//Set this value see "nonce" value from API json response
		//const unix_ts_ms_t	ts		= GpDateTimeOps::SUnixTS_ms();
		const unix_ts_ms_t	ts		= 1598794001994_unix_ts_ms;

		//You can see address information in blockchain explorers (for testnet):
		//https://testnet.semux.top/address/0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56 (if NotFoundError then this is new address with no transactions)
		//Or https://testnet.semux.info/explorer/account/0x1007c5b26903235f2bf6b1bec2bb4eccaf28fc56

		//Fill transaction values
		/*UnoSemuxTransaction tx = UnoSemuxTransaction::STransfer(UnoSemuxNetworkType::TESTNET,
																"0x2162745af703d5893877d6e899fe864411c2cbc1"_sv,//To address
																10000000_usem,									//Amount value of nano sem to send
																5000000_usem,									//Comission 5000000_usem
																nonce,											//Nonce
																ts,												//Current unix timestamp (ms)
																GpRawPtrByteR());	*/							//Data (bytes) optional


		UnoSemuxTransaction tx(UnoSemuxNetworkType::DEVNET,
							   UnoSemuxTransactionType::TRANSFER,
							   StrOps::SToBytes("0x37884a1a94d60a7924f730c86d751c4fa7086044"_sv),//To address
							   1000000000_usem,									//Amount value of nano sem to send
							   5000000_usem,									//Comission 5000000_usem
							   nonce,											//Nonce
							   ts,												//Current unix timestamp (ms)
							   GpBytesArray(),
							   0_semgas,
							   0_usem);

		//Sign transaction with address
		UnoSemuxTransactionSign txSign1		= hd_2_Addr_1->Sign1(tx);
		UnoSemuxTransactionSign txSign2		= hd_2_Addr_1->Sign2(tx);

		//Encode transaction sign
		GpBytesArray			txSignBytes1	= txSign1.Encode();
		GpBytesArray			txSignBytes2	= txSign2.Encode();

		//Convert transaction sign to hex str
		std::string				txSignHexStr1= StrOps::SFromBytes(txSignBytes1);
		std::string				txSignHexStr2= StrOps::SFromBytes(txSignBytes2);

		std::cout << "Transaction:\n";
		std::cout << "    From:                0x" << hd_2_Addr_1->AddrStrHex() << "\n";
		std::cout << "    To:                  0x" << tx.AddrToStrHex() << "\n";
		std::cout << "    Value(nano sem):     " << tx.Value().Value() << "\n";
		std::cout << "    Fee(nano sem):       " << tx.Fee().Value() << "\n";
		std::cout << "    Gas(gas):            " << tx.Gas().Value() << "\n";
		std::cout << "    Gas price(nano sem): " << tx.GasPrice().Value() << "\n";
		std::cout << "    Network:             " << tx.NetworkType().ToString() << "\n";
		std::cout << "    Type:                " << tx.Type().ToString() << "\n";
		std::cout << "    Unix TS(ms):         " << tx.Timestamp().Value() << "\n";
		std::cout << "    Data(hex):           " << tx.DataStrHex() << "\n";
		std::cout << "    TX hex 1:            " << txSign1.HashHex() << std::endl;
		std::cout << "    TX hex 2:            " << txSign2.HashHex() << std::endl;
		std::cout << "    Sign hex 1:          " << txSignHexStr1 << std::endl;
		std::cout << "    Sign hex 2:          " << txSignHexStr2 << std::endl;
		/*
		"result": {
			"hash": "0x376fa2cab1639913b801d35eaccfc284944cd38640e5fff22660c9f806894403",
			"type": "TRANSFER",
			"from": "0xfb75c8abcaa54025d6e8dffcd014258f51ad1cca",
			"to": "0x37884a1a94d60a7924f730c86d751c4fa7086044",
			"value": "1000000000",
			"fee": "5000000",
			"nonce": "0",
			"timestamp": "1598794001994",
			"data": "0x",
			"gas": "0",
			"gasPrice": "0"
		  }
		*/
		//Now you can send transaction to the network using full node server
		//curl -X GET "http://api.testnet.semux.top/v2.4.0/broadcast-raw-transaction?raw=...set_this_to_sign_hex_value..." -H "accept: application/json"
	}

	std::string walletDataHex = wallet.SerializeHex("123456"_sv);

	std::cout << "walletDataHex = " << walletDataHex << std::endl;
	wallet.DeserializeHex(walletDataHex, "123456"_sv);


	//Global SemuxLightCore clear (once before app stop)
	UnoSemuxLightCore::SClear();
}
