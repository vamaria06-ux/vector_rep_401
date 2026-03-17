#include <iostream>
#include "top_ip_vector.hpp"
bool testEmptyVector()
{
  return false;
}
int main()
{
  using test_t = std::pair < const char*, bool(*)() >;
  test_t tests[] =
  {
    {
      "Empty vector", testEmptyVector
    }
  };
  /*
  bool(*tests[])() = {
    testEmptyVector
  }; */
  const size_t count = sizeof(tests) / sizeof(bool(*)());
  for (size_t i = 0; i < count; ++i)
  {
    std::cout << testEmptyVector() << "\n";
  }
}
