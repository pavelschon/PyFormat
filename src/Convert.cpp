/**
 * @file Convert.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "PyFormat.hpp"


namespace boost
{

namespace python
{

template<> string Convert<boost::format>::toString( const boost::format& fmt )
{
    return fmt.str();
}

template<> string Convert<boost::wformat>::toString( const boost::wformat& fmt )
{
    const wstring w = fmt.str();

    return string( w.begin(), w.end() );
}

#if PY_MAJOR_VERSION >= 3

template<> object Convert<boost::format>::toBytes( const boost::format& fmt )
{
    return bytes( fmt.str(), encoding );
}

template<> object Convert<boost::format>::toUnicode( const boost::format& fmt )
{
    return str( fmt.str() );
}

#else

template<> object Convert<boost::format>::toBytes( const boost::format& fmt )
{
    return str( fmt.str() );
}

template<> object Convert<boost::format>::toUnicode( const boost::format& fmt )
{
    return str( fmt.str() ).decode( encoding );
}

#endif

#if PY_MAJOR_VERSION >= 3

template<> object Convert<boost::wformat>::toBytes( const boost::wformat& fmt )
{
    return bytes( fmt.str(), encoding );
}

template<> object Convert<boost::wformat>::toUnicode( const boost::wformat& fmt )
{
    return str( fmt.str() );
}

#else /* Python 2 */

template<> object Convert<boost::wformat>::toBytes( const boost::wformat& fmt )
{
    return unicode( fmt.str() ).attr( "encode" )( encoding );
}

template<> object Convert<boost::wformat>::toUnicode( const boost::wformat& fmt )
{
    return unicode( fmt.str() );
}

#endif

template struct Convert<boost::format>;
template struct Convert<boost::wformat>;


} /* namespace python */

} /* namespace boost */

