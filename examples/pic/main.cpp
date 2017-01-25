#include <iostream>
#include <tuple>
#include <typeinfo>

#include "phys/units/quantity.hpp"
#include "phys/units/quantity_io.hpp"
//#include "phys/units/quantity_io_symbols.hpp"

#include <type_traits>
#include <array>
#include <chrono>
#include <sys/socket.h>
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
/*
template<size_t... Is> struct seq{};

template<size_t N, size_t... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};

template<size_t... Is>
struct gen_seq<0, Is...> : seq<Is...>{};
*/

template<size_t... Is> struct seq{};

template<typename T1, typename T2> struct join_seq;

template<size_t... Is1, size_t... Is2>
struct join_seq< seq<Is1...>, seq<Is2...> >
{
    typedef seq<Is1...,Is2...> type;
};


template<size_t F, size_t E>
struct rec_gen_seq;

template<size_t F>
struct rec_gen_seq< F, F >
{
    typedef seq<F> type;
};

template<size_t F, size_t E>
struct rec_gen_seq
{
    static constexpr size_t diff = (E - F + 1 ) / 2;
    typedef typename join_seq<
        typename rec_gen_seq< F, F + diff - 1 >::type,
        typename rec_gen_seq< F + diff, F + ( E - F ) >::type
    >::type type;
};


template<size_t N>
struct gen_seq : rec_gen_seq<0, N-1>::type {};

template<>
struct gen_seq<0> : seq<>{};





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

struct Echo
{

    struct Unary
    {
        constexpr Unary( )
        {
        }

        template< typename T >
        constexpr T operator()( T& value) const
        {
            return value;
        }
    };
};

template< typename T_Op, typename T>
constexpr typename T_Op::template Unary<T>
make_unary( T_Op const, T const value )
{
    return typename T_Op::template Unary<T>{value};
}

template< typename T_Op>
constexpr typename T_Op::Unary
make_unary( T_Op const )
{
    return typename T_Op::Unary{};
}

template< typename T_Op >
constexpr typename T_Op::Binary
make_binary( T_Op const = T_Op{} )
{
    return typename T_Op::Binary{};
}

namespace vec
{


template< typename T_Type, size_t T_size >
struct vec;
}

namespace phys
{
namespace units
{

template< typename T_Type, size_t T_size >
struct disableQuantityOperatorsFor< vec::vec< T_Type, T_size> >
{
    static constexpr bool value = true;
};

} //namespace units
} //namepsace phys

