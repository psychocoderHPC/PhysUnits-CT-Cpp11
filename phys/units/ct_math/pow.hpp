

#pragma once

#include <cstdint>

namespace phys {
namespace units {
namespace ct_math {

namespace detail
{
    /** power function - with extra const parameter for efficient code
      *
      * T_type requires cast from int and multiplication
      * @tparam T_Type - base type
      * @param x - base value
      * @param exp - exponent
      * @param results (=1) - do not change - workaround to produce efficient code
      * @return std::pow(x, exp)
      */
    template< typename T_Type >
    constexpr T_Type pow( T_Type const x , uint32_t const exp, const T_Type result = T_Type( 1 ) )
    {
        return exp == 0 ? result : (
            exp == 1 ? x * result : detail::pow( x, exp - 1, result * x )
        );
    }
} // namespace detail

/** power function
  *
  * T_type requires cast from int and multiplication
  * @tparam T_Type - base type
  * @param x - base value
  * @param exp - exponent
  * @return std::pow(x, exp)
  */
template< typename T_Type >
constexpr T_Type pow( T_Type const x , uint32_t const exp )
{
    return detail::pow( x, exp );
}

} // namespace ct_math
} // namespace units
} // namespace phys

