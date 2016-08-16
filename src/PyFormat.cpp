/**
 * @file PyFormat.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include <boost/python.hpp>
#include <boost/format.hpp>

typedef boost::wformat::string_type wstring_type;


namespace boost
{

namespace python
{

/**
 * @brief Convert boost::python::object to unicode
 *
 */
std::wostream& operator<<( std::wostream& out, const object& obj )
{
    const wstring_type s = extract<wstring_type>( str( obj ) );

    return out << s;
}

} /* namespace boost */

} /* namespace python */


BOOST_PYTHON_MODULE( pyformat )
{
    using namespace boost::python;

    register_exception_translator<boost::io::format_error>( []( const boost::io::format_error& e )
    {
        PyErr_SetString( PyExc_ValueError, e.what() );

        throw_error_already_set();
    });

    const return_internal_reference<> return_policy;

    class_< boost::wformat >( "Format", init<const wstring_type&>()                             )
        .def( "__str__",        &boost::wformat::str                                            )
        .def( "__mod__",        &boost::wformat::operator% <const object&>,       return_policy )
        .def( "__mod__",        &boost::wformat::operator% <const wstring_type&>, return_policy )
        .def( "__mod__",        &boost::wformat::operator% <const int&>,          return_policy )
        .def( "__mod__",        &boost::wformat::operator% <const long&>,         return_policy )
        .def( "__mod__",        &boost::wformat::operator% <const long long&>,    return_policy )
        .def( "__mod__",        &boost::wformat::operator% <const float&>,        return_policy )
        .def( "__mod__",        &boost::wformat::operator% <const double&>,       return_policy )
        .def( "swap",           &boost::wformat::swap,                            return_policy )
        .def( "clear",          &boost::wformat::clear,                           return_policy )
        .def( "clear_binds",    &boost::wformat::clear_bind,                      return_policy )
        .def( "parse",          &boost::wformat::parse,                           return_policy )
        .def( "size",           &boost::wformat::size                                           )
        .def( "expected_args",  &boost::wformat::expected_args                                  )
        .def( "bound_args",     &boost::wformat::bound_args                                     )
        .def( "fed_args",       &boost::wformat::fed_args                                       )
        .def( "remaining_args", &boost::wformat::remaining_args                                 )
    ;

    auto module = scope();

    module.attr( "__doc__"     ) = "PyFormat - boost::format python module";
    module.attr( "__author__"  ) = "Pavel Schon <pavel@schon.cz>";
    module.attr( "__version__" ) = "0.1.0";

} /* pyformat */

