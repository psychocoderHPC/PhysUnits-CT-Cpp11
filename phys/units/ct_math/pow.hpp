

#pragma once

namespace phys {
namespace units {
namespace ct_math {

namespace detail
{
    /** recursive helper power function
      *
      * @tparam T_Type - base type
      * @param x - base value
      * @param exp - exponent
      * @param results (=1) - do not change
      * @return result of x^exp
      */
    template< typename T_Type >
    constexpr T_Type pow( T_Type const x , int const exp, const T_Type result = T_Type( 1 ) )
    {
        return exp == 0 ? result : (
            exp == 1 ? x * result : detail::pow( x, exp - 1, result * x )
        );
    }
} // namespace detail

/** power function
  *
  * @tparam T_Type - base type
  * @param x - base value
  * @param exp - exponent
  * @return result of x^exp
  */
template< typename T_Type >
constexpr T_Type pow( T_Type const x , int const exp )
{
    return detail::pow( x, exp );
}

} // namespace ct_math
} // namespace units
} // namespace phys