namespace vec
{


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

template< size_t min, size_t elem >
struct Accumulate;

template< size_t min >
struct Accumulate< min, min >
{
    template<size_t T_size, typename F, typename T, template<typename,size_t> class T_Array>
    // Expansion pack
    constexpr auto
    operator()(const F& f,const T_Array<T, T_size>& a) const
    -> decltype( a[ min ] )
    {
        return a[ min ];
    }
};


template< size_t min, size_t elem >
struct Accumulate
{
    //static_assert( min == 0, "accumulate with zero size array is not allowed!" );
    static constexpr size_t diff = (elem-min +1) / 2;
    template<size_t T_size, typename F, typename T, template<typename,size_t> class T_Array>
    // Expansion pack
    constexpr auto
    operator()(const F& f,const T_Array<T, T_size>& a) const
    -> decltype( f( Accumulate< min, min + diff - 1 >{}( f, a ), Accumulate<  min + diff, min  + ( elem-min )  >{}( f, a ) ) )
    {
       // static_assert(diff == 1,"nonono");
        return f( Accumulate< min, min + diff - 1 >{}( f, a ), Accumulate<  min + diff, min  + (elem-min) >{}( f, a ) );
    }
};

template<size_t T_size, typename F, typename T, template<typename,size_t> class T_Array,
    typename = typename std::enable_if<
        IsVector<T_Array<T, T_size> >::value
    >::type
>
constexpr auto
accumulate(const F& f, const T_Array<T, T_size>& a)
-> decltype( Accumulate<0, T_size -1 >{}(f, a) )
{
    static_assert( T_size > 0, "accumulate with zero size array is not allowed!" );
    return Accumulate<0, T_size - 1>{}(f, a);
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

template<size_t T_size, typename F, typename T, template<typename,size_t> class T_Array,
    typename = typename std::enable_if<
        IsVector<T_Array<T, T_size> >::value
    >::type
>
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

template<size_t T_size, typename F, typename T1, typename T2, template<typename,size_t> class T_Array,
    typename = typename std::enable_if<
        IsVector<T_Array<T1, T_size> >::value && IsVector<T_Array<T2, T_size> >::value
    >::type
>
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


template<size_t T_size1, size_t T_size2, size_t ... I1, typename T1, size_t ... I2, typename T2, template<typename,size_t> class T_Array>
// Expansion pack
constexpr auto
concat2(const T_Array<T1, T_size1>& a, const T_Array<T2, T_size2>& b, seq<I1...>, seq<I2...> )
-> T_Array<
    typename std::common_type< T1, T2 >::type,
    T_size1 + T_size2
>
{
    return { a[I1]..., b[I2]... };
}

template<size_t T_size1, size_t T_size2, typename T1, typename T2, template<typename,size_t> class T_Array,
    typename = typename std::enable_if<
        IsVector<T_Array<T1, T_size1> >::value && IsVector<T_Array<T2, T_size2> >::value
    >::type
>
// Initializer for the recursion
constexpr auto
concat(const T_Array<T1, T_size1>& a, const T_Array<T2, T_size2>& b)
-> T_Array<
    typename std::common_type< T1, T2 >::type,
    T_size1 + T_size2
>
{
    return concat2(a, b, gen_seq<T_size1>{}, gen_seq<T_size2>{});
}

template< typename T, typename T2 >
struct OperatorConflitc
{
    static constexpr bool value = false;
};

template< typename T, typename T2, typename T_Type, size_t T_size >
struct OperatorConflitc< quantity<T, T2>, vec<T_Type,T_size> >
{
    static constexpr bool value = true;
};



template<typename T, typename T2>
struct Vec
{
    constexpr vec<T,T2::size> operator()(const T& t) const
    {
        return vec<T,T2::size>{}.fill(t);
    }
};

template<typename T, typename T2, size_t size>
struct Vec< vec<T,size>, vec<T2,size> >
{
    constexpr vec<T,size> operator()(const vec<T,size>& v) const
    {
        return v;
    }
};

template<typename T, typename T2, size_t size,size_t size2>
struct Vec< vec<T,size>, vec<T2,size2> >
{
    constexpr vec<T,size> operator()(const vec<T,size>& v) const
    {
        static_assert(size==size2,"size need to be equal");
        return v;
    }
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

    template<
        typename T,
        typename = typename std::enable_if< !IsVector<T>::value >::type
    >
    constexpr auto
    operator-( const T& rhs ) const
    ->  decltype(for_each(  make_binary( Sub{} ), *this, Vec<T, vec<type,size> >{}(rhs) ))
    {
        return for_each(  make_binary( Sub{} ), *this, Vec<T, vec<type,size> >{}(rhs) );
    }

    template<
        typename T,
        typename = typename std::enable_if< !IsVector<T>::value >::type
    >
    constexpr auto
    operator+( const T& rhs ) const
    ->  decltype(for_each(  make_binary( Add{} ), *this, Vec<T, vec<type,size> >{}(rhs) ))
    {
        return for_each(  make_binary( Add{} ), *this, Vec<T, vec<type,size> >{}(rhs) );
    }

    template<
        typename T,
        typename = typename std::enable_if< !IsVector<T>::value >::type
    >
    constexpr auto
    operator*( const T& rhs ) const
    ->  decltype(for_each(  make_binary( Mul{} ), *this, Vec<T, vec<type,size> >{}(rhs) ))
    {
        return for_each(  make_binary( Mul{} ), *this, Vec<T, vec<type,size> >{}(rhs) );
    }

    template<
        typename T,
        typename = typename std::enable_if< !IsVector<T>::value >::type
    >
    constexpr auto
    operator/( const T& rhs ) const
    ->  decltype(for_each(  make_binary( Div{} ), *this, Vec<T, vec<type,size> >{}(rhs) ))
    {
        return for_each(  make_binary( Div{} ), *this, Vec<T, vec<type,size> >{}(rhs) );
    }

    template< typename T >
    constexpr auto
    fill( const T& value ) const
    -> decltype( for_each(make_unary(Fill{},value), *this) )
    {
        return for_each(make_unary(Fill{},value), *this);
    }

};

template<
    typename T_Left,
    typename T_Right,
    size_t T_size
>constexpr auto
operator/( const T_Left& lhs, const vec<T_Right,T_size>& rhs )
-> decltype( for_each( make_binary<Div>(), Vec<T_Left,vec<T_Right,T_size>>{}(lhs), rhs ) )
{
    return for_each( make_binary<Div>(), Vec<T_Left,vec<T_Right,T_size>>{}(lhs), rhs );
}

template<
    typename T_Left,
    typename T_Right,
    size_t T_size
>constexpr auto
operator*( const T_Left& lhs, const vec<T_Right,T_size>& rhs )
-> decltype( for_each( make_binary<Mul>(), Vec<T_Left,vec<T_Right,T_size>>{}(lhs), rhs ) )
{
    return for_each( make_binary<Mul>(), Vec<T_Left,vec<T_Right,T_size>>{}(lhs), rhs );
}

template<
    typename T_Left,
    typename T_Right,
    size_t T_size
>constexpr auto
operator+( const T_Left& lhs, const vec<T_Right,T_size>& rhs )
-> decltype( for_each( make_binary<Add>(), Vec<T_Left,vec<T_Right,T_size>>{}(lhs), rhs ) )
{
    return for_each( make_binary<Add>(), Vec<T_Left,vec<T_Right,T_size>>{}(lhs), rhs );
}

template<
    typename T_Left,
    typename T_Right,
    size_t T_size
>constexpr auto
operator-( const T_Left& lhs, const vec<T_Right,T_size>& rhs )
-> decltype( for_each( make_binary<Sub>(), Vec<T_Left,vec<T_Right,T_size>>{}(lhs), rhs ) )
{
    return for_each( make_binary<Sub>(), Vec<T_Left,vec<T_Right,T_size>>{}(lhs), rhs );
}


template< typename T, typename... T1 >
constexpr auto
make_vec( const T& value, const T1&... values )
-> vec<T, sizeof...(T1) + 1>
{
    return vec<T, sizeof...(T1) + 1>{value, values...};
}


namespace detail
{
    template< typename T, typename I>
    constexpr T always( const T& value, const I )
    {
        return value;
    }

    template<typename T, size_t ... I1>
    // Expansion pack
    constexpr auto
    make_vec( const T& value, seq<I1...>)
    -> vec<T, sizeof...(I1)>
    {
        return { always(value,I1)... };
    }


    // Initializer for the recursion
    template<typename T, size_t T_sizeOld, size_t ... I1>
    constexpr auto
    shrink(const vec<T, T_sizeOld>& v, seq<I1...>)
    -> vec<
        T,
        sizeof...(I1)
    >
    {
        return { v[I1]... };
    }

} // namespace detail
template< size_t T_size, typename T>
constexpr auto
make_vec( const T& value )
-> vec<T, T_size>
{
    return  detail::make_vec(value,gen_seq<T_size>{} );
}

// Initializer for the recursion
template<size_t T_Size, typename T, size_t T_sizeOld>
constexpr auto
shrink(const vec<T, T_sizeOld>& v)
-> vec<
    T,
    T_Size
>
{
    return detail::shrink( v, gen_seq<T_Size>{});
}

} //namepsace vec


template<typename T, size_t T_size>
std::ostream & operator<<(std::ostream &os, const vec::vec<T,T_size> & v)
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

