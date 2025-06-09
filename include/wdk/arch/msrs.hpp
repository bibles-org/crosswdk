#ifndef WDK_ARCH_MSRS_HPP
#define WDK_ARCH_MSRS_HPP

namespace arch {
    template <typename T>
    concept is_msr = requires { T::number; };

    struct efer {
        MAKE_SCALAR_CONVERTIBLE(efer, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'0080;

        std::uint64_t syscall_extensions                  : 1 {};
        std::uint64_t reserved1                           : 7 {};
        std::uint64_t long_mode                           : 1 {};
        std::uint64_t reserved2                           : 1 {};
        std::uint64_t long_mode_active                    : 1 {};
        std::uint64_t no_execute                          : 1 {};
        std::uint64_t amd64_svm                           : 1 {};
        std::uint64_t amd64_long_mode_segment_limit       : 1 {};
        std::uint64_t amd64_fast_fxsave_fxrstor           : 1 {};
        std::uint64_t amd64_translation_cache_extension   : 1 {};
        std::uint64_t amd64_execute_only_pte              : 1 {}; // this is xotext, allows any given pte to be marked as execute only
        std::uint64_t amd64_mcommit                       : 1 {};
        std::uint64_t amd64_interruptible_wbinvd_wbnoinvd : 1 {};
        std::uint64_t reserved3                           : 1 {};
        std::uint64_t amd64_upper_address_ignore          : 1 {};
        std::uint64_t amd64_auto_ibrs                     : 1 {};
        std::uint64_t reserved4                           : 42 {};
    };

    // virtual machine host save physical address as per the AMD manual
    struct vmhs_pa {
        MAKE_SCALAR_CONVERTIBLE(vmhs_pa, std::uint64_t)
        static constexpr std::uint32_t number = 0xC001'0117;

        std::uint64_t value{};
    };

    struct lstar {
        MAKE_SCALAR_CONVERTIBLE(lstar, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'0082;

        std::uint64_t value{};
    };

    struct cstar {
        MAKE_SCALAR_CONVERTIBLE(cstar, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'0083;

        std::uint64_t value{};
    };

    struct syscall_flag_mask {
        MAKE_SCALAR_CONVERTIBLE(syscall_flag_mask, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'0084;

        std::uint64_t value{};
    };

    // max performance
    struct mperf {
        MAKE_SCALAR_CONVERTIBLE(mperf, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'00E7;

        std::uint64_t max_core_clocks_counter{};
    };

    // actual performance
    struct aperf {
        MAKE_SCALAR_CONVERTIBLE(aperf, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'00E8;

        std::uint64_t actual_core_clocks_counter{};
    };

    // instructions retired
    struct irperf {
        MAKE_SCALAR_CONVERTIBLE(irperf, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'00E9;

        std::uint64_t instructions_retired_counter : 48 {};
        std::uint64_t reserved                     : 16 {};
    };

    struct fs_base {
        MAKE_SCALAR_CONVERTIBLE(fs_base, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'0100;

        std::uint64_t value{};
    };

    struct gs_base {
        MAKE_SCALAR_CONVERTIBLE(gs_base, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'0101;

        std::uint64_t value{};
    };

    struct kernel_gs_base {
        MAKE_SCALAR_CONVERTIBLE(kernel_gs_base, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'0102;

        std::uint64_t value{};
    };

    struct auxilary_tsc {
        MAKE_SCALAR_CONVERTIBLE(auxilary_tsc, std::uint64_t)
        static constexpr std::uint32_t number = 0xC000'0103;

        std::uint64_t auxilary_tsc_data : 32 {};
        std::uint64_t reserved          : 32 {};
    };
} // namespace arch

#endif // WDK_ARCH_MSRS_HPP
