#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import unittest

from pyformat import Format  as S
from pyformat import UFormat as F


class TestFormat(unittest.TestCase):
    def testInit(self):
        f = F( '' )
        f = F( '%|| %|| %||' )
        f = F( '%1% %2% %3%' )

        with self.assertRaises(ValueError):
            f = F( '%|xx|')

        s = S( '' )
        s = S( '%|| %|| %||' )
        s = S( '%1% %2% %3%' )

        with self.assertRaises(ValueError):
            s = S( '%|xx|')


    def testOutput(self):
        f = F('%|| %|| %||')
        self.assertEqual(unicode( f % 'a' % 'b' % 'c' ), 'a b c')

        f = F('%|.2f|')
        self.assertEqual(unicode( f % 1.0 ), '1.00')

        f = F('%||')
        self.assertEqual(unicode( f % None ), 'None')

        s = S('%|| %|| %||')
        self.assertEqual(str( s % 'a' % 'b' % 'c' ), 'a b c')

        s = S('%|.2f|')
        self.assertEqual(str( s % 1.0 ), '1.00')

        s = S('%||')
        self.assertEqual(str( s % None ), 'None')


class TestUFormat(unittest.TestCase):
    def testInit(self):
        f = F( u'' )
        f = F( u'%|| %|| %||' )
        f = F( u'%1% %2% %3%' )

        with self.assertRaises(ValueError):
            f = F( u'%|xx|')


    def testOutput(self):
        f = F(u'%|| %|| %||')
        self.assertEqual(unicode( f % u'ě' % u'č' % u'š' ), u'ě č š')

        f = F(u'%|.2f|')
        self.assertEqual(unicode( f % 1.0 ), u'1.00')

        f = F(u'%||')
        self.assertEqual(unicode( f % None ), u'None')


if __name__ == '__main__':
    unittest.main()



# EOF


