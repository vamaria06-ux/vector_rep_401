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
    Vector(size_t size, const T&init);

    Vector& operator = (const Vector&);
    Vector& operator=(Vector&&);

    bool isEmpty() const noexcept;
    size_t getsize() const noexcept;
    size_t getcapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    void swap(Vector<T>) noexcept;
    void push_back(const T& v);
    void popback();
    void insert(size_t i, const T& v);
    void erase(size_t i);
  private:
    T* data_;
    size_t size_, capacity_;
    Vector(size_t size);
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
topit::Vector<T>::Vector(const Vector& rhs):
  Vector(rhs.getsize())
  /*data_(rhs.getsize() ? new t[rhs.getsize()] : nullptr),
  size_(rhs.getsize()),
  capacity_(rhs.getsize()) */
{
  for (size_t i = 0; i < rhs.getsize(); ++i)
  {
    try {
      data_[i] = rhs[i];
    } catch(...)
    {
      delete [] data_;
      throw;
    }
  }
}
template <class T>
topit::Vector<T>::Vector(size_t size):
  data_(size ?? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}
template <class T>
topit::Vector<T>::Vector(size_t size, const T& init)
  Vector(size)
{
  for (szie_ t i = 0; i < size ; ++i)
  {
    data_[i] = init;
  }
}
template <class T>
void::topit::Vector<T>::swap(Vector<T>& rhs ) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_,rhs.size_);
  std::swap(capacity, rhs.capacity_);
}
template <class T>
topit::Vector<T>& topit::Vector<T>:: operator=(const Vector<T>& rhs) // конструктор копирования
{
  Vector<T> cpy = rhs;
  // free data of this
  // this <- cpy
  // dtat this <-> cpy
  // ~cpy -> free data 
  swap(cpy);
  return *this;
}
template <class T>
topit::Vector<T>& topit::Vector<T>:: operator =(Vector<T>&& rhs)
{
  Vector<T> cpy(std:;move(rhs));
  swap(cpy);
  return *this;
}
template <class T>
topit::Vector<T>& topit::Vector<T>:: operator =(const Vector<T>&& rhs)
{
  if (this == std::addressof(rhs))
  {
    retirn *this;
  }
  Vector<T> cpy(std:;move(rhs));
  swap(cpy);
  return *this;
}
template <class T>
topit::Vector<T>::Vector(<T>&& rhs) noexcept
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = 
}
template <class T>
void topit::Vector<T>::changeVectorInSomeway()
{
  Vector<T> cpy(*this);
  cpy.push_back(T());
  swap(cpy);  // SWAP NOEXCEPT!!!
}
#endif
