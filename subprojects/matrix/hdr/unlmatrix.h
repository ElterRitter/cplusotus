#pragma once

#include <iostream>
#include <map>
#include <queue>
#include <array>
#include <assert.h>
#include <string>

namespace proxymatrix {

using std::cout;
using std::endl;

template<typename SzT, std::size_t... n>
auto n_tuple_impl(std::index_sequence<n...>) { return std::make_tuple( (n)...); }

template<typename T, T defValue, std::size_t dimensions = 2>
class Matrix
{
public:
    using key_type = std::array<std::size_t, dimensions>;
    using storage_type = std::map<key_type, T>;
    using storage_iterator = typename storage_type::iterator;


    template<typename PT, PT dV, std::size_t dims = 2>
    class ProxyMatrixItem
    {
    public:
        using Parent = Matrix<T, dV, dims>;
        using ParentPtr = Parent*;

        ProxyMatrixItem(std::size_t dimIndex, ParentPtr parent) : m_parent(parent)
        {
            m_indexes.push(dimIndex);
        };

        ProxyMatrixItem& operator[](const std::size_t idx)
        {
            if(m_indexes.size() >= dims)
                throw std::out_of_range("Index " + std::to_string(idx) + " is out of range dimension");
            else
                m_indexes.push(idx);

            return *this;
        }

        operator PT()
        {
            auto key = makeKey();
            return m_parent->value(key);
        }

        void operator=(PT value)
        {
            auto key = makeKey();
            m_parent->setValue(key, value);
        }

    private:
        ParentPtr m_parent;
        std::queue<std::size_t> m_indexes;

        key_type makeKey()
        {
            assert(m_indexes.size() == dimensions);

            key_type ret;
            for(std::size_t i = 0; !m_indexes.empty(); i++)
            {
                ret[i] = m_indexes.front();
                m_indexes.pop();
            }
            return ret;
        }

//         std::string makeKey()
//         {
//             std::string strKey;
//             while(!m_indexes.empty())
//             {
// //                boost::hash_combine(ret, m_indexes.front());
//                 strKey.append(std::to_string(m_indexes.front()));
//                 if(m_indexes.size() != 1)
//                     strKey.append(",");

//                 m_indexes.pop();
//             }

//             return strKey;
//         }
    };


    template<typename IT>
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using value_tuple = std::tuple<T>;

        using n_tuple_position = decltype( n_tuple_impl<std::size_t>( std::make_index_sequence<dimensions>()) );
        using value_type = decltype( std::tuple_cat( n_tuple_position(), value_tuple() ) );

        using pointer = value_type;
        using reference = value_type;

        explicit Iterator(storage_iterator it ) : m_ptr(it) { };

        template<size_t... Is>
        n_tuple_position as_tuple_helper(Matrix::key_type const & key, std::index_sequence<Is...> ) const
        {
            return std::make_tuple((key[Is])...);
        }

        value_type makeValue() const
        {
            auto position = as_tuple_helper(m_ptr->first, std::make_index_sequence<dimensions>{});
            return std::tuple_cat( position, std::make_tuple(m_ptr->second) );
        }

        reference operator*()
        {
            return makeValue();
        }

        pointer operator->()
        {
            return makeValue();
        }


        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int){ auto temp = *this; ++(*this); return temp;}
        friend bool operator==(const Iterator<IT> &a, const Iterator<IT> &b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const Iterator<IT> &a, const Iterator<IT> &b) { return a.m_ptr != b.m_ptr; }

    private:
        IT m_ptr;
    };

    Iterator<storage_iterator> begin()
    {
        return Matrix::Iterator<storage_iterator>(m_storage.begin());
    }

    Iterator<const storage_iterator> cbegin() const
    {
        return Matrix::Iterator<const storage_iterator>(m_storage.cbegin());
    }

    Iterator<storage_iterator> end() {
        return Iterator<storage_iterator>(m_storage.end());
    }

    Iterator<const storage_iterator> cend() const {
        return Iterator<const storage_iterator>(m_storage.cend());
    }


    using SpecificProxy = ProxyMatrixItem<T, defValue, dimensions>;

    Matrix() = default;
    SpecificProxy operator[](std::size_t idx)
    {
        SpecificProxy ret = SpecificProxy(idx, this);
        return ret;
    }

    std::size_t size() const
    {
        return m_storage.size();
    }

protected:
    T value(const key_type &key) const
    {
        auto it = m_storage.find(key);
        if(it == m_storage.end())
            return defValue;
        else
            return it->second;
    };

    void setValue(const key_type &key, T value)
    {
        auto it = m_storage.find(key);
        if(value == defValue && it != m_storage.end())
            m_storage.erase(it);
        else if(value != defValue)
            m_storage[key] = value;
    }


private:
    storage_type m_storage;
};


}
