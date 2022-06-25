#include "ordered_set.hpp"
#include "quicksort.hpp"

#include <string_view>
#include <array>

#include <cstdio>

#ifndef COMPILE_TIME_INIT_BUILD_FIND_HPP
#define COMPILE_TIME_INIT_BUILD_FIND_HPP

template<typename T>
using FirstArg = T.type_args...[0];

namespace cib::detail {
    template<typename Tag, typename MetaFunc, typename... Types>
    constexpr auto const & find(ordered_set<Types...> const & t) {
        constexpr int I = (typename MetaFunc::template invoke<Types>).find(Tag);
        static_assert(-1 != I);
        return t.template get<I>();
    }



}


#endif //COMPILE_TIME_INIT_BUILD_FIND_HPP

