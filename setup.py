#!/usr/bin/env python
# -*- coding: utf-8 -*-
##
# @file setup.py
# @brief Setup script
#
# Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
#
#

import glob

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

pyformat = Extension('pyformat',
    language = 'c++',
    extra_compile_args = [ '-Wall', '-pedantic', '-fPIC' ],
    libraries = [ 'boost_python' ],
    include_dirs = [ 'src' ],
    sources = glob.glob('src/*.cpp'),
    depends = glob.glob('src/*.hpp')
)

setup(
    name = 'PythonFormat',
    version = '0.1.1',
    description = 'PyFormat - boost::format python module',
    long_description = 'PyFormat is fast string formatting module, which exposes boost::format class to Python',
    url = 'https://github.com/pavelschon/PyFormat.git',
    author = u'Pavel Schön',
    author_email = 'pavel@schon.cz',
    license = 'Boost Software License - Version 1.0 - August 17th, 2003',
    platforms = [ 'all' ],
    ext_modules = [ pyformat ],
    data_files = [
        ( 'pyformat/tests', glob.glob('tests/*.py') ),
        ( 'pyformat/', [ 'LICENSE', 'README.md' ] ),
    ],
)


# EOF

