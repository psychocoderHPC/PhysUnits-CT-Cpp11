/**
 * \file quantity.hpp
 *
 * \brief   Zero-overhead dimensional analysis and unit/quantity manipulation and conversion.
 * \author  Michael S. Kenniston, Martin Moene
 * \date    7 September 2013
 * \since   0.4
 *
 * Copyright 2013 Universiteit Leiden. All rights reserved.
 *
 * Copyright (c) 2001 by Michael S. Kenniston.  For the most
 * recent version check www.xnet.com/~msk/quantity.  Permission is granted
 * to use this code without restriction so long as this copyright
 * notice appears in all source files.
 *
 * This code is provided as-is, with no warrantee of correctness.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * Unless otherwise specified, the definitions of all units in this
 * file are from NIST Special Publication 811, found online at
 * http://physics.nist.gov/Document/sp811.pdf
 * Other sources: OED = Oxford English Dictionary
 */

#ifndef PHYS_UNITS_QUANTITY_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_HPP_INCLUDED

#include <cmath>
#include <cstdlib>
#include <utility>  // std::declval
#include <array>
#include <tuple>
#include <type_traits>

/// namespace phys.

namespace phys {

/// namespace units.

namespace units {

#ifdef PHYS_UNITS_REP_TYPE
   using Rep = PHYS_UNITS_REP_TYPE;
#else
   using Rep = double;
   using DimType = int;
#endif

/*
 * declare now, define later.
 */
template< typename Dims, typename T = Rep >
class quantity;


struct const_string {
    char const* str;
    std::size_t size;

    template <std::size_t N>
    constexpr const_string(char const (&s)[N])
        : str(s)
        , size(N - 1)
    {}

    std::string name( ) const
    {
        return str;
    }

};


/**
 * We could drag dimensions around individually, but it's much more convenient to package them.
 */
template< typename T_ExpType >
struct dimension
{

    using exp_type = T_ExpType;

    const const_string m_symbol;
    const exp_type m_exp;



    constexpr dimension(
        const const_string symbol,
        const exp_type dim
    ) :
        m_symbol( symbol ),
        m_exp( dim )
    {

    }

    constexpr dimension zero() const
    {
        return dimension( m_symbol, 0 );
    }

    constexpr dimension inverse() const
    {
        return dimension( m_symbol, -1 * m_exp );
    }

    constexpr operator exp_type() const
    {
        return m_exp;
    }

    constexpr dimension
    operator+( const dimension rhs ) const
    {
        return { m_symbol, m_exp + rhs.m_exp };
    }

    constexpr dimension
    operator-( const dimension rhs ) const
    {
        return { m_symbol, m_exp - rhs.m_exp };
    }

    constexpr dimension
    operator*( const dimension rhs ) const
    {
        return { m_symbol, m_exp * rhs.m_exp };
    }

    constexpr dimension
    operator*( const exp_type rhs ) const
    {
        return { m_symbol, m_exp * rhs };
    }

    constexpr dimension
    operator/( const dimension rhs ) const
    {
        return { m_symbol, m_exp / rhs.m_exp };
    }
};

template<
    typename T_Tuple
>
struct dimensions : public T_Tuple
{
    using dim_type = typename std::tuple_element<
        0,
        T_Tuple
    >::type;
    using exp_type = typename dim_type::exp_type;

    constexpr dimensions(
        const T_Tuple dims
    ) :
        T_Tuple{ dims }
    {

    }

    constexpr bool
    is_all_zero() const
    {
        return std::get< 0 >( *this ) == dim_type( 0 )  &&
            std::get< 1 >( *this ) == dim_type( 0 ) &&
            std::get< 2 >( *this ) == dim_type( 0 ) &&
            std::get< 3 >( *this ) == dim_type( 0 ) &&
            std::get< 4 >( *this ) == dim_type( 0 ) &&
            std::get< 5 >( *this ) == dim_type( 0 ) &&
            std::get< 6 >( *this ) == dim_type( 0 );
    }

    constexpr bool
    is_base() const
    {
        return ( dim_type( 1 ) ==
            (
                std::get< 0 >( *this ) != dim_type( 0 ) +
                std::get< 1 >( *this ) != dim_type( 0 ) +
                std::get< 2 >( *this ) != dim_type( 0 ) +
                std::get< 3 >( *this ) != dim_type( 0 ) +
                std::get< 4 >( *this ) != dim_type( 0 ) +
                std::get< 5 >( *this ) != dim_type( 0 ) +
                std::get< 6 >( *this ) != dim_type( 0 )
            )
        )
        &&
        ( dim_type( 1 ) ==
            (
                std::get< 0 >( *this ) +
                std::get< 1 >( *this ) +
                std::get< 2 >( *this ) +
                std::get< 3 >( *this ) +
                std::get< 4 >( *this ) +
                std::get< 5 >( *this ) +
                std::get< 6 >( *this )
            )
        );
    }

    constexpr bool operator==( const dimensions rhs ) const
    {
        return std::get< 0 >( *this ) == std::get< 0 >( rhs )  &&
            std::get< 1 >( *this ) == std::get< 1 >( rhs ) &&
            std::get< 2 >( *this ) == std::get< 2 >( rhs ) &&
            std::get< 3 >( *this ) == std::get< 3 >( rhs ) &&
            std::get< 4 >( *this ) == std::get< 4 >( rhs ) &&
            std::get< 5 >( *this ) == std::get< 5 >( rhs ) &&
            std::get< 6 >( *this ) == std::get< 6 >( rhs );
    }