    constexpr auto m = meter;
    constexpr vec::vec< decltype(meter),2 > v = {m,2*m};
    constexpr vec::vec< decltype(meter),5 > vv = {2*m,m,m,m,m };
    //constexpr vec< double,2 > v(23.f,42.);


    std::cout<<"v "<<v<<std::endl;
    constexpr auto vpv = v+v;
    std::cout<<"v+v "<<vpv<<std::endl;

    constexpr auto res=v;
    //static_assert(res[1]==2,"wrong v");
    constexpr auto res2 = res * res ;
    std::cout << "res2=" << res2 << std::endl;
    constexpr auto res4 = res / res ;
    std::cout << "res4=" << res4 << std::endl;
    constexpr auto res5 = res + res ;
    std::cout << "res5=" << res5 << std::endl;
    constexpr auto res6 = res - res*2 ;
    std::cout << "res6=" << res6 << std::endl;
    constexpr auto res7 = res - 3*meter ;
    std::cout << "res7=" << res7 << std::endl;
    constexpr auto res8 = res + 3 *meter;
    std::cout << "res8=" << res8 << std::endl;
    constexpr auto res9 = res * 3 * res ;
    std::cout << "res9=" << res9 << std::endl;
    constexpr auto res10 =  3. * meter ;
    std::cout << "res10=" << res10 << std::endl;
    constexpr auto res11 = res/ res10;
    std::cout << "res11=" << res11 << std::endl;
    constexpr auto res12 = concat( res, vv );
    std::cout << "res12=" << res12 << std::endl;
    constexpr auto res13 = res12 * meter;
    std::cout << "res13=" << res13 << std::endl;
    constexpr auto res14 = res13 + meter*meter;
    std::cout << "res14=" << res14 << std::endl;
    constexpr auto res15 = meter*meter + res13;
    std::cout << "res15=" << res15 << std::endl;
    constexpr auto res16 = res15 * res15;
    std::cout << "res16=" << res16 << std::endl;
    constexpr auto res17 = vec::make_vec(3*meter, 42*meter);
    std::cout << "res17=" << res17 << std::endl;
    constexpr auto res18 = vec::make_vec<11>(42*meter);
    std::cout << "res18=" << res18 << std::endl;
    constexpr auto res19 = vec::shrink<5>(res18);
    std::cout << "res19=" << res19 << std::endl;

    constexpr auto xxx1 = vec::make_vec<11>(meter*3);
    constexpr auto xxx2 = xxx1/(2 *meter);
    std::cout<<"xxx2 = "<< xxx2<<std::endl;

    /*constexpr auto xxx3 = accumulate( make_binary<Add>(), xxx2 );
    std::cout<<"xxx3 = "<< xxx3 <<std::endl;*/

    constexpr auto c3 =  vec::make_vec<100>(2*meter);;
    constexpr auto xxx4 = accumulate( make_binary<Mul>(), c3 );
    std::cout<<"xxx4 = "<< xxx4 <<std::endl;

    std::cout<<1/meter<<std::endl;
   // std::cout<<"vec "<<v[1]<<" res2="<<res2[1]<<std::endl;

    //constexpr auto res3 = for_each(make_unary(Fill{},42), res2);



}

