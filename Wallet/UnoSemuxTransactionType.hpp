#pragma once

#include "../UnoSemuxLightCore_global.hpp"

namespace UnoSemux {

GP_ENUM(UNOSEMUXLIGHTCORE_API, UnoSemuxTransactionType,
    COINBASE    = 0,
    TRANSFER    = 1,
    DELEGATE    = 2,
    VOTE        = 3,
    UNVOTE      = 4,
    CREATE      = 5,
    CALL        = 6
);

}//namespace UnoSemux
