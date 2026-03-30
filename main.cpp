#include <iostream>
#include "top_ip_vector.hpp"
#include <iomanip>
// подсчет пройденных непройденных ттестов 
// выводить только непрошедшие тесты
// тестирование для компирования и перемещения 
// insert earase тесты - для диапозана значений из другого вектора 
// void insert(size_t i, const Vector<T>& rhs, size_t start, size_t end)
// void erase(szie_t strat, size_t end) везде должна быть строгая гарантия 
// insert test x2
// erase test x 2

// итераторы для вектора
//по 3 шт + тесты снизу 
// придумать несколько insert erase с итераторами void insert (VectorIterator pos, FwdIterator begin, FwdIterator end)
bool testEmptyVector()
{
  //std::cout << __func__<<"\n"; вывод названия функции
  topit::Vector<int> v;
  return v.isEmpty();
}
bool testElementInboundAccess()
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
  const topit::Vector<int> v;
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
bool testElementInboundConstAccess()
{
  topit::Vector<int> v;
  v.push_back(1);
  const topit::Vector<int> & rv = v;;
  try {
    const int & val = rv.at(0);
    return val == 1;
  } catch ( ...)
  {
    return false;
  }
}
bool testElementOutOfBoundConstAccess()
{
  const topit::Vector<int> v;
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
bool testCopyConstructorForEmpty()
{
  topit::Vector<int> v;
  topit::Vector<int> yav = v;
  return v == yav;
}
bool testCopyConstructorForNonEmpty()
{
  topit::Vector<int> v;
  v.push_back(1);
  topit::Vector<int> yav = v;
  try
  {
    return yav.getsize() == v.getsize() && yav.at(0) == v.at(0);
  } catch (...)
  {
    return false;
  }
}
bool testInitializerList()
{
  topit::Vector<int> v{1,2};
  return v.getsize() == 2 && (v[0] == 1) && ( v[1] == 2);
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
    { "Inbound access", testElementInboundAccess },
    { "Out of bound access", testElementOutOfBoundAccess },
    { "Inbound const access", testElementInboundConstAccess },
    { "Out of bound const accsess", testElementOutOfBoundConstAccess },
    { "Copy empty vector", testCopyConstructorForEmpty },
    { "Copy non-empty vector", testCopyConstructorForNonEmpty },
    { "Non-empty vector for non-empty initializer list", testInitializerList }
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    if (!res)
    {
      std::cout << tests[i].first << ": FAILD\n";
    }
    pass = pass && res;
  }
  if (pass)
  {
    std::cout << "All tests passed\n";
  }
  else
  {
    std::cout << "Some tests failed\n";
  }
}
