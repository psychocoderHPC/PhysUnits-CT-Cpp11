#include <iostream>
#include <tuple>
#include <typeinfo>

#include "phys/units/quantity.hpp"
#include "phys/units/quantity_io.hpp"
//#include "phys/units/quantity_io_symbols.hpp"

#include <type_traits>
#include <array>
#include <chrono>
using namespace phys::units;
using namespace phys::units::io;

using namespace phys::units::literals;

/*
template< typename T >
constexpr auto
make_quantity( T const  arg )
-> quantity<
    decltype( arg.dimension() ),
    decltype( arg.magnitude() )
>
{
   return arg;

   return quantity<
        decltype( arg.dimension() ),
        decltype( arg.magnitude() )
    >( detail::magnitude_tag, arg.magnitude( ));

}
*/

template<size_t... Is> struct seq{};

template<size_t N, size_t... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};

template<size_t... Is>
struct gen_seq<0, Is...> : seq<Is...>{};



struct Mul
{
    template< typename T_Type >
    struct Unary
    {
        const T_Type m_value;

        constexpr Unary( T_Type const value ): m_value{ value }
        {
        }

        template< typename T >
        constexpr auto operator()( T&  t) const
        -> decltype( t * m_value)
        {
            return t * m_value;
        }
    };

    struct Binary
    {
        template< typename T1, typename T2 >
        constexpr auto
        operator()( T1 const t1, T2 const t2) const
        -> decltype( t1 * t2)
        {
            return t1 * t2;
        }
    };

};

struct Div
{
    template< typename T_Type >
    struct Unary
    {
        const T_Type m_value;

        constexpr Unary( T_Type const value ): m_value{ value }
        {
        }

        template< typename T >
        constexpr auto operator()( T&  t) const
        -> decltype( t / m_value)
        {
            return t / m_value;
        }
    };

    struct Binary
    {
        template< typename T1, typename T2 >
        constexpr auto
        operator()( T1 const t1, T2 const t2) const
        -> decltype( t1 / t2)
        {
            return t1 / t2;
        }
    };

};

struct Add
{
    template< typename T_Type >
    struct Unary
    {
        const T_Type m_value;

        constexpr Unary( T_Type const value ): m_value{ value }
        {
        }

        template< typename T >
        constexpr auto operator()( T&  t) const
        -> decltype( t + m_value)
        {
            return t + m_value;
        }
    };

    struct Binary
    {
        template< typename T1, typename T2 >
        constexpr auto
        operator()( T1 const t1, T2 const t2) const
        -> decltype( t1 + t2)
        {
            return t1 + t2;
        }
    };

};

struct Sub
{
    template< typename T_Type >
    struct Unary
    {
        const T_Type m_value;

        constexpr Unary( T_Type const value ): m_value{ value }
        {
        }

        template< typename T >
        constexpr auto operator()( T&  t) const
        -> decltype( t - m_value)
        {
            return t - m_value;
        }
    };

    struct Binary
    {
        template< typename T1, typename T2 >
        constexpr auto
        operator()( T1 const t1, T2 const t2) const
        -> decltype( t1 - t2)
        {
            return t1 - t2;
        }
    };

};

struct Fill
{
    template< typename T_Type >
    struct Unary
    {
        const T_Type m_value;

        constexpr Unary( T_Type const value ): m_value{ value }
        {
        }

        template< typename T >
        constexpr T_Type operator()( T& ) const
        {
            return m_value;
        }
    };
};

template< typename T_Op, typename T>
constexpr typename T_Op::template Unary<T>
make_unary( T_Op const, T const value )
{
    return typename T_Op::template Unary<T>{value};
}

template< typename T_Op >
constexpr typename T_Op::Binary
make_binary( T_Op const = T_Op{} )
{
    return typename T_Op::Binary{};
}

template<size_t T_size, typename F, typename T, size_t ... I1, template<typename,size_t> class T_Array>
// Expansion pack
constexpr auto
for_each2(const F& f,const T_Array<T, T_size>& a, seq<I1...>)
-> T_Array<
    decltype( f( a[0] ) ),
    T_size
