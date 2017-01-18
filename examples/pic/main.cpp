#include <iostream>
#include <tuple>
#include <typeinfo>

#include "phys/units/quantity.hpp"
#include "phys/units/quantity_io.hpp"

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

    constexpr auto y = Test::mySpeed;
    std::cout<<"test="<<y<<std::endl;

    constexpr auto g = 10._g * newton * meter;
   //g.to(unit_time).to(unit_time).to(unit_length)
    //static_assert( std::get<2>(g.dimension()) == -2, "nonono");
    std::cout<<typeid(g.to(pic::meter)).name()<<" ---gg="<<g<<std::endl;

    constexpr auto xx = speed.to( unit_speed )*unit_speed;
    //constexpr auto yy = square( xx );
    //auto x = make_quantity( speed ); //.to(kilo*meter/second) );
    std::cout << "speed km = " <<  g * meter<< std::endl;
    std::cout << "wave = " << speed.to(unit_speed)<< std::endl;
    static_assert( speed.to(unit_speed).magnitude() == 1.0, "hhhh");

    constexpr auto delta_t = 1.79e-16 * second;



    constexpr auto cellSize =  std::make_tuple(
        wavelength,
        0.1772e-6 * meter,
        0.1772e-6 * meter
    );


}
