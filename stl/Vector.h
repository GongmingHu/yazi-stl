#pragma once

#include <cstring>

namespace yazi {
namespace stl {

template <typename T>
class Vector
{
public:
    Vector();
    ~Vector();

    void push_back(const T & value);
    void pop_back();
    int size() const;
    int capacity() const;
    void reserve(int size);
    void resize(int size);
    void show() const;
    T & at(int index);
    T & front();
    T & back();
    bool empty() const;
    void clear();
    T & operator [] (int index);
    Vector<T> & operator = (const Vector<T> & other);
    T * data();
    void swap(Vector<T> & other);

    class Iterator
    {
    public:
        Iterator() : m_pointer(nullptr) {}
        Iterator(T * pointer) : m_pointer(pointer) {}
        ~Iterator() {}

        bool operator == (const Iterator & other)
        {
            return m_pointer == other.m_pointer;
        }
        
        bool operator != (const Iterator & other)
        {
            return m_pointer != other.m_pointer;
        }

        Iterator & operator = (const Iterator & other)
        {
            m_pointer = other.m_pointer;
            return *this;
        }

        Iterator & operator ++ ()
        {
            m_pointer += 1;
            return *this;
        }

        Iterator operator ++ (int)
        {
            Iterator it = *this;
            ++(*this);
            return it;
        }

        Iterator operator + (int i)
        {
            Iterator it = *this;
            it.m_pointer += i;
            return it;
        }

        Iterator operator - (int i)
        {
            Iterator it = *this;
            it.m_pointer -= i;
            return it;
        }

        Iterator & operator -= (int i)
        {
            m_pointer -= i;
            return *this;
        }

        int operator - (const Iterator & other) const
        {
            return m_pointer - other.m_pointer;
        }

        T & operator * ()
        {
            return *m_pointer;
        }

        T * operator -> ()
        {
            return m_pointer;
        }

    private:
        T * m_pointer;
    };

    Iterator begin();
    Iterator end();

    class ReverseIterator
    {
    public:
        ReverseIterator() : m_pointer(nullptr) {}
        ReverseIterator(T * pointer) : m_pointer(pointer) {}
        ~ReverseIterator() {}

        bool operator == (const ReverseIterator & other)
        {
            return m_pointer == other.m_pointer;
        }
        
        bool operator != (const ReverseIterator & other)
        {
            return m_pointer != other.m_pointer;
        }

        ReverseIterator & operator = (const ReverseIterator & other)
        {
            m_pointer = other.m_pointer;
            return *this;
        }

        ReverseIterator & operator ++ ()
        {
            m_pointer -= 1;
            return *this;
        }

        ReverseIterator operator ++ (int)
        {
            ReverseIterator it = *this;
            ++(*this);
            return it;
        }

        ReverseIterator operator + (int i)
        {
            ReverseIterator it = *this;
            it.m_pointer -= i;
            return it;
        }

        ReverseIterator & operator += (int i)
        {
            m_pointer -= i;
            return *this;
        }

        ReverseIterator operator - (int i)
        {
            ReverseIterator it = *this;
            it.m_pointer += i;
            return it;
        }

        ReverseIterator & operator -= (int i)
        {
            m_pointer += i;
            return *this;
        }

        T & operator * ()
        {
            return *m_pointer;
        }

        T * operator -> ()
        {
            return m_pointer;
        }

    private:
        T * m_pointer;
    };

    ReverseIterator rbegin();
    ReverseIterator rend();

    Iterator find(const T & value);
    Iterator rfind(const T & value);

    Iterator insert(const Iterator it, const T & value);
    Iterator insert(const Iterator it, int n, const T & value);

