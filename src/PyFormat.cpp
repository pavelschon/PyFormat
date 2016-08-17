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

typedef boost::format::string_type   string;
typedef boost::wformat::string_type wstring;

using boost::io::format_error;

const char * const encoding = "utf-8";

#if PY_MAJOR_VERSION >= 3

const object builtins = import( "builtins" );
const object bytes    = builtins.attr( "bytes" );

#else /* Python 2 */

const object builtins = import( "__builtin__" );
const object unicode  = builtins.attr( "unicode" );

#endif

template<class FORMAT> struct Convert
{
    static object toBytes( const FORMAT& fmt );
    static object toUnicode( const FORMAT& fmt );
};


/**
 * @brief Translate format_error to PyExc_ValueError
 *
 */
void translate_format_error( const format_error& e )
{
    PyErr_SetString( PyExc_ValueError, e.what() );

    throw_error_already_set();
}


#if PY_MAJOR_VERSION >= 3

/**
 * @brief Convert object to unicode ( Python 2 and 3 )
 *
 */
std::wostream& operator<<( std::wostream& out, const object& obj )
{
    const wstring s = extract<wstring>( str( obj ) );

    return out << s;
}

/**
 * @brief Convert object to bytes ( Python 3 )
 *
 */
std::ostream& operator<<( std::ostream& out, const object& obj )
{
    const string s = extract<string>( bytes( str( obj ), encoding ) );

    return out << s;
}

#else /* Python 2 */

/**
 * @brief Convert object to unicode ( Python 2 and 3 )
 *
 */
std::wostream& operator<<( std::wostream& out, const object& obj )
{
    const wstring s = extract<wstring>( unicode( obj ) );

    return out << s;
}

/**
 * @brief Convert object to string ( Python 2 )
 *
 */
std::ostream& operator<<( std::ostream& out, const object& obj )
{
    const string s = extract<string>( str( obj ) );

    return out << s;
}

#endif

#if PY_MAJOR_VERSION >= 3

template<> struct Convert<boost::format>
{
    /**
    * @brief Convert unicode to bytes
    *
    */
    static object toBytes( const boost::format& fmt )
    {
        return bytes( fmt.str(), encoding );
    }

    /**
     * @brief Convert unicode to bytes
     *
     */
    static object toUnicode( const boost::format& fmt )
    {
        return str( fmt.str() );
    }
};

template<> struct Convert<boost::wformat>
{
    /**
     * @brief Convert unicode to bytes
     *
     */
    static object toBytes( const boost::wformat& fmt )
    {
        return bytes( fmt.str(), encoding );
    }

    /**
     * @brief Convert unicode to bytes
     *
     */
    static object toUnicode( const boost::wformat& fmt )
    {
        return str( fmt.str() );
    }
};

#else /* Python 2 */

template<> struct Convert<boost::format>
{
    /**
     * @brief Convert unicode to bytes
     *
     */
    static object toBytes( const boost::format& fmt )
    {
        return str( fmt.str() );
    }

    /**
     * @brief Convert unicode to bytes
     *
     */
    static object toUnicode( const boost::format& fmt )
    {
        return str( fmt.str() ).decode( encoding );
    }
};

template<> struct Convert<boost::wformat>
{
    /**
     * @brief Convert wformat to bytes
     *
     */
    static object toBytes( const boost::wformat& fmt )
    {
        return unicode( fmt.str() ).attr( "encode" )( encoding );
    }

    /**
     * @brief Convert wformat to unicode
     *
     */
    static object toUnicode( const boost::wformat& fmt )
    {
        return unicode( fmt.str() );
    }
};

#endif


/**
 * @brief Expose Format class
 *
 */
template<class FORMAT> void expose( const FORMAT& fmt, const char* const name )
{
    typedef typename FORMAT::string_type string_t;

    const return_internal_reference<> return_policy;

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

    expose( boost::format(),   "Format" );
    expose( boost::wformat(), "UFormat" );

    object module = scope();

    module.attr( "__doc__"     ) = "PyFormat - boost::format python module";
    module.attr( "__author__"  ) = "Pavel Schon <pavel@schon.cz>";
    module.attr( "__version__" ) = "0.1.0";

} /* pyformat */

