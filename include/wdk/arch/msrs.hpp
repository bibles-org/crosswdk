#ifndef WDK_ARCH_MSRS_HPP
#define WDK_ARCH_MSRS_HPP

namespace arch {
    template <typename T>
    concept is_msr = requires {
        { T::number } -> std::convertible_to<std::uint32_t>;
    } && std::is_base_of_v<crosswdk::utils::bits64, T>;

    struct efer : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'0080;

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
    };

    // virtual machine host save physical address as per the AMD manual
    struct vmhs_pa : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC001'0117;
    };

    struct lstar : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'0082;
    };

    struct cstar : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'0083;
    };

    struct syscall_flag_mask : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'0084;
    };

    // max performance
    struct mperf : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'00E7;

        CROSSWDK_BITFIELD_PROXY(value, max_core_clocks_counter, std::uint64_t, 0, 63)
    };

    // actual performance
    struct aperf : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'00E8;

        CROSSWDK_BITFIELD_PROXY(value, actual_core_clocks_counter, std::uint64_t, 0, 63)
    };

    // instructions retired
    struct irperf : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'00E9;

        CROSSWDK_BITFIELD_PROXY(value, instructions_retired_counter, std::uint64_t, 0, 47)
        CROSSWDK_BITFIELD_PROXY(value, reserved, std::uint16_t, 48, 63)
    };

    struct fs_base : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'0100;
    };

    struct gs_base : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'0101;
    };

    struct kernel_gs_base : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'0102;
    };

    struct auxiliary_tsc : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'0103;

        CROSSWDK_BITFIELD_PROXY(value, auxiliary_tsc_data, std::uint32_t, 0, 31)
        CROSSWDK_BITFIELD_PROXY(value, reserved, std::uint32_t, 32, 63)
    };
} // namespace arch

#endif // WDK_ARCH_MSRS_HPP
