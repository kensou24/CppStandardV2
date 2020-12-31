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
#include <memory>
#include <doctest/doctest.h>
using namespace std;

class Person3 {
  public:
    string name;
    shared_ptr<Person3> mother;
    shared_ptr<Person3> father;
    vector<shared_ptr<Person3>> kids;

    Person3 (const string& n,
            shared_ptr<Person3> m = nullptr,
            shared_ptr<Person3> f = nullptr)
     : name(n), mother(m), father(f) {
    }

    ~Person3() {
      cout << "delete " << name << endl;
    }
};

shared_ptr<Person3> initFamily3 (const string& name)
{
    shared_ptr<Person3> mom(new Person3(name+"'s mom"));
    shared_ptr<Person3> dad(new Person3(name+"'s dad"));
    shared_ptr<Person3> kid(new Person3(name,mom,dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

TEST_CASE("weakptr1")
{
    string name("nico");
    shared_ptr<Person3> p = initFamily3(name);

    cout << "nico's family exists" << endl;
    cout << "- nico is shared " << p.use_count() << " times" << endl;
    cout << "- name of 1st kid of nico's mom: " 
         << p->mother->kids[0]->name << endl;

    p = initFamily3("jim");
    cout << "jim's family exists" << endl;
}
