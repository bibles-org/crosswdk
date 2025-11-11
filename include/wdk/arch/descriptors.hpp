#ifndef WDK_ARCH_DESCRIPTORS_HPP
#define WDK_ARCH_DESCRIPTORS_HPP
#include "memory.hpp"


#include <iterator>

namespace arch {
    template <typename T>
    struct descriptor_table_first {
        std::uint16_t limit{};
        __attribute__((packed)) address base{};

        static constexpr std::size_t descriptor_size = sizeof(T); // long mode focused

        struct iterator {
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            T* current;
            std::size_t index = 0;

            iterator(T* base, std::size_t idx) : current(base + idx), index(idx) {
            }

            T& operator*() const {
                return *current;
            }

            iterator& operator++() {
                ++index;
                ++current;
                return *this;
            }

            iterator operator++(int) {
                iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const iterator& other) const {
                return current == other.current;
            }
        };

        std::size_t size() const {
            return (limit + 1) / descriptor_size;
        }

        iterator begin() const {
            return iterator(static_cast<T*>(base), 0);
        }

        iterator end() const {
            return iterator(static_cast<T*>(base), size());
        }
    } __attribute__((packed));

    static_assert(sizeof(descriptor_table_first<address>) == 10, "arch::descriptor_table_first size is incorrect");
    // using global_descriptor_table = descriptor_table_first</*segment descriptors*/>
    using global_descriptor_table = descriptor_table_first<address>;
    using interrupt_descriptor_table = descriptor_table_first<struct interrupt_descriptor>;

    struct interrupt_descriptor {
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 0, 15> offset_low16_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 16, 31> selector_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 32, 34> interrupt_stack_table_index_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 35, 39> reserved1_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 40, 43> type_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 44> must_be_zero_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 45, 46> descriptor_privilege_level_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 47> present_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 48, 63> offset_mid16_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 64, 95> offset_high32_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 96, 127> reserved2_;

    private:
        crosswdk::utils::bits64 low{};
        crosswdk::utils::bits64 high{};

    public:
        template <typename value_type, std::size_t start_index, std::size_t end_index>
        constexpr auto operator[](
                this auto&& self,
                const crosswdk::utils::bitfield_descriptor<value_type, start_index, end_index>& descriptor
        ) noexcept
            requires((start_index / 64) == (end_index / 64) && end_index < 128)
        {
            if constexpr (end_index < 64) {
                return self.low[descriptor];
            } else {
                return self.high[crosswdk::utils::bitfield_descriptor<value_type, start_index - 64, end_index - 64>{}];
            }
        }

        constexpr auto offset_low16(this auto&& self) noexcept {
            return self[offset_low16_];
        }

        constexpr auto selector(this auto&& self) noexcept {
            return self[selector_];
        }

        constexpr auto interrupt_stack_table_index(this auto&& self) noexcept {
            return self[interrupt_stack_table_index_];
        }

        constexpr auto reserved1(this auto&& self) noexcept {
            return self[reserved1_];
        }

        constexpr auto type(this auto&& self) noexcept {
            return self[type_];
        }

        constexpr auto must_be_zero(this auto&& self) noexcept {
            return self[must_be_zero_];
        }

        constexpr auto descriptor_privilege_level(this auto&& self) noexcept {
            return self[descriptor_privilege_level_];
        }

        constexpr auto present(this auto&& self) noexcept {
            return self[present_];
        }

        constexpr auto offset_mid16(this auto&& self) noexcept {
            return self[offset_mid16_];
        }

        constexpr auto offset_high32(this auto&& self) noexcept {
            return self[offset_high32_];
        }

        constexpr auto reserved2(this auto&& self) noexcept {
            return self[reserved2_];
        }

        constexpr address get_handler() const noexcept {
            const auto high32 = static_cast<std::uint64_t>(offset_high32());
            const auto mid16 = static_cast<std::uint64_t>(offset_mid16());
            const auto low16 = static_cast<std::uint64_t>(offset_low16());
            return (high32 << 32) | (mid16 << 16) | low16;
        }

        constexpr void set_handler(const address handler) noexcept {
            const auto handler_u64 = static_cast<std::uint64_t>(handler);
            offset_low16() = static_cast<std::uint16_t>(handler_u64);
            offset_mid16() = static_cast<std::uint16_t>(handler_u64 >> 16);
            offset_high32() = static_cast<std::uint32_t>(handler_u64 >> 32);
        }
    };

    enum class exception_vector {
        divide_error = 0,
        debug = 1,
        nmi = 2,
        breakpoint = 3,
        overflow = 4,
        bound_range_exceeded = 5,
        invalid_opcode = 6,
        device_not_available = 7,
        double_fault = 8,
        coprocessor_segment_overrun = 9,
        invalid_tss = 10,
        segment_not_present = 11,
        stack_segment_fault = 12,
        general_protection = 13,
        page_fault = 14,
        x87_floating_point_error = 16,
        alignment_check = 17,
        machine_check = 18,
        simd_floating_point_error = 19,
        virtualization_exception = 20,
        control_protection = 21,
        hypervisor_injection_exception = 28,
        vmm_communication_exception = 29,
        security_exception = 30
    };

    constexpr bool exception_pushes_error_code(const exception_vector v) {
        switch (v) {
            using enum exception_vector;

            case double_fault:
            case invalid_tss:
            case segment_not_present:
            case stack_segment_fault:
            case general_protection:
            case page_fault:
            case alignment_check:
            case control_protection:
            case vmm_communication_exception:
            case security_exception:
                return true;

            default:
                return false;
        }
    }
} // namespace arch

#endif // WDK_ARCH_DESCRIPTORS_HPP
