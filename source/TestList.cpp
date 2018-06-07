#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "List.hpp"
#include <iostream>

TEST_CASE ("list_default_constructor","[4.2]")
{
  List <int> list1;
  List <int> list2;
  list2.push_front(4);
  list2.push_front(1);
  REQUIRE (list1.empty() == true);
  REQUIRE (list1.size() == 0);
  REQUIRE (list2.empty() == false);
  REQUIRE (list2.size() == 2);
}


TEST_CASE ("list_push_back","[push_back]")
{
  List <int> list1;
  List <int> list2;
  list2.push_front(4);
  list2.push_front(1);
  list2.push_back(3);
  list1.push_back(6);
  REQUIRE (list1.empty() == false);
  REQUIRE (list1.size() == 1);
  REQUIRE (list2.empty() == false);
  REQUIRE (list2.size() == 3);
}


int main(int argc, char* argv[]){

  return Catch::Session().run(argc, argv);
}

