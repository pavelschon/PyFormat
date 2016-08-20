/**
 * @file PyFormat.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "PyFormat.hpp"

namespace boost
{

namespace python
{

using boost::io::format_error;

/**
 * @brief Translate format_error to PyExc_ValueError
 *
 */
void translate_format_error( const format_error& e )
{
    PyErr_SetString( PyExc_ValueError, e.what() );

    throw_error_already_set();
}


/**
 * @brief Expose Format class
 *
 */
template<class FORMAT> scope expose( const FORMAT& fmt )
{
    typedef typename FORMAT::string_type string_t;

    const return_internal_reference<> return_ref_policy;
    const return_value_policy<return_by_value> return_new_policy;

    const char* const name = Format<FORMAT>::toString( fmt ).c_str();

    return class_< FORMAT >( name, init<const string_t&>() ).def( init<>() )
#if PY_MAJOR_VERSION >= 3
        .def( "__bytes__",      &Format<FORMAT>::toBytes )
        .def( "__str__",        &Format<FORMAT>::toUnicode )
#else
        .def( "__str__",        &Format<FORMAT>::toBytes )
        .def( "__unicode__",    &Format<FORMAT>::toUnicode )
#endif
        .def( "__len__",        &FORMAT::size )
        .def( "__repr__",       &Format<FORMAT>::repr )
        .def( "__copy__",       &Format<FORMAT>::clone,return_new_policy )

        .def( "__mod__",        &FORMAT::template operator% <const object&>,      return_ref_policy )
        .def( "__mod__",        &FORMAT::template operator% <const string_t&>,    return_ref_policy )
        .def( "__mod__",        &FORMAT::template operator% <const bool&>,        return_ref_policy )
        .def( "__mod__",        &FORMAT::template operator% <const int&>,         return_ref_policy )
        .def( "__mod__",        &FORMAT::template operator% <const long&>,        return_ref_policy )
#if __cplusplus >= 201103L /* C++11 */
        .def( "__mod__",        &FORMAT::template operator% <const long long&>,   return_ref_policy )
#endif
        .def( "__mod__",        &FORMAT::template operator% <const float&>,       return_ref_policy )
        .def( "__mod__",        &FORMAT::template operator% <const double&>,      return_ref_policy )
        .def( "__mod__",        &FORMAT::template operator% <const long double&>, return_ref_policy )

        .def( "clone",          &Format<FORMAT>::clone,return_new_policy )
        .def( "swap",           &FORMAT::swap,          return_ref_policy )
        .def( "clear",          &FORMAT::clear,         return_ref_policy )
        .def( "clear_binds",    &FORMAT::clear_bind,    return_ref_policy )
        .def( "parse",          &FORMAT::parse,         return_ref_policy )

        // get exceptions
        .add_property( "exceptions", static_cast<typename FORMAT::exceptions_const_t>( &FORMAT::exceptions )
                                   , static_cast<typename FORMAT::exceptions_1arg_t>(  &FORMAT::exceptions ) )

        /* const functions */
        .def( "size",           &FORMAT::size           )
        .def( "expected_args",  &FORMAT::expected_args  )
        .def( "bound_args",     &FORMAT::bound_args     )
        .def( "fed_args",       &FORMAT::fed_args       )
        .def( "remaining_args", &FORMAT::remaining_args )
    ;
}


} /* namespace python */

} /* namespace boost */


BOOST_PYTHON_MODULE( pyformat )
{
    using namespace boost::python;
    using boost::io::format_error;

    register_exception_translator<format_error>( &translate_format_error );

    expose( boost::format( "Format" ) );
    expose( boost::wformat( L"UFormat") );

    enum_<Bits>( "bits" )
        .value( "bad_format_string_bit",    bad_format_string_bit )
        .value( "too_few_args_bit",         too_few_args_bit      )
        .value( "too_many_args_bit",        too_many_args_bit     )
        .value( "out_of_range_bit",         out_of_range_bit      )
        .value( "all_error_bits",           all_error_bits        )
        .value( "bad_format_string_bit",    bad_format_string_bit )
        .value( "no_error_bits",            no_error_bits )
        ;

    scope module = scope();

    module.attr( "__doc__"     ) = "PyFormat - boost::format python module";
    module.attr( "__author__"  ) = "Pavel Schon <pavel@schon.cz>";
    module.attr( "__version__" ) = "0.1.0";

} /* pyformat */

