#ifndef top_ip_vector_hpp
#define top_ip_vector_hpp
#include <cstddef>
namespace topit {
  template <class T>
  struct Vector
  {
    ~Vector();
    Vector();
    Vector(const Vector&);
    Vector& operator = (const Vector&);
    Vector& operator=(Vector&&);

    bool isEmpty() const noexcept;
    size_t getsize() const noexcept;
    size_t getcapacity() const noexcept;

    void push_back(const T& v); //
    void popback();
    void insert(size_t i, const T& v);
    void erase(size_t i);
  private:
    T* data_;
    size_t size_, capacity_;
  };
}
template <class T>
topit::Vector< T >::~Vector()
{
  delete[] data_;
}
template <class T>
topit::Vector<T>::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
template< class T >
bool topit::Vector<T>::isEmpty() const noexcept
{
  return !size_;
}
template <class T>
size_t topit::Vector<T>::getsize() const noexcept
{
  return size_;
}
template <class T>
size_t topit::Vector<T>::getcapacity() const noexcept
{
  return capacity_;
}
template <class T>
void topit::Vector<T>::push_back(const T& v)
{
  if (size_ == capacity_)
  {
    size_t newcap;
    if (capacity_ == 0)
    {
      newcap = 1;
    } else{
      newcap = capacity_ + 1;
    }
    T* newdata = new T[newcap];
    for (size_t i = 0; i < size_; i++)
    {
      newdata[i] = data_[i];
    }
    delete[] data_;
    data_ = newdata;
    capacity_ = newcap;
  }
  data_[size_] = v;
  size_++;
}
template<class T>
void topit::Vector<T>::popback()
{
  if(size_ == 0)
  {
    throw std::out_of_range("size is zero; no data");
  }
  size_--;
}
#endif
