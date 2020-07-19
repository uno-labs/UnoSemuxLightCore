#pragma once

#include "Utils/UnoSemuxUtils.hpp"
#include "Wallet/UnoSemuxWallet.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxLightCore
{
    CLASS_REMOVE_CTRS(UnoSemuxLightCore)

public:
    static void         SInit                   (void);
    static void         SClear                  (void);
};

}//UnoSemux
