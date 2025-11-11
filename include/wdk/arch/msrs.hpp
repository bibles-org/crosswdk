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

        static constexpr crosswdk::utils::bitfield_descriptor<bool, 0> syscall_extensions_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 1, 7> reserved1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 8> long_mode_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 9> reserved2_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 10> long_mode_active_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 11> no_execute_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 12> secure_virtual_machine_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 13> long_mode_segment_limit_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 14> fast_fxsave_fxrstor_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 15> translation_cache_extension_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 16> execute_only_pte_extension_; // amd64 xotext
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 17> mcommit_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 18> interruptible_wbinvd_wbnoinvd_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 19> reserved3_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 20> upper_address_ignore_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 21> auto_ibrs_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 22, 63> reserved4_;

        constexpr auto syscall_extensions(this auto&& self) noexcept {
            return self[syscall_extensions_];
        }

        constexpr auto reserved1(this auto&& self) noexcept {
            return self[reserved1_];
        }

        constexpr auto long_mode(this auto&& self) noexcept {
            return self[long_mode_];
        }

        constexpr auto reserved2(this auto&& self) noexcept {
            return self[reserved2_];
        }

        constexpr auto long_mode_active(this auto&& self) noexcept {
            return self[long_mode_active_];
        }

        constexpr auto no_execute(this auto&& self) noexcept {
            return self[no_execute_];
        }

        constexpr auto secure_virtual_machine(this auto&& self) noexcept {
            return self[secure_virtual_machine_];
        }

        constexpr auto long_mode_segment_limit(this auto&& self) noexcept {
            return self[long_mode_segment_limit_];
        }

        constexpr auto fast_fxsave_fxrstor(this auto&& self) noexcept {
            return self[fast_fxsave_fxrstor_];
        }

        constexpr auto translation_cache_extension(this auto&& self) noexcept {
            return self[translation_cache_extension_];
        }

        constexpr auto execute_only_pte_extension(this auto&& self) noexcept {
            return self[execute_only_pte_extension_];
        }

        constexpr auto mcommit(this auto&& self) noexcept {
            return self[mcommit_];
        }

        constexpr auto interruptible_wbinvd_wbnoinvd(this auto&& self) noexcept {
            return self[interruptible_wbinvd_wbnoinvd_];
        }

        constexpr auto reserved3(this auto&& self) noexcept {
            return self[reserved3_];
        }

        constexpr auto upper_address_ignore(this auto&& self) noexcept {
            return self[upper_address_ignore_];
        }

        constexpr auto auto_ibrs(this auto&& self) noexcept {
            return self[auto_ibrs_];
        }

        constexpr auto reserved4(this auto&& self) noexcept {
            return self[reserved4_];
        }
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

        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 0, 63> max_core_clocks_counter_;

        constexpr auto max_core_clocks_counter(this auto&& self) noexcept {
            return self[max_core_clocks_counter_];
        }
    };

    // actual performance
    struct aperf : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'00E8;

        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 0, 63> actual_core_clocks_counter_;

        constexpr auto actual_core_clocks_counter(this auto&& self) noexcept {
            return self[actual_core_clocks_counter_];
        }
    };

    // instructions retired
    struct irperf : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr std::uint32_t number = 0xC000'00E9;

        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 0, 47> instructions_retired_counter_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 48, 63> reserved_;

        constexpr auto instructions_retired_counter(this auto&& self) noexcept {
            return self[instructions_retired_counter_];
        }

        constexpr auto reserved(this auto&& self) noexcept {
            return self[reserved_];
        }
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

        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 0, 31> auxiliary_tsc_data_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 31, 63> reserved_;

        constexpr auto auxiliary_tsc_data(this auto&& self) noexcept {
            return self[auxiliary_tsc_data_];
        }

        constexpr auto reserved(this auto&& self) noexcept {
            return self[reserved_];
        }
    };
} // namespace arch

#endif // WDK_ARCH_MSRS_HPP
