#include "type_pack_element.hpp"

#include <type_traits>
#include <utility>
#include <array>


#ifndef COMPILE_TIME_INIT_BUILD_TUPLE_HPP
#define COMPILE_TIME_INIT_BUILD_TUPLE_HPP


namespace cib::detail {
    template<typename... Ts>
    struct ordered_set {       
        // All parameters must be unique.
        static_assert(sizeof...(Ts.unique) == sizeof...(Ts));

        constexpr ordered_set(Ts... values) : m(values)... { }

        template<int Index>
        constexpr const Ts...[Index]& get() const {
            return m...[Index];
        }

        template<typename T>
        constexpr T const & get() const {
            static constexpr int index = Ts.find(T);
            static_assert(-1 != index);
            return m...[index];
        }

        constexpr static auto size() {
            return sizeof...(Ts);
        }

        constexpr bool operator==(ordered_set<Ts...> const & rhs) const {
            return (... && (m == rhs.m));
        }

        template<typename... RhsTn>
        constexpr bool operator==(ordered_set<RhsTn...>) const noexcept {
            return false;
        }

        template<typename... RhsTn>
        constexpr bool operator!=(ordered_set<RhsTn...> const & rhs) const {
            return !(*this == rhs);
        }

        Ts ...m;
    };


    template<typename Callable, typename... Values>
    constexpr auto apply(Callable operation, ordered_set<Values...> const & t) {
        return operation(t.[:]...);
    }


    template<typename... Tuples>
    constexpr ordered_set<
        for typename Tuple : Tuples => Tuple.type_args...
    > 
    make_tuple(Tuples&&... tuples forward) {
        return { for tup : tuples => tup... };
    }
}

namespace std {
    template<typename... Values>
    struct tuple_size<cib::detail::ordered_set<Values...>>
        : std::integral_constant<std::size_t, sizeof...(Values)>
    {};
}


#endif //COMPILE_TIME_INIT_BUILD_TUPLE_HPP