    Iterator erase(const Iterator it);
    Iterator erase(const Iterator first, const Iterator last);

private:
    bool is_basic_type();

private:
    T * m_data;
    int m_size;
    int m_capacity;
};

template <typename T>
Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0)
{
}

template <typename T>
Vector<T>::~Vector()
{
    if (m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_size = 0;
    m_capacity = 0;
}

template <typename T>
void Vector<T>::push_back(const T & value)
{
    if (m_size < m_capacity)
    {
        m_data[m_size] = value;
        m_size++;
        return;
    }
    if (m_capacity == 0)
    {
        m_capacity = 1;
    }
    else
    {
        m_capacity *= 2;
    }
    T * data = new T[m_capacity];
    if (is_basic_type())
    {
        std::memcpy(data, m_data, m_size * sizeof(T));
    }
    else
    {
        for (int i = 0; i < m_size; i++)
        {
            data[i] = m_data[i];
        }
    }

    if (m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
    m_data[m_size] = value;
    m_size++;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (m_size > 0)
    {
        m_size--;
    }
}

template <typename T>
int Vector<T>::size() const
{
    return m_size;
}

template <typename T>
int Vector<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
void Vector<T>::reserve(int size)
{
    if (m_capacity >= size)
    {
        return;
    }
    while (m_capacity < size)
    {
        if (m_capacity == 0)
        {
            m_capacity = 1;
        }
        else
        {
            m_capacity *= 2;
        }
    }
    T * data = new T[m_capacity];
    if (is_basic_type())
    {
        std::memcpy(data, m_data, m_size * sizeof(T));
    }
    else
    {
        for (int i = 0; i < m_size; i++)
        {
            data[i] = m_data[i];
        }
    }
    if (m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
}

template <typename T>
void Vector<T>::resize(int size)
{
    if (m_size >= size)
    {
        m_size = size;
        return;
    }
    if (size <= m_capacity)
    {
        for (int i = m_size; i < size; i++)
        {
            m_data[i] = T();
        }
        m_size = size;
        return;
    }
    while (m_capacity < size)
    {
        if (m_capacity == 0)
        {
            m_capacity = 1;
        }
        else
        {
            m_capacity *= 2;
        }
    }
    T * data = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
    {
        data[i] = m_data[i];
    }
    if (m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
    for (int i = m_size; i < size; i++)
    {
        m_data[i] = T();
    }
    m_size = size;
}

template <typename T>
void Vector<T>::show() const
{
    std::cout << "size=" << size() << ", capacity=" << capacity() << std::endl;
    for (int i = 0; i < m_size; i++)
    {
        std::cout << m_data[i] << ",";
    }
    std::cout << std::endl;
}

template <typename T>
T & Vector<T>::at(int index)
{
    if (index < 0 || index >= m_size)
    {
        throw std::logic_error("out of range");
    }
    return m_data[index];
}

template <typename T>
T & Vector<T>::front()
{
    if (m_size <= 0)
    {
        throw std::logic_error("vector is empty");
    }
    return m_data[0];
}

template <typename T>
T & Vector<T>::back()
{
    if (m_size <= 0)
    {
        throw std::logic_error("vector is empty");
    }
    return m_data[m_size - 1];
}

template <typename T>
bool Vector<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
void Vector<T>::clear()
{
    m_size = 0;
}

template <typename T>
T & Vector<T>::operator [] (int index)
{
    return at(index);
}

template <typename T>
Vector<T> & Vector<T>::operator = (const Vector<T> & other)
{
    if (m_capacity < other.m_size)
    {
        if (m_data != nullptr)
        {
            delete [] m_data;
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        while (m_capacity < other.m_size)
        {
            if (m_capacity == 0)
            {
                m_capacity = 1;
            }
            else
            {
                m_capacity *= 2;
            }
        }
        m_data = new T[m_capacity];
    }
    if (is_basic_type())
    {
        std::memcpy(m_data, other.m_data, m_size * sizeof(T));
    }
    else
    {
        for (int i = 0; i < other.m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }
    m_size = other.m_size;
    return *this;
}

template <typename T>
T * Vector<T>::data()
{
    return m_data;
}

template <typename T>
void Vector<T>::swap(Vector<T> & other)
{
    T * data = other.m_data;
    int size = other.m_size;
    int capacity = other.m_capacity;

    other.m_data = m_data;
    other.m_size = m_size;
    other.m_capacity = m_capacity;

    m_data = data;
    m_size = size;
    m_capacity = capacity;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin()
{
    Vector<T>::Iterator it(m_data);
    return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end()
{
    Vector<T>::Iterator it(m_data + m_size);
    return it;
}

template <typename T>
typename Vector<T>::ReverseIterator Vector<T>::rbegin()
{
    Vector<T>::ReverseIterator it(m_data + m_size - 1);
    return it;
}

template <typename T>
typename Vector<T>::ReverseIterator Vector<T>::rend()
{
    Vector<T>::ReverseIterator it(m_data - 1);
    return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::find(const T & value)
{
    for (Vector<T>::Iterator it = begin(); it != end(); it++)
    {
        if (*it == value)
        {
            return it;
        }
    }
    return end();
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::rfind(const T & value)
{
    for (Vector<T>::ReverseIterator it = rbegin(); it != rend(); it++)
    {
        if (*it == value)
        {
            return Vector<T>::Iterator(it.operator->());
        }
    }
    return end();
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(const Vector<T>::Iterator it, const T & value)
{
    return insert(it, 1, value);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(const Vector<T>::Iterator it, int n, const T & value)
{
    int size = it - begin();
    if (m_size + n <= m_capacity)
    {
        if (is_basic_type())
        {
            memmove(m_data + size + n, m_data + size, (m_size - size) * sizeof(T));
        }
        else
        {
            for (int i = m_size; i > size; i--)
            {
                m_data[i + n - 1] = m_data[i - 1];
            }
        }
        m_data[size] = value;
        m_size += 1;
        return Vector<T>::Iterator(m_data + size);
    }
    while (m_size + n > m_capacity)
    {
        if (m_capacity == 0)
        {
            m_capacity = 1;
        }
        else
        {
            m_capacity *= 2;
        }
    }
    T * data = new T[m_capacity];
    if (is_basic_type())
    {
        std::memcpy(data, m_data, size * sizeof(T));
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = m_data[i];
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        data[size + i] = value;
    }

    if (is_basic_type())
    {
        std::memcpy(data + size + n, m_data + size, (m_size - size) * sizeof(T));
    }
    else
    {
        for (int i = size; i < m_size; i++)
        {
            data[i + n] = m_data[i];
        }
    }
    if (m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
    m_size += n;
    return Vector<T>::Iterator(m_data + size);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(const Vector<T>::Iterator it)
{
    if (end() - it == 1)
    {
        m_size -= 1;
        return end();
    }
    int size = it - begin();
    if (is_basic_type())
    {
        memmove(m_data + size, m_data + size + 1, (m_size - size - 1) * sizeof(T));
    }
    else
    {
        for (int i = size; i < m_size - 1; i++)
        {
            m_data[i] = m_data[i + 1];
        }
    }
    m_size -= 1;
    return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(const Vector<T>::Iterator first, const Vector<T>::Iterator last)
{
    int f = first - begin();
    int l = last - begin();
    int n = last - first;
    if (is_basic_type())
    {
        memmove(m_data + f, m_data + l, (m_size - l) * sizeof(T));
    }
    else
    {
        for (int i = 0; i < m_size - l; i++)
        {
            m_data[f] = m_data[l];
        }
    }
    m_size -= n;
    return first;
}

template <typename T>
bool Vector<T>::is_basic_type()
{
    return (typeid(T) == typeid(bool)) ||
           (typeid(T) == typeid(char)) ||
           (typeid(T) == typeid(unsigned char)) ||
           (typeid(T) == typeid(short)) ||
           (typeid(T) == typeid(unsigned short)) ||
           (typeid(T) == typeid(int)) ||
           (typeid(T) == typeid(unsigned int)) ||
           (typeid(T) == typeid(long)) ||
           (typeid(T) == typeid(unsigned long)) ||
           (typeid(T) == typeid(float)) ||
           (typeid(T) == typeid(double));
}

}
}