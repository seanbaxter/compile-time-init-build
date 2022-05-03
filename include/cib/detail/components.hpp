#include "compiler.hpp"
#include "config_item.hpp"
#include "meta.hpp"
#include "indexed_tuple.hpp"
#include "type_list.hpp"

#include <type_traits>


#ifndef COMPILE_TIME_INIT_BUILD_COMPONENTS_HPP
#define COMPILE_TIME_INIT_BUILD_COMPONENTS_HPP


namespace cib::detail {
    template<typename... Components>
    struct components : public detail::config_item {
        template<typename Builders, typename... Args>
        [[nodiscard]] CIB_CONSTEVAL auto init(
            Builders const & builders_tuple,
            Args const & ... args
        ) const {
            return detail::fold_right(make_indexed_tuple(Components{}...), builders_tuple, [&](auto const & c, auto const & builders){
                return c.config.init(builders, args...);
            });
        }

        template<typename... Args>
        [[nodiscard]] CIB_CONSTEVAL auto exports_tuple(
            Args const & ... args
        ) const {
            return type_list_cat(Components::config.exports_tuple(args...)...);
        }
    };
}


#endif //COMPILE_TIME_INIT_BUILD_COMPONENTS_HPP
