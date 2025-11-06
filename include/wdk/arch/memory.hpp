#ifndef WDK_ARCH_PAGING_HPP
#define WDK_ARCH_PAGING_HPP

namespace arch {
    template <typename T>
    concept is_address = std::is_trivially_copyable_v<T> && sizeof(T) <= 8 &&
                         (std::is_pointer_v<T> || std::is_integral_v<T> || std::is_null_pointer_v<T>);

    struct address {
    private:
        template <is_address T>
        constexpr address& assign(const T& from) {
            if constexpr (std::is_integral_v<T> && sizeof(T) < sizeof(std::uint64_t)) {
                *this = static_cast<std::uint64_t>(from);
            } else {
                *this = std::bit_cast<address>(from);
            }
            return *this;
        }

    public:
        std::uint64_t offset   : 12 {};
        std::uint64_t p1_index : 9 {};
        std::uint64_t p2_index : 9 {};
        std::uint64_t p3_index : 9 {};
        std::uint64_t p4_index : 9 {};
        std::uint64_t sign     : 16 {};

        constexpr std::uint64_t offset_1gb() const {
            return (static_cast<std::uint64_t>(p2_index) << 21) | (static_cast<std::uint64_t>(p1_index) << 12) | offset;
        }

        constexpr std::uint64_t offset_2mb() const {
            return (static_cast<std::uint64_t>(p1_index) << 12) | offset;
        }

        constexpr address() = default;

        constexpr address(const is_address auto& from) {
            assign(from);
        }

        constexpr address& operator=(const is_address auto& from) {
            return assign(from);
        }

        constexpr operator void*() const {
            return std::bit_cast<void*>(*this);
        }
        constexpr operator std::uintptr_t() const {
            return std::bit_cast<std::uintptr_t>(*this);
        }

        template <is_address T>
        explicit constexpr operator T() const {
            return std::bit_cast<T>(*this);
        }

        explicit constexpr operator bool() const {
            return static_cast<bool>(static_cast<std::uint64_t>(*this));
        }

        constexpr address operator*() const {
            return *static_cast<void**>(*this);
        }


        friend constexpr address operator+(const address& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) + static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator+(const address& lhs, const is_address auto& rhs) {
            return static_cast<std::uint64_t>(lhs) + static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator+(const is_address auto& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) + static_cast<std::uint64_t>(rhs);
        }


        friend constexpr address operator-(const address& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) - static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator-(const address& lhs, const is_address auto& rhs) {
            return static_cast<std::uint64_t>(lhs) - static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator-(const is_address auto& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) - static_cast<std::uint64_t>(rhs);
        }


        friend constexpr address operator<<(const address& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) << static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator<<(const address& lhs, const is_address auto& rhs) {
            return lhs << static_cast<address>(rhs);
        }

        friend constexpr address operator<<(const is_address auto& lhs, const address& rhs) {
            return static_cast<address>(lhs) << rhs;
        }


        friend constexpr address operator>>(const address& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) >> static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator>>(const address& lhs, const is_address auto& rhs) {
            return lhs >> static_cast<address>(rhs);
        }

        friend constexpr address operator>>(const is_address auto& lhs, const address& rhs) {
            return static_cast<address>(lhs) >> rhs;
        }


        friend constexpr address operator&(const address& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) & static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator&(const address& lhs, const is_address auto& rhs) {
            return lhs & static_cast<address>(rhs);
        }

        friend constexpr address operator&(const is_address auto& lhs, const address& rhs) {
            return static_cast<address>(lhs) & rhs;
        }


        friend constexpr address operator|(const address& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) | static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator|(const address& lhs, const is_address auto& rhs) {
            return lhs | static_cast<address>(rhs);
        }

        friend constexpr address operator|(const is_address auto& lhs, const address& rhs) {
            return static_cast<address>(lhs) | rhs;
        }


        friend constexpr address operator^(const address& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) ^ static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator^(const address& lhs, const is_address auto& rhs) {
            return lhs ^ static_cast<address>(rhs);
        }