    constexpr dimensions operator+( const dimensions rhs ) const
    {
        return T_Tuple{
            std::get< 0 >( *this ) + std::get< 0 >( rhs ),
            std::get< 1 >( *this ) + std::get< 1 >( rhs ),
            std::get< 2 >( *this ) + std::get< 2 >( rhs ),
            std::get< 3 >( *this ) + std::get< 3 >( rhs ),
            std::get< 4 >( *this ) + std::get< 4 >( rhs ),
            std::get< 5 >( *this ) + std::get< 5 >( rhs ),
            std::get< 6 >( *this ) + std::get< 6 >( rhs )
        };
    }

    constexpr dimensions operator-( const dimensions rhs ) const
    {
        return T_Tuple{
            std::get< 0 >( *this ) - std::get< 0 >( rhs ),
            std::get< 1 >( *this ) - std::get< 1 >( rhs ),
            std::get< 2 >( *this ) - std::get< 2 >( rhs ),
            std::get< 3 >( *this ) - std::get< 3 >( rhs ),
            std::get< 4 >( *this ) - std::get< 4 >( rhs ),
            std::get< 5 >( *this ) - std::get< 5 >( rhs ),
            std::get< 6 >( *this ) - std::get< 6 >( rhs )
        };
    }

    constexpr dimensions operator*( const dimensions rhs ) const
    {
        return T_Tuple{
            std::get< 0 >( *this ) * std::get< 0 >( rhs ),
            std::get< 1 >( *this ) * std::get< 1 >( rhs ),
            std::get< 2 >( *this ) * std::get< 2 >( rhs ),
            std::get< 3 >( *this ) * std::get< 3 >( rhs ),
            std::get< 4 >( *this ) * std::get< 4 >( rhs ),
            std::get< 5 >( *this ) * std::get< 5 >( rhs ),
            std::get< 6 >( *this ) * std::get< 6 >( rhs )
        };
    }

    constexpr dimensions operator*( const dim_type rhs ) const
    {
        return T_Tuple{
            std::get< 0 >( *this ) * rhs,
            std::get< 1 >( *this ) * rhs,
            std::get< 2 >( *this ) * rhs,
            std::get< 3 >( *this ) * rhs,
            std::get< 4 >( *this ) * rhs,
            std::get< 5 >( *this ) * rhs,
            std::get< 6 >( *this ) * rhs
        };
    }

    constexpr dimensions operator*( const exp_type rhs ) const
    {
        return T_Tuple{
            std::get< 0 >( *this ) * rhs,
            std::get< 1 >( *this ) * rhs,
            std::get< 2 >( *this ) * rhs,
            std::get< 3 >( *this ) * rhs,
            std::get< 4 >( *this ) * rhs,
            std::get< 5 >( *this ) * rhs,
            std::get< 6 >( *this ) * rhs
        };
    }


    constexpr dimensions operator/( const dimensions rhs ) const
    {
        return T_Tuple{
            std::get< 0 >( *this ) / std::get< 0 >( rhs ),
            std::get< 1 >( *this ) / std::get< 1 >( rhs ),
            std::get< 2 >( *this ) / std::get< 2 >( rhs ),
            std::get< 3 >( *this ) / std::get< 3 >( rhs ),
            std::get< 4 >( *this ) / std::get< 4 >( rhs ),
            std::get< 5 >( *this ) / std::get< 5 >( rhs ),
            std::get< 6 >( *this ) / std::get< 6 >( rhs )
        };
    }

    constexpr dimensions operator/( const dim_type rhs ) const
    {
        return T_Tuple{
            std::get< 0 >( *this ) / rhs,
            std::get< 1 >( *this ) / rhs,
            std::get< 2 >( *this ) / rhs,
            std::get< 3 >( *this ) / rhs,
            std::get< 4 >( *this ) / rhs,
            std::get< 5 >( *this ) / rhs,
            std::get< 6 >( *this ) / rhs
        };
    }

    friend constexpr dimensions operator/( const dim_type rhs, const dimensions );

    friend constexpr dimensions operator*( const dim_type rhs, const dimensions );


