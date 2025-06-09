#ifndef WDK_ARCH_DESCRIPTORS_HPP
#define WDK_ARCH_DESCRIPTORS_HPP
#include "memory.hpp"


#include <iterator>

namespace arch {
    template <typename T>
    struct descriptor_table_first {
        std::uint16_t limit{};
        address base{};

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
        std::uint16_t offset_low{};
        std::uint16_t selector{};
        std::uint8_t interrupt_stack_table_index : 3 {};
        std::uint8_t reserved1                   : 5 {};
        std::uint8_t type                        : 4 {};
        std::uint8_t must_be_zero                : 1 {};
        std::uint8_t descriptor_privilege_level  : 2 {};
        std::uint8_t present                     : 1 {};
        std::uint16_t offset_mid{};
        std::uint32_t offset_high{};
        std::uint32_t reserved2 : 32 {};

        address get_handler() const {
            return static_cast<std::uint64_t>(offset_high) << 32 | static_cast<std::uint64_t>(offset_mid) << 16 | offset_low;
        }

        void set_handler(const address handler) {
            const auto addr = static_cast<std::uint64_t>(handler);
            offset_low = addr & 0xFFFF;
            offset_mid = (addr >> 16) & 0xFFFF;
            offset_high = (addr >> 32) & 0xFFFFFFFF;
        }
    } __attribute__((packed));

    static_assert(sizeof(interrupt_descriptor) == 16, "arch::interrupt_descriptor size is incorrect");

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

    constexpr bool exception_has_error_code(const exception_vector v) {
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
