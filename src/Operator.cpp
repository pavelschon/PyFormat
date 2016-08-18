/**
 * @file Operator.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "PyFormat.hpp"


namespace boost
{

namespace python
{


#if PY_MAJOR_VERSION >= 3

/**
 * @brief Convert object to unicode ( Python 3 )
 *
 */
std::wostream& operator<<( std::wostream& out, const object& obj )
{
    const wstring s = extract<wstring>( str( obj ) );

    return out << s;
}

#else /* Python 2 */

/**
 * @brief Convert object to unicode ( Python 2 )
 *
 */
std::wostream& operator<<( std::wostream& out, const object& obj )
{
    const wstring s = extract<wstring>( unicode( obj ) );

    return out << s;
}

#endif

#if PY_MAJOR_VERSION >= 3

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
 * @brief Convert object to string ( Python 2 )
 *
 */
std::ostream& operator<<( std::ostream& out, const object& obj )
{
    const string s = extract<string>( str( obj ) );

    return out << s;
}

#endif


} /* namespace python */

} /* namespace boost */