        friend constexpr address operator^(const is_address auto& lhs, const address& rhs) {
            return static_cast<address>(lhs) ^ rhs;
        }


        constexpr address operator~() const {
            return ~static_cast<std::uint64_t>(*this);
        }

        constexpr address& operator+=(const address& delta) {
            return *this = *this + delta;
        }

        constexpr address& operator+=(const is_address auto& delta) {
            return *this = *this + delta;
        }

        constexpr address& operator-=(const address& delta) {
            return *this = *this - delta;
        }

        constexpr address& operator-=(const is_address auto& delta) {
            return *this = *this - delta;
        }

        constexpr address& operator<<=(const address& shift) {
            return *this = *this << shift;
        }

        constexpr address& operator<<=(const is_address auto& shift) {
            return *this = *this << shift;
        }

        constexpr address& operator>>=(const address& shift) {
            return *this = *this >> shift;
        }

        constexpr address& operator>>=(const is_address auto& shift) {
            return *this = *this >> shift;
        }

        constexpr address& operator&=(const address& other) {
            return *this = *this & other;
        }

        constexpr address& operator&=(const is_address auto& other) {
            return *this = *this & other;
        }

        constexpr address& operator|=(const address& other) {
            return *this = *this | other;
        }

        constexpr address& operator|=(const is_address auto& other) {
            return *this = *this | other;
        }

        constexpr address& operator^=(const address& val) {
            return *this = *this ^ val;
        }

        constexpr address& operator^=(const is_address auto& val) {
            return *this = *this ^ val;
        }

        constexpr address& operator++() {
            *this += 1;
            return *this;
        }

        constexpr address operator++(int) {
            const address temp = *this;
            ++(*this);
            return temp;
        }

        constexpr address& operator--() {
            *this -= 1;
            return *this;
        }

        constexpr address operator--(int) {
            const address temp = *this;
            --(*this);
            return temp;
        }

        friend constexpr bool operator==(const address& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) == static_cast<std::uint64_t>(rhs);
        }

        friend constexpr bool operator==(const address& lhs, const is_address auto& rhs) {
            return lhs == static_cast<address>(rhs);
        }

        friend constexpr bool operator==(const is_address auto& lhs, const address& rhs) {
            return static_cast<address>(lhs) == rhs;
        }

        friend constexpr bool operator!=(const address& lhs, const address& rhs) {
            return !(lhs == rhs);
        }

        friend constexpr bool operator!=(const address& lhs, const is_address auto& rhs) {
            return !(lhs == rhs);
        }

        friend constexpr bool operator!=(const is_address auto& lhs, const address& rhs) {
            return !(lhs == rhs);
        }

        friend constexpr auto operator<=>(const address& lhs, const address& rhs) {
            return static_cast<std::uint64_t>(lhs) <=> static_cast<std::uint64_t>(rhs);
        }

        friend constexpr auto operator<=>(const address& lhs, const is_address auto& rhs) {
            return lhs <=> static_cast<address>(rhs);
        }

