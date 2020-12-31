/* The following code example is taken from the book
 * "The C++ Standard Library - A Tutorial and Reference, 2nd Edition"
 * by Nicolai M. Josuttis, Addison-Wesley, 2012
 *
 * (C) Copyright Nicolai M. Josuttis 2012.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */
#include "printtuple.hpp"
#include <tuple>
#include <iostream>
#include <string>
#include <doctest/doctest.h>
using namespace std;

TEST_CASE("tuple2")
{
    tuple <int,float,string> t(77,1.1,"more light");
    cout << "io: " << t << endl;
}
