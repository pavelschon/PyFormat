# PyFormat - boost::format python module #

**PyFormat** is fast string formatting module, which exposes **boost::format** class to Python.

Please refer to **boost::format** documentation to explore all formatting capabilities.

The module is compatible with Python 2.x and Python 3.x versions:

- In Python 2.x the module exposes **Format** and **UFormat** classes (*str* and *unicode*)

- In Python 3.x the module exposes **Format** class only (*str*, which is de facto *unicode*)


## Requirements ##

1. C++ compiler

2. CMake

3. Python headers (2.x or 3.x)

4. Boost libraries


## Build ##

```
$ mkdir build
$ cd build
$ cmake ..
$ make package
$ dpkg -i pyformat-0.1.0-Linux.deb
```

## Run ##

Format object can be reused after it has been evaluated. Passing less or more arguments will raise ValueError.
```
>>> from pyformat import Format as F
>>> f = F('%|| %|| %||')
>>> print( f % 'a' % 'b' % 'c' )
a b c
>>> print( f % 1 % 2 % 3 )
1 2 3
```