#pragma once

#include "../UnoSemuxLightCore_global.hpp"

namespace UnoSemux {

class UnoSemuxUnitType_NANOSEM;
using nanosem_t = GpUnit<s_int_64, UnoSemuxUnitType_NANOSEM, std::ratio<intmax_t(1), intmax_t(1)>, decltype("usem"_template_str)>;
constexpr nanosem_t operator""_usem (unsigned long long int aValue) {return nanosem_t::SMake(aValue);}
constexpr nanosem_t operator""_sem  (unsigned long long int aValue) {return nanosem_t::SMake(aValue*1000000000);}


class UnoSemuxUnitType_GAS;
using semgas_t = GpUnit<s_int_64, UnoSemuxUnitType_GAS, std::ratio<intmax_t(1), intmax_t(1)>, decltype("semgas"_template_str)>;
constexpr semgas_t  operator""_semgas   (unsigned long long int aValue) {return semgas_t::SMake(aValue);}

}//namespace UnoSemux
