CONFIG		-= qt
QT			-= core gui widgets
TEMPLATE	= lib
VER_MAJ		= 0
VER_MIN		= 1
VER_PAT		= 0
CONFIG		+= warn_on
DEFINES		+= UNOSEMUXLIGHTCORE_LIBRARY \
			HAVE_NETINET_IN_H \
			_GLIBCXX_USE_NANOSLEEP

PACKET_NAME     = UnoSemuxLightCore
OUT_BUILD_PATH  = ./../../../Bin_tmp/

compiler_gcc{
	os_linux{
		QMAKE_CC	= gcc-9
		QMAKE_CXX	= g++-9
	}
}else:compiler_clang{
	QMAKE_CXXFLAGS	+= -stdlib=libc++
	QMAKE_LFLAGS    += -stdlib=libc++

	#QMAKE_CXXFLAGS	+= -stdlib=libstdc++
	#QMAKE_LFLAGS   += -stdlib=libstdc++
}else:compiler_emscripten{
}else{
	error(Unknown compiler mode. Set CONFIG+=compiler_gcc OR CONFIG+=compiler_clang OR CONFIG+=compiler_emscripten)
}

#c++2a
CONFIG					+=	c++2a
QMAKE_CXXFLAGS_GNUCXX11 =	-std=gnu++2a
QMAKE_CXXFLAGS_GNUCXX14 =	-std=gnu++2a
QMAKE_CXXFLAGS_GNUCXX1Z =	-std=gnu++2a
QMAKE_CXXFLAGS			+=	-std=gnu++2a

compiler_gcc{
	QMAKE_CXXFLAGS	+= -fstrict-aliasing -Wall -Wextra -Wno-comment -Wdouble-promotion -Wswitch-default -Wswitch-enum -Wuninitialized -Wstrict-aliasing -Wfloat-equal -Wshadow -Wplacement-new -Wcast-align -Wconversion -Wlogical-op
	QMAKE_CXXFLAGS	+= -Wduplicated-cond -Wduplicated-branches -Wrestrict -Wnull-dereference -Wno-terminate
	#QMAKE_CXXFLAGS	+= -fconcepts -fgnu-tm
	QMAKE_CXXFLAGS  += -fstack-clash-protection
}else:compiler_clang{
}else:compiler_emscripten{
	QMAKE_CXXFLAGS  += -fexceptions
}

QMAKE_CXXFLAGS	+= -fvisibility=hidden -fvisibility-inlines-hidden
QMAKE_CXXFLAGS	+= -ffunction-sections -fdata-sections
#QMAKE_CXXFLAGS	+= -fno-rtti
QMAKE_LFLAGS    += -Wl,--gc-sections

QMAKE_CFLAGS	+= -fstrict-aliasing -Wall -Wextra -Wno-comment -Wdouble-promotion -Wswitch-default -Wswitch-enum -Wuninitialized -Wstrict-aliasing -Wfloat-equal -Wshadow -Wplacement-new -Wcast-align -Wconversion -Wlogical-op
QMAKE_CFLAGS	+= -fvisibility=hidden -fvisibility-inlines-hidden

#------------------------ DEBUG or RELEASE ---------------------
debug_build {
	message([$$PACKET_NAME]: ***************** Build mode DEBUG *****************)
	DEFINES			   += DEBUG_BUILD
	TARGET_POSTFIX		= _d
	OUT_BUILD_MODE_PATH	= Debug
	os_linux {
		QMAKE_CXXFLAGS	+= -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr
		LIBS += -lasan
		LIBS += -lubsan
		BOOST_POSTFIX = _asan
	}
} else:release_build {
	message([$$PACKET_NAME]: ***************** Build mode RELEASE *****************)
	DEFINES			    += RELEASE_BUILD
	TARGET_POSTFIX		=
	OUT_BUILD_MODE_PATH	= Release
} else {
	error(Unknown build mode. Set CONFIG+=debug_build OR CONFIG+=release_build)
}

