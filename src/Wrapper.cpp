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
    return bytes( fmt.str(), encoding );
}

template<> object Wrapper<boost::format>::toUnicode( const boost::format& fmt )
{
    return str( fmt.str() );
}

#else

template<> object Wrapper<boost::format>::toBytes( const boost::format& fmt )
{
    return str( fmt.str() );
}

template<> object Wrapper<boost::format>::toUnicode( const boost::format& fmt )
{
    return str( fmt.str() ).decode( encoding );
}

#endif

#if PY_MAJOR_VERSION >= 3

template<> object Wrapper<boost::wformat>::toBytes( const boost::wformat& fmt )
{
    return str( fmt.str() ).attr( encode )( encoding );
}

template<> object Wrapper<boost::wformat>::toUnicode( const boost::wformat& fmt )
{
    return str( fmt.str() );
}

#else /* Python 2 */

template<> object Wrapper<boost::wformat>::toBytes( const boost::wformat& fmt )
{
    return unicode( fmt.str() ).attr( encode )( encoding );
}

template<> object Wrapper<boost::wformat>::toUnicode( const boost::wformat& fmt )
{
    return unicode( fmt.str() );
}

#endif

template struct Wrapper<boost::format>;
template struct Wrapper<boost::wformat>;


} /* namespace python */

} /* namespace boost */