    constexpr bool operator!=( const dim_type rhs ) const
    {
        return !( *this == rhs );
    }
};

template<
    typename T_Tuple
>
constexpr dimensions<T_Tuple> operator/( const typename dimensions<T_Tuple>::dim_type rhs, const dimensions<T_Tuple> dim )
{
    using dim_type = typename dimensions<T_Tuple>::dim_type;
    return T_Tuple{
        rhs / std::get< 0 >( dim ),
        rhs / std::get< 1 >( dim ),
        rhs / std::get< 2 >( dim ),
        rhs / std::get< 3 >( dim ),
        rhs / std::get< 4 >( dim ),
        rhs / std::get< 5 >( dim ),
        rhs / std::get< 6 >( dim )
    };
}

template<
    typename T_Tuple
>
constexpr dimensions<T_Tuple> operator*( const typename dimensions<T_Tuple>::dim_type rhs, const dimensions<T_Tuple> dim )
{
    using dim_type = typename dimensions<T_Tuple>::dim_type;
    return T_Tuple{
        rhs * std::get< 0 >( dim ),
        rhs * std::get< 1 >( dim ),
        rhs * std::get< 2 >( dim ),
        rhs * std::get< 3 >( dim ),
        rhs * std::get< 4 >( dim ),
        rhs * std::get< 5 >( dim ),
        rhs * std::get< 6 >( dim )
    };
}

template< typename... T >
constexpr auto
make_dimensions(const T... args)
-> dimensions <
    std::tuple< T... >
>
{
    return std::tuple< T... >{args...};
};


/// namespace detail.
#if 0
namespace detail {

/**
 * \brief The "collapse" template is used to avoid quantity< dimensions< 0, 0, 0 > >,
 * i.e. to make dimensionless results come out as type "Rep".
 */
template< typename D, typename T >
struct collapse
{
    typedef quantity< D, T > type;
};

template< typename T >
struct collapse< dimensionless_d, T >
{
    typedef T type;
};

template< typename D, typename T >
using Collapse = typename collapse<D,T>::type;

// promote types of expression to result type.

template < typename X, typename Y >
using PromoteAdd = decltype( std::declval<X>() + std::declval<Y>() );

template < typename X, typename Y >
using PromoteMul = decltype( std::declval<X>() * std::declval<Y>() );

/*
 * The following batch of structs are type generators to calculate
 * the correct type of the result of various operations.
 */

/**
 * product type generator.
 */
template< typename DX, typename DY, typename T >
struct product
{
    enum
    {
        d1 = DX::dim1 + DY::dim1,
        d2 = DX::dim2 + DY::dim2,
        d3 = DX::dim3 + DY::dim3,
        d4 = DX::dim4 + DY::dim4,
        d5 = DX::dim5 + DY::dim5,
        d6 = DX::dim6 + DY::dim6,
        d7 = DX::dim7 + DY::dim7,
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename DX, typename DY, typename X, typename Y>
using Product = typename product<DX, DY, PromoteMul<X,Y>>::type;

/**
 * quotient type generator.
 */
template< typename DX, typename DY, typename T >
struct quotient
{
    enum
    {
        d1 = DX::dim1 - DY::dim1,
        d2 = DX::dim2 - DY::dim2,
        d3 = DX::dim3 - DY::dim3,
        d4 = DX::dim4 - DY::dim4,
        d5 = DX::dim5 - DY::dim5,
        d6 = DX::dim6 - DY::dim6,
        d7 = DX::dim7 - DY::dim7,
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename DX, typename DY, typename X, typename Y>
using Quotient = typename quotient<DX, DY, PromoteMul<X,Y>>::type;

/**
 * reciprocal type generator.
 */
template< typename D, typename T >
struct reciprocal
{
    enum
    {
        d1 = - D::dim1,
        d2 = - D::dim2,
        d3 = - D::dim3,
        d4 = - D::dim4,
        d5 = - D::dim5,
        d6 = - D::dim6,
        d7 = - D::dim7,
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename D, typename X, typename Y>
using Reciprocal = typename reciprocal<D, PromoteMul<X,Y>>::type;

/**
 * power type generator.
 */
template< typename D, int N, typename T >
struct power
{
    enum
    {
        d1 = N * D::dim1,
        d2 = N * D::dim2,
        d3 = N * D::dim3,
        d4 = N * D::dim4,
        d5 = N * D::dim5,
        d6 = N * D::dim6,
        d7 = N * D::dim7,
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename D, int N, typename T >
using Power = typename detail::power< D, N, T >::type;

/**
 * root type generator.
 */
template< typename D, int N, typename T >
struct root
{
    enum
    {
        all_even_multiples =
            D::dim1 % N == 0 &&
            D::dim2 % N == 0 &&
            D::dim3 % N == 0 &&
            D::dim4 % N == 0 &&
            D::dim5 % N == 0 &&
            D::dim6 % N == 0 &&
            D::dim7 % N == 0
    };

    enum
    {
        d1 = D::dim1 / N,
        d2 = D::dim2 / N,
        d3 = D::dim3 / N,
        d4 = D::dim4 / N,
        d5 = D::dim5 / N,
        d6 = D::dim6 / N,
        d7 = D::dim7 / N
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename D, int N, typename T >
using Root = typename detail::root< D, N, T >::type;
#endif
namespace detail
{
/**
 * tag to construct a quantity from a magnitude.
 */
constexpr struct magnitude_tag_t{} magnitude_tag{};

} // namespace detail

/**
 * \brief class "quantity" is the heart of the library. It associates
 * dimensions  with a single "Rep" data member and protects it from
 * dimensionally inconsistent use.
 */
template< typename Dims, typename T /*= Rep */ >
class quantity
{
public:
    typedef Dims dimension_type;
    typedef typename Dims::dim_type::exp_type exp_type;

    typedef T value_type;

    constexpr quantity() : m_value{}, m_dim{} { }

    /**
     * public converting initializing constructor;
     * requires magnitude_tag to prevent constructing a quantity from a raw magnitude.
     */
    template <typename X>
    constexpr explicit quantity( detail::magnitude_tag_t, const X x, const dimension_type dim )
    : m_value( x ), m_dim( dim ) { }

    /**
     * converting copy-assignment constructor.
     */
    template <typename X >
    constexpr quantity( quantity<Dims, X> const & x )
    : m_value( x.magnitude() ), m_dim( x.dimension() ) { }

//    /**
//     * convert to compatible unit, for example: (3._dm).to(meter) gives 0.3;
//     */
//    constexpr value_type to( quantity const & x ) const {  return *this / x; }

    /**
     * convert to given unit, for example: (3._dm).to(meter) gives 0.3;
     */
    constexpr auto to( quantity const & x ) const -> quantity
    {
        return *this / x;
    }

    /**
     * the quantity's magnitude.
     */
    constexpr value_type magnitude() const { return m_value; }

    /**
     * the quantity's dimensions.
     */
    constexpr dimension_type dimension() const { return m_dim; }

    /**
     * We need a "zero" of each type -- for comparisons, to initialize running
     * totals, etc.  Note:  0 m != 0 kg, since they are of different dimensionality.
     * zero is really just defined for convenience, since
     * quantity< length_d >::zero == 0 * meter, etc.
     */
    static constexpr quantity zero() { return quantity{ value_type( 0.0 ) }; }
//    static constexpr quantity zero = quantity{ value_type( 0.0 ) };

private:
    /**
     * private initializing constructor.
     */
    constexpr quantity( value_type x, dimension_type dim ) : m_value{ x }, m_dim{ dim } { }

private:
    value_type m_value;
    dimension_type m_dim;

public:
    // friends:

