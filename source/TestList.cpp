#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "List.hpp"
#include <iostream>


TEST_CASE ("list_default_constructor","[default]")
{
  
  List <int> list1;
  REQUIRE (list1.empty() == true);
  REQUIRE (list1.size() == 0);

}

TEST_CASE ("list_push_front","[push_front]")
{
  List <int> list1;
  list1.push_front(6);
  REQUIRE (list1.empty() == false);
  REQUIRE (list1.size() == 1);
  REQUIRE (list1.front() == 6);
  list1.push_front(7);
  REQUIRE (list1.front() == 7);
}

TEST_CASE ("list_pop_back","[pop_back]")
{
  List <int> list1;
  list1.push_back(6);
  list1.push_front(4);
  list1.push_front(1);
  REQUIRE (list1.empty() == false);
  REQUIRE (list1.size() == 3);
  REQUIRE (list1.back() == 6);
  list1.pop_back();
  //std::cout<<list1.back();
  REQUIRE (list1.back() == 4);
}

TEST_CASE ("list_pop_front","[pop_front]")
{
  List <int> list1;
  list1.push_back(6);
  list1.push_front(4);
  list1.push_front(1);
  REQUIRE (list1.empty() == false);
  REQUIRE (list1.size() == 3);
  REQUIRE (list1.front() == 1);
  list1.pop_front();
  REQUIRE (list1.front() == 4);
}


TEST_CASE ("list_push_back","[push_back]")
{
  List <int> list1;
  list1.push_back(6);
  REQUIRE (list1.empty() == false);
  REQUIRE (list1.size() == 1);
  REQUIRE (list1.back() == 6);
  list1.push_back(7);
  REQUIRE (list1.back() == 7);
}


TEST_CASE ("list_back()","[back]")
{
  List <int> list1;
  list1.push_back(6);
  list1.push_back(9);

  REQUIRE (list1.back() == 9);
}

TEST_CASE ("list_front()","[front]")
{
  List <int> list1;
  list1.push_front(9);
  list1.push_front(6);

  REQUIRE (list1.front() == 6);
}

TEST_CASE ("should be empty after clearing","[modifiers]")
{
List <int> list;
list.push_front(42);
list.push_front(41);
list.push_front(4);
list.push_front(1);
list.push_front(31);
list.push_front(18);

list.clear();
REQUIRE (list.size() == 0);
}


TEST_CASE ("should be an empty range after default construction","[iterators]")
{
List <int> list;
auto b = list.begin();
auto e = list.end();
REQUIRE (b == e);
}


TEST_CASE ("provide access to the first element with begin","[iterators]")
{
List <int> list;
list.push_front(42);
REQUIRE (42 == *list.begin());
}

TEST_CASE ("check if listelements are equal","[list_operator]")
{
List <int> list;
list.push_front(42);
list.push_front(41);
list.push_front(4);
list.push_front(1);
list.push_front(31);
list.push_front(18);

List <int> list2;
list2.push_front(42);
list2.push_front(41);
list2.push_front(4);
list2.push_front(1);
list2.push_front(31);
list2.push_front(18);

List <int> list3;
list3.push_front(42);
list3.push_front(41);
list3.push_front(44);
list3.push_front(1);
list3.push_front(7);
list3.push_front(18);

REQUIRE (operator==(list,list2) == true);
REQUIRE (operator==(list,list3) == false);
}

TEST_CASE ("check if listelements are unequal","[list_operator]")
{
List <int> list;
list.push_front(42);
list.push_front(41);
list.push_front(4);
list.push_front(1);
list.push_front(31);
list.push_front(18);

List <int> list2;
list2.push_front(42);
list2.push_front(41);
list2.push_front(4);
list2.push_front(1);
list2.push_front(31);
list2.push_front(18);

List <int> list3;
list3.push_front(42);
list3.push_front(41);
list3.push_front(44);
list3.push_front(1);
list3.push_front(7);
list3.push_front(18);

REQUIRE (operator!=(list,list2) == false);
REQUIRE (operator!=(list,list3) == true);
}

TEST_CASE ("copy constructor","[constructor]")
{
List <int> list;
list.push_front(1);
list.push_front(2);
list.push_front(3);
list.push_front(4);
List <int> list2{list};
REQUIRE (list == list2);
}
/*
TEST_CASE ("move constructor","[constructor]")
{
List <int> list;
list.push_front(1);
list.push_front(2);
list.push_front(3);
list.push_front(4);
List <int> list2 = std::move(list);
REQUIRE (0 == list.size());
REQUIRE (list.empty());
REQUIRE (4 == list2.size());
}*/

TEST_CASE ("reverse list itself","[reverse]")
{
List <int> list;
list.push_front(1);
list.push_front(2);
list.push_front(3);
list.push_front(4);

List <int> list2;
list2.push_front(4);
list2.push_front(3);
list2.push_front(2);
list2.push_front(1);

list.reverse();

REQUIRE (list2 == list);
}

TEST_CASE ("reverse list and save in new list","[reverse]")
{
List <int> list;
list.push_front(1);
list.push_front(2);
list.push_front(3);
list.push_front(4);

List <int> list2;
list2.push_front(4);
list2.push_front(3);
list2.push_front(2);
list2.push_front(1);

reverse(list);

REQUIRE (list2 == reverse(list));
}  //Funzt alles bis auf Move Constructor

TEST_CASE ("add an element with insert ", "[Aufg. 4.9]")
{
  List <int> list;
  list.push_front(4);
  list.push_front(2);
  list.push_front(6);
  
  auto e = list.begin();      //list now: 624
  REQUIRE (*e == 6);  
  REQUIRE (list.size() == 3);

  list.insert(list.begin(),9);        //Add at the front  

  auto h = list.begin();      //list now: 9624
  REQUIRE (*h == 9);  
  REQUIRE (list.size() == 4);

  list.insert(list.end(),1);           //Add at the place of the last node

  auto g = list.begin();      //list now: 96214
  REQUIRE (*g == 9);  
  REQUIRE (list.size() == 5);


  auto i = list.begin();
  ++i;
  ++i;    //i = 3

  list.insert(i,7);

  auto k = list.begin();      //list now: 9672143
  REQUIRE (*k == 9);  
  REQUIRE (list.size() == 6);
}




int main(int argc, char* argv[]) {

  return Catch::Session().run(argc, argv);
}

