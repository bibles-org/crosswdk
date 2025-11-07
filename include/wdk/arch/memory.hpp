#ifndef WDK_ARCH_PAGING_HPP
#define WDK_ARCH_PAGING_HPP

namespace arch {
    template <typename T>
    concept is_address_capable =
            (sizeof(T) == 8) && std::is_trivially_copyable_v<T> || std::is_pointer_v<T> || std::is_null_pointer_v<T>;

    struct address : crosswdk::utils::bits64 {
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 0, 11> offset_4kb_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 0, 20> offset_2mb_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 0, 29> offset_1gb_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 12, 20> p1_index_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 21, 29> p2_index_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 30, 38> p3_index_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 39, 47> p4_index_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 48, 63> sign_;

        auto offset_4kb(this auto&& self) noexcept {
            return self[offset_4kb_];
        }

        auto offset_2mb(this auto&& self) noexcept {
            return self[offset_2mb_];
        }

        auto offset_1gb(this auto&& self) noexcept {
            return self[offset_1gb_];
        }

        auto p1_index(this auto&& self) noexcept {
            return self[p1_index_];
        }

        auto p2_index(this auto&& self) noexcept {
            return self[p2_index_];
        }

        auto p3_index(this auto&& self) noexcept {
            return self[p3_index_];
        }

        auto p4_index(this auto&& self) noexcept {
            return self[p4_index_];
        }

        auto sign(this auto&& self) noexcept {
            return self[sign_];
        }

        constexpr address() = default;
        constexpr address(const is_address_capable auto& from) :
            crosswdk::utils::bits64(std::bit_cast<std::uint64_t>(from)) {
        }

        constexpr address& operator=(const is_address_capable auto& from) noexcept {
            value = std::bit_cast<std::uint64_t>(from);
            return *this;
        }

        constexpr operator void*() const noexcept {
            return std::bit_cast<void*>(value);
        }

        explicit constexpr operator std::uint64_t() const noexcept {
            return value;
        }

        template <is_address_capable T>
        explicit constexpr operator T() const noexcept {
            return std::bit_cast<T>(value);
        }

        explicit constexpr operator bool() const noexcept {
            return static_cast<bool>(value);
        }

        constexpr address operator~() const noexcept {
            return ~static_cast<std::uint64_t>(*this);
        }

        constexpr address& operator+=(const address& other) noexcept {
            value += other.value;
            return *this;
        }

        constexpr address& operator-=(const address& other) noexcept {
            value -= other.value;
            return *this;
        }

        constexpr address& operator<<=(const address& other) noexcept {
            value <<= other.value;
            return *this;
        }

        constexpr address& operator>>=(const address& other) noexcept {
            value >>= other.value;
            return *this;
        }

        constexpr address& operator&=(const address& other) noexcept {
            value &= other.value;
            return *this;
        }

        constexpr address& operator|=(const address& other) noexcept {
            value |= other.value;
            return *this;
        }

        constexpr address& operator^=(const address& val) noexcept {
            value ^= val.value;
            return *this;
        }

        constexpr address& operator++() noexcept {
            ++value;
            return *this;
        }

        constexpr address operator++(int) noexcept {
            const auto ret = *this;
            ++value;
            return ret;
        }

        constexpr address& operator--() noexcept {
            --value;
            return *this;
        }

        constexpr address operator--(int) noexcept {
            const auto ret = *this;
            --value;
            return ret;
        }

        friend constexpr address operator+(address lhs, address rhs) noexcept {
            return lhs += rhs;
        }

        friend constexpr address operator-(address lhs, address rhs) noexcept {
            return lhs -= rhs;
        }

        friend constexpr address operator<<(address lhs, address rhs) {
            return lhs <<= rhs;
        }

        friend constexpr address operator>>(address lhs, address rhs) {
            return lhs >>= rhs;
        }

        friend constexpr address operator&(address lhs, address rhs) {
            return lhs &= rhs;
        }

        friend constexpr address operator|(address lhs, address rhs) {
            return lhs |= rhs;
        }

        friend constexpr address operator^(address lhs, address rhs) {
            return lhs ^= rhs;
        }

        friend constexpr bool operator==(address lhs, address rhs) {
            return lhs.value == rhs.value;
        }

        friend constexpr bool operator!=(address lhs, address rhs) {
            return !(lhs == rhs);
        }

        friend constexpr auto operator<=>(address lhs, address rhs) {
            return lhs.value <=> rhs.value;
        }
    } __attribute__((packed));

    struct page_entry_4kb : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<bool, 0> present_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 1> write_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 2> user_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 3> write_through_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 4> cache_disable_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 5> accessed_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 6> dirty_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 7> page_attribute_table_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 8> global_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 9, 11> ignored1_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 12, 51> page_frame_number_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 52, 58> ignored2_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 59, 62> memory_protection_key_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 63> execute_disable_;

        auto present(this auto&& self) noexcept {
            return self[present_];
        }

        auto write(this auto&& self) noexcept {
            return self[write_];
        }

