#ifndef WDK_ARCH_CONTROL_REGS_HPP
#define WDK_ARCH_CONTROL_REGS_HPP

namespace arch {
    struct cr0 : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<bool, 0> protection_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 1> monitor_coprocessor_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 2> emulate_fpu_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 3> task_switched_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 4> extension_type_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 5> numeric_error_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 6, 15> reserved1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 16> write_protect_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 17> reserved2_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 18> alignment_mask_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 19, 28> reserved3_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 29> not_write_through_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 30> cache_disable_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 31> paging_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 32, 63> reserved4_;

        constexpr auto protection(this auto&& self) noexcept {
            return self[protection_];
        }

        constexpr auto monitor_coprocessor(this auto&& self) noexcept {
            return self[monitor_coprocessor_];
        }

        constexpr auto emulate_fpu(this auto&& self) noexcept {
            return self[emulate_fpu_];
        }

        constexpr auto task_switched(this auto&& self) noexcept {
            return self[task_switched_];
        }

        constexpr auto extension_type(this auto&& self) noexcept {
            return self[extension_type_];
        }

        constexpr auto numeric_error(this auto&& self) noexcept {
            return self[numeric_error_];
        }

        constexpr auto reserved1(this auto&& self) noexcept {
            return self[reserved1_];
        }

        constexpr auto write_protect(this auto&& self) noexcept {
            return self[write_protect_];
        }

        constexpr auto reserved2(this auto&& self) noexcept {
            return self[reserved2_];
        }

        constexpr auto alignment_mask(this auto&& self) noexcept {
            return self[alignment_mask_];
        }

        constexpr auto reserved3(this auto&& self) noexcept {
            return self[reserved3_];
        }

        constexpr auto not_write_through(this auto&& self) noexcept {
            return self[not_write_through_];
        }

        constexpr auto cache_disable(this auto&& self) noexcept {
            return self[cache_disable_];
        }

        constexpr auto paging(this auto&& self) noexcept {
            return self[paging_];
        }

