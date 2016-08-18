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
template<class FORMAT> void expose( const FORMAT& fmt )
{
    typedef typename FORMAT::string_type string_t;

    const return_internal_reference<> return_policy;

    const char* const name = Convert<FORMAT>::toString( fmt ).c_str();

    class_< FORMAT >( name, init<const string_t&>() )
#if PY_MAJOR_VERSION >= 3
        .def( "__bytes__",      &Convert<FORMAT>::toBytes )
        .def( "__str__",        &Convert<FORMAT>::toUnicode )
#else
        .def( "__str__",        &Convert<FORMAT>::toBytes )
        .def( "__unicode__",    &Convert<FORMAT>::toUnicode )
#endif
        .def( "__mod__",        &FORMAT::template operator% <const object&>,    return_policy  )
        .def( "__mod__",        &FORMAT::template operator% <const string_t&>,  return_policy  )
        .def( "__mod__",        &FORMAT::template operator% <const int&>,       return_policy  )
        .def( "__mod__",        &FORMAT::template operator% <const long&>,      return_policy  )
#if __cplusplus >= 201103L /* C++11 */
        .def( "__mod__",        &FORMAT::template operator% <const long long&>, return_policy  )
#endif
        .def( "__mod__",        &FORMAT::template operator% <const float&>,     return_policy  )
        .def( "__mod__",        &FORMAT::template operator% <const double&>,    return_policy  )

        .def( "swap",           &FORMAT::swap,          return_policy  )
        .def( "clear",          &FORMAT::clear,         return_policy  )
        .def( "clear_binds",    &FORMAT::clear_bind,    return_policy  )
        .def( "parse",          &FORMAT::parse,         return_policy  )

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

    scope module = scope();

    module.attr( "__doc__"     ) = "PyFormat - boost::format python module";
    module.attr( "__author__"  ) = "Pavel Schon <pavel@schon.cz>";
    module.attr( "__version__" ) = "0.1.0";

} /* pyformat */

