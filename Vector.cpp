#include "headers/Vector.hpp"

#include <cassert>
#include <cstddef>

namespace cd05 {

template <typename T>
std::istream&
operator>>(std::istream& in, Vector<T>& v)
{
    for (T* p = v.begin_; p != v.end_; ++p) {
        in >> *p;
    }
    return in;
}

template <typename T>
std::ostream&
operator<<(std::ostream& out, const Vector<T>& v)
{
    out << "{ ";
    for (T* p = v.begin_; p != v.end_; ++p) {
        out << *p << ' ';
    }
    out << '}';
    return out;
}

template <typename T>
Vector<T>::Vector(const int size, const T& initialValue)
    : begin_(NULL)
    , end_(NULL)
{
    resize(size, initialValue);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhv)
    : begin_(new T[rhv.size()])
    , end_(begin_ + rhv.size())
{
    for (int i = 0; i < size(); ++i) {
        begin_[i] = rhv.begin_[i];
    }
}

template <typename T>
Vector<T>::~Vector()
{
    if (begin_ != NULL) {
        delete [] begin_;
        begin_ = end_ = NULL;
    }
}

template <typename T>
const Vector<T>&
Vector<T>::operator=(const Vector<T>& rhv)
{
    if (&rhv == this) {
        return *this;
    }

    if (size() != rhv.size()) {
        if (begin_ != NULL) {
            delete [] begin_;
        }
        begin_ = new int[rhv.size()];
        end_ = begin_ + rhv.size();
    }
    for (int i = 0; i < size(); ++i) {
        begin_[i] = rhv.begin_[i];
    }
    return *this;
}

template <typename T>
int
Vector<T>::size() const
{
    return end_ - begin_;
}

template <typename T>
void
Vector<T>::resize(const int newSize, const T& initialValue)
{
    assert(newSize >= 0);
    if (newSize != size()) {
        T* temp = new T[newSize];
        for (T* p = begin_, *np = temp; p != end_; ++p, ++np) {
            *np = *p;
        }
        if (begin_ != NULL) {
            delete [] begin_;
        }
        begin_ = temp;
        end_ = begin_;
        while (size() < newSize) {
            *end_++ = initialValue;
        }
    }
}

template <typename T>
void
Vector<T>::set(const int index, const T& value)
{
    assert(index >= 0 && index < size());
    begin_[index] = value;
}

template <typename T>
const T&
Vector<T>::get(const int index) const
{
    assert(index >= 0 && index < size());
    return begin_[index];
}

template <typename T>
const T&
Vector<T>::operator[](const int index) const
{
    assert(index >= 0 && index < size());
    return begin_[index];
}

template <typename T>
T&
Vector<T>::operator[](const int index)
{
    assert(index >= 0 && index < size());
    return begin_[index];
}

template <typename T>
size_t
Vector<T>::capacity() const
{
    return bufferEnd_ - begin_;
}

template <typename T>
void
Vector<T>::reserve(const size_t n)
{
    if (n > capacity()) {
        T* temp = new T[n];
        const size_t vSize = size();
        for (size_t i = 0; i < vSize; ++i) {
            temp[i] = begin_[i];
        }
        if (begin_ != NULL) {
            delete [] begin_;
        }
        begin_ = temp;
        end_ = begin_ + vSize;
        bufferEnd_ = begin_ + n;
    }
}

template <typename T>
void
Vector<T>::resize(const size_t n, const T& init)
{
    const size_t vSize = size();
    if (n < vSize) {
        end_ = begin_ + n;
        return;
    }

    if (n > capacity()) { /// imast uni?
        reserve(n);
    }

    for (size_t i = vSize; i < n; ++i) {
        begin_[i] = init; /// ? begin[i] = init; end_[i] = init;???
    }

    end_ = begin_ + n;
}
//
template <typename T>
void
Vector<T>::push_back(const T& element)
{
    resize(size() + 1, element);
}
}