        constexpr auto reserved4(this auto&& self) noexcept {
            return self[reserved4_];
        }
    };

    struct cr2 : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 0, 63> page_fault_linear_address_;

        constexpr auto page_fault_linear_address(this auto&& self) noexcept {
            return self[page_fault_linear_address_];
        }
    };

    struct cr3 : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 0, 2> reserved1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 3> write_through_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 4> cache_disable_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 5, 11> reserved2_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 12, 51> pml4_frame_number_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 52, 63> reserved3_;

        constexpr auto reserved1(this auto&& self) noexcept {
            return self[reserved1_];
        }

        constexpr auto write_through(this auto&& self) noexcept {
            return self[write_through_];
        }

        constexpr auto cache_disable(this auto&& self) noexcept {
            return self[cache_disable_];
        }

        constexpr auto reserved2(this auto&& self) noexcept {
            return self[reserved2_];
        }

        constexpr auto pml4_frame_number(this auto&& self) noexcept {
            return self[pml4_frame_number_];
        }

        constexpr auto reserved3(this auto&& self) noexcept {
            return self[reserved3_];
        }
    };

    struct cr4 : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<bool, 0> virtual_8086_mode_extensions_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 1> protected_mode_virtual_interrupts_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 2> time_stamp_disable_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 3> debugging_extensions_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 4> page_size_extensions_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 5> physical_address_extensions_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 6> machine_check_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 7> page_global_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 8> performance_monitoring_counter_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 9> os_fxsave_fxrstor_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 10> os_xmm_exception_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 11> usermode_instruction_prevention_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 12> linear_address_57bits_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 13> vmx_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 14> smx_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 15> reserved1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 16> fs_gs_base_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 17> process_context_identifier_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 18> os_xsave_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 19> keylocker_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 20> supervisor_execution_prevention_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 21> supervisor_access_prevention_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 22> protection_key_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 23> control_flow_enforcement_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 24> protection_key_for_supervisor_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 25, 63> reserved3_;

        constexpr auto virtual_8086_mode_extensions(this auto&& self) noexcept {
            return self[virtual_8086_mode_extensions_];
        }

        constexpr auto protected_mode_virtual_interrupts(this auto&& self) noexcept {
            return self[protected_mode_virtual_interrupts_];
        }

        constexpr auto time_stamp_disable(this auto&& self) noexcept {
            return self[time_stamp_disable_];
        }

        constexpr auto debugging_extensions(this auto&& self) noexcept {
            return self[debugging_extensions_];
        }

        constexpr auto page_size_extensions(this auto&& self) noexcept {
            return self[page_size_extensions_];
        }

        constexpr auto physical_address_extensions(this auto&& self) noexcept {
            return self[physical_address_extensions_];
        }

        constexpr auto machine_check(this auto&& self) noexcept {
            return self[machine_check_];
        }

        constexpr auto page_global(this auto&& self) noexcept {
            return self[page_global_];
        }

        constexpr auto performance_monitoring_counter(this auto&& self) noexcept {
            return self[performance_monitoring_counter_];
        }

        constexpr auto os_fxsave_fxrstor(this auto&& self) noexcept {
            return self[os_fxsave_fxrstor_];
        }

        constexpr auto os_xmm_exception(this auto&& self) noexcept {
            return self[os_xmm_exception_];
        }

        constexpr auto usermode_instruction_prevention(this auto&& self) noexcept {
            return self[usermode_instruction_prevention_];
        }

        constexpr auto linear_address_57bits(this auto&& self) noexcept {
            return self[linear_address_57bits_];
        }

        constexpr auto vmx(this auto&& self) noexcept {
            return self[vmx_];
        }

        constexpr auto smx(this auto&& self) noexcept {
            return self[smx_];
        }

        constexpr auto reserved1(this auto&& self) noexcept {
            return self[reserved1_];
        }

        constexpr auto fs_gs_base(this auto&& self) noexcept {
            return self[fs_gs_base_];
        }

        constexpr auto process_context_identifier(this auto&& self) noexcept {
            return self[process_context_identifier_];
        }

        constexpr auto os_xsave(this auto&& self) noexcept {
            return self[os_xsave_];
        }

        constexpr auto keylocker(this auto&& self) noexcept {
            return self[keylocker_];
        }

        constexpr auto supervisor_execution_prevention(this auto&& self) noexcept {
            return self[supervisor_execution_prevention_];
        }

        constexpr auto supervisor_access_prevention(this auto&& self) noexcept {
            return self[supervisor_access_prevention_];
        }

        constexpr auto protection_key(this auto&& self) noexcept {
            return self[protection_key_];
        }

        constexpr auto control_flow_enforcement(this auto&& self) noexcept {
            return self[control_flow_enforcement_];
        }

        constexpr auto protection_key_for_supervisor(this auto&& self) noexcept {
            return self[protection_key_for_supervisor_];
        }

        constexpr auto reserved3(this auto&& self) noexcept {
            return self[reserved3_];
        }
    };

    struct cr8 : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 0, 3> task_priority_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint64_t, 4, 63> reserved_;

        constexpr auto task_priority(this auto&& self) noexcept {
            return self[task_priority_];
        }

        constexpr auto reserved(this auto&& self) noexcept {
            return self[reserved_];
        }
    };

    enum class bp_type : std::uint8_t {
        execution = 0b00,
        write = 0b01,
        io = 0b10,
        read_write = 0b11
    };

    struct dr6 : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<bool, 0> bp0_condition_detected_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 1> bp1_condition_detected_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 2> bp2_condition_detected_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 3> bp3_condition_detected_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 4, 10> reserved1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 11> bus_lock_detected_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 12> reserved2_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 13> bp_debug_access_detected_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 14> bp_single_step_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 15> bp_task_switch_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 16> restricted_transactional_memory_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 17, 31> reserved3_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 32, 63> reserved4_;

        constexpr auto bp0_condition_detected(this auto&& self) noexcept {
            return self[bp0_condition_detected_];
        }

        constexpr auto bp1_condition_detected(this auto&& self) noexcept {
            return self[bp1_condition_detected_];
        }

        constexpr auto bp2_condition_detected(this auto&& self) noexcept {
            return self[bp2_condition_detected_];
        }

        constexpr auto bp3_condition_detected(this auto&& self) noexcept {
            return self[bp3_condition_detected_];
        }

        constexpr auto reserved1(this auto&& self) noexcept {
            return self[reserved1_];
        }

        constexpr auto bus_lock_detected(this auto&& self) noexcept {
            return self[bus_lock_detected_];
        }

        constexpr auto reserved2(this auto&& self) noexcept {
            return self[reserved2_];
        }

        constexpr auto bp_debug_access_detected(this auto&& self) noexcept {
            return self[bp_debug_access_detected_];
        }

        constexpr auto bp_single_step(this auto&& self) noexcept {
            return self[bp_single_step_];
        }

        constexpr auto bp_task_switch(this auto&& self) noexcept {
            return self[bp_task_switch_];
        }

        constexpr auto restricted_transactional_memory(this auto&& self) noexcept {
            return self[restricted_transactional_memory_];
        }

        constexpr auto reserved3(this auto&& self) noexcept {
            return self[reserved3_];
        }

        constexpr auto reserved4(this auto&& self) noexcept {
            return self[reserved4_];
        }
    };

    struct dr7 : crosswdk::utils::bits64 {
        using crosswdk::utils::bits64::bits64;
        using crosswdk::utils::bits64::operator=;

        static constexpr crosswdk::utils::bitfield_descriptor<bool, 0> local_bp0_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 1> global_bp0_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 2> local_bp1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 3> global_bp1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 4> local_bp2_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 5> global_bp2_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 6> local_bp3_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 7> global_bp3_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 8> local_bp_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 9> global_bp_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 10> reserved1_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 11> restricted_transactional_memory_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 12> reserved2_;
        static constexpr crosswdk::utils::bitfield_descriptor<bool, 13> general_detect_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 14, 15> reserved3_;
        static constexpr crosswdk::utils::bitfield_descriptor<bp_type, 16, 17> bp0_type_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 18, 19> bp0_length_;
        static constexpr crosswdk::utils::bitfield_descriptor<bp_type, 20, 21> bp1_type_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 22, 23> bp1_length_;
        static constexpr crosswdk::utils::bitfield_descriptor<bp_type, 24, 25> bp2_type_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 26, 27> bp2_length_;
        static constexpr crosswdk::utils::bitfield_descriptor<bp_type, 28, 29> bp3_type_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 30, 31> bp3_length_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint32_t, 32, 63> reserved4_;

        constexpr auto local_bp0(this auto&& self) noexcept {
            return self[local_bp0_];
        }

        constexpr auto global_bp0(this auto&& self) noexcept {
            return self[global_bp0_];
        }

        constexpr auto local_bp1(this auto&& self) noexcept {
            return self[local_bp1_];
        }

        constexpr auto global_bp1(this auto&& self) noexcept {
            return self[global_bp1_];
        }

        constexpr auto local_bp2(this auto&& self) noexcept {
            return self[local_bp2_];
        }

        constexpr auto global_bp2(this auto&& self) noexcept {
            return self[global_bp2_];
        }

        constexpr auto local_bp3(this auto&& self) noexcept {
            return self[local_bp3_];
        }

        constexpr auto global_bp3(this auto&& self) noexcept {
            return self[global_bp3_];
        }

        constexpr auto local_bp(this auto&& self) noexcept {
            return self[local_bp_];
        }

        constexpr auto global_bp(this auto&& self) noexcept {
            return self[global_bp_];
        }

        constexpr auto reserved1(this auto&& self) noexcept {
            return self[reserved1_];
        }

        constexpr auto restricted_transactional_memory(this auto&& self) noexcept {
            return self[restricted_transactional_memory_];
        }

        constexpr auto reserved2(this auto&& self) noexcept {
            return self[reserved2_];
        }

        constexpr auto general_detect(this auto&& self) noexcept {
            return self[general_detect_];
        }

        constexpr auto reserved3(this auto&& self) noexcept {
            return self[reserved3_];
        }

        constexpr auto bp0_type(this auto&& self) noexcept {
            return self[bp0_type_];
        }

        constexpr auto bp0_length(this auto&& self) noexcept {
            return self[bp0_length_];
        }

        constexpr auto bp1_type(this auto&& self) noexcept {
            return self[bp1_type_];
        }

        constexpr auto bp1_length(this auto&& self) noexcept {
            return self[bp1_length_];
        }

        constexpr auto bp2_type(this auto&& self) noexcept {
            return self[bp2_type_];
        }

        constexpr auto bp2_length(this auto&& self) noexcept {
            return self[bp2_length_];
        }

        constexpr auto bp3_type(this auto&& self) noexcept {
            return self[bp3_type_];
        }

        constexpr auto bp3_length(this auto&& self) noexcept {
            return self[bp3_length_];
        }

        constexpr auto reserved4(this auto&& self) noexcept {
            return self[reserved4_];
        }
    };

} // namespace arch

#endif // WDK_ARCH_CONTROL_REGS_HPP
