#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import unittest

from pyformat import  Format as F
from pyformat import UFormat as U


class TestFormat(unittest.TestCase):
    def testInit(self):
        f = F( '' )
        f = F( '%|| %|| %||' )
        f = F( '%1% %2% %3%' )

        with self.assertRaises(ValueError):
            f = F( '%|xx|')


    def testOutput(self):
        f = F('%|| %|| %||')
        self.assertEqual(str( f % 'a' % 'b' % 'c' ), 'a b c')

        f = F('%|.2f|')
        self.assertEqual(str( f % 1.0 ), '1.00')

        f = F('%||')
        self.assertEqual(str( f % None ), 'None')


class TestUFormat(unittest.TestCase):
    def testInit(self):
        f = U( u'' )
        f = U( u'%|| %|| %||' )
        f = U( u'%1% %2% %3%' )

        with self.assertRaises(ValueError):
            f = U( u'%|xx|')


    def testOutput(self):
        f = U(u'%|| %|| %||')
        self.assertEqual(unicode( f % u'ě' % u'č' % u'š' ), u'ě č š')

        f = U(u'%|.2f|')
        self.assertEqual(unicode( f % 1.0 ), u'1.00')

        f = U(u'%||')
        self.assertEqual(unicode( f % None ), u'None')


if __name__ == '__main__':
    unittest.main()



# EOF


