#include <iostream>
#include "top_ip_vector.hpp"
// подсчет пройденных непройденных ттестов 
// выводить только непрошедшие тесты
// 
bool testEmptyVector()
{
  //std::cout << __func__<<"\n"; вывод названия функции
  topit::Vector<int> v;
  return v.isEmpty();
}
bool testElementAccess()
{
  topit::Vector<int> v;
  v.push_back(1);
  try {
    int & val = v.at(0);
    return val == 1;
  } catch ( ...)
  {
    return false;
  }
}
bool testElementOutOfBoundAccess()
{
  topit::Vector<int> v;
  try {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range &)
  {
    return true;
  } catch (...)
  {
    return false;
  }
}  
bool testSize()
{
  topit::Vector<int> v;
  return v.getsize() == 0;
}

bool testSize2() {
    topit::Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.popback();
    v.push_back(3);
    return v.getsize() == 2;
}

bool testPushback()
{
  topit::Vector< int > v;
  v.push_back(5);
  return v.getsize() == 1 && !v.isEmpty() && v.getcapacity() >= 1;;
}

bool testMultiplePushback()
{
  topit::Vector< int > v;
  for (int i = 0; i < 5; i++)
  {
    v.push_back(i);
  }
  return v.getsize() == 5;
}

bool testPopback()
{
  topit::Vector< int > v;
  v.push_back(10);
  v.popback();
  return v.getsize() == 0 && v.isEmpty();
}

bool testPopbackEmpty()
{
  topit::Vector< int > v;
  try
  {
    v.popback();
  }catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return true;
  }
  return false;
}

bool testCapacityMultiple()
{
  topit::Vector< int > v;
  v.push_back(1);
  bool q1 = v.getcapacity() == 1;
  v.push_back(2);
  bool q2 = v.getcapacity() == 2;
  v.push_back(3);
  bool q3 = v.getcapacity() == 3;
  return q1 && q2 && q3;
}

bool testCapacityPopback()
{
  topit::Vector< int > v;
  for (int i = 0; i < 5; i++)
  {
    v.push_back(i);
  }
  size_t firstCap = v.getcapacity();
  v.popback();
  v.popback();
  return v.getcapacity() == firstCap;

}

int main()
{
  using test_t = std::pair < const char*, bool(*)() >;
  test_t tests[] =
  {
    {"Empty vector", testEmptyVector},
    {"Test size of empty vector", testSize},
    {"Test size of non empty vector", testSize2},
    {"test single pushback", testPushback},
    {"test multiple pushback's", testMultiplePushback},
    {"test single popback after pushback",testPopback },
    {"test if try to popback empty list", testPopbackEmpty},
    {"test changes of capacity", testCapacityMultiple},
    {"test capacity if popback's", testCapacityPopback},
    {"test element", testElementAccess},
    {"test elemet 2", testElementOutOfBoundAccess}
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first<< ": " << res << "\n";
    pass = pass && res;
  }
  std::cout << "Total: " << pass << "\n";
}
