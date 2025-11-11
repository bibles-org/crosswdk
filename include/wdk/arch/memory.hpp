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

        constexpr auto offset_4kb(this auto&& self) noexcept {
            return self[offset_4kb_];
        }

        constexpr auto offset_2mb(this auto&& self) noexcept {
            return self[offset_2mb_];
        }

        constexpr auto offset_1gb(this auto&& self) noexcept {
            return self[offset_1gb_];
        }

        constexpr auto p1_index(this auto&& self) noexcept {
            return self[p1_index_];
        }

        constexpr auto p2_index(this auto&& self) noexcept {
            return self[p2_index_];
        }

        constexpr auto p3_index(this auto&& self) noexcept {
            return self[p3_index_];
        }

        constexpr auto p4_index(this auto&& self) noexcept {
            return self[p4_index_];
        }

        constexpr auto sign(this auto&& self) noexcept {
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
    };

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

        constexpr auto present(this auto&& self) noexcept {
            return self[present_];
        }

        constexpr auto write(this auto&& self) noexcept {
            return self[write_];
        }

        constexpr auto user(this auto&& self) noexcept {
            return self[user_];
        }

        constexpr auto write_through(this auto&& self) noexcept {
            return self[write_through_];
        }

        constexpr auto cache_disable(this auto&& self) noexcept {
            return self[cache_disable_];
        }

        constexpr auto accessed(this auto&& self) noexcept {
            return self[accessed_];
        }

        constexpr auto dirty(this auto&& self) noexcept {
            return self[dirty_];
        }

        constexpr auto page_attribute_table(this auto&& self) noexcept {
            return self[page_attribute_table_];
        }

        constexpr auto global(this auto&& self) noexcept {
            return self[global_];
        }

        constexpr auto ignored1(this auto&& self) noexcept {
            return self[ignored1_];
        }

        constexpr auto page_frame_number(this auto&& self) noexcept {
            return self[page_frame_number_];
        }

        constexpr auto ignored2(this auto&& self) noexcept {
            return self[ignored2_];
        }

        constexpr auto memory_protection_key(this auto&& self) noexcept {
            return self[memory_protection_key_];
        }

        constexpr auto execute_disable(this auto&& self) noexcept {
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

        constexpr auto present(this auto&& self) noexcept {
            return self[present_];
        }

        constexpr auto write(this auto&& self) noexcept {
            return self[write_];
        }

        constexpr auto user(this auto&& self) noexcept {
            return self[user_];
        }

        constexpr auto write_through(this auto&& self) noexcept {
            return self[write_through_];
        }

        constexpr auto cache_disable(this auto&& self) noexcept {
            return self[cache_disable_];
        }

        constexpr auto accessed(this auto&& self) noexcept {
            return self[accessed_];
        }

        constexpr auto dirty(this auto&& self) noexcept {
            return self[dirty_];
        }

        constexpr auto page_size(this auto&& self) noexcept {
            return self[page_size_];
        }

        constexpr auto global(this auto&& self) noexcept {
            return self[global_];
        }

        constexpr auto ignored1(this auto&& self) noexcept {
            return self[ignored1_];
        }

        constexpr auto page_attribute_table(this auto&& self) noexcept {
            return self[page_attribute_table_];
        }

        constexpr auto must_be_zero(this auto&& self) noexcept {
            return self[must_be_zero_];
        }

        constexpr auto page_frame_number(this auto&& self) noexcept {
            return self[page_frame_number_];
        }

        constexpr auto ignored2(this auto&& self) noexcept {
            return self[ignored2_];
        }

        constexpr auto memory_protection_key(this auto&& self) noexcept {
            return self[memory_protection_key_];
        }

        constexpr auto execute_disable(this auto&& self) noexcept {
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

        constexpr auto present(this auto&& self) noexcept {
            return self[present_];
        }

        constexpr auto write(this auto&& self) noexcept {
            return self[write_];
        }

        constexpr auto user(this auto&& self) noexcept {
            return self[user_];
        }

        constexpr auto write_through(this auto&& self) noexcept {
            return self[write_through_];
        }

        constexpr auto cache_disable(this auto&& self) noexcept {
            return self[cache_disable_];
        }

        constexpr auto accessed(this auto&& self) noexcept {
            return self[accessed_];
        }

        constexpr auto dirty(this auto&& self) noexcept {
            return self[dirty_];
        }

        constexpr auto page_size(this auto&& self) noexcept {
            return self[page_size_];
        }

        constexpr auto global(this auto&& self) noexcept {
            return self[global_];
        }

        constexpr auto ignored1(this auto&& self) noexcept {
            return self[ignored1_];
        }

        constexpr auto page_attribute_table(this auto&& self) noexcept {
            return self[page_attribute_table_];
        }

        constexpr auto must_be_zero(this auto&& self) noexcept {
            return self[must_be_zero_];
        }

        constexpr auto page_frame_number(this auto&& self) noexcept {
            return self[page_frame_number_];
        }

        constexpr auto ignored2(this auto&& self) noexcept {
            return self[ignored2_];
        }

        constexpr auto memory_protection_key(this auto&& self) noexcept {
            return self[memory_protection_key_];
        }

        constexpr auto execute_disable(this auto&& self) noexcept {
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