>
{
    return { f(a[I1])... };
}

template<size_t T_size, typename F, typename T, template<typename,size_t> class T_Array>
// Initializer for the recursion
constexpr auto
for_each(const F& f, const T_Array<T, T_size>& a)
-> T_Array<
    decltype( f( a[0] ) ),
    T_size
>
{
    return for_each2(f, a, gen_seq<T_size>{});
}


template<size_t T_size, typename F, size_t ... I, typename T1, typename T2, template<typename,size_t> class T_Array>
// Expansion pack
constexpr auto
for_each2(const F& f,const T_Array<T1, T_size>& a, const T_Array<T2, T_size>& b, seq<I...>)
-> T_Array<
    decltype( f( a[0], b[0] ) ),
    T_size
>
{
    return { f(a[I], b[I])... };
}

template<size_t T_size, typename F, typename T1, typename T2, template<typename,size_t> class T_Array>
// Initializer for the recursion
constexpr auto
for_each(const F& f, const T_Array<T1, T_size>& a, const T_Array<T2, T_size>& b)
-> T_Array<
    decltype( f( a[0], b[0] ) ),
    T_size
>
{
    return for_each2(f, a, b, gen_seq<T_size>{});
}





template< typename T_Type, size_t T_size >
struct vec;

template< typename T >
struct IsVector
{
    static constexpr bool value = false;
};

template< typename T, size_t T_Size >
struct IsVector< vec<T, T_Size> >
{
    static constexpr bool value = true;
};




template< typename T_Type, size_t T_size >
struct vec : public std::array< T_Type, T_size>
{

    using type = T_Type;
    using size_type = size_t;
    using self = vec;

    static const size_t size = T_size;


    //using std::array< T_Type, T_size>::si

    template< typename... T >
    constexpr vec( T const ... args ) :
        std::array< type, size>{ {args...} }
    {

    }


    template< typename T >
    constexpr auto
    operator+( const vec< T, size >& rhs ) const
    -> decltype( for_each( make_binary<Add>(), *this, rhs ) )
    {
        return for_each( make_binary<Add>(), *this, rhs );
    }

    template< typename T >
    constexpr auto
    operator-( const vec< T, size >& rhs ) const
    -> decltype( for_each( make_binary<Sub>(), *this, rhs ) )
    {
        return for_each( make_binary<Sub>(), *this, rhs );
    }

    template< typename T>
    constexpr auto
    operator*( const vec< T, size >& rhs ) const
    -> decltype( for_each( make_binary<Mul>(), *this, rhs ) )
    {
        return for_each( make_binary<Mul>(), *this, rhs );
    }

    /*
    template<
        typename T
    >
    constexpr
    typename enableVecOpReturnType<self, T>::type
    operator/( const T& rhs ) const
    {
        return for_each( make_binary<Div>(), *this, rhs );
    }
    */

    template<
        typename T,
        typename = typename std::enable_if< IsVector<T>::value >::type
    >
    constexpr auto
    operator/( const T& rhs ) const
    -> decltype( for_each( make_binary<Div>(), *this, rhs ) )
    {
        return for_each( make_binary<Div>(), *this, rhs );
    }

    template< typename T >
    constexpr auto
    operator-( const T& rhs ) const
    -> decltype( for_each( make_unary( Sub{}, rhs ), *this ) )
    {
        return for_each(  make_unary( Sub{}, rhs ), *this );
    }

    template< typename T >
    constexpr auto
    operator+( const T& rhs ) const
    -> decltype( for_each( make_unary( Add{}, rhs ), *this ) )
    {
        return for_each(  make_unary( Add{}, rhs ), *this );
    }

    template< typename T >
    constexpr auto
    operator*( const T& rhs ) const
    -> decltype( for_each( make_unary( Mul{}, rhs ), *this ) )
    {
        return for_each(  make_unary( Mul{}, rhs ), *this );
    }

