#ifndef WDK_ARCH_MSRS_HPP
#define WDK_ARCH_MSRS_HPP

namespace arch {
    template <typename T>
    concept is_msr = requires { T::number; };

    struct efer {
        static constexpr std::uint32_t number = 0xC000'0080;
        std::uint64_t value;

        CROSSWDK_BITFIELD_PROXY1(value, syscall_extensions, bool, 0)
        CROSSWDK_BITFIELD_PROXY(value, reserved1, std::uint8_t, 1, 7)
        CROSSWDK_BITFIELD_PROXY1(value, long_mode, bool, 8)
        CROSSWDK_BITFIELD_PROXY1(value, reserved2, bool, 9)
        CROSSWDK_BITFIELD_PROXY1(value, long_mode_active, bool, 10)
        CROSSWDK_BITFIELD_PROXY1(value, no_execute, bool, 11)
        CROSSWDK_BITFIELD_PROXY1(value, secure_virtual_machine, bool, 12)
        CROSSWDK_BITFIELD_PROXY1(value, long_mode_segment_limit, bool, 13)
        CROSSWDK_BITFIELD_PROXY1(value, fast_fxsave_fxrstor, bool, 14)
        CROSSWDK_BITFIELD_PROXY1(value, translation_cache_extension, bool, 15)
        CROSSWDK_BITFIELD_PROXY1(value, execute_only_pte_extension, bool, 16) // amd64 xotext
        CROSSWDK_BITFIELD_PROXY1(value, mcommit, bool, 17)
        CROSSWDK_BITFIELD_PROXY1(value, interruptible_wbinvd_wbnoinvd, bool, 18)
        CROSSWDK_BITFIELD_PROXY1(value, reserved3, bool, 19)
        CROSSWDK_BITFIELD_PROXY1(value, upper_address_ignore, bool, 20)
        CROSSWDK_BITFIELD_PROXY1(value, auto_ibrs, bool, 21)
        CROSSWDK_BITFIELD_PROXY(value, reserved4, std::uint64_t, 22, 63)

        CROSSWDK_BITFIELD_INTERFACE(efer, value)
    };

    // virtual machine host save physical address as per the AMD manual
    struct vmhs_pa {
        static constexpr std::uint32_t number = 0xC001'0117;
        std::uint64_t value{};

        CROSSWDK_BITFIELD_INTERFACE(vmhs_pa, value)
    };

    struct lstar {
        static constexpr std::uint32_t number = 0xC000'0082;
        std::uint64_t value{};

        CROSSWDK_BITFIELD_INTERFACE(lstar, value)
    };

    struct cstar {
        static constexpr std::uint32_t number = 0xC000'0083;
        std::uint64_t value{};

        CROSSWDK_BITFIELD_INTERFACE(cstar, value)
    };

    struct syscall_flag_mask {
        static constexpr std::uint32_t number = 0xC000'0084;
        std::uint64_t value{};

        CROSSWDK_BITFIELD_INTERFACE(syscall_flag_mask, value)
    };

    // max performance
    struct mperf {
        static constexpr std::uint32_t number = 0xC000'00E7;
        std::uint64_t max_core_clocks_counter{};

        CROSSWDK_BITFIELD_INTERFACE(mperf, max_core_clocks_counter)
    };

    // actual performance
    struct aperf {
        static constexpr std::uint32_t number = 0xC000'00E8;
        std::uint64_t actual_core_clocks_counter{};

        CROSSWDK_BITFIELD_INTERFACE(aperf, actual_core_clocks_counter)
    };

    // instructions retired
    struct irperf {
        static constexpr std::uint32_t number = 0xC000'00E9;
        std::uint64_t value{};

        CROSSWDK_BITFIELD_PROXY(value, instructions_retired_counter, std::uint64_t, 0, 47)
        CROSSWDK_BITFIELD_PROXY(value, reserved, std::uint16_t, 48, 63)

        CROSSWDK_BITFIELD_INTERFACE(irperf, value)
    };

    struct fs_base {
        static constexpr std::uint32_t number = 0xC000'0100;
        std::uint64_t value{};

        CROSSWDK_BITFIELD_INTERFACE(fs_base, value)
    };

    struct gs_base {
        static constexpr std::uint32_t number = 0xC000'0101;
        std::uint64_t value{};

        CROSSWDK_BITFIELD_INTERFACE(gs_base, value)
    };

    struct kernel_gs_base {
        static constexpr std::uint32_t number = 0xC000'0102;
        std::uint64_t value{};

        CROSSWDK_BITFIELD_INTERFACE(kernel_gs_base, value)
    };

    struct auxilary_tsc {
        static constexpr std::uint32_t number = 0xC000'0103;
        std::uint64_t value{};

        CROSSWDK_BITFIELD_PROXY(value, auxilary_tsc_data, std::uint32_t, 0, 31)
        CROSSWDK_BITFIELD_PROXY(value, reserved, std::uint32_t, 32, 63)

        CROSSWDK_BITFIELD_INTERFACE(auxilary_tsc, value)
    };

} // namespace arch

#endif // WDK_ARCH_MSRS_HPP
