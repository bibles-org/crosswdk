#ifndef WDK_UTILS_HPP
#define WDK_UTILS_HPP

#include <bit>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <functional>
#include <type_traits>
#include <utility>

#define ALWAYS_INLINE __attribute__((always_inline)) inline

#define BEGIN_INTEL_SYNTAX ".intel_syntax noprefix;"
#define END_INTEL_SYNTAX ".att_syntax;"

// I have to admit, I don't like this.
// enables implicit conversions between a trivial struct and a scalar type
#define MAKE_SCALAR_CONVERTIBLE(THIS, TYPE)                                                                            \
    constexpr THIS() = default;                                                                                        \
    constexpr THIS(const THIS&) = default;                                                                             \
    constexpr THIS& operator=(const THIS&) = default;                                                                  \
                                                                                                                       \
    constexpr THIS(TYPE value) {                                                                                       \
        *this = std::bit_cast<THIS>(value);                                                                            \
    }                                                                                                                  \
                                                                                                                       \
    constexpr THIS& operator=(TYPE value) {                                                                            \
        *this = std::bit_cast<THIS>(value);                                                                            \
        return *this;                                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    constexpr operator TYPE() const {                                                                                  \
        return std::bit_cast<TYPE>(*this);                                                                             \
    }

namespace utils {
    template <typename T>
    concept is_enum_or_integral =
            std::integral<T> || (std::is_enum_v<T> && std::integral<std::underlying_type_t<T>>);

} // namespace utils

#endif // WDK_UTILS_HPP
