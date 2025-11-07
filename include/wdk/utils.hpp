#ifndef WDK_UTILS_HPP
#define WDK_UTILS_HPP

#include <bit>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iterator>
#include <limits>
#include <type_traits>
#include <utility>

#define ALWAYS_INLINE __attribute__((always_inline)) inline

#define BEGIN_INTEL_SYNTAX ".intel_syntax noprefix;"
#define END_INTEL_SYNTAX ".att_syntax;"

// TODO: remove
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

namespace crosswdk {
    namespace utils {
        template <typename T>
        concept is_enum_or_integral =
                std::integral<T> || (std::is_enum_v<T> && std::integral<std::underlying_type_t<T>>);

        template <
                typename storage_type, typename value_type, std::size_t start_index,
                std::size_t end_index = start_index>
        struct bitfield_proxy {
            using storage_t = std::remove_cv_t<storage_type>;
            using value_t = std::remove_cv_t<value_type>;

            using value_base_t = typename std::conditional_t<
                    std::is_enum_v<value_t>, std::underlying_type<value_t>, std::type_identity<value_t>>::type;

            static constexpr std::size_t storage_bits = std::numeric_limits<storage_t>::digits;
            static constexpr std::size_t value_bits = std::numeric_limits<value_base_t>::digits;

            static_assert(start_index < storage_bits, "start_index out of range");
            static_assert(end_index < storage_bits, "end_index out of range");
            static_assert(start_index <= end_index, "start_index must be <= end_index");

            static constexpr std::size_t field_width = end_index - start_index + 1;
            static_assert(field_width <= storage_bits, "field width must fit in storage type");
            static_assert(field_width <= value_bits, "value type must hold full field");

            static constexpr storage_t low_mask = std::numeric_limits<storage_t>::max() >> (storage_bits - field_width);
            static constexpr storage_t field_mask = static_cast<storage_t>(low_mask << start_index);

            bitfield_proxy() = delete;
            explicit constexpr bitfield_proxy(storage_type& w) noexcept : value(w) {
            }

            storage_type& value;

            constexpr operator value_t() const noexcept {
                const auto raw = (static_cast<storage_t>(value) & field_mask) >> start_index;
                return static_cast<value_t>(static_cast<value_base_t>(raw));
            }

            constexpr bitfield_proxy& operator=(value_t value) noexcept
                requires(!std::is_const_v<storage_type>)
            {
                auto value_cpy = static_cast<storage_t>(value);
                const auto masked = static_cast<storage_t>(static_cast<value_base_t>(value)) & low_mask;
                value_cpy = (value_cpy & ~field_mask) | (masked << start_index);
                value = value_cpy;
                return *this;
            }
        };

        template <
                typename value_type, std::size_t start_index, std::size_t end_index = start_index,
                typename storage_type>
        constexpr auto make_bitfield(storage_type& w) {
            return bitfield_proxy<storage_type, value_type, start_index, end_index>(w);
        }
        // [start_index, end_index]
        template <typename value_type, std::size_t start_index, std::size_t end_index = start_index>
            requires(
                    (std::unsigned_integral<std::remove_cv_t<value_type>> ||
                     (std::is_enum_v<std::remove_cv_t<value_type>> &&
                      std::is_unsigned_v<std::underlying_type_t<std::remove_cv_t<value_type>>>))
            )
        struct bitfield_descriptor {};

        template <typename T>
        struct bits {
            T value{};

            constexpr bits() = default;
            constexpr bits(const bits&) = default;
            constexpr bits(bits&&) = default;
            constexpr bits& operator=(const bits&) = default;
            constexpr bits& operator=(bits&&) = default;
            ~bits() = default;

            constexpr bits(T v) noexcept : value(v) {
            }

            constexpr bits& operator=(T v) noexcept {
                value = v;
                return *this;
            }

            constexpr operator T() const noexcept {
                return value;
            }

            constexpr bool operator==(const bits&) const = default;

            template <typename value_type, std::size_t start_index, std::size_t end_index>
            auto operator[](this auto&& self, const bitfield_descriptor<value_type, start_index, end_index>&) noexcept
                requires(std::unsigned_integral<std::remove_cv_t<T>>)
            {
                return make_bitfield<value_type, start_index, end_index>(std::forward_like<decltype(self)>(self.value));
            }
        };

        using bits64 = bits<std::uint64_t>;
        using bits32 = bits<std::uint32_t>;
        using bits16 = bits<std::uint16_t>;
        using bits8 = bits<std::uint8_t>;
    } // namespace utils
} // namespace crosswdk

#endif // WDK_UTILS_HPP
