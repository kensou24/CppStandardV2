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

class Person2 {
  public:
    string name;
    shared_ptr<Person2> mother;
    shared_ptr<Person2> father;
    vector<weak_ptr<Person2>> kids;  // weak pointer !!!

    Person2 (const string& n,
            shared_ptr<Person2> m = nullptr,
            shared_ptr<Person2> f = nullptr)
     : name(n), mother(m), father(f) {
    }

    ~Person2() {
      cout << "delete " << name << endl;
    }
};

shared_ptr<Person2> initFamily2 (const string& name)
{
    shared_ptr<Person2> mom(new Person2(name+"'s mom"));
    shared_ptr<Person2> dad(new Person2(name+"'s dad"));
    shared_ptr<Person2> kid(new Person2(name,mom,dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);

    cout << name << "'s mom use count " << mom.use_count() << endl;
    cout << name << "'s dad use count " << dad.use_count() << endl;
    cout << name << "'s use count " << kid.use_count() << endl;
    return kid;
}

TEST_CASE("weakptr2")
{
    shared_ptr<Person2> p = initFamily2("nico");

    cout << "nico's family exists" << endl;
    cout << "- nico is shared " << p.use_count() << " times" << endl;
    cout << "- nico's mom is shared " << p->mother.use_count() << " times" << endl;
    cout << "- name of 1st kid of nico's mom: " 
         << p->mother->kids[0].lock()->name << endl;

    p = initFamily2("jim");
    cout << "jim's family exists" << endl;
}
