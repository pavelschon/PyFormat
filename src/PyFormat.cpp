/**
 * @file PyFormat.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include <boost/python.hpp>
#include <boost/format.hpp>


namespace boost
{

namespace python
{

typedef boost::format::string_type  string;
typedef boost::wformat::string_type wstring;

/**
 * @brief Convert boost::python::object to unicode
 *
 */
std::wostream& operator<<( std::wostream& out, const object& obj )
{
    const wstring s = extract<wstring>( str( obj ) );

    return out << s;
}

#if PY_MAJOR_VERSION >= 3

const auto encoding = "utf-8";
const auto builtins = import( "builtins" );
const auto bytes    = builtins.attr( "bytes" );


/**
 * @brief Convert unicode to bytes
 *
 */
template<class FORMAT>
object fmtToBytes( const FORMAT& fmt )
{
    return bytes( fmt.str(), encoding );
}


/**
 * @brief Convert boost::python::object to unicode
 *
 */
std::ostream& operator<<( std::ostream& out, const object& obj )
{
    const string s = extract<string>( bytes( str( obj ), encoding ) );

    return out << s;
}

#else

/**
 * @brief Convert boost::python::object to unicode
 *
 */
std::ostream& operator<<( std::ostream& out, const object& obj )
{
    const string s = extract<string>( str( obj ) );

    return out << s;
}

#endif

/**
 * @brief Expose Format class
 *
 */
template<class FORMAT>
void expose( const FORMAT& fmt, const char* const name )
{
    typedef typename FORMAT::string_type string_t;

    const return_internal_reference<> return_policy;

    class_< FORMAT >( name, init<const string_t&>() )
#if PY_MAJOR_VERSION >= 3
        .def( "__bytes__",      &fmtToBytes<FORMAT> )
        .def( "__str__",        &FORMAT::str )
#else
        .def( "__str__",        &FORMAT::str )
        .def( "__unicode__",    &FORMAT::str )
#endif
        .def( "__mod__",        &FORMAT::template operator% <const object&>,    return_policy  )
        .def( "__mod__",        &FORMAT::template operator% <const string_t&>,  return_policy  )
        .def( "__mod__",        &FORMAT::template operator% <const int&>,       return_policy  )
        .def( "__mod__",        &FORMAT::template operator% <const long&>,      return_policy  )
        .def( "__mod__",        &FORMAT::template operator% <const long long&>, return_policy  )
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

    register_exception_translator<format_error>( []( const format_error& e )
    {
        PyErr_SetString( PyExc_ValueError, e.what() );

        throw_error_already_set();
    });

    expose( boost::format(),   "Format" );
    expose( boost::wformat(), "UFormat" );

    auto module = scope();

    module.attr( "__doc__"     ) = "PyFormat - boost::format python module";
    module.attr( "__author__"  ) = "Pavel Schon <pavel@schon.cz>";
    module.attr( "__version__" ) = "0.1.0";

} /* pyformat */

