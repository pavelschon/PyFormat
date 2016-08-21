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

const char * const encode   = "encode";
const char * const encoding = "utf-8";

#if PY_MAJOR_VERSION >= 3

const object builtins = import( "builtins" );
const object bytes    = builtins.attr( "bytes" );

#else /* Python 2 */

const object builtins = import( "__builtin__" );
const object unicode  = builtins.attr( "unicode" );

#endif

enum Bits
{
    bad_format_string_bit = boost::io::bad_format_string_bit,
    too_few_args_bit      = boost::io::too_few_args_bit,
    too_many_args_bit     = boost::io::too_many_args_bit,
    out_of_range_bit      = boost::io::out_of_range_bit,
    all_error_bits        = boost::io::all_error_bits,
    no_error_bits         = boost::io::no_error_bits
};

template<class FORMAT> struct Convert
{
    typedef unsigned char(FORMAT::*exceptions_get_t)()const;
    typedef unsigned char(FORMAT::*exceptions_set_t)(unsigned char);
    
    static object toBytes( const FORMAT& fmt );
    static object toUnicode( const FORMAT& fmt );
    static string toString( const FORMAT& fmt );

    static FORMAT clone( const FORMAT& fmt );
    static typename FORMAT::string_type repr( object& obj );
};

std::ostream&  operator<<( std::ostream& out,  const object& obj );
std::wostream& operator<<( std::wostream& out, const object& obj );

inline bool hasattr( const object& obj, const char* const attr_ )
{
    return PyObject_HasAttrString( obj.ptr(), attr_ );
}


} /* namespace python */

} /* namespace boost */

#endif /* PYFORMAT_HPP_ */