        auto user(this auto&& self) noexcept {
            return self[user_];
        }

        auto write_through(this auto&& self) noexcept {
            return self[write_through_];
        }

        auto cache_disable(this auto&& self) noexcept {
            return self[cache_disable_];
        }

        auto accessed(this auto&& self) noexcept {
            return self[accessed_];
        }

        auto dirty(this auto&& self) noexcept {
            return self[dirty_];
        }

        auto page_attribute_table(this auto&& self) noexcept {
            return self[page_attribute_table_];
        }

        auto global(this auto&& self) noexcept {
            return self[global_];
        }

        auto ignored1(this auto&& self) noexcept {
            return self[ignored1_];
        }

        auto page_frame_number(this auto&& self) noexcept {
            return self[page_frame_number_];
        }

        auto ignored2(this auto&& self) noexcept {
            return self[ignored2_];
        }

        auto memory_protection_key(this auto&& self) noexcept {
            return self[memory_protection_key_];
        }

        auto execute_disable(this auto&& self) noexcept {
            return self[execute_disable_];
        }
    };

    struct page_entry_2mb : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<bool, 0> present_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 1> write_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 2> user_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 3> write_through_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 4> cache_disable_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 5> accessed_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 6> dirty_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 7> page_size_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 8> global_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 9, 11> ignored1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 12> page_attribute_table_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 13, 20> must_be_zero_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 21, 51> page_frame_number_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 52, 58> ignored2_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 59, 62> memory_protection_key_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 63> execute_disable_;

        auto present(this auto&& self) noexcept {
            return self[present_];
        }

        auto write(this auto&& self) noexcept {
            return self[write_];
        }

        auto user(this auto&& self) noexcept {
            return self[user_];
        }

        auto write_through(this auto&& self) noexcept {
            return self[write_through_];
        }

        auto cache_disable(this auto&& self) noexcept {
            return self[cache_disable_];
        }

        auto accessed(this auto&& self) noexcept {
            return self[accessed_];
        }

        auto dirty(this auto&& self) noexcept {
            return self[dirty_];
        }

        auto page_size(this auto&& self) noexcept {
            return self[page_size_];
        }

        auto global(this auto&& self) noexcept {
            return self[global_];
        }

        auto ignored1(this auto&& self) noexcept {
            return self[ignored1_];
        }

        auto page_attribute_table(this auto&& self) noexcept {
            return self[page_attribute_table_];
        }

        auto must_be_zero(this auto&& self) noexcept {
            return self[must_be_zero_];
        }

        auto page_frame_number(this auto&& self) noexcept {
            return self[page_frame_number_];
        }

        auto ignored2(this auto&& self) noexcept {
            return self[ignored2_];
        }

        auto memory_protection_key(this auto&& self) noexcept {
            return self[memory_protection_key_];
        }

        auto execute_disable(this auto&& self) noexcept {
            return self[execute_disable_];
        }
    };

    struct page_entry_1gb : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<bool, 0> present_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 1> write_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 2> user_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 3> write_through_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 4> cache_disable_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 5> accessed_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 6> dirty_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 7> page_size_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 8> global_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 9, 11> ignored1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 12> page_attribute_table_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 13, 29> must_be_zero_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 30, 51> page_frame_number_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 52, 58> ignored2_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 59, 62> memory_protection_key_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 63> execute_disable_;

        auto present(this auto&& self) noexcept {
            return self[present_];
        }

        auto write(this auto&& self) noexcept {
            return self[write_];
        }

        auto user(this auto&& self) noexcept {
            return self[user_];
        }

        auto write_through(this auto&& self) noexcept {
            return self[write_through_];
        }

        auto cache_disable(this auto&& self) noexcept {
            return self[cache_disable_];
        }

        auto accessed(this auto&& self) noexcept {
            return self[accessed_];
        }

        auto dirty(this auto&& self) noexcept {
            return self[dirty_];
        }

        auto page_size(this auto&& self) noexcept {
            return self[page_size_];
        }

        auto global(this auto&& self) noexcept {
            return self[global_];
        }

        auto ignored1(this auto&& self) noexcept {
            return self[ignored1_];
        }

        auto page_attribute_table(this auto&& self) noexcept {
            return self[page_attribute_table_];
        }

        auto must_be_zero(this auto&& self) noexcept {
            return self[must_be_zero_];
        }

        auto page_frame_number(this auto&& self) noexcept {
            return self[page_frame_number_];
        }

        auto ignored2(this auto&& self) noexcept {
            return self[ignored2_];
        }

        auto memory_protection_key(this auto&& self) noexcept {
            return self[memory_protection_key_];
        }

        auto execute_disable(this auto&& self) noexcept {
            return self[execute_disable_];
        }
    };

    using pml4e = page_entry_4kb;
    using pdpe = page_entry_4kb;
    using pde = page_entry_4kb;
    using pte = page_entry_4kb;

    using pdpe_1gb = page_entry_1gb;
    using pde_2mb = page_entry_2mb;
} // namespace arch

#endif // WDK_ARCH_PAGING_HPP
