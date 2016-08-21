#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import unicode_literals

import copy
import sys
import unittest

from pyformat import Format as F, UFormat as U


if sys.version_info[0] >= 3:
    str_, bytes_ = str, bytes
else:
    str_, bytes_ = unicode, str


class TestUFormat(unittest.TestCase):
    def testInit(self):
        U()
        U( '' )
        U( '%|| %|| %||' )
        U( '%1% %2% %3%' )

        with self.assertRaises(ValueError):
            U( '%|xx|')

        F()
        F( b'' )
        F( b'%|| %|| %||' )
        F( b'%1% %2% %3%' )

        with self.assertRaises(ValueError):
            F( b'%|xx|')


    def testOutput(self):
        u = U('%|| %|| %||')
        self.assertEqual(str_( u % 'ě' % 'č' % 'š' ), 'ě č š')
        self.assertEqual(bytes_( u ), b'\xc4\x9b \xc4\x8d \xc5\xa1')

        u = U('%|.2f|')
        self.assertEqual(str_( u % 1.0 ), '1.00')

        u = U('%||')
        self.assertEqual(str_( u % None ), 'None')
        self.assertEqual(bytes_( u % None ), b'None')

        u = U('%||')
        self.assertEqual(bytes_( u % None ), b'None')
        self.assertEqual(bytes_( u % None ), b'None')

        f = F(b'%|| %|| %||')
        self.assertEqual(bytes_( f % b'e' % b'c' % b's' ), b'e c s')

        f = F(b'%|| %|| %||')
        self.assertEqual(bytes_( f % b'e' % b'c' % b's' ), b'e c s')
        self.assertEqual(str_( f % 'ě' % 'č' % 'š' ), 'ě č š')

        f = F(b'%|.2f|')
        self.assertEqual(bytes_( f % 1.0 ), b'1.00')

        f = F(b'%||')
        self.assertEqual(bytes_( f % None ), b'None')


    def testTooMany(self):
        f = F(b'%||')
        with self.assertRaises(ValueError):
            f % 1 % 2

        u = U('%||')
        with self.assertRaises(ValueError):
            u % 1 % 2


    def testTooFew(self):
        f = F(b'%||%||')
        with self.assertRaises(ValueError):
            bytes_(f % 1)

        u = U('%||%||')
        with self.assertRaises(ValueError):
            str_(u % 1)


    def testSwap(self):
        f, g = F(b'f'), F(b'g')
        f.swap(g)

        self.assertEqual(bytes_( f ), b'g')
        self.assertEqual(bytes_( g ), b'f')

        u, v = U('u'), U(b'v')
        u.swap(v)

        self.assertEqual(str_( u ), 'v')
        self.assertEqual(str_( v ), 'u')


    def testCopy(self):
        u = U('%||')
        v = u.clone()
        w = copy.copy(v)


if __name__ == '__main__':
    unittest.main()



# EOF


