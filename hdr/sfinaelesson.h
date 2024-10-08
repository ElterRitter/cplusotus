#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <cassert>

namespace sfinae {

template<typename T>
using isArithmetic = std::enable_if_t< std::is_arithmetic<T>::value, bool >;

template<typename T>
using isNotArithmetic = std::enable_if_t< !std::is_arithmetic<T>::value, bool >;


template <typename T>
struct is_vec : std::false_type
{ };

template <typename T>
struct is_vec<std::vector<T,std::allocator<T> > > : std::true_type
{  };

template <typename T>
struct is_list : std::false_type
{  };

template <typename T>
struct is_list<std::list<T, std::allocator<T> > > : std::true_type
{  };

template<typename ...T>
struct is_tuple : std::false_type
{  };

template<typename ...T>
struct is_tuple<std::tuple<T...>> : std::true_type
{ };

template<typename T, typename ... Ts>
struct all_same_tuple_params {
    static constexpr bool value = std::is_same_v< std::tuple<T,Ts... >, std::tuple<Ts...,T> >;
};

template<typename... T>
struct all_same_tuple_params<std::tuple<T...>> : all_same_tuple_params<T...>
{  };

using aliasBasicString = std::basic_string<char, std::char_traits<char>, std::allocator<char>>;

template<typename T>
using isString = std::enable_if_t< std::is_same< T, aliasBasicString>::value, bool >;

template<typename T>
using isNotString = std::enable_if_t< !std::is_same< T, aliasBasicString>::value, bool >;

template<typename T>
using isIteribleContainer = std::enable_if_t<is_vec<T>::value || is_list<T>::value, bool>;

template<typename T>
using isNotIteribleContainer = std::enable_if_t<!is_vec<T>::value && !is_list<T>::value, bool>;

template<typename ...T>
using isTuple = std::enable_if_t<is_tuple<T...>::value, bool>;

template<typename ...T>
using isNotTuple = std::enable_if_t<!is_tuple<T...>::value, bool>;

template<std::size_t Idx, std::size_t Max>
using isLastTupleElement = std::enable_if_t<std::conditional<Idx >= Max, std::true_type::type, std::false_type::type>::type::value, bool >;

template<std::size_t Idx, std::size_t Max>
using isNotLastTupleElement = std::enable_if_t<!std::conditional<Idx >= Max, std::true_type::type, std::false_type::type>::type::value, int >;

// func is enabled if all Ts... have the same type as T
template<typename T, typename... Ts>
using isSameTupleTypes = std::enable_if_t<std::conjunction<std::is_same<T, Ts>...>::value, bool>;

// otherwise
template<typename T, typename... Ts>
using isNotSameTupleTypes = std::enable_if_t<!std::conjunction<std::is_same<T, Ts>...>::value, bool>;

template<typename ...T>
using isSameTyple = std::enable_if_t<all_same_tuple_params<T...>::value, bool>;

template<typename ...T>
using isNotSameTyple = std::enable_if_t<!all_same_tuple_params<T...>::value, bool>;

template<class>
constexpr bool dependent_false = false; // workaround before CWG2518/P2593R1

/*!
 * \brief print_ip - шаблонная функция, которая не должна быть вызывана
 */
template<typename T,
         isNotArithmetic<T> = true,
         isNotIteribleContainer<T> = true,
         isNotTuple<T> = true,
         isNotString<T> = true
         >
void print_ip(const T& )
{
    static_assert(dependent_false<T>, "Can't print type. Workaround of static_assert<false> for old compilers, before CWG2518/P2593R1");
    assert(false);
    std::cout << "Wrong type detection " << typeid(T).name();
}


/*!
 * \brief print_ip шаблонная функция для печати арифметических типов
 * \param item любой арифметический тип
 * \details представляет тип как массив байт и последовательно распечатывает байты
 * от старшего к младшему
 */
template<typename T,
         isArithmetic<T> = true>
void print_ip(const T& item)
{
    const char *buffer = reinterpret_cast<const char*>(&item);
    auto sz = sizeof(T);
    for(auto i = sz; i > 0; i--)
    {
        uint32_t val = uint8_t(buffer[i-1]);
        std::cout << std::dec << val;
        if(i != 1)
            std::cout << ".";
    }

    std::cout << std::endl;
}

/*!
 * \brief print_ip шаблонная функция для печати строки
 * \param строка
 * \details функция вызыввается для строкового типа ( std::string )
 */
template<typename T,
         isString<T> = true >
void print_ip(const T& item)
{
    std::cout << item << std::endl;
}

/*!
 * \brief print_ip шаблонная функция для печати содержимого контейнера
 * \param item контейнер содержимое которого нужно распечатать
 */
template<typename T,
         isIteribleContainer<T> = true>
void print_ip(const T& item)
{
    auto it = std::begin(item);
    const auto it_end = std::end(item);
    if(it == it_end)
        return;

    do
    {
        std::cout << *it;
        ++it;
        if(it != it_end)
            std::cout << ".";

    } while(it != it_end);

    std::cout << std::endl;
}


/*!
 * \brief printElement функция-хелпер для перевода каретки после последнего символа из кортежа
 * \tparam Tu - кортеж
 * \tparam I - индекс элемента кортежа
 * \tparam Ts - рамер кортежа
 */
template<class Tu, std::size_t I, std::size_t Ts, isLastTupleElement<I, Ts> >
void printElement(const Tu&)
{
    std::cout << std::endl;
}

/*!
 * \brief printElement функция печати элементов кортежа по индексу
 * \param item кортеж для печати
 * \tparam Tu - кортеж
 * \tparam I - индекс элемента кортежа
 * \tparam Ts - рамер кортежа
 */
template < class Tu, std::size_t I, std::size_t Ts, isNotLastTupleElement<I, Ts> >
void printElement(const Tu& item)
{
    std::cout << std::get<I>(item);

    printElement<Tu, I+1, Ts, 0>(item);
}

/*!
 * \brief print_ip шаблонная функция для печати кортежа
 * \param item кортеж
 */
template<typename T,
         isTuple<T> = true,
         isSameTyple<T> = true >
void print_ip(const T& item)
{
    using sz = std::tuple_size<T>;
    printElement<T, 0, sz::value, sz::value>(item);
}



// template<typename T>
// void printElement(const T& elem)
// {
//     std::cout << elem;
// }

// template<typename TupleT, std::size_t ...Sz>
// void printTypleElement(const TupleT &tp, std::index_sequence<Sz...>)
// {
//     (printElement(std::get<Sz>(tp)),...);
// }

// template<typename T,
//          isTuple<T> = true,
//          std::size_t Tsz = std::tuple_size_v<T> >
// void print_ip(const T& item)
// {
//     std::cout << "Detected tuple! " << std::endl;
//     printTypleElement(item, std::make_index_sequence<Tsz>{});
// }


}   // namespace sfinae
