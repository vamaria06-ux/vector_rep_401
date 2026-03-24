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
    Vector(Vector&&);

    Vector& operator = (const Vector&);
    Vector& operator=(Vector&&);

    bool isEmpty() const noexcept;
    size_t getsize() const noexcept;
    size_t getcapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    void push_back(const T& v);
    void popback();
    void insert(size_t i, const T& v);
    void erase(size_t i);
  private:
    T* data_;
    size_t size_, capacity_;
  };
  template <class T>
  bool operator== (const Vector<T>& lhs, const Vector<T>& rhs);
}
template <class T>
bool topit::operator==(const Vector<T>& rhs, const Vector<T>& lhs)
{
  bool isEqual = lhs.getsize() == rhs.getsize();
  for (size_t i = 0; i < lhs.getsize() && (isEqual = isEqual && lhs[i] == rhs[i]); ++i );
  return isEqual;
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
template <class T>
T& topit::Vector<T>::at(size_t id)
{
  const Vector<T> *cthis = this;
  return const_cast<T&>(cthis -> at(id));
}
template <class T>
const T& topit::Vector<T>::at(size_t id) const
{
  if (id < getsize())
  {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}
template <class T>
T& topit::Vector<T>::operator[](size_t id) noexcept
{
  const Vector<T>* cthis = this;
  return const_cast<T&>((*cthis)[id]);
}
template <class T>
const T& topit::Vector<T>::operator[](size_t id) const noexcept
{
  return data_[id];
}
template< class T >
topit::Vector<T>::Vector(const Vector& other):
  data_(new T[other.cap_]),
  size_(0),
  cap_(other.cap_)
{
  for (size_t i = 0; i < other.size_; ++i) {
    data_[i] = other.data_[i];
    size_++;
  }
}
#endif