#------------------------ OS ---------------------
os_linux {
	OUT_BUILD_OS_PATH = Linux
} else:os_android {
	OUT_BUILD_OS_PATH = Android
} else:os_ios {
	OUT_BUILD_OS_PATH = Ios
} else:os_windows {
	OUT_BUILD_OS_PATH = Win
} else:os_macx {
	OUT_BUILD_OS_PATH = Macx
} else:os_browser {
	OUT_BUILD_OS_PATH = Browser
} else {
	error(Unknown OS. Set CONFIG+=... one of values: os_linux, os_android, os_ios, os_windows, os_macx, os_browser)
}

#------------------------ ARC ---------------------
arc_x86_64 {
	OUT_BUILD_ARCH_PATH = x86_64
	QMAKE_CXXFLAGS	+= -mtune=generic -march=x86-64
} else:arc_x86 {
	OUT_BUILD_ARCH_PATH = x86
	QMAKE_CXXFLAGS	+= -mtune=generic -march=i686
} else:arc_arm_v6 {
	OUT_BUILD_ARCH_PATH = arm_v6
} else:arc_armeabi_v7a {
	OUT_BUILD_ARCH_PATH = armeabi_v7a
} else:arc_arm64_v8a {
	OUT_BUILD_ARCH_PATH = arm64_v8a
} else:arc_mips {
	OUT_BUILD_ARCH_PATH = mips
} else:arc_wasm32 {
	OUT_BUILD_ARCH_PATH = wasm32
} else:arc_wasm64 {
	OUT_BUILD_ARCH_PATH = wasm64
} else {
	error(Unknown ARC. Set CONFIG+=... one of values: arc_x86_64, arc_x86, arc_arm_v6, arc_armeabi_v7a, arc_arm64_v8a, arc_mips, arc_wasm32, arc_wasm64)
}

TARGET = $$PACKET_NAME$$TARGET_POSTFIX

SP = _
DESTDIR = $$OUT_BUILD_PATH$$OUT_BUILD_MODE_PATH$$SP$$OUT_BUILD_OS_PATH$$SP$$OUT_BUILD_ARCH_PATH/

message([$$PACKET_NAME]: Target name: $$TARGET)
message([$$PACKET_NAME]: Target arch: $$OUT_BUILD_ARCH_PATH)
message([$$PACKET_NAME]: Target OS:   $$OUT_BUILD_OS_PATH)
message([$$PACKET_NAME]: Build directory $$DESTDIR)
message([$$PACKET_NAME]: -------------------------------------------------)

#------------------------------ LIBS BEGIN ---------------------------------
LIBS += -L$$DESTDIR \
		-L$$DESTDIR/Plugins

os_linux
{
	LIBS += -L/usr/lib/gcc/x86_64-linux-gnu/9
}

os_windows{
	GP_CORE_LIB_V			= 2
	GP_CRYPTO_CORE_LIB_V	= 0
}

#LIBS += -lpthread
#LIBS += -lboost_context
LIBS += -lGpCore$$TARGET_POSTFIX$$GP_CORE_LIB_V
LIBS += -lGpCryptoCore$$TARGET_POSTFIX$$GP_CRYPTO_CORE_LIB_V
LIBS += -lutf8proc$$TARGET_POSTFIX

#------------------------------ LIBS END ---------------------------------

INCLUDEPATH += \
	../../Extras \
	../../Extras/Boost/boost_1_72_0$$BOOST_POSTFIX

SOURCES += \
    UnoSemuxLightCore.cpp \
    Wallet/UnoSemuxAccount.cpp \
    Wallet/UnoSemuxAccountHD.cpp \
    Wallet/UnoSemuxAddr.cpp \
    Wallet/UnoSemuxNetworkType.cpp \
    Wallet/UnoSemuxTransaction.cpp \
    Wallet/UnoSemuxTransactionSign.cpp \
    Wallet/UnoSemuxTransactionType.cpp

HEADERS += \
    UnoSemuxLightCore_global.hpp \
    UnoSemuxLightCore.hpp \
    Utils/UnoSemuxUnits.hpp \
    Utils/UnoSemuxUtils.hpp \
    Wallet/UnoSemuxAccount.hpp \
    Wallet/UnoSemuxAccountHD.hpp \
    Wallet/UnoSemuxAddr.hpp \
    Wallet/UnoSemuxNetworkType.hpp \
    Wallet/UnoSemuxTransaction.hpp \
    Wallet/UnoSemuxTransactionSign.hpp \
    Wallet/UnoSemuxTransactionType.hpp