    // arithmetic

    template< typename X >
    constexpr auto
    operator/(const quantity< dimension_type, X > & x) const ->
        quantity<
            dimension_type,
            typename std::conditional< sizeof(T) >= sizeof(X), T, X >::type
        >
    {
        return quantity<
            dimension_type,
            typename std::conditional< sizeof(T) >= sizeof(X), T, X >::type
        >{ detail::magnitude_tag, m_value / x.magnitude(), m_dim - x.dimension() };
    }

    template< typename X >
    constexpr auto
    operator*(const quantity< dimension_type, X > & x) const ->
        quantity<
            dimension_type,
            typename std::conditional< sizeof(T) >= sizeof(X), T, X >::type
        >
    {
        return quantity<
            dimension_type,
            typename std::conditional< sizeof(T) >= sizeof(X), T, X >::type
        >{ detail::magnitude_tag, m_value * x.magnitude(), m_dim + x.dimension() };
    }

    template< typename X >
    constexpr auto
    operator-(const quantity< dimension_type, X > & x) const ->
        quantity<
            dimension_type,
            typename std::conditional< sizeof(T) >= sizeof(X), T, X >::type
        >
    {
        return quantity<
            dimension_type,
            typename std::conditional< sizeof(T) >= sizeof(X), T, X >::type
        >{ detail::magnitude_tag, m_value - x.magnitude(), dimension() };
    }

    template< typename X >
    constexpr auto
    operator+(const quantity< dimension_type, X > & x) const ->
        quantity<
            dimension_type,
            typename std::conditional< sizeof(T) >= sizeof(X), T, X >::type
        >
    {
        return quantity<
            dimension_type,
            typename std::conditional< sizeof(T) >= sizeof(X), T, X >::type
        >{ detail::magnitude_tag, m_value + x.magnitude(), dimension() };
    }

    template <typename D, typename X, typename Y>
    friend constexpr auto
    operator*( const Y & y, quantity<D, X> const & x ) ->
        quantity<
            D,
            typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
        >;

    template <typename D, typename X, typename Y>
    friend constexpr auto
    operator*( quantity<D, X> const & x, const Y & y ) ->
        quantity<
            D,
            typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
        >;

    template <typename D, typename X, typename Y>
    friend constexpr auto
    operator/( const Y & y, quantity<D, X> const & x ) ->
        quantity<
            D,
            typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
        >;

    template <typename D, typename X, typename Y>
    friend constexpr auto
    operator/( quantity<D, X> const & x, const Y & y ) ->
        quantity<
            D,
            typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
        >;

    template <typename D, typename X, typename Y>
    friend constexpr auto
    pow( quantity<D, X> const & x, const Y & y ) ->
        quantity<
            D,
            typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
        >;

    // absolute value.
#if 0
    template <typename D, typename X>
    friend constexpr quantity<D,X>
    abs( quantity<D,X> const & x );

    // powers and roots

    template <int N, typename D, typename X>
    friend detail::Power<D, N, X>
    nth_power( quantity<D, X> const & x );

    template <typename D, typename X>
    friend constexpr detail::Power<D, 2, X>
    square( quantity<D, X> const & x );

    template <typename D, typename X>
    friend constexpr detail::Power<D, 3, X>
    cube( quantity<D, X> const & x );

    template <int N, typename D, typename X>
    friend detail::Root<D, N, X>
    nth_root( quantity<D, X> const & x );

    template <typename D, typename X>
    friend detail::Root< D, 2, X >
    sqrt( quantity<D, X> const & x );

    // comparison

