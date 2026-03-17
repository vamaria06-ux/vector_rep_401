#ifndef top_ip_vector.hpp
#define top_ip_vector.hpp
#include <cstddef>
template <class T>
struct Vector
{
  T* data;
  size_t size, capacity;
};
#endif
