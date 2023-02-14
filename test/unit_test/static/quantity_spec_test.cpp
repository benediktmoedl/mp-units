// The MIT License (MIT)
//
// Copyright (c) 2018 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "test_tools.h"
#include <mp_units/quantity.h>
#include <mp_units/quantity_spec.h>
#include <mp_units/reference.h>
#include <mp_units/unit.h>

namespace {

using namespace mp_units;

using dimensionless_ = struct dimensionless;
using dim_one_ = struct dimension_one;

// clang-format off
inline constexpr struct dim_length_ : base_dimension<"L"> {} dim_length;
inline constexpr struct dim_mass_ : base_dimension<"M"> {} dim_mass;
inline constexpr struct dim_time_ : base_dimension<"T"> {} dim_time;

// quantities specification
QUANTITY_SPEC_(length, dim_length);
QUANTITY_SPEC_(mass, dim_mass);
QUANTITY_SPEC_(time, dim_time);

inline constexpr struct second_ : named_unit<"s", kind_of<time>> {} second;

QUANTITY_SPEC_(height, length);
QUANTITY_SPEC_(width, length);
QUANTITY_SPEC_(path_length, length);
QUANTITY_SPEC_(distance, path_length);
QUANTITY_SPEC_(position_vector, length, quantity_character::vector);
QUANTITY_SPEC_(period_duration, time);

QUANTITY_SPEC_(frequency, 1 / period_duration);
QUANTITY_SPEC_(activity, 1 / time);
QUANTITY_SPEC_(area, pow<2>(length));
QUANTITY_SPEC_(volume, area * length);
QUANTITY_SPEC_(speed, distance / time);
QUANTITY_SPEC_(velocity, speed, position_vector / time);
QUANTITY_SPEC_(rate_of_climb, speed, height / time);
QUANTITY_SPEC_(acceleration, velocity / time);
QUANTITY_SPEC_(acceleration_of_free_fall, acceleration);
QUANTITY_SPEC_(force, mass * acceleration);
QUANTITY_SPEC_(weight, force, mass * acceleration_of_free_fall);
QUANTITY_SPEC_(moment_of_force, position_vector* force);
QUANTITY_SPEC_(torque, moment_of_force, quantity_character::scalar);
QUANTITY_SPEC_(pressure, force / area, quantity_character::scalar);
QUANTITY_SPEC_(stress, pressure, quantity_character::tensor);
QUANTITY_SPEC_(strain, dimensionless, quantity_character::tensor);
QUANTITY_SPEC_(power, force* velocity, quantity_character::scalar);
QUANTITY_SPEC_(efficiency, power / power);
QUANTITY_SPEC_(energy, force * length);
QUANTITY_SPEC_(mechanical_energy, energy);
QUANTITY_SPEC_(potential_energy, mechanical_energy);
QUANTITY_SPEC_(gravitational_potential_energy, potential_energy, mass * acceleration_of_free_fall / height);
QUANTITY_SPEC_(kinetic_energy, mechanical_energy, mass* pow<2>(speed));
// clang-format on

// concepts verification
static_assert(QuantitySpec<length_>);
static_assert(BaseQuantitySpec<length_>);
static_assert(detail::NamedQuantitySpec<length_>);
static_assert(!detail::IntermediateDerivedQuantitySpec<length_>);
static_assert(!QuantityKindSpec<length_>);

static_assert(QuantitySpec<frequency_>);
static_assert(!BaseQuantitySpec<frequency_>);
static_assert(detail::NamedQuantitySpec<frequency_>);
static_assert(!detail::IntermediateDerivedQuantitySpec<frequency_>);
static_assert(!QuantityKindSpec<frequency_>);

static_assert(QuantitySpec<decltype(1 / time)>);
static_assert(!BaseQuantitySpec<decltype(1 / time)>);
static_assert(!detail::NamedQuantitySpec<decltype(1 / time)>);
static_assert(detail::IntermediateDerivedQuantitySpec<decltype(1 / time)>);
static_assert(!QuantityKindSpec<decltype(1 / time)>);

static_assert(QuantitySpec<dimensionless_>);
static_assert(!BaseQuantitySpec<dimensionless_>);
static_assert(detail::NamedQuantitySpec<dimensionless_>);
static_assert(!detail::IntermediateDerivedQuantitySpec<dimensionless_>);
static_assert(!QuantityKindSpec<dimensionless_>);

static_assert(QuantitySpec<kind_of_<length>>);
static_assert(BaseQuantitySpec<kind_of_<length>>);
static_assert(detail::NamedQuantitySpec<kind_of_<length>>);
static_assert(!detail::IntermediateDerivedQuantitySpec<kind_of_<length>>);
static_assert(QuantityKindSpec<kind_of_<length>>);

static_assert(QuantitySpec<frequency_>);
static_assert(!BaseQuantitySpec<frequency_>);
static_assert(detail::NamedQuantitySpec<frequency_>);
static_assert(!detail::IntermediateDerivedQuantitySpec<frequency_>);
static_assert(!QuantityKindSpec<frequency_>);

static_assert(QuantitySpec<decltype(1 / time)>);
static_assert(!BaseQuantitySpec<decltype(1 / time)>);
static_assert(!detail::NamedQuantitySpec<decltype(1 / time)>);
static_assert(detail::IntermediateDerivedQuantitySpec<decltype(1 / time)>);
static_assert(!QuantityKindSpec<decltype(1 / time)>);

static_assert(QuantitySpec<decltype(kind_of<length> / kind_of<time>)>);
static_assert(!BaseQuantitySpec<decltype(kind_of<length> / kind_of<time>)>);
static_assert(detail::NamedQuantitySpec<decltype(kind_of<length> / kind_of<time>)>);
static_assert(!detail::IntermediateDerivedQuantitySpec<decltype(kind_of<length> / kind_of<time>)>);
static_assert(QuantityKindSpec<decltype(kind_of<length> / kind_of<time>)>);

static_assert(QuantitySpec<decltype(kind_of<length> * kind_of<time>)>);
static_assert(!BaseQuantitySpec<decltype(kind_of<length> * kind_of<time>)>);
static_assert(detail::NamedQuantitySpec<decltype(kind_of<length> * kind_of<time>)>);
static_assert(!detail::IntermediateDerivedQuantitySpec<decltype(kind_of<length> * kind_of<time>)>);
static_assert(QuantityKindSpec<decltype(kind_of<length> * kind_of<time>)>);

// dimensionless
static_assert(QuantitySpec<dimensionless_>);
static_assert(!BaseQuantitySpec<dimensionless_>);
static_assert(detail::NamedQuantitySpec<dimensionless_>);
static_assert(!detail::IntermediateDerivedQuantitySpec<dimensionless_>);
static_assert(!QuantityKindSpec<dimensionless_>);

static_assert(QuantitySpec<decltype(length / length)>);
static_assert(!BaseQuantitySpec<decltype(length / length)>);
static_assert(detail::NamedQuantitySpec<decltype(length / length)>);
static_assert(!detail::IntermediateDerivedQuantitySpec<decltype(length / length)>);
static_assert(!QuantityKindSpec<decltype(length / length)>);

static_assert(QuantitySpec<decltype(width / length)>);
static_assert(!BaseQuantitySpec<decltype(width / length)>);
static_assert(!detail::NamedQuantitySpec<decltype(width / length)>);
static_assert(detail::IntermediateDerivedQuantitySpec<decltype(width / length)>);
static_assert(!QuantityKindSpec<decltype(width / length)>);

static_assert(QuantitySpec<decltype(kind_of<length> / kind_of<length>)>);
static_assert(!BaseQuantitySpec<decltype(kind_of<length> / kind_of<length>)>);
static_assert(detail::NamedQuantitySpec<decltype(kind_of<length> / kind_of<length>)>);
static_assert(!detail::IntermediateDerivedQuantitySpec<decltype(kind_of<length> / kind_of<length>)>);
static_assert(QuantityKindSpec<decltype(kind_of<length> / kind_of<length>)>);

static_assert(QuantitySpec<decltype(kind_of<length> / length)>);
static_assert(!BaseQuantitySpec<decltype(kind_of<length> / length)>);
static_assert(detail::NamedQuantitySpec<decltype(kind_of<length> / length)>);
static_assert(!detail::IntermediateDerivedQuantitySpec<decltype(kind_of<length> / length)>);
static_assert(!QuantityKindSpec<decltype(kind_of<length> / length)>);

static_assert(QuantitySpec<decltype(length / kind_of<length>)>);
static_assert(!BaseQuantitySpec<decltype(length / kind_of<length>)>);
static_assert(detail::NamedQuantitySpec<decltype(length / kind_of<length>)>);
static_assert(!detail::IntermediateDerivedQuantitySpec<decltype(length / kind_of<length>)>);
static_assert(!QuantityKindSpec<decltype(length / kind_of<length>)>);

static_assert(QuantitySpec<decltype(width / kind_of<length>)>);
static_assert(!BaseQuantitySpec<decltype(width / kind_of<length>)>);
static_assert(!detail::NamedQuantitySpec<decltype(width / kind_of<length>)>);
static_assert(detail::IntermediateDerivedQuantitySpec<decltype(width / kind_of<length>)>);
static_assert(!QuantityKindSpec<decltype(width / kind_of<length>)>);

// length
static_assert(QuantitySpec<decltype(speed * time)>);
static_assert(!BaseQuantitySpec<decltype(speed * time)>);
static_assert(!detail::NamedQuantitySpec<decltype(speed * time)>);
static_assert(detail::IntermediateDerivedQuantitySpec<decltype(speed * time)>);

// derived QuantitySpec expression template syntax verification
static_assert(!detail::NamedQuantitySpec<decltype(speed * time)>);
static_assert(detail::IntermediateDerivedQuantitySpec<decltype(speed * time)>);

static_assert(is_of_type<dimensionless * time, time_>);
static_assert(is_of_type<time * dimensionless, time_>);
static_assert(is_of_type<dimensionless * (1 / time), derived_quantity_spec<dimensionless_, per<time_>>>);
static_assert(is_of_type<1 / time * dimensionless, derived_quantity_spec<dimensionless_, per<time_>>>);

static_assert(is_of_type<length / length, dimensionless_>);
static_assert(is_of_type<pow<2>(length / length), dimensionless_>);
static_assert(is_of_type<pow<2>(length) / pow<2>(length), dimensionless_>);

static_assert(is_of_type<pow<2>(length) / length, length_>);
static_assert(is_of_type<length / pow<2>(length), derived_quantity_spec<dimensionless_, per<length_>>>);

static_assert(is_of_type<length * time, derived_quantity_spec<length_, time_>>);
static_assert(is_of_type<length * length, derived_quantity_spec<mp_units::power<length_, 2>>>);

static_assert(is_of_type<length * length * time, derived_quantity_spec<mp_units::power<length_, 2>, time_>>);
static_assert(is_of_type<length * time * length, derived_quantity_spec<mp_units::power<length_, 2>, time_>>);

static_assert(is_of_type<length*(time* length), derived_quantity_spec<mp_units::power<length_, 2>, time_>>);
static_assert(is_of_type<time*(length* length), derived_quantity_spec<mp_units::power<length_, 2>, time_>>);

static_assert(is_of_type<1 / time * length, derived_quantity_spec<length_, per<time_>>>);
static_assert(is_of_type<length * (1 / time), derived_quantity_spec<length_, per<time_>>>);
static_assert(is_of_type<1 / time * time, dimensionless_>);

static_assert(is_of_type<1 / length / (1 / width), derived_quantity_spec<width_, per<length_>>>);
static_assert(is_of_type<dimensionless / (time / length), derived_quantity_spec<length_, per<time_>>>);

static_assert(is_of_type<time / dimensionless, time_>);
static_assert(is_of_type<1 / time / dimensionless, derived_quantity_spec<dimensionless_, per<time_>>>);

static_assert(is_of_type<length / time * time, length_>);
static_assert(is_of_type<1 / time * (1 / time), derived_quantity_spec<dimensionless_, per<mp_units::power<time_, 2>>>>);
static_assert(is_of_type<1 / (time * time), derived_quantity_spec<dimensionless_, per<mp_units::power<time_, 2>>>>);
static_assert(is_of_type<1 / (1 / (time * time)), derived_quantity_spec<mp_units::power<time_, 2>>>);

static_assert(is_of_type<length / time * (1 / time), derived_quantity_spec<length_, per<mp_units::power<time_, 2>>>>);
static_assert(is_of_type<length / time*(length / time),
                         derived_quantity_spec<mp_units::power<length_, 2>, per<mp_units::power<time_, 2>>>>);
static_assert(is_of_type<length / time*(time / length), dimensionless_>);

static_assert(is_of_type<speed / acceleration, derived_quantity_spec<speed_, per<acceleration_>>>);
static_assert(is_of_type<(speed / acceleration).dimension, dim_time_>);
static_assert(is_of_type<acceleration / speed, derived_quantity_spec<acceleration_, per<speed_>>>);
static_assert(is_of_type<(acceleration / speed).dimension, derived_dimension<dim_one_, per<dim_time_>>>);
static_assert(is_of_type<speed * speed / length, derived_quantity_spec<mp_units::power<speed_, 2>, per<length_>>>);
static_assert(
  is_of_type<(speed * speed / length).dimension, derived_dimension<dim_length_, per<mp_units::power<dim_time_, 2>>>>);
static_assert(
  is_of_type<1 / (speed * speed) * length, derived_quantity_spec<length_, per<mp_units::power<speed_, 2>>>>);
static_assert(is_of_type<(1 / (speed * speed) * length).dimension,
                         derived_dimension<mp_units::power<dim_time_, 2>, per<dim_length_>>>);

static_assert(is_of_type<(length * length) * (time * time),
                         derived_quantity_spec<mp_units::power<length_, 2>, mp_units::power<time_, 2>>>);
static_assert(is_of_type<(time * time) * (length * length),
                         derived_quantity_spec<mp_units::power<length_, 2>, mp_units::power<time_, 2>>>);

static_assert(is_of_type<length * time * time, derived_quantity_spec<length_, mp_units::power<time_, 2>>>);
static_assert(
  is_of_type<mass / length / time / time, derived_quantity_spec<mass_, per<length_, mp_units::power<time_, 2>>>>);
static_assert(
  is_of_type<mass / (length * time * time), derived_quantity_spec<mass_, per<length_, mp_units::power<time_, 2>>>>);
static_assert(
  is_of_type<mass / length / (time * time), derived_quantity_spec<mass_, per<length_, mp_units::power<time_, 2>>>>);

static_assert(is_of_type<force / area, derived_quantity_spec<force_, per<area_>>>);
static_assert(
  is_of_type<(force / area).dimension, derived_dimension<dim_mass_, per<dim_length_, mp_units::power<dim_time_, 2>>>>);

static_assert(is_of_type<mass * acceleration, derived_quantity_spec<acceleration_, mass_>>);
static_assert(is_of_type<(mass * acceleration).dimension,
                         derived_dimension<dim_length_, dim_mass_, per<mp_units::power<dim_time_, 2>>>>);
static_assert(is_of_type<acceleration * mass, derived_quantity_spec<acceleration_, mass_>>);
static_assert(is_of_type<(acceleration * mass).dimension,
                         derived_dimension<dim_length_, dim_mass_, per<mp_units::power<dim_time_, 2>>>>);

// power
static_assert(is_of_type<pow<2>(length), derived_quantity_spec<mp_units::power<length_, 2>>>);
static_assert(is_of_type<pow<1, 2>(length), derived_quantity_spec<mp_units::power<length_, 1, 2>>>);
static_assert(is_of_type<pow<1, 2>(length* length), length_>);
static_assert(is_of_type<pow<1, 3>(length* length* length), length_>);
static_assert(is_of_type<pow<1, 3>(length* length), derived_quantity_spec<mp_units::power<length_, 2, 3>>>);
static_assert(is_of_type<pow<1, 2>(length / time),
                         derived_quantity_spec<mp_units::power<length_, 1, 2>, per<mp_units::power<time_, 1, 2>>>>);
static_assert(
  is_of_type<pow<1, 2>(length / (time * time)), derived_quantity_spec<mp_units::power<length_, 1, 2>, per<time_>>>);

static_assert(is_same_v<decltype(pow<2>(length)), decltype(length * length)>);
static_assert(is_same_v<decltype(pow<2>(length / time)), decltype(length * length / time / time)>);

template<auto& t>
concept invalid_operations = requires {
  requires !requires { t < t; };
  requires !requires { t / 2; };
  requires !requires { 2 * t; };
  requires !requires { t * 2; };
  requires !requires { t + 2; };
  requires !requires { 2 + t; };
  requires !requires { t + t; };
  requires !requires { t - 2; };
  requires !requires { 2 - t; };
  requires !requires { t - t; };
  requires !requires { t == 2; };
  requires !requires { 2 == t; };
  requires !requires { t < 2; };
  requires !requires { 2 < t; };
  requires !requires { t + time[second]; };
  requires !requires { t - time[second]; };
  requires !requires { t* time[second]; };
  requires !requires { t / time[second]; };
  requires !requires { t == time[second]; };
  requires !requires { t < time[second]; };
  requires !requires { time[second] + t; };
  requires !requires { time[second] - t; };
  requires !requires { time[second] * t; };
  requires !requires { time[second] / t; };
  requires !requires { time[second] == t; };
  requires !requires { time[second] < t; };
  requires !requires { t + 1 * time[second]; };
  requires !requires { t - 1 * time[second]; };
  requires !requires { t * 1 * time[second]; };
  requires !requires { t / 1 * time[second]; };
  requires !requires { t == 1 * time[second]; };
  requires !requires { t == 1 * time[second]; };
  requires !requires { 1 * time[second] + t; };
  requires !requires { 1 * time[second] - t; };
  requires !requires { 1 * time[second] * t; };
  requires !requires { 1 * time[second] == t; };
  requires !requires { 1 * time[second] < t; };
};
static_assert(invalid_operations<time>);

// comparisons
static_assert(mass * acceleration == acceleration * mass);
static_assert(length / length == width / width);
static_assert(length / length == time / time);
static_assert(length * time / time == length);
// static_assert(length * time / period_duration == time);
// static_assert(length * height / width == length);

static_assert(length != time);
static_assert(length != width);
static_assert(acceleration != speed);

static_assert(frequency != activity);
static_assert(efficiency != strain);
static_assert(dimensionless != efficiency);
static_assert(power / power != efficiency);
static_assert(stress / stress != strain);
static_assert(stress / stress != efficiency);

static_assert(rate_of_climb != speed);
static_assert(rate_of_climb != distance / time);
static_assert(rate_of_climb != length / time);

static_assert(velocity != speed);
static_assert(energy != torque);

static_assert(1 / time != frequency);
static_assert(1 / frequency != time);
static_assert(frequency * time != dimensionless);
static_assert(length * length != area);
static_assert(length * length != volume);
static_assert(area / length != length);
static_assert(length * length * length != volume);
static_assert(area * length != volume);
static_assert(volume / length != area);
static_assert(volume / length / length != length);
static_assert(area * area / length != volume);
static_assert(area * (area / length) != volume);
static_assert(volume / (length * length) != length);
static_assert(force * length != energy);
static_assert(force * length != torque);
static_assert(force * position_vector != energy);
static_assert(force * position_vector != torque);
static_assert(length / time != speed);
static_assert(position_vector / time != speed);
static_assert(length / time != velocity);
static_assert(position_vector / time != velocity);

static_assert(length * time != speed);
static_assert(length / time / time != speed);
static_assert(length / speed != time);
static_assert(speed * time != length);

static_assert(length / time / time != acceleration);
static_assert(position_vector / time / time != acceleration);
static_assert(position_vector / (time * time) != acceleration);
static_assert(velocity / time != acceleration);
static_assert(velocity / acceleration != time);
static_assert(acceleration * time != velocity);
static_assert(acceleration * (time * time) != position_vector);
static_assert(acceleration / speed != frequency);

// get_kind
static_assert(get_kind(length) == length);
static_assert(get_kind(distance) == length);
static_assert(get_kind(time) == time);
static_assert(get_kind(period_duration) == time);
static_assert(get_kind(length / time) == length / time);
static_assert(get_kind(speed) == speed);
static_assert(get_kind(height / time) == length / time);
static_assert(get_kind(1 / time) == 1 / time);
static_assert(get_kind(1 / period_duration) == 1 / time);
static_assert(get_kind(frequency) == frequency);
static_assert(get_kind(mass * frequency) == mass * frequency);
static_assert(get_kind(moment_of_force) == moment_of_force);
static_assert(get_kind(energy) == energy);
static_assert(get_kind(potential_energy) == energy);
static_assert(get_kind(kinetic_energy) == energy);

// comparisons of the same dimensions
static_assert(length == length);
static_assert(speed == speed);

// comparisons of equivalent dimensions (named vs unnamed/derived)
static_assert(length / length == dimensionless);

// get_complexity
static_assert(detail::get_complexity(dimensionless) == 1);
static_assert(detail::get_complexity(length) == 1);
static_assert(detail::get_complexity(frequency) == 2);
static_assert(detail::get_complexity(area) == 3);
static_assert(detail::get_complexity(volume) == 5);
static_assert(detail::get_complexity(speed) == 3);
static_assert(detail::get_complexity(velocity) == 3);
static_assert(detail::get_complexity(acceleration) == 5);
static_assert(detail::get_complexity(force) == 7);

static_assert(detail::get_complexity(acceleration * time) == 6);
static_assert(detail::get_complexity(acceleration / time) == 6);

// TODO complexity for integrated types (1/2)


// explode
static_assert(detail::explode<detail::get_complexity(velocity)>(acceleration * time) == velocity);
static_assert(detail::explode<detail::get_complexity(area)>(volume / length) == area);
static_assert(detail::explode<detail::get_complexity(area)>(volume / height) == area * length / height);
static_assert(detail::explode<detail::get_complexity(area)>(pow<3>(length) / height) == pow<3>(length) / height);
static_assert(detail::explode<detail::get_complexity(area)>(area * time / period_duration) ==
              area * time / period_duration);
static_assert(detail::explode<detail::get_complexity(area)>(pow<2>(length) * time / period_duration) ==
              pow<2>(length) * time / period_duration);

using namespace detail;
using enum convertible_to_result;

// different dimensions
static_assert(convertible_to_impl(mass, length) == no);
static_assert(convertible_to_impl(speed, length) == no);
static_assert(convertible_to_impl(length, speed) == no);
static_assert(convertible_to_impl(energy, speed) == no);
static_assert(convertible_to_impl(length, kind_of<time>) == no);
static_assert(convertible_to_impl(kind_of<time>, length) == no);
static_assert(convertible_to_impl(energy, kind_of<speed>) == no);
static_assert(convertible_to_impl(kind_of<speed>, energy) == no);

// the same types
static_assert(convertible_to_impl(length, length) == yes);
static_assert(convertible_to_impl(width, width) == yes);
static_assert(convertible_to_impl(energy, energy) == yes);
static_assert(convertible_to_impl(kind_of<length>, kind_of<length>) == yes);
static_assert(convertible_to_impl(kind_of<energy>, kind_of<energy>) == yes);
static_assert(convertible_to_impl(kind_of<get_kind(moment_of_force)>, kind_of<get_kind(moment_of_force)>) == yes);

// converting to a different branch
static_assert(convertible_to_impl(height, width) == cast);
static_assert(convertible_to_impl(potential_energy, kinetic_energy) == cast);
static_assert(convertible_to_impl(kinetic_energy, potential_energy) == cast);
static_assert(convertible_to_impl(rate_of_climb, velocity) == cast);

// converting to a different kind
static_assert(convertible_to_impl(frequency, activity) == no);
static_assert(convertible_to_impl(activity, frequency) == no);
static_assert(convertible_to_impl(energy, moment_of_force) == no);
static_assert(convertible_to_impl(energy, torque) == no);

// upcasting same hierarchy branch
static_assert(convertible_to_impl(width, length) == yes);
static_assert(convertible_to_impl(path_length, length) == yes);
static_assert(convertible_to_impl(distance, length) == yes);
static_assert(convertible_to_impl(distance, path_length) == yes);
static_assert(convertible_to_impl(potential_energy, energy) == yes);
static_assert(convertible_to_impl(kinetic_energy, energy) == yes);

// upcasting beyond the hierarchy/kind
static_assert(convertible_to_impl(frequency, 1 / time) == explicit_conversion);
static_assert(convertible_to_impl(speed, length / time) == explicit_conversion);
static_assert(convertible_to_impl(speed, length / time) == explicit_conversion);
static_assert(convertible_to_impl(velocity, length / time) == explicit_conversion);
static_assert(convertible_to_impl(rate_of_climb, length / time) == explicit_conversion);
static_assert(convertible_to_impl(rate_of_climb, height / time) == explicit_conversion);

// downcasting same hierarchy branch
static_assert(convertible_to_impl(length, width) == explicit_conversion);
static_assert(convertible_to_impl(path_length, distance) == explicit_conversion);
static_assert(convertible_to_impl(length, distance) == explicit_conversion);
static_assert(convertible_to_impl(path_length, distance) == explicit_conversion);
static_assert(convertible_to_impl(energy, potential_energy) == explicit_conversion);
static_assert(convertible_to_impl(energy, kinetic_energy) == explicit_conversion);

// derived quantities to type
static_assert(convertible_to_impl(1 / frequency, time) == yes);
static_assert(convertible_to_impl(1 / time, frequency) == yes);
static_assert(convertible_to_impl(length * length, area) == yes);
static_assert(convertible_to_impl(length / time, speed) == yes);
static_assert(convertible_to_impl(height / time, speed) == yes);
static_assert(convertible_to_impl(length / time, velocity) == yes);
static_assert(convertible_to_impl(position_vector / time, velocity) == yes);
static_assert(convertible_to_impl(length / time, rate_of_climb) == yes);
static_assert(convertible_to_impl(height / time, rate_of_climb) == yes);
static_assert(convertible_to_impl(area / length, length) == yes);
static_assert(convertible_to_impl(length * length * length, volume) == yes);
static_assert(convertible_to_impl(area * length, volume) == yes);
static_assert(convertible_to_impl(volume / length, area) == yes);
static_assert(convertible_to_impl(volume / area, length) == yes);
static_assert(convertible_to_impl(volume / length / length, length) == yes);
// static_assert(convertible_to_impl(area * area / length, volume) == yes);
// static_assert(convertible_to_impl(area * (area / length), volume) == yes);
static_assert(convertible_to_impl(volume / (length * length), length) == yes);
static_assert(convertible_to_impl(length / time, speed) == yes);
static_assert(convertible_to_impl(length / time, velocity) == yes);
static_assert(convertible_to_impl(position_vector / time, speed) == yes);
static_assert(convertible_to_impl(position_vector / time, velocity) == yes);
static_assert(convertible_to_impl(distance / speed, time) == yes);
// static_assert(convertible_to_impl(length / speed, time) == yes);
static_assert(convertible_to_impl(speed * time, length) == yes);
static_assert(convertible_to_impl(length / time / time, acceleration) == yes);
static_assert(convertible_to_impl(position_vector / time / time, acceleration) == yes);
static_assert(convertible_to_impl(position_vector / (time * time), acceleration) == yes);
static_assert(convertible_to_impl(velocity / time, acceleration) == yes);
static_assert(convertible_to_impl(velocity / acceleration, time) == yes);
static_assert(convertible_to_impl(acceleration * time, velocity) == yes);
static_assert(convertible_to_impl(acceleration * (time * time), position_vector) == yes);
static_assert(convertible_to_impl(acceleration / velocity, frequency) == yes);
static_assert(convertible_to_impl(force * length, energy) == yes);
static_assert(convertible_to_impl(force * position_vector, energy) == yes);
static_assert(convertible_to_impl(force * length, torque) == yes);
static_assert(convertible_to_impl(force * position_vector, torque) == yes);
static_assert(convertible_to_impl(width * height, area) == yes);

// quantities derived from dimensionless
static_assert(convertible_to_impl(power / power, efficiency) == explicit_conversion);
static_assert(convertible_to_impl(stress / stress, strain) == explicit_conversion);
static_assert(convertible_to_impl(stress / stress, efficiency) == explicit_conversion);

// derived quantities to incompatible type
// static_assert(convertible_to_impl(height / time, velocity) == cast);
// static_assert(convertible_to_impl(position_vector / time, rate_of_climb) == cast);

// type to compatible derived
static_assert(convertible_to_impl(distance, speed* time) == yes);

// type to more specialized derived quantity
// static_assert(convertible_to_impl(speed, height / time) == explicit_conversion);
// static_assert(convertible_to_impl(speed, position_vector / time) == explicit_conversion);

// type to a derived quantity on a different branch
// static_assert(convertible_to_impl(velocity, height / time) == cast);
// static_assert(convertible_to_impl(rate_of_climb, position_vector / time) == cast);

// derived quantities requiring explosion to a type
static_assert(convertible_to_impl(acceleration * time, velocity) == yes);
static_assert(convertible_to_impl(acceleration * period_duration, velocity) == yes);
static_assert(convertible_to_impl(velocity * time / period_duration, velocity) == yes);
static_assert(convertible_to_impl(mass * acceleration_of_free_fall * height / weight, height) == yes);

// derived quantities to more generic derived compatible type
static_assert(convertible_to_impl(1 / (width * height), 1 / area) == yes);
static_assert(convertible_to_impl(path_length * distance, pow<2>(path_length)) == yes);

// derived to compatible derived
static_assert(convertible_to_impl(1 / (length * length), 1 / area) == yes);
static_assert(convertible_to_impl(velocity * time, acceleration* pow<2>(time)) == yes);
static_assert(convertible_to_impl(height / period_duration, length / time) == yes);
static_assert(convertible_to_impl(height / width, length / length) == yes);
static_assert(convertible_to_impl(height * width, length* length) == yes);
static_assert(convertible_to_impl(1 / (path_length * distance), 1 / pow<2>(path_length)) == yes);

// derived to more specialized derived
// static_assert(convertible_to_impl(length / time, height / period_duration) == explicit_conversion);
// static_assert(convertible_to_impl(length * length, height / width) == explicit_conversion);

// derived to incompatible specialized derived
// static_assert(convertible_to_impl(height / time, distance / time) == cast);

// when more than one possible combination is present
// static_assert(convertible_to_impl(width * height, pow<2>(height)) == cast);
// static_assert(convertible_to_impl(1 / (width * height), 1 / pow<2>(height)) == cast);
// static_assert(convertible_to_impl(width * distance, path_length* width) == cast);
// static_assert(convertible_to_impl(height * distance, path_length* height) == cast);
// static_assert(convertible_to_impl(width * length, length* height) == cast);
// static_assert(convertible_to_impl(length * distance, path_length* height) == cast);
// static_assert(convertible_to_impl(width * distance, width* path_length) == cast);
// static_assert(convertible_to_impl(altitude * distance, height* path_length) == cast);
// static_assert(convertible_to_impl(length * distance, altitude* path_length) == cast);

// kind to its type
static_assert(convertible_to_impl(kind_of<length>, length) == yes);
static_assert(convertible_to_impl(kind_of<length>, width) == yes);
static_assert(convertible_to_impl(kind_of<length>, position_vector) == yes);
static_assert(convertible_to_impl(kind_of<frequency>, frequency) == yes);
static_assert(convertible_to_impl(kind_of<speed>, velocity) == yes);
static_assert(convertible_to_impl(kind_of<energy>, energy) == yes);
static_assert(convertible_to_impl(kind_of<energy>, potential_energy) == yes);
static_assert(convertible_to_impl(kind_of<energy>, kinetic_energy) == yes);

// kind to a type of a different dimension
static_assert(convertible_to_impl(kind_of<length>, mass) == no);
static_assert(convertible_to_impl(kind_of<length>, speed) == no);
static_assert(convertible_to_impl(kind_of<energy>, length) == no);
static_assert(convertible_to_impl(kind_of<energy>, speed) == no);

// kind to a type of another kind but the same dimension
static_assert(convertible_to_impl(kind_of<energy>, moment_of_force) == no);
static_assert(convertible_to_impl(kind_of<activity>, frequency) == no);
static_assert(convertible_to_impl(kind_of<frequency>, activity) == no);

// derived kind to a compatible type
static_assert(convertible_to_impl(kind_of<length / time>, speed) == yes);
static_assert(convertible_to_impl(kind_of<length / time>, velocity) == yes);
static_assert(convertible_to_impl(kind_of<length / pow<2>(time)>, acceleration) == yes);
static_assert(convertible_to_impl(kind_of<1 / time>, frequency) == yes);
static_assert(convertible_to_impl(kind_of<1 / time>, activity) == yes);
static_assert(convertible_to_impl(kind_of<mass * pow<2>(length) / pow<2>(time)>, energy) == yes);
static_assert(convertible_to_impl(kind_of<mass * pow<2>(length) / pow<2>(time)>, moment_of_force) == yes);

// type to a kind of a different kind
static_assert(convertible_to_impl(mass, kind_of<length>) == no);
static_assert(convertible_to_impl(speed, kind_of<length>) == no);
static_assert(convertible_to_impl(length, kind_of<energy>) == no);
static_assert(convertible_to_impl(speed, kind_of<energy>) == no);
static_assert(convertible_to_impl(moment_of_force, kind_of<energy>) == no);
static_assert(convertible_to_impl(frequency, kind_of<activity>) == no);
static_assert(convertible_to_impl(activity, kind_of<frequency>) == no);
static_assert(convertible_to_impl(moment_of_force, kind_of<energy>) == no);

// converting type to a kind
static_assert(convertible_to_impl(length, kind_of<length>) == yes);
static_assert(convertible_to_impl(width, kind_of<length>) == yes);
static_assert(convertible_to_impl(frequency, kind_of<frequency>) == yes);
static_assert(convertible_to_impl(frequency, kind_of<1 / time>) == yes);
static_assert(convertible_to_impl(frequency, kind_of<activity>) == no);
static_assert(convertible_to_impl(energy, kind_of<energy>) == yes);
static_assert(convertible_to_impl(potential_energy, kind_of<energy>) == yes);
static_assert(convertible_to_impl(kinetic_energy, kind_of<energy>) == yes);

// converting derived type to a kind
static_assert(convertible_to_impl(1 / time, kind_of<frequency>) == yes);
static_assert(convertible_to_impl(length / time, kind_of<speed>) == yes);
static_assert(convertible_to_impl(length / pow<2>(time), kind_of<acceleration>) == yes);

// converting derived kind to a kind
static_assert(convertible_to_impl(kind_of<1 / time>, kind_of<frequency>) == yes);
static_assert(convertible_to_impl(kind_of<length / time>, kind_of<speed>) == yes);
static_assert(convertible_to_impl(kind_of<length / pow<2>(time)>, kind_of<acceleration>) == yes);

// converting type to a derived kind
static_assert(convertible_to_impl(speed, kind_of<length / time>) == yes);
static_assert(convertible_to_impl(velocity, kind_of<length / time>) == yes);
static_assert(convertible_to_impl(energy, kind_of<mass * pow<2>(length) / pow<2>(time)>) == yes);

// kinds of different dimensions
static_assert(convertible_to_impl(kind_of<mass>, kind_of<length>) == no);
static_assert(convertible_to_impl(kind_of<energy>, kind_of<length>) == no);
static_assert(convertible_to_impl(kind_of<length>, kind_of<energy>) == no);
static_assert(convertible_to_impl(kind_of<frequency>, kind_of<energy>) == no);

// derived quantities to dimensionless
static_assert(convertible_to_impl(frequency * period_duration, dimensionless) == yes);
static_assert(convertible_to_impl(frequency * time, dimensionless) == yes);
static_assert(convertible_to_impl(length / length, dimensionless) == yes);
static_assert(convertible_to_impl(length / width, dimensionless) == yes);

static_assert(convertible_to_impl(efficiency, strain) == cast);

// quantity character checks
static_assert((position_vector / time).character == quantity_character::vector);
static_assert((position_vector / position_vector * time).character == quantity_character::scalar);
// static_assert((velocity / acceleration).character == quantity_character::scalar);

// common_quantity_spec
static_assert(is_of_type<common_quantity_spec(width, height), length_>);
static_assert(is_of_type<common_quantity_spec(distance, path_length), path_length_>);
static_assert(is_of_type<common_quantity_spec(potential_energy, kinetic_energy), mechanical_energy_>);

static_assert(is_of_type<common_quantity_spec(length / time, length / time), decltype(length / time)>);
static_assert(is_of_type<common_quantity_spec(length / time, 1 / (time / length)), decltype(length / time)>);

// static_assert(is_of_type<common_quantity_spec(speed, length / time), speed_>);
// static_assert(is_of_type<common_quantity_spec(length / time, speed), speed_>);


// static_assert(
//   is_of_type<common_quantity_spec(length* length, area), derived_quantity_spec<mp_units::power<length_, 2>>>);
// static_assert(
//   is_of_type<common_quantity_spec(area, length* length), derived_quantity_spec<mp_units::power<length_, 2>>>);


// static_assert(is_of_type<common_quantity_spec(length / time, speed), derived_quantity_spec<length_, per<time_>>>);
// static_assert(is_of_type<common_quantity_spec(speed, length / time), derived_quantity_spec<length_, per<time_>>>);
// static_assert(is_of_type<common_quantity_spec(kinetic_energy, mass* pow<2>(length) / pow<2>(time)), energy_>);
// static_assert(
//   is_of_type<common_quantity_spec(kinetic_energy, kind_of<mass * pow<2>(length) / pow<2>(time)>), kinetic_energy_>);
// static_assert(is_of_type<common_quantity_spec(kinetic_energy, mass* pow<2>(speed)), kinetic_energy_>);
// static_assert(is_of_type<common_quantity_spec(gravitational_potential_energy, mass* acceleration / length),
// energy_>);
// static_assert(
//   is_of_type<common_quantity_spec(gravitational_potential_energy, kind_of(mass* pow<2>(length) / pow<2>(time))),
//              gravitational_potential_energy_>);
// static_assert(is_of_type<common_quantity_spec(gravitational_potential_energy, mass* acceleration / height),
// energy_>);
// static_assert(is_of_type<common_quantity_spec(gravitational_potential_energy, mass* acceleration_of_free_fall /
// height),
//                          gravitational_potential_energy_>);

template<auto T1, auto T2>
concept no_common_type = requires {
  requires !requires { typename std::common_type_t<decltype(T1), decltype(T2)>; };
  requires !requires { typename std::common_type_t<decltype(T2), decltype(T1)>; };
};
static_assert(no_common_type<energy, torque>);
static_assert(no_common_type<frequency, activity>);

}  // namespace
