/**
 * \file other_units.hpp
 *
 * \brief   Units not approved for use with SI.
 * \author  Michael S. Kenniston
 * \date    16 July 2001
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
 * This file contains the definitions of units that are *NOT* approved
 * for use with SI, as specified by SP811.  These units should not
 * be used with any new work.  However, they may be needed for
 * handling and converting legacy data.
 */

#ifndef PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED
#define PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED

#include "phys/units/quantity.hpp"

namespace phys { namespace units {

constexpr auto abampere           { Rep( 1e+1L ) * ampere };
constexpr auto abcoulomb          { Rep( 1e+1L ) * coulomb };
constexpr auto abfarad            { Rep( 1e+9L ) * farad };
constexpr auto abhenry            { Rep( 1e-9L ) * henry };
constexpr auto abmho              { Rep( 1e+9L ) * siemens };
constexpr auto abohm              { Rep( 1e-9L ) * ohm };
constexpr auto abvolt             { Rep( 1e-8L ) * volt };
constexpr auto acre               { Rep( 4.046873e+3L ) * square( meter ) };
constexpr auto acre_foot          { Rep( 1.233489e+3L ) * cube( meter ) };
constexpr auto astronomical_unit  { Rep( 1.495979e+11L ) * meter };
constexpr auto atmosphere_std     { Rep( 1.01325e+5L ) * pascal };
constexpr auto atmosphere_tech    { Rep( 9.80665e+4L ) * pascal };

constexpr auto barrel             { Rep( 1.589873e-1L ) * cube( meter ) };
constexpr auto biot               { Rep( 1e+1L ) * ampere };
constexpr auto btu                { Rep( 1.05587e+3L ) * joule };
constexpr auto btu_it             { Rep( 1.055056e+3L ) * joule };
constexpr auto btu_th             { Rep( 1.054350e+3L ) * joule };
constexpr auto btu_39F            { Rep( 1.05967e+3L ) * joule };
constexpr auto btu_59F            { Rep( 1.05480e+3L ) * joule };
constexpr auto btu_60F            { Rep( 1.05468e+3L ) * joule };
constexpr auto bushel             { Rep( 3.523907e-2L ) * cube( meter ) };

constexpr auto calorie            { Rep( 4.19002L ) * joule };
constexpr auto calorie_it         { Rep( 4.1868L ) * joule };
constexpr auto calorie_th         { Rep( 4.184L ) * joule };
constexpr auto calorie_15C        { Rep( 4.18580L ) * joule };
constexpr auto calorie_20C        { Rep( 4.18190L ) * joule };
constexpr auto carat_metric       { Rep( 2e-4L ) * kilogram };
constexpr auto chain              { Rep( 2.011684e+1L ) * meter };
constexpr auto clo                { Rep( 1.55e-1L ) * square( meter ) * kelvin / watt };
constexpr auto cm_mercury         { Rep( 1.333224e+3L ) * pascal };
constexpr auto cord               { Rep( 3.624556L ) * cube( meter ) };
constexpr auto cup                { Rep( 2.365882e-4L ) * cube( meter ) };

constexpr auto darcy              { Rep( 9.869233e-13L ) * square( meter ) };
constexpr auto day_sidereal       { Rep( 8.616409e+4L ) * second };
constexpr auto debye              { Rep( 3.335641e-30L ) * coulomb * meter };
constexpr auto degree_fahrenheit{ Rep( 5.555556e-1L ) * kelvin };
constexpr auto degree_rankine   { Rep( 5.555556e-1L ) * kelvin };
constexpr auto denier             { Rep( 1.111111e-7L ) * kilogram / meter };
constexpr auto dyne               { Rep( 1e-5L ) * newton };

constexpr auto erg                { Rep( 1e-7L ) * joule };

constexpr auto faraday            { Rep( 9.648531e+4L ) * coulomb };
constexpr auto fathom             { Rep( 1.828804L ) * meter };
constexpr auto fermi              { Rep( 1e-15L ) * meter };
constexpr auto foot               { Rep( 3.048e-1L ) * meter };
constexpr auto foot_pound_force   { Rep( 1.355818L ) * joule };
constexpr auto foot_poundal       { Rep( 4.214011e-2L ) * joule };
constexpr auto foot_us_survey     { Rep( 3.048006e-1L ) * meter };
constexpr auto footcandle         { Rep( 1.076391e+1L ) * lux };
constexpr auto footlambert        { Rep( 3.426259L ) * candela / square( meter ) };
constexpr auto fortnight          { Rep( 14 ) * day }; // from OED
constexpr auto franklin           { Rep( 3.335641e-10L ) * coulomb };
constexpr auto furlong            { Rep( 2.01168e+2L ) * meter }; // from OED

constexpr auto gallon_imperial    { Rep( 4.54609e-3L ) * cube( meter ) };
constexpr auto gallon_us          { Rep( 3.785412e-3L ) * cube( meter ) };
constexpr auto gamma              { Rep( 1e-9L ) * tesla };
constexpr auto gamma_mass         { Rep( 1e-9L ) * kilogram };
constexpr auto gauss              { Rep( 1e-4L ) * tesla };
constexpr auto gilbert            { Rep( 7.957747e-1L ) * ampere };
constexpr auto gill_imperial      { Rep( 1.420653e-4L ) * cube( meter ) };
constexpr auto gill_us            { Rep( 1.182941e-4L ) * cube( meter ) };
constexpr Rep                                gon                { Rep( 9e-1L ) * degree_angle };
constexpr auto grain              { Rep( 6.479891e-5L ) * kilogram };

constexpr auto horsepower         { Rep( 7.456999e+2L ) * watt };
constexpr auto horsepower_boiler  { Rep( 9.80950e+3L ) * watt };
constexpr auto horsepower_electric{ Rep( 7.46e+2L ) * watt };
constexpr auto horsepower_metric  { Rep( 7.354988e+2L ) * watt };
constexpr auto horsepower_uk      { Rep( 7.4570e+2L ) * watt };
constexpr auto horsepower_water   { Rep( 7.46043e+2L ) * watt };
constexpr auto hour_sidereal      { Rep( 3.590170e+3L ) * second };
constexpr auto hundredweight_long { Rep( 5.080235e+1L ) * kilogram };
constexpr auto hundredweight_short{ Rep( 4.535924e+1L ) * kilogram };

constexpr auto inch               { Rep( 2.54e-2L ) * meter };
constexpr auto inches_mercury     { Rep( 3.386389e+3L ) * pascal };

constexpr auto kayser             { Rep( 1e+2 ) / meter };
constexpr auto kilogram_force     { Rep( 9.80665 ) * newton };
constexpr auto kilopond           { Rep( 9.80665 ) * newton };
constexpr auto kip                { Rep( 4.448222e+3L ) * newton };

constexpr auto lambda_volume      { Rep( 1e-9L ) * cube( meter ) };
constexpr auto lambert            { Rep( 3.183099e+3L ) * candela / square( meter ) };
constexpr auto langley            { Rep( 4.184e+4L ) * joule / square( meter ) };
constexpr auto light_year         { Rep( 9.46073e+15L ) * meter };

constexpr auto maxwell            { Rep( 1e-8L ) * weber };
constexpr auto mho                { siemens };
constexpr auto micron             { micro * meter };
constexpr auto mil                { Rep( 2.54e-5L ) * meter };
constexpr Rep                                mil_angle          { Rep( 5.625e-2L ) * degree_angle };
constexpr auto mil_circular       { Rep( 5.067075e-10L ) * square( meter ) };
constexpr auto mile               { Rep( 1.609344e+3L ) * meter };
constexpr auto mile_us_survey     { Rep( 1.609347e+3L ) * meter };
constexpr auto minute_sidereal    { Rep( 5.983617e+1L ) * second };

constexpr auto oersted            { Rep( 7.957747e+1L ) * ampere / meter };
constexpr auto ounce_avdp         { Rep( 2.834952e-2L ) * kilogram };
constexpr auto ounce_fluid_imperial{ Rep( 2.841306e-5L ) * cube( meter ) };
constexpr auto ounce_fluid_us     { Rep( 2.957353e-5L ) * cube( meter ) };
constexpr auto ounce_force        { Rep( 2.780139e-1L ) * newton };
constexpr auto ounce_troy         { Rep( 3.110348e-2L ) * kilogram };

constexpr auto parsec             { Rep( 3.085678e+16L ) * meter };
constexpr auto peck               { Rep( 8.809768e-3L ) * cube( meter ) };
constexpr auto pennyweight        { Rep( 1.555174e-3L ) * kilogram };
constexpr auto perm_0C            { Rep( 5.72135e-11L ) * kilogram / pascal / second / square( meter ) };
constexpr auto perm_23C           { Rep( 5.74525e-11L ) * kilogram / pascal / second / square( meter ) };
constexpr auto phot               { Rep( 1e+4L ) * lux };
constexpr auto pica_computer      { Rep( 4.233333e-3L ) * meter };
constexpr auto pica_printers      { Rep( 4.217518e-3L ) * meter };
constexpr auto pint_dry           { Rep( 5.506105e-4L ) * cube( meter ) };
constexpr auto pint_liquid        { Rep( 4.731765e-4L ) * cube( meter ) };
constexpr auto point_computer     { Rep( 3.527778e-4L ) * meter };
constexpr auto point_printers     { Rep( 3.514598e-4L ) * meter };
constexpr auto poise              { Rep( 1e-1L ) * pascal * second };
constexpr auto pound_avdp         { Rep( 4.5359237e-1L ) * kilogram };
constexpr auto pound_force        { Rep( 4.448222L ) * newton };
constexpr auto pound_troy         { Rep( 3.732417e-1L ) * kilogram };
constexpr auto poundal            { Rep( 1.382550e-1L ) * newton };
constexpr auto psi                { Rep( 6.894757e+3L ) * pascal };

constexpr auto quad               { Rep( 1e+15L ) * btu_it };
constexpr auto quart_dry          { Rep( 1.101221e-3L ) * cube( meter ) };
constexpr auto quart_liquid       { Rep( 9.463529e-4L ) * cube( meter ) };

constexpr Rep                                revolution         { Rep( 2 ) * pi };
constexpr auto rhe                { Rep( 1e+1L ) / pascal / second };
constexpr auto rod                { Rep( 5.029210L ) * meter };
constexpr auto rpm                { Rep( 1.047198e-1L ) / second };

constexpr auto second_sidereal    { Rep( 9.972696e-1L ) * second };
constexpr auto shake              { Rep( 1e-8L ) * second };
constexpr auto slug               { Rep( 1.459390e+1L ) * kilogram };
constexpr auto statampere         { Rep( 3.335641e-10L ) * ampere };
constexpr auto statcoulomb        { Rep( 3.335641e-10L ) * coulomb };
constexpr auto statfarad          { Rep( 1.112650e-12L ) * farad };
constexpr auto stathenry          { Rep( 8.987552e+11L ) * henry };
constexpr auto statmho            { Rep( 1.112650e-12L ) * siemens };
constexpr auto statohm            { Rep( 8.987552e+11L ) * ohm };
constexpr auto statvolt           { Rep( 2.997925e+2L ) * volt };
constexpr auto stere              { cube( meter ) };
constexpr auto stilb              { Rep( 1e+4L ) * candela / square( meter ) };
constexpr auto stokes             { Rep( 1e-4L ) * square( meter ) / second };

constexpr auto tablespoon         { Rep( 1.478676e-5L ) * cube( meter ) };
constexpr auto teaspoon           { Rep( 4.928922e-6L ) * cube( meter ) };
constexpr auto tex                { Rep( 1e-6L ) * kilogram / meter };
constexpr auto therm_ec           { Rep( 1.05506e+8L ) * joule };
constexpr auto therm_us           { Rep( 1.054804e+8L ) * joule };
constexpr auto ton_assay          { Rep( 2.916667e-2L ) * kilogram };
constexpr auto ton_force          { Rep( 8.896443e+3L ) * newton };
constexpr auto ton_long           { Rep( 1.016047e+3L ) * kilogram };
constexpr auto ton_refrigeration  { Rep( 3.516853e+3L ) * watt };
constexpr auto ton_register       { Rep( 2.831685L ) * cube( meter ) };
constexpr auto ton_short          { Rep( 9.071847e+2L ) * kilogram };
constexpr auto ton_tnt            { Rep( 4.184e+9L ) * joule };
constexpr auto torr               { Rep( 1.333224e+2L ) * pascal };

constexpr auto unit_pole          { Rep( 1.256637e-7L ) * weber };

constexpr auto week               { Rep( 604800L ) * second }; // 7 days

constexpr auto x_unit             { Rep( 1.002e-13L ) * meter };

constexpr auto yard               { Rep( 9.144e-1L ) * meter };
constexpr auto year_sidereal      { Rep( 3.155815e+7L ) * second };
constexpr auto year_std           { Rep( 3.1536e+7L ) * second }; // 365 days
constexpr auto year_tropical      { Rep( 3.155693e+7L ) * second };

}} // namespace phys::units

#endif // PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED

/*
 * end of file
 */
