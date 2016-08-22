# PyFormat - boost::format python module #

**PyFormat** is fast string formatting module, which exposes **boost::format** class to Python.

Please refer to <a href="http://www.boost.org/doc/libs/1_61_0/libs/format/doc/format.html#syntax" target="_blank">**boost::format**</a> documentation to explore all formatting capabilities.

The module is compatible with Python 2.x and Python 3.x versions and fully supports unicode.

## Python 2 vs Python 3

User of the module must be aware of handling byte strings and unicode strings in Python 2 or 3.
Module does not any decoding/encoding internally, so all type conversions has to be done manually.
The module exposes classes **Format** and **UFormat** (*U* indicates unicode).

- Format:  operates on byte strings (py2: str, py3: bytes)
- UFormat: operates on unicode strings (py2: unicode, py3: str)

Under normal circumstances, *UFormat* should be prefered over *Format*.

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

## Basic usage ##

```
>>> from pyformat import Format as F, UFormat as U
>>> fmt = U('%s %s %s')
>>> print(fmt % 'a' % 'b' % 'c')
a b c
>>> print(fmt % 1 % 2 % 3)
1 2 3
```

## repr() works also on format object which is not fully populated ##
```
>>> U('some args are missing: %s') 
some args are not missing:
```

## Cloning format object ##

```
from pyformat import Format as F, UFormat as U

tmpl = U('foo %s') # parsed only once

def foo(i):
    fmt = tmpl.clone() # clone parsed object (copy.copy() also works)
    print(fmt % i)

foo(1)
foo(2)
foo(3)
```

## Functional use case ##

```
>>> fmt = U('a=%s b=%s c=%s d=%s e=%s')                                                                                                                                                                                                                                        
>>> reduce(lambda f, i: f % i, range(fmt.expected_args()), fmt.clone())                                                                                                                                                                                                        
a=0 b=1 c=2 d=3 e=4
```

## Passing any object as argument ##

```
>>> U('arg=%s') % type
arg=<class 'type'>
>>> U('arg=%s') % None
arg=None
```

## Parsing format object ##

```
>>> fmt = U()
>>> fmt.parse('%s')
```

## Swap format objects ##

```
>>> fmt1, fmt2 = U('first'), U('second')
>>> fmt1.swap(fmt2)
```

## Setting which errors raise exception (using bitmask) ##

```
>>> fmt = U('first %s second %s')
>>> print(fmt % '1' )
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ValueError: boost::too_few_args: format-string referred to more arguments than were passed
>>> from pyformat import bits
>>> fmt.exceptions = bits.all_error_bits ^ bits.too_few_args_bit 
>>> print(fmt % '1' )
first 1 second
```

