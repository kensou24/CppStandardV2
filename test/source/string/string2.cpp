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
#include <iostream>
#include <string>
#include <vector>
#include <doctest/doctest.h>
using namespace std;

TEST_CASE("string2")
{
   const string delims(" \t,.;");

   std::vector<string> lines;
   lines.push_back("abcdefg");
   lines.push_back("1234567890");

   string line;
   auto itr = lines.begin();

   // for every line read successfully
   while (itr != lines.end()) {
       line = *itr;
       string::size_type begIdx, endIdx;

       // search beginning of the first word
       begIdx = line.find_first_not_of(delims);

       // while beginning of a word found
       while (begIdx != string::npos) {
           // search end of the actual word
           endIdx = line.find_first_of (delims, begIdx);
           if (endIdx == string::npos) {
               // end of word is end of line
               endIdx = line.length();
           }

           // print characters in reverse order
           for (int i=endIdx-1; i>=static_cast<int>(begIdx); --i) {
               cout << line[i];
           }
           cout << ' ';

           // search beginning of the next word
           begIdx = line.find_first_not_of (delims, endIdx);
       }
       cout << endl;
       itr++;
   }
}