        friend constexpr auto operator<=>(const is_address auto& lhs, const address& rhs) {
            return static_cast<address>(lhs) <=> rhs;
        }
    } __attribute__((packed));

    static_assert(sizeof(address) == sizeof(std::uint64_t), "arch::address size is incorrect");

    struct page_entry_4kb : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        CROSSWDK_BITFIELD_PROXY1(value, present, bool, 0);
        CROSSWDK_BITFIELD_PROXY1(value, write, bool, 1);
        CROSSWDK_BITFIELD_PROXY1(value, user, bool, 2);
        CROSSWDK_BITFIELD_PROXY1(value, write_through, bool, 3);
        CROSSWDK_BITFIELD_PROXY1(value, cache_disable, bool, 4);
        CROSSWDK_BITFIELD_PROXY1(value, accessed, bool, 5);
        CROSSWDK_BITFIELD_PROXY1(value, dirty, bool, 6);
        CROSSWDK_BITFIELD_PROXY1(value, page_attribute_table, bool, 7);
        CROSSWDK_BITFIELD_PROXY1(value, global, bool, 8);
        CROSSWDK_BITFIELD_PROXY(value, ignored1, std::uint8_t, 9, 11);
        CROSSWDK_BITFIELD_PROXY(value, page_frame_number, std::uint64_t, 12, 51);
        CROSSWDK_BITFIELD_PROXY(value, ignored2, std::uint8_t, 52, 58);
        CROSSWDK_BITFIELD_PROXY(value, memory_protection_key, std::uint8_t, 59, 62);
        CROSSWDK_BITFIELD_PROXY1(value, execute_disable, bool, 63);
    };

    struct page_entry_2mb : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        CROSSWDK_BITFIELD_PROXY1(value, present, bool, 0);
        CROSSWDK_BITFIELD_PROXY1(value, write, bool, 1);
        CROSSWDK_BITFIELD_PROXY1(value, user, bool, 2);
        CROSSWDK_BITFIELD_PROXY1(value, write_through, bool, 3);
        CROSSWDK_BITFIELD_PROXY1(value, cache_disable, bool, 4);
        CROSSWDK_BITFIELD_PROXY1(value, accessed, bool, 5);
        CROSSWDK_BITFIELD_PROXY1(value, dirty, bool, 6);
        CROSSWDK_BITFIELD_PROXY1(value, page_size, bool, 7);
        CROSSWDK_BITFIELD_PROXY1(value, global, bool, 8);
        CROSSWDK_BITFIELD_PROXY(value, ignored1, std::uint8_t, 9, 11);
        CROSSWDK_BITFIELD_PROXY1(value, page_attribute_table, bool, 12);
        CROSSWDK_BITFIELD_PROXY(value, must_be_zero, std::uint8_t, 13, 20);
        CROSSWDK_BITFIELD_PROXY(value, page_frame_number, std::uint64_t, 21, 51);
        CROSSWDK_BITFIELD_PROXY(value, ignored2, std::uint8_t, 52, 58);
        CROSSWDK_BITFIELD_PROXY(value, memory_protection_key, std::uint8_t, 59, 62);
        CROSSWDK_BITFIELD_PROXY1(value, execute_disable, bool, 63);
    };

    struct page_entry_1gb : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        CROSSWDK_BITFIELD_PROXY1(value, present, bool, 0);
        CROSSWDK_BITFIELD_PROXY1(value, write, bool, 1);
        CROSSWDK_BITFIELD_PROXY1(value, user, bool, 2);
        CROSSWDK_BITFIELD_PROXY1(value, write_through, bool, 3);
        CROSSWDK_BITFIELD_PROXY1(value, cache_disable, bool, 4);
        CROSSWDK_BITFIELD_PROXY1(value, accessed, bool, 5);
        CROSSWDK_BITFIELD_PROXY1(value, dirty, bool, 6);
        CROSSWDK_BITFIELD_PROXY1(value, page_size, bool, 7);
        CROSSWDK_BITFIELD_PROXY1(value, global, bool, 8);
        CROSSWDK_BITFIELD_PROXY(value, ignored1, std::uint8_t, 9, 11);
        CROSSWDK_BITFIELD_PROXY1(value, page_attribute_table, bool, 12);
        CROSSWDK_BITFIELD_PROXY(value, must_be_zero, std::uint32_t, 13, 29);
        CROSSWDK_BITFIELD_PROXY(value, page_frame_number, std::uint64_t, 30, 51);
        CROSSWDK_BITFIELD_PROXY(value, ignored2, std::uint8_t, 52, 58);
        CROSSWDK_BITFIELD_PROXY(value, memory_protection_key, std::uint8_t, 59, 62);
        CROSSWDK_BITFIELD_PROXY1(value, execute_disable, bool, 63);
    };

    using pml4e = page_entry_4kb;
    using pdpe = page_entry_4kb;
    using pde = page_entry_4kb;
    using pte = page_entry_4kb;

    using pdpe_1gb = page_entry_1gb;
    using pde_2mb = page_entry_2mb;
} // namespace arch

#endif // WDK_ARCH_PAGING_HPP
