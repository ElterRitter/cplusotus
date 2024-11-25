#pragma once

#include <iostream>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cstdint>

using std::cout;
using std::endl;

namespace matrix {

template<typename T>
using umap = std::unordered_map<uint64_t, T>;

template<typename T, T defaultValue>
class ProxyItem
{
public:
    ProxyItem(T value) : m_value(value) { cout << "ProxyItem(T)" << endl ;};
    ProxyItem() : m_value(defaultValue) { cout << "ProxyItem()" << endl; };

    operator T() { return m_value; }
    operator const T&() const { return m_value; }
    void operator= (T value)  { m_value = value; };

    bool isValid() const { return m_value != defaultValue; }

private:
    T m_value;
};

template<typename T, T defaultValue, uint64_t dimensions = 2>
class Matrix
{
public:
    using itemType = Matrix<T, defaultValue, dimensions-1>;

    itemType& operator[](int idx)
    {
        return m_data[idx];
    }

    const itemType& operator[](int idx) const
    {
        return m_data[idx];
    }


    std::size_t size() const
    {
        std::size_t ret = 0;
        std::for_each(m_data.begin(), m_data.end(), [&ret](const auto &it) { ret += it.second.size(); } );
        return ret;
    }

    auto end() const
    {
        return m_data.cend();
    }

    auto end()
    {
        return m_data.end();
    }

    auto begin()
    {
        return m_data.begin();
    }

private:
    umap<itemType> m_data;
};

template<typename T, T defaultValue>
class Matrix<T, defaultValue , 1>
{
public:
    using itemType = ProxyItem<T, defaultValue>;

    itemType& operator[](int idx)
    {
        return m_data[idx];
    }

    const itemType& operator[](int idx) const
    {
        return m_data[idx];
    }

    std::size_t size() const
    {
        std::size_t ret = std::count_if(m_data.begin(), m_data.end(), [&ret](const auto &it) { return it.second.isValid(); } );
        return ret;
    }

    auto end() const
    {
        return m_data.cend();
    }

    auto end()
    {
        return m_data.end();
    }

    auto begin()
    {
        return m_data.begin();
    }

private:
    umap<itemType> m_data;
};


}; // namespace matrix
