/**
 * @file PyFormat.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include <boost/python.hpp>
#include <boost/format.hpp>


typedef boost::format::string_type  string_type;
typedef boost::wformat::string_type wstring_type;


namespace boost
{

namespace python
{

#if PY_MAJOR_VERSION >= 3

/**
 * @brief Convert boost::python::object to unicode
 *
 */
std::wostream& operator<<( std::wostream& out, const object& obj )
{
    const wstring_type s = extract<wstring_type>( str( obj ) );

    return out << s;
}

#else /* Python 2.x */

/**
 * @brief Convert boost::python::object to string
 *
 */
std::ostream& operator<<( std::ostream& out, const object& obj )
{
    const string_type s = extract<string_type>( str( obj ) );

    return out << s;
}

/**
 * @brief Convert boost::python::object to unicode
 *
 */
std::wostream& operator<<( std::wostream& out, const object& obj )
{
    const wstring_type s = extract<wstring_type>( str( obj ).decode( "utf-8" ) );

    return out << s;
}

#endif

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

#if PY_MAJOR_VERSION >= 3

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

#else /* Python 2.x */

    class_< boost::format >( "Format", init<const string_type&>()                               )
        .def( "__str__",        &boost::format::str                                             )
        .def( "__mod__",        &boost::format::operator% <const object&>,        return_policy )
        .def( "__mod__",        &boost::format::operator% <const string_type&>,   return_policy )
        .def( "__mod__",        &boost::format::operator% <const int&>,           return_policy )
        .def( "__mod__",        &boost::format::operator% <const long&>,          return_policy )
        .def( "__mod__",        &boost::format::operator% <const long long&>,     return_policy )
        .def( "__mod__",        &boost::format::operator% <const float&>,         return_policy )
        .def( "__mod__",        &boost::format::operator% <const double&>,        return_policy )
        .def( "swap",           &boost::format::swap,                             return_policy )
        .def( "clear",          &boost::format::clear,                            return_policy )
        .def( "clear_binds",    &boost::format::clear_bind,                       return_policy )
        .def( "parse",          &boost::format::parse,                            return_policy )
        .def( "size",           &boost::format::size                                            )
        .def( "expected_args",  &boost::format::expected_args                                   )
        .def( "bound_args",     &boost::format::bound_args                                      )
        .def( "fed_args",       &boost::format::fed_args                                        )
        .def( "remaining_args", &boost::format::remaining_args                                  )
        ;

    class_< boost::wformat >( "UFormat", init<const wstring_type&>()                            )
        .def( "__unicode__",    &boost::wformat::str                                            )
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

#endif

    auto module = scope();

    module.attr( "__doc__"     ) = "PyFormat - boost::format python module";
    module.attr( "__author__"  ) = "Pavel Schon <pavel@schon.cz>";
    module.attr( "__version__" ) = "0.1.0";

} /* pyformat */

