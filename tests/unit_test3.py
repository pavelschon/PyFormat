#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import unittest

from pyformat import Format as F


class TestUFormat(unittest.TestCase):
    def testInit(self):
        f = F( '' )
        f = F( '%|| %|| %||' )
        f = F( '%1% %2% %3%' )

        with self.assertRaises(ValueError):
            f = F( '%|xx|')


    def testOutput(self):
        f = F('%|| %|| %||')
        self.assertEqual(str( f % 'ě' % 'č' % 'š' ), 'ě č š')

        f = F('%|.2f|')
        self.assertEqual(str( f % 1.0 ), '1.00')

        f = F('%||')
        self.assertEqual(str( f % None ), 'None')


if __name__ == '__main__':
    unittest.main()



# EOF


