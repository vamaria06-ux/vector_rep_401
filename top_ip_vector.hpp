#ifndef TOP_IP_VECTOR_HPP
#define TOP_IP_VECTOR_HPP
#include <cstddef>
#include <utility>    // std::move
#include <memory>     // std::addressof
#include <stdexcept>  // std::out_of_range
#include <initializer_list>
namespace topit {
  template <class T>
  struct Vector
  {
    ~Vector();
    Vector();
    Vector(const Vector<T>&);
    Vector(Vector<T>&&) noexcept;
    Vector(size_t size, const T& init);
    explicit Vector(std::initializer_list<T> il); // explicit - запрещает пользователю делать неявыне преобразования

    Vector& operator=(const Vector<T>&);
    Vector& operator=(Vector<T>&&) noexcept;

    void swap(Vector<T>&) noexcept;

    bool isEmpty() const noexcept;
    size_t getsize() const noexcept;
    size_t getcapacity() const noexcept;
    // классная работа 30 
    void reserve(size_t k);
    void shrinktoFit();
    void pushBackCount(size_t k, const T& v);
    template <class IT>
    void pushBackRange(IT b, size_t c);

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    void push_back(const T& v);
    void popback();

    void insert(size_t i, const T& v);
    void erase(size_t i);

    void insert(size_t i, const Vector< T >& rhs, size_t start, size_t end);
    void erase(size_t start, size_t end);

    template< class VectorIterator, class FwdIterator >
    void insert(VectorIterator pos, FwdIterator begin, FwdIterator end);

  private:
    T* data_;
    size_t size_, capacity_;
    explicit Vector(size_t size);
    void unsafePushBack(const T&);
  };
  template <class T>
  bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
}
template <class T>
topit::Vector<T>::Vector(std::initializer_list<T> il):
  Vector(il.size())
{
  size_t i = 0;
  for (auto it = il.begin(); it != il.end(); ++it)
  {
    data_[i++] = *it;
  }
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
template <class T>
template <class IT>
void topit::Vector<T>::pushBackRange(IT b, size_t c)
{
  /*
  size_t c = 0;
  for (auto it = b; it != e; ++it, ++c);

  size_t c = std::distance(b,e);
  */
}
template <class T>
void topit::Vector<T>::pushBackCount(size_t k, const T& v)
{ 
  // елси памяти не хватает на k
  // -делаем так, чтоб хватало  - добовляем в конец
   /*for (size_t i = 0; i < k; ++i)
  {
    pushback(val);
  } */

}
template <class T>
void topit::Vector<T>::unsafePushBack(const T&)
{
  /*
  assert(size_ < capacity_);
  //добавить в конец
  */
}
template <class T>
void topit::Vector<T>::swap(Vector<T>& rhs ) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_,rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}
template <class T>
topit::Vector<T>& topit::Vector<T>::operator=(Vector<T>&& rhs) noexcept
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector<T> cpy(std::move(rhs));
  swap(cpy);
  return *this;
}
template <class T>
topit::Vector<T>& topit::Vector<T>::operator=(const Vector<T>& rhs) // конструктор копирования
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector<T> cpy = rhs;
  // free data of this
  // this <- cpy
  // dtat this <-> cpy
  // ~cpy -> free data 
  swap(cpy);
  return *this;
}
template <class T>
topit::Vector<T>::Vector(Vector<T>&& rhs) noexcept :
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}
template< class T >
topit::Vector<T>::Vector(const Vector<T>& rhs):
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
topit::Vector<T>::Vector(size_t size, const T& init) :
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = init;
  }
}
template <class T>
topit::Vector<T>::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}
template <class T>
bool topit::operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
  bool isEqual = lhs.getsize() == rhs.getsize();
  for (size_t i = 0; (i < lhs.getsize() )&& (isEqual = isEqual && lhs[i] == rhs[i]); ++i );
  return isEqual;
}
template <class T>
T& topit::Vector<T>::operator[](size_t id) noexcept
{
  const Vector<T>* cthis = this;
  const T& ret = (*cthis)[id];
  return const_cast<T&>(ret);
}
template <class T>
const T& topit::Vector<T>::operator[](size_t id) const noexcept
{
  return data_[id];
}
template <class T>
T& topit::Vector<T>::at(size_t id)
{
  const Vector<T> *cthis = this;
  const T& ret = cthis->at(id);
  return const_cast<T&>(ret);
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
template<class T>
void topit::Vector<T>::popback()
{
  if(size_ == 0)
  {
    throw std::out_of_range("size is zero; no data");
  }
  size_--;
}
/*
template <class T>
topit::Vector<T>& move_assign()
template <class T>
topit::Vector<T>& topit::Vector<T>:: operator =(Vector<T>&& rhs)
{
  Vector<T> cpy(std:;move(rhs));
  swap(cpy);
  return *this;
}
template <class T>
void topit::Vector<T>::changeVectorInSomeway()
{
  Vector<T> cpy(*this);
  cpy.push_back(T());
  swap(cpy);  // SWAP NOEXCEPT!!!
}
*/
#endif