    template<
        typename T,
        typename = typename std::enable_if< IsVector<T>::value == false >::type
    >
    constexpr auto
    operator/( const T& rhs ) const
    ->  decltype(for_each(  make_unary( Div{}, rhs ), *this ))
    {
       // static_assert(size!=size,"nononono");
        return for_each(  make_unary( Div{}, rhs ), *this );
    }

    template< typename T >
    constexpr auto
    fill( const T& value ) const
    -> decltype( for_each(make_unary(Fill{},value), *this) )
    {
        return for_each(make_unary(Fill{},value), *this);
    }

    template<
        typename T,
        typename T2,
        size_t z,
        typename = typename std::enable_if< IsVector<T>::value == false >::type
    >
    friend constexpr auto
    operator/( const T& value, const vec<T2,z> v)
    ->  decltype(
             v.fill(value) / v
    )
    {
        static_assert(size!=size,"nononono");
        return
           v.fill(value)/ v;
    }

};



/*
template<  typename T, size_t T_size  >
constexpr auto
operator/( const T& lhs, const vec< T, T_size >& v )
-> decltype( for_each( make_binary<Div>(),for_each(make_unary(Fill{},lhs), v),v))
{
    return for_each(make_unary(Fill{},lhs), v)/v;
}
*/
#if 0
template<
    typename T1,
    typename T2,
    size_t T_size ,
    typename = std::enable_if<
        IsVector<T1>::isVector == false
    >
>
constexpr auto
operator/( const T1 value, const vec< T2, T_size > v )
-> decltype(
    (  IsVector<T1>::isVector == false) ? (for_each(make_unary(Fill{},value), v) ): 1
)
{
    static_assert(v.size!=2,"nononono");
    return v.fill(value) / v;
}
#endif
/*
template<
    typename T1,
    typename T2,
    size_t T_size
>
constexpr auto
operator/( const T1& value, const vec< T2, T_size >& v )
->
    decltype(
        for_each(make_binary<Div>(),for_each(make_unary(Fill{},value)), v)
    )
{
    static_assert(v.size!=2,"nononono");
    return v.fill(value) / v;
}
        */


template<typename T, size_t T_size>
std::ostream & operator<<(std::ostream &os, const vec<T,T_size> & v)
    {
        os << "{";
        for(int i = 0; i < (T_size); i++)
        {
            if( i != 0) os << " , ";
            os << (v)[i];
        }
        os << "}";
        return os;
    }

struct Test
{
    static constexpr auto mySpeed  = 1.2 * meter /second;

};


int main()
{
    constexpr auto speed = 299792458 * meter / second;
    constexpr auto pic_speed = (1.0/(299792458./1000.)) * second / (kilo*meter);
    constexpr auto unit_speed = 299792458* meter / second;

    constexpr auto wavelength = 800*nano*meter;

    auto xyz = 100 * meter/second;
    auto z = xyz *10;
    z *= Rep(12.0);

    constexpr auto mm = meter;
    constexpr vec< decltype(meter),2 > v = {mm,2*mm};

    //constexpr vec< double,2 > v(23.f,42.);


    std::cout<<"v "<<v<<std::endl;
    constexpr auto vpv = v/v;
    std::cout<<"v+v "<<vpv<<std::endl;
/*
    constexpr auto res=v;
    //static_assert(res[1]==2,"wrong v");
    constexpr auto res2 = res * res ;
    constexpr auto res4 = res / res ;
    constexpr auto res5 = res + res ;
    constexpr auto res6 = res - res*2 ;
    constexpr auto res7 = res - 3 ;
    constexpr auto res8 = res + 3 ;
    constexpr auto res9 = res * 3 ;
    constexpr auto res10 = res / 3  ;
   // constexpr auto res11 = 40000 / res;
 * */



   // std::cout<<res2<<res4<<res5<<res6<<res7<<res8<<res9<<res10<<res10*res10<<res11<<std::endl;
   // std::cout<<"vec "<<v[1]<<" res2="<<res2[1]<<std::endl;

    //constexpr auto res3 = for_each(make_unary(Fill{},42), res2);



}

