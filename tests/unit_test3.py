#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import unittest

from pyformat import UFormat as F
from pyformat import Format  as S


class TestUFormat(unittest.TestCase):
    def testInit(self):
        f = F( '' )
        f = F( '%|| %|| %||' )
        f = F( '%1% %2% %3%' )

        with self.assertRaises(ValueError):
            f = F( '%|xx|')

        s = S( b'' )
        s = S( b'%|| %|| %||' )
        s = S( b'%1% %2% %3%' )

        with self.assertRaises(ValueError):
            s = S( '%|xx|')


    def testOutput(self):
        f = F('%|| %|| %||')
        self.assertEqual(str( f % 'ě' % 'č' % 'š' ), 'ě č š')

        f = F('%|.2f|')
        self.assertEqual(str( f % 1.0 ), '1.00')

        f = F('%||')
        self.assertEqual(str( f % None ), 'None')

        s = S(b'%|| %|| %||')
        self.assertEqual(bytes( s % b'e' % b'c' % b's' ), b'e c s')

        s = S(b'%|.2f|')
        self.assertEqual(bytes( s % 1.0 ), b'1.00')

        s = S('%||')
        self.assertEqual(bytes( s % None ), b'None')


if __name__ == '__main__':
    unittest.main()



# EOF


