/**
 * @file PyFormat.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef PYFORMAT_HPP_
#define PYFORMAT_HPP_

#include <boost/python.hpp>
#include <boost/format.hpp>


namespace boost
{

namespace python
{


typedef boost::format::string_type   string;
typedef boost::wformat::string_type wstring;

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
    static string toString( const FORMAT& fmt );
};

std::ostream&  operator<<( std::ostream& out,  const object& obj );
std::wostream& operator<<( std::wostream& out, const object& obj );


} /* namespace python */

} /* namespace boost */

#endif /* PYFORMAT_HPP_ */

