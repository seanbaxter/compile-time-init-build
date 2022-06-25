#include "type_pack_element.hpp"

#include <type_traits>
#include <utility>
#include <array>


#ifndef COMPILE_TIME_INIT_BUILD_TYPE_LIST_HPP
#define COMPILE_TIME_INIT_BUILD_TYPE_LIST_HPP


namespace cib::detail {
    template<typename... Values>
    struct type_list {
        constexpr static auto size = sizeof...(Values);

        template<unsigned int Index>
        constexpr static auto get() noexcept {
            return Values...[Index]{};
        }
    };
    template<typename... TypeLists>
    using type_list_cat_impl = 
        type_list<for typename List : TypeLists => List.type_args... >;

    template<typename... TypeLists>
    constexpr auto type_list_cat(TypeLists...) {
        return type_list_cat_impl<TypeLists...>{};
    }

}


#endif //COMPILE_TIME_INIT_BUILD_TYPE_LIST_HPP