    template <typename D, typename X, typename Y>
    friend constexpr bool operator==( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator!=( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator<( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator<=( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator>( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator>=( quantity<D, X> const & x, quantity<D, Y> const & y );

#endif
};

template< typename T_Mag, typename T_Dim >
constexpr quantity< T_Dim, T_Mag >
make_quantity( const T_Mag mag, const T_Dim dim )
{
    return quantity< T_Dim, T_Mag >{ detail::magnitude_tag, mag, dim };
}

#if 0
template< typename T >
struct GetSymbol
{



};
#endif


// Give names to the seven fundamental dimensions of physical reality.

namespace si
{
    constexpr dimension<DimType> length = { "m", 1 };
    constexpr dimension<DimType> mass = { "kg", 1 };
    constexpr dimension<DimType> time_interval = { "s", 1 };
    constexpr dimension<DimType> electric_current = { "A", 1 };
    constexpr dimension<DimType> thermodynamic_temperature = { "K", 1 };
    constexpr dimension<DimType> amount_of_substance = { "mol", 1 };
    constexpr dimension<DimType> luminous_intensity = { "cd", 1 };
}

// Low powers defined separately for efficiency.

/// square.

template <typename D, typename X>
constexpr quantity<D, X>
square( quantity<D, X> const & x )
{
   return x * x;
}

/// cube.

template <typename D, typename X>
constexpr quantity<D, X>
cube( quantity<D, X> const & x )
{
   return x * x * x;
}


namespace detail
{
    template< typename T_Type, typename T >
    constexpr T_Type pow( T_Type const x , T const exp, const T_Type result = T_Type( 1 ) )
    {
        return exp == 0 ? result : (
            exp == 1 ? x * result : detail::pow( x, exp - 1, result * x )
        );
    }
} // namespace details


template< typename T_Type, typename T >
constexpr T_Type pow( T_Type const x , T const exp )
{
    return detail::pow( x, exp );
}

template <typename D, typename X, typename Y>
constexpr auto
operator*( const Y & y, quantity<D, X> const & x )
-> quantity<
    D,
    typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
>
{
    return quantity<
        D,
        typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
    >( y * x.m_value, x.m_dim );
}

template <typename D, typename X, typename Y>
constexpr auto
operator*( quantity<D, X> const & x, const Y & y )
-> quantity<
    D,
    typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
>
{
    return quantity<
        D,
        typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
    >( y * x.m_value, x.m_dim );
}

template <typename D, typename X, typename Y>
constexpr auto
operator/( const Y & y, quantity<D, X> const & x )
-> quantity<
    D,
    typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
>
{
    return quantity<D,X>( y / x.m_value, x.m_dim );
}

template <typename D, typename X, typename Y>
constexpr auto
operator/( quantity<D, X> const & x, const Y & y )
-> quantity<
    D,
    typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
>
{
    return quantity<
        D,
        typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
    >( x.m_value / y, x.m_dim );
}

template <typename D, typename X, typename Y>
constexpr auto
pow( quantity<D, X> const & x, const Y & exp ) ->
    quantity<
        D,
        typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
    >
{
    return quantity<
        D,
        typename std::conditional< sizeof(X) >= sizeof(Y), X, Y >::type
    >{
        pow(x.m_value, exp),
        x.m_dim * exp
    };
}

#if 0
// Addition operators

/// quan += quan

template <typename D, typename X, typename Y>
constexpr quantity<D, X> &
operator+=( quantity<D, X> & x, quantity<D, Y> const & y )
{
    return x.m_value += y.m_value, x;
}

/// + quan

template <typename D, typename X>
constexpr quantity<D, X>
operator+( quantity<D, X> const & x )
{
   return quantity<D, X >( +x.m_value );
}

/// quan + quan

template< typename D, typename X, typename Y >
constexpr quantity <D, detail::PromoteAdd<X,Y>>
operator+( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return quantity<D, detail::PromoteAdd<X,Y>>( x.m_value + y.m_value );
}

// Subtraction operators

/// quan -= quan

template <typename D, typename X, typename Y>
constexpr quantity<D, X> &
operator-=( quantity<D, X> & x, quantity<D, Y> const & y )
{
    return x.m_value -= y.m_value, x;
}

/// - quan

template <typename D, typename X>
constexpr quantity<D, X>
operator-( quantity<D, X> const & x )
{
   return quantity<D, X >( -x.m_value );
}

/// quan - quan

template< typename D, typename X, typename Y >
constexpr quantity <D, detail::PromoteAdd<X,Y>>
operator-( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return quantity<D, detail::PromoteAdd<X,Y>>( x.m_value - y.m_value );
}

// Multiplication operators

/// quan *= num

template< typename D, typename X, typename Y>
constexpr quantity<D, X> &
operator*=( quantity<D, X> & x, const Y & y )
{
   return x.m_value *= y, x;
}

/// quan * num

template <typename D, typename X, typename Y>
constexpr quantity<D, detail::PromoteMul<X,Y>>
operator*( quantity<D, X> const & x, const Y & y )
{
   return quantity<D, detail::PromoteMul<X,Y>>( x.m_value * y );
}

/// num * quan

template <typename D, typename X, typename Y>
constexpr quantity< D, detail::PromoteMul<X,Y> >
operator*( const X & x, quantity<D, Y> const & y )
{
   return quantity<D, detail::PromoteMul<X,Y>>( x * y.m_value );
}

/// quan * quan:

template <typename DX, typename DY, typename X, typename Y>
constexpr detail::Product<DX, DY, X, Y>
operator*( quantity<DX, X> const & lhs, quantity< DY, Y > const & rhs )
{
    return detail::Product<DX, DY, X, Y>( lhs.m_value * rhs.m_value );
}

// Division operators

/// quan /= num

template< typename D, typename X, typename Y>
constexpr quantity<D, X> &
operator/=( quantity<D, X> & x, const Y & y )
{
   return x.m_value /= y, x;
}

/// quan / num

template <typename D, typename X, typename Y>
constexpr quantity<D, detail::PromoteMul<X,Y>>
operator/( quantity<D, X> const & x, const Y & y )
{
   return quantity<D, detail::PromoteMul<X,Y>>( x.m_value / y );
}

/// num / quan

template <typename D, typename X, typename Y>
constexpr detail::Reciprocal<D, X, Y>
operator/( const X & x, quantity<D, Y> const & y )
{
   return detail::Reciprocal<D, X, Y>( x / y.m_value );
}

/// quan / quan:

template <typename DX, typename DY, typename X, typename Y>
constexpr detail::Quotient<DX, DY, X, Y>
operator/( quantity<DX, X> const & x, quantity< DY, Y > const & y )
{
    return detail::Quotient<DX, DY, X, Y>( x.m_value / y.m_value );
}

/// absolute value.

template <typename D, typename X>
constexpr quantity<D,X> abs( quantity<D,X> const & x )
{
   return quantity<D,X>( std::abs( x.m_value ) );
}

// General powers

/// N-th power.

template <int N, typename D, typename X>
detail::Power<D, N, X>
nth_power( quantity<D, X> const & x )
{
   return detail::Power<D, N, X>( std::pow( x.m_value, X( N ) ) );
}

// Low powers defined separately for efficiency.

/// square.

template <typename D, typename X>
constexpr detail::Power<D, 2, X>
square( quantity<D, X> const & x )
{
   return x * x;
}

/// cube.

template <typename D, typename X>
constexpr detail::Power<D, 3, X>
cube( quantity<D, X> const & x )
{
   return x * x * x;
}

// General root

/// n-th root.

template <int N, typename D, typename X>
detail::Root<D, N, X>
nth_root( quantity<D, X> const & x )
{
   static_assert( detail::root<D, N, X>::all_even_multiples, "root result dimensions must be integral" );

   return detail::Root<D, N, X>( std::pow( x.m_value, X( 1.0 ) / N ) );
}

// Low roots defined separately for convenience.

/// square root.

template <typename D, typename X>
detail::Root< D, 2, X >
sqrt( quantity<D, X> const & x )
{
   static_assert(
      detail::root<D, 2, X >::all_even_multiples, "root result dimensions must be integral" );

   return detail::Root<D, 2, X>( std::pow( x.m_value, X( 1.0 ) / 2 ) );
}

// Comparison operators

/// equality.

template <typename D, typename X, typename Y>
constexpr bool
operator==( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value == y.m_value;
}

/// inequality.

template <typename D, typename X, typename Y>
constexpr bool
operator!=( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value != y.m_value;
}

/// less-than.

template <typename D, typename X, typename Y>
constexpr bool
operator<( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value < y.m_value;
}

/// less-equal.

template <typename D, typename X, typename Y>
constexpr bool
operator<=( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value <= y.m_value;
}

/// greater-than.

template <typename D, typename X, typename Y>
constexpr bool
operator>( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value > y.m_value;
}

/// greater-equal.

template <typename D, typename X, typename Y>
constexpr bool
operator>=( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value >= y.m_value;
}

/// quantity's dimension.

template <typename DX, typename X>
inline constexpr DX dimension( quantity<DX,X> const & q ) { return q.dimension(); }

/// quantity's magnitude.

template <typename DX, typename X>
inline constexpr X magnitude( quantity<DX,X> const & q ) { return q.magnitude(); }
#endif
// The seven SI base units.  These tie our numbers to the real world.

constexpr auto meter = make_quantity(
    Rep( 1.0 ),
    make_dimensions(
        si::length,
        si::mass.zero(),
        si::time_interval.zero(),
        si::electric_current.zero(),
        si::thermodynamic_temperature.zero(),
        si::amount_of_substance.zero(),
        si::luminous_intensity.zero()
    )
);

namespace pic
{
    constexpr auto meter = make_quantity(
    Rep( 5.0 ),
    make_dimensions(
        si::length,
        si::mass.zero(),
        si::time_interval.zero(),
        si::electric_current.zero(),
        si::thermodynamic_temperature.zero(),
        si::amount_of_substance.zero(),
        si::luminous_intensity.zero()
    )
);
}

constexpr auto kilogram = make_quantity(
    Rep( 1.0 ),
    make_dimensions(
        si::length.zero(),
        si::mass,
        si::time_interval.zero(),
        si::electric_current.zero(),
        si::thermodynamic_temperature.zero(),
        si::amount_of_substance.zero(),
        si::luminous_intensity.zero()
    )
);

constexpr auto second = make_quantity(
    Rep( 1.0 ),
    make_dimensions(
        si::length.zero(),
        si::mass.zero(),
        si::time_interval,
        si::electric_current.zero(),
        si::thermodynamic_temperature.zero(),
        si::amount_of_substance.zero(),
        si::luminous_intensity.zero()
    )
);

constexpr auto ampere = make_quantity(
    Rep( 1.0 ),
    make_dimensions(
        si::length.zero(),
        si::mass.zero(),
        si::time_interval.zero(),
        si::electric_current,
        si::thermodynamic_temperature.zero(),
        si::amount_of_substance.zero(),
        si::luminous_intensity.zero()
    )
);

constexpr auto kelvin = make_quantity(
    Rep( 1.0 ),
    make_dimensions(
        si::length.zero(),
        si::mass.zero(),
        si::time_interval.zero(),
        si::electric_current.zero(),
        si::thermodynamic_temperature,
        si::amount_of_substance.zero(),
        si::luminous_intensity.zero()
    )
);

constexpr auto mole = make_quantity(
    Rep( 1.0 ),
    make_dimensions(
        si::length.zero(),
        si::mass.zero(),
        si::time_interval.zero(),
        si::electric_current.zero(),
        si::thermodynamic_temperature.zero(),
        si::amount_of_substance,
        si::luminous_intensity.zero()
    )
);

constexpr auto candela = make_quantity(
    Rep( 1.0 ),
    make_dimensions(
        si::length.zero(),
        si::mass.zero(),
        si::time_interval.zero(),
        si::electric_current.zero(),
        si::thermodynamic_temperature.zero(),
        si::amount_of_substance.zero(),
        si::luminous_intensity
    )
);


// The standard SI prefixes.

constexpr long double yotta = 1e+24L;
constexpr long double zetta = 1e+21L;
constexpr long double   exa = 1e+18L;
constexpr long double  peta = 1e+15L;
constexpr long double  tera = 1e+12L;
constexpr long double  giga = 1e+9L;
constexpr long double  mega = 1e+6L;
constexpr long double  kilo = 1e+3L;
constexpr long double hecto = 1e+2L;
constexpr long double  deka = 1e+1L;
constexpr long double  deci = 1e-1L;
constexpr long double centi = 1e-2L;
constexpr long double milli = 1e-3L;
constexpr long double micro = 1e-6L;
constexpr long double  nano = 1e-9L;
constexpr long double  pico = 1e-12L;
constexpr long double femto = 1e-15L;
constexpr long double  atto = 1e-18L;
constexpr long double zepto = 1e-21L;
constexpr long double yocto = 1e-24L;

// Binary prefixes, pending adoption.

constexpr long double kibi = 1024;
constexpr long double mebi = 1024 * kibi;
constexpr long double gibi = 1024 * mebi;
constexpr long double tebi = 1024 * gibi;
constexpr long double pebi = 1024 * tebi;
constexpr long double exbi = 1024 * pebi;
constexpr long double zebi = 1024 * exbi;
constexpr long double yobi = 1024 * zebi;

#if 0
// The rest of the standard dimensional types, as specified in SP811.

using absorbed_dose_d             = dimensions< 2, 0, -2 >;
using absorbed_dose_rate_d        = dimensions< 2, 0, -3 >;
using acceleration_d              = dimensions< 1, 0, -2 >;
using activity_of_a_nuclide_d     = dimensions< 0, 0, -1 >;
using angular_velocity_d          = dimensions< 0, 0, -1 >;
using angular_acceleration_d      = dimensions< 0, 0, -2 >;
using area_d                      = dimensions< 2, 0, 0 >;
using capacitance_d               = dimensions< -2, -1, 4, 2 >;
using concentration_d             = dimensions< -3, 0, 0, 0, 0, 1 >;
using current_density_d           = dimensions< -2, 0, 0, 1 >;
using dose_equivalent_d           = dimensions< 2, 0, -2 >;
using dynamic_viscosity_d         = dimensions< -1, 1, -1 >;
using electric_charge_d           = dimensions< 0, 0, 1, 1 >;
using electric_charge_density_d   = dimensions< -3, 0, 1, 1 >;
using electric_conductance_d      = dimensions< -2, -1, 3, 2 >;
using electric_field_strenth_d    = dimensions< 1, 1, -3, -1 >;
using electric_flux_density_d     = dimensions< -2, 0, 1, 1 >;
using electric_potential_d        = dimensions< 2, 1, -3, -1 >;
using electric_resistance_d       = dimensions< 2, 1, -3, -2 >;
using energy_d                    = dimensions< 2, 1, -2 >;
using energy_density_d            = dimensions< -1, 1, -2 >;
using exposure_d                  = dimensions< 0, -1, 1, 1 >;
using force_d                     = dimensions< 1, 1, -2 >;
using frequency_d                 = dimensions< 0, 0, -1 >;
using heat_capacity_d             = dimensions< 2, 1, -2, 0, -1 >;
using heat_density_d              = dimensions< 0, 1, -2 >;
using heat_density_flow_rate_d    = dimensions< 0, 1, -3 >;
using heat_flow_rate_d            = dimensions< 2, 1, -3 >;
using heat_flux_density_d         = dimensions< 0, 1, -3 >;
using heat_transfer_coefficient_d = dimensions< 0, 1, -3, 0, -1 >;
using illuminance_d               = dimensions< -2, 0, 0, 0, 0, 0, 1 >;
using inductance_d                = dimensions< 2, 1, -2, -2 >;
using irradiance_d                = dimensions< 0, 1, -3 >;
using kinematic_viscosity_d       = dimensions< 2, 0, -1 >;
using luminance_d                 = dimensions< -2, 0, 0, 0, 0, 0, 1 >;
using luminous_flux_d             = dimensions< 0, 0, 0, 0, 0, 0, 1 >;
using magnetic_field_strength_d   = dimensions< -1, 0, 0, 1 >;
using magnetic_flux_d             = dimensions< 2, 1, -2, -1 >;
using magnetic_flux_density_d     = dimensions< 0, 1, -2, -1 >;
using magnetic_permeability_d     = dimensions< 1, 1, -2, -2 >;
using mass_density_d              = dimensions< -3, 1, 0 >;
using mass_flow_rate_d            = dimensions< 0, 1, -1 >;
using molar_energy_d              = dimensions< 2, 1, -2, 0, 0, -1 >;
using molar_entropy_d             = dimensions< 2, 1, -2, -1, 0, -1 >;
using moment_of_force_d           = dimensions< 2, 1, -2 >;
using permittivity_d              = dimensions< -3, -1, 4, 2 >;
using power_d                     = dimensions< 2, 1, -3 >;
using pressure_d                  = dimensions< -1, 1, -2 >;
using radiance_d                  = dimensions< 0, 1, -3 >;
using radiant_intensity_d         = dimensions< 2, 1, -3 >;
using speed_d                     = dimensions< 1, 0, -1 >;
using specific_energy_d           = dimensions< 2, 0, -2 >;
using specific_heat_capacity_d    = dimensions< 2, 0, -2, 0, -1 >;
using specific_volume_d           = dimensions< 3, -1, 0 >;
using substance_permeability_d    = dimensions< -1, 0, 1 >;
using surface_tension_d           = dimensions< 0, 1, -2 >;
using thermal_conductivity_d      = dimensions< 1, 1, -3, 0, -1 >;
using thermal_diffusivity_d       = dimensions< 2, 0, -1 >;
using thermal_insulance_d         = dimensions< 0, -1, 3, 0, 1 >;
using thermal_resistance_d        = dimensions< -2, -1, 3, 0, 1 >;
using thermal_resistivity_d       = dimensions< -1, -1, 3, 0, 1 >;
using torque_d                    = dimensions< 2, 1, -2 >;
using volume_d                    = dimensions< 3, 0, 0 >;
using volume_flow_rate_d          = dimensions< 3, 0, -1 >;
using wave_number_d               = dimensions< -1, 0, 0 >;
#endif
// Handy values.

constexpr Rep pi      { Rep( 3.141592653589793238462L ) };
constexpr Rep percent { Rep( 1 ) / 100 };

//// Not approved for use alone, but needed for use with prefixes.
constexpr auto gram         { kilogram / 1000 };

// The derived SI units, as specified in SP811.

constexpr Rep                                 radian       { Rep( 1 ) };
constexpr Rep                                 steradian    { Rep( 1 ) };
constexpr auto newton       { meter * kilogram / square( second ) };
constexpr auto pascal       { newton / square( meter ) };
constexpr auto joule        { newton * meter };
constexpr auto watt         { joule / second };
constexpr auto coulomb      { second * ampere };
constexpr auto volt         { watt / ampere };
constexpr auto farad        { coulomb / volt };
constexpr auto ohm          { volt / ampere };
constexpr auto siemens      { ampere / volt };
constexpr auto weber        { volt * second };
constexpr auto tesla        { weber / square( meter ) };
constexpr auto henry        { weber / ampere };
constexpr auto degree_celsius   { kelvin };
constexpr auto lumen        { candela * steradian };
constexpr auto lux          { lumen / meter / meter };
constexpr auto becquerel    { 1 / second };
constexpr auto gray         { joule / kilogram };
constexpr auto sievert      { joule / kilogram };
constexpr auto hertz        { 1 / second };

// The rest of the units approved for use with SI, as specified in SP811.
// (However, use of these units is generally discouraged.)

constexpr auto angstrom     { Rep( 1e-10L ) * meter };
constexpr auto are          { Rep( 1e+2L ) * square( meter ) };
constexpr auto bar          { Rep( 1e+5L ) * pascal };
constexpr auto barn         { Rep( 1e-28L ) * square( meter ) };
constexpr auto curie        { Rep( 3.7e+10L ) * becquerel };
constexpr auto day          { Rep( 86400L ) * second };
constexpr Rep                                 degree_angle { pi / 180 };
constexpr auto gal          { Rep( 1e-2L ) * meter / square( second ) };
constexpr auto hectare      { Rep( 1e+4L ) * square( meter ) };
constexpr auto hour         { Rep( 3600 ) * second };
constexpr auto knot         { Rep( 1852 ) / 3600 * meter / second };
constexpr auto liter        { Rep( 1e-3L ) * cube( meter ) };
constexpr auto minute       { Rep( 60 ) * second };
constexpr Rep                                 minute_angle { pi / 10800 };
constexpr auto mile_nautical{ Rep( 1852 ) * meter };
constexpr auto rad          { Rep( 1e-2L ) * gray };
constexpr auto rem          { Rep( 1e-2L ) * sievert };
constexpr auto roentgen     { Rep( 2.58e-4L ) * coulomb / kilogram };
constexpr Rep                                 second_angle { pi / 648000L };
constexpr auto ton_metric   { Rep( 1e+3L ) * kilogram };

// Alternate (non-US) spellings:

constexpr auto metre        { meter };
constexpr auto litre        { liter };
constexpr Rep                                 deca         { deka };
constexpr auto tonne        { ton_metric };

// cooked literals for base units;
// these could also have been created with a script.

#define QUANTITY_DEFINE_SCALING_LITERAL( sfx, quant, factor ) \
    constexpr quantity<  decltype(quant.dimension()), long double> operator "" _ ## sfx(unsigned long long x) \
    { \
        return make_quantity( factor * x, quant.dimension() ); \
    } \
    constexpr quantity< decltype(quant.dimension()), long double> operator "" _ ## sfx(long double x) \
    { \
        return make_quantity( factor * x, quant.dimension() ); \
    }

#define QUANTITY_DEFINE_SCALING_LITERALS( pfx, quant, fact ) \
    QUANTITY_DEFINE_SCALING_LITERAL( Y ## pfx, quant, fact * yotta ) \
    QUANTITY_DEFINE_SCALING_LITERAL( Z ## pfx, quant, fact * zetta ) \
    QUANTITY_DEFINE_SCALING_LITERAL( E ## pfx, quant, fact * exa   ) \
    QUANTITY_DEFINE_SCALING_LITERAL( P ## pfx, quant, fact * peta  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( T ## pfx, quant, fact * tera  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( G ## pfx, quant, fact * giga  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( M ## pfx, quant, fact * mega  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( k ## pfx, quant, fact * kilo  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( h ## pfx, quant, fact * hecto ) \
    QUANTITY_DEFINE_SCALING_LITERAL( da## pfx, quant, fact * deka  ) \
    QUANTITY_DEFINE_SCALING_LITERAL(      pfx, quant, fact * 1     ) \
    QUANTITY_DEFINE_SCALING_LITERAL( d ## pfx, quant, fact * deci  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( c ## pfx, quant, fact * centi ) \
    QUANTITY_DEFINE_SCALING_LITERAL( m ## pfx, quant, fact * milli ) \
    QUANTITY_DEFINE_SCALING_LITERAL( u ## pfx, quant, fact * micro ) \
    QUANTITY_DEFINE_SCALING_LITERAL( n ## pfx, quant, fact * nano  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( p ## pfx, quant, fact * pico  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( f ## pfx, quant, fact * femto ) \
    QUANTITY_DEFINE_SCALING_LITERAL( a ## pfx, quant, fact * atto  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( z ## pfx, quant, fact * zepto ) \
    QUANTITY_DEFINE_SCALING_LITERAL( y ## pfx, quant, fact * yocto )


#define QUANTITY_DEFINE_LITERALS( pfx, dim ) \
    QUANTITY_DEFINE_SCALING_LITERALS( pfx, dim, 1 )

/// literals

namespace literals {

QUANTITY_DEFINE_SCALING_LITERALS( g, phys::units::kilogram, 1e-3 )

QUANTITY_DEFINE_LITERALS( m  , phys::units::meter )
QUANTITY_DEFINE_LITERALS( s  , phys::units::second )
QUANTITY_DEFINE_LITERALS( A  , phys::units::ampere )
QUANTITY_DEFINE_LITERALS( K  , phys::units::kelvin )
QUANTITY_DEFINE_LITERALS( mol, phys::units::mole )
QUANTITY_DEFINE_LITERALS( cd , phys::units::candela )

} // namespace literals

}} // namespace phys::units

#endif // PHYS_UNITS_QUANTITY_HPP_INCLUDED

/*
 * end of file
 */
