
#pragma once

#include <limits>

namespace phys {
namespace units {
namespace ct_math {

    namespace detail
    {
        template< typename T >
        constexpr T
        sqrtNewtonRaphson(
            T x,
            T curr,
            T prev
        )
        {
            return curr == prev
                ? curr
                : sqrtNewtonRaphson(
                    x,
                    T(0.5) * (curr + x / curr),
                    curr
                );
        }
    }

    /*
    * Constexpr version of the square root
    * Return value:
    *   - For a finite and non-negative value of "x", returns an approximation for the square root of "x"
    *   - Otherwise, returns NaN
    */
    template< typename T >
    constexpr T
    sqrt( T x )
    {
        return x >= T(0) && x < std::numeric_limits<T>::infinity()
            ? detail::sqrtNewtonRaphson(x, x, T(0))
            : std::numeric_limits<T>::quiet_NaN();
    }

}
}
}

