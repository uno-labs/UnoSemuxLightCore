TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 0
VER_MIN		    = 1
VER_PAT		    = 1
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=8a3d2013-210b-424d-a0a6-a5b2384b5d9c
QMAKE_CXXFLAGS += -DGP_TYPE_SYSTEM_STATIC_ADD_TO_MANAGER
DEFINES		   += UNOSEMUXLIGHTCORE_LIBRARY
PACKET_NAME     = UnoSemuxLightCore
DIR_LEVEL       = ./..

include(../../QtGlobalPro.pri)

#------------------------------ LIBS BEGIN ---------------------------------
os_windows{
	GP_CORE_LIB_V			= 2
	GP_CRYPTO_CORE_LIB_V	= 0
}

os_linux{
}

LIBS += -lGpCore2$$TARGET_POSTFIX$$GP_CORE_LIB_V
LIBS += -lGpCryptoCore$$TARGET_POSTFIX$$GP_CRYPTO_CORE_LIB_V
#------------------------------ LIBS END ---------------------------------

SOURCES += \
    Examples/UnoSemuxWalletExamples.cpp \
    UnoSemuxLightCore.cpp \
    Wallet/UnoSemuxAddr.cpp \
    Wallet/UnoSemuxAddrsGroup.cpp \
    Wallet/UnoSemuxNetworkType.cpp \
    Wallet/UnoSemuxTransaction.cpp \
    Wallet/UnoSemuxTransactionSign.cpp \
    Wallet/UnoSemuxTransactionType.cpp \
    Wallet/UnoSemuxWallet.cpp \
    Wallet/UnoSemuxWalletUtils.cpp

HEADERS += \
    Examples/UnoSemuxLightCoreExamples.hpp \
    Examples/UnoSemuxWalletExamples.hpp \
    UnoSemuxLightCore_global.hpp \
    UnoSemuxLightCore.hpp \
    Utils/UnoSemuxUnits.hpp \
    Utils/UnoSemuxUtils.hpp \
    Wallet/UnoSemuxAddr.hpp \
    Wallet/UnoSemuxAddrsGroup.hpp \
    Wallet/UnoSemuxNetworkType.hpp \
    Wallet/UnoSemuxTransaction.hpp \
    Wallet/UnoSemuxTransactionSign.hpp \
    Wallet/UnoSemuxTransactionType.hpp \
    Wallet/UnoSemuxWallet.hpp \
    Wallet/UnoSemuxWalletUtils.hpp
