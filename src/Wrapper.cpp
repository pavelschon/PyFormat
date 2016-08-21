/**
 * @file Wrapper.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "PyFormat.hpp"


namespace boost
{

namespace python
{

object method_not_supported( const string& method )
{
    const string message = method + string( "is not implemented" );

    PyErr_SetString( PyExc_NotImplementedError, message.c_str() );

    throw_error_already_set();

    return object();
}


template<> string Wrapper<boost::format>::toString( const boost::format& fmt )
{
    return fmt.str();
}

template<> string Wrapper<boost::wformat>::toString( const boost::wformat& fmt )
{
    const wstring w = fmt.str();

    return string( w.begin(), w.end() );
}

/**
 * @brief Get representation of format
 *
 */
template<class FORMAT> typename FORMAT::string_type Wrapper<FORMAT>::repr( const FORMAT& fmt )
{
    FORMAT fmtCopy( fmt );

    fmtCopy.exceptions( all_error_bits ^ ( too_many_args_bit | too_few_args_bit )  );

    return fmtCopy.str();
}


/**
 * @brief Expose Format class
 *
 */
template<class FORMAT> FORMAT Wrapper<FORMAT>::clone( const FORMAT& fmt )
{
    return fmt;
}


#if PY_MAJOR_VERSION >= 3

template<> object Wrapper<boost::format>::toBytes( const boost::format& fmt )
{
    // FIXME https://github.com/boostorg/python/pull/54
    return object( handle<>( PyBytes_FromString( fmt.str().c_str() ) ) );
}

template<> object Wrapper<boost::format>::toUnicode( const boost::format& fmt )
{
    return method_not_supported( "__str__" );
}

#else

template<> object Wrapper<boost::format>::toBytes( const boost::format& fmt )
{
    return str( fmt.str() );
}

template<> object Wrapper<boost::format>::toUnicode( const boost::format& fmt )
{
    return method_not_supported( "__unicode__" );
}

#endif

#if PY_MAJOR_VERSION >= 3

template<> object Wrapper<boost::wformat>::toBytes( const boost::wformat& fmt )
{
    return method_not_supported( "__bytes__" );
}

template<> object Wrapper<boost::wformat>::toUnicode( const boost::wformat& fmt )
{
    return str( fmt.str() );
}

#else /* Python 2 */

template<> object Wrapper<boost::wformat>::toBytes( const boost::wformat& fmt )
{
    return method_not_supported( "__str__" );
}

template<> object Wrapper<boost::wformat>::toUnicode( const boost::wformat& fmt )
{
    return object( fmt.str() ); // unicode object
}

#endif

template struct Wrapper<boost::format>;
template struct Wrapper<boost::wformat>;


} /* namespace python */

} /* namespace boost */

