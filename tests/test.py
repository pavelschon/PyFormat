#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import unicode_literals

import sys
from functools import reduce

from pyformat import Format as F, UFormat as U


if sys.version_info[0] >= 3:
    str_, bytes_ = str, bytes
else:
    str_, bytes_ = unicode, str


fmt = U("scope %|| %|| %||")

def outer():
    outerFmt = fmt.clone() % "outer"
    def inner(obj):
        innerFmt = outerFmt.clone() % "inner" % obj
        print(innerFmt)

    return inner

o = outer()
o(1)
o(b"a")

