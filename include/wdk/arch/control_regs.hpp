#ifndef WDK_ARCH_CONTROL_REGS_HPP
#define WDK_ARCH_CONTROL_REGS_HPP

namespace arch {
    struct cr0 {
        MAKE_SCALAR_CONVERTIBLE(cr0, std::uint64_t)

        std::uint64_t protection          : 1 {};
        std::uint64_t monitor_coprocessor : 1 {};
        std::uint64_t emulate_fpu         : 1 {};
        std::uint64_t task_switched       : 1 {};
        std::uint64_t extension_type      : 1 {};
        std::uint64_t numeric_error       : 1 {};
        std::uint64_t reserved1           : 10 {};
        std::uint64_t write_protect       : 1 {};
        std::uint64_t reserved2           : 1 {};
        std::uint64_t alignment_mask      : 1 {};
        std::uint64_t reserved3           : 10 {};
        std::uint64_t not_write_through   : 1 {};
        std::uint64_t cache_disable       : 1 {};
        std::uint64_t paging              : 1 {};
        std::uint64_t reserved4           : 32 {};
    } __attribute__((packed));

    struct cr2 {
        MAKE_SCALAR_CONVERTIBLE(cr2, std::uint64_t)

        std::uint64_t page_fault_linear_address{};
    } __attribute__((packed));

    static_assert(sizeof(cr2) == sizeof(std::uint64_t), "arch::cr2 size is incorrect");

    struct cr3 {
        MAKE_SCALAR_CONVERTIBLE(cr3, std::uint64_t)

        std::uint64_t reserved1         : 3 {};
        std::uint64_t write_through     : 1 {};
        std::uint64_t cache_disable     : 1 {};
        std::uint64_t reserved2         : 7 {};
        std::uint64_t pml4_frame_number : 40 {};
        std::uint64_t reserved3         : 12 {};
    } __attribute__((packed));

    static_assert(sizeof(cr3) == sizeof(std::uint64_t), "arch::cr3 size is incorrect");

    struct cr4 {
        MAKE_SCALAR_CONVERTIBLE(cr4, std::uint64_t)

        std::uint64_t virtual_8086_mode_extensions       : 1 {};
        std::uint64_t protected_mode_virtual_interrupts  : 1 {};
        std::uint64_t time_stamp_disable                 : 1 {};
        std::uint64_t debugging_extensions               : 1 {};
        std::uint64_t page_size_extensions               : 1 {};
        std::uint64_t physical_address_extensions        : 1 {};
        std::uint64_t machine_check                      : 1 {};
        std::uint64_t page_global                        : 1 {};
        std::uint64_t performance_monitoring_counter     : 1 {};
        std::uint64_t os_fxsave_fxrstor                  : 1 {};
        std::uint64_t os_xmm_exception                   : 1 {};
        std::uint64_t usermode_instruction_prevention    : 1 {};
        std::uint64_t linear_address_57bits              : 1 {};
        std::uint64_t ia32_vmx                           : 1 {};
        std::uint64_t ia32_smx                           : 1 {};
        std::uint64_t reserved1                          : 1 {};
        std::uint64_t fs_gs_base                         : 1 {};
        std::uint64_t process_context_identifier         : 1 {};
        std::uint64_t os_xsave                           : 1 {};
        std::uint64_t ia32_keylocker                     : 1 {};
        std::uint64_t supervisor_execution_prevention    : 1 {};
        std::uint64_t supervisor_access_prevention       : 1 {};
        std::uint64_t protection_key                     : 1 {};
        std::uint64_t control_flow_enforcement           : 1 {};
        std::uint64_t ia32_protection_key_for_supervisor : 1 {};
        std::uint64_t reserved3                          : 39 {};
    } __attribute__((packed));

    static_assert(sizeof(cr4) == sizeof(std::uint64_t), "arch::cr4 size is incorrect");

    struct cr8 {
        MAKE_SCALAR_CONVERTIBLE(cr8, std::uint64_t)

        std::uint64_t task_priority : 4 {};
        std::uint64_t reserved      : 60 {};
    } __attribute__((packed));

    static_assert(sizeof(cr8) == sizeof(std::uint64_t), "arch::cr8 size is incorrect");

    enum class bp_type : std::uint64_t {
        execution,
        write,
        io,
        read_write
    };

    struct dr6 {
        MAKE_SCALAR_CONVERTIBLE(dr6, std::uint64_t)

        std::uint64_t bp0_condition_detected               : 1 {};
        std::uint64_t bp1_condition_detected               : 1 {};
        std::uint64_t bp2_condition_detected               : 1 {};
        std::uint64_t bp3_condition_detected               : 1 {};
        std::uint64_t reserved1                            : 7 {};
        std::uint64_t amd64_bus_lock_detected              : 1 {};
        std::uint64_t reserved2                            : 1 {};
        std::uint64_t bp_debug_access_detected             : 1 {};
        std::uint64_t bp_single_step                       : 1 {};
        std::uint64_t bp_task_switch                       : 1 {};
        std::uint64_t ia32_restricted_transactional_memory : 1 {};
        std::uint64_t reserved3                            : 15 {};
        std::uint64_t reserved4                            : 32 {};
    } __attribute__((packed));

    static_assert(sizeof(dr6) == sizeof(std::uint64_t), "arch::dr6 size is incorrect");

    struct dr7 {
        MAKE_SCALAR_CONVERTIBLE(dr7, std::uint64_t)

        std::uint64_t local_bp0                            : 1 {};
        std::uint64_t global_bp0                           : 1 {};
        std::uint64_t local_bp1                            : 1 {};
        std::uint64_t global_bp1                           : 1 {};
        std::uint64_t local_bp2                            : 1 {};
        std::uint64_t global_bp2                           : 1 {};
        std::uint64_t local_bp3                            : 1 {};
        std::uint64_t global_bp3                           : 1 {};
        std::uint64_t local_bp                             : 1 {};
        std::uint64_t global_bp                            : 1 {};
        std::uint64_t reserved1                            : 1 {};
        std::uint64_t ia32_restricted_transactional_memory : 1 {};
        std::uint64_t reserved2                            : 1 {};
        std::uint64_t general_detect                       : 1 {};
        std::uint64_t reserved3                            : 2 {};
        bp_type bp0_type                                   : 2 {};
        std::uint64_t bp0_length                           : 2 {};
        bp_type bp1_type                                   : 2 {};
        std::uint64_t bp1_length                           : 2 {};
        bp_type bp2_type                                   : 2 {};
        std::uint64_t bp2_length                           : 2 {};
        bp_type bp3_type                                   : 2 {};
        std::uint64_t bp3_length                           : 2 {};
        std::uint64_t reserved4                            : 32 {};
    } __attribute__((packed));

    static_assert(sizeof(dr7) == sizeof(std::uint64_t), "arch::dr7 size is incorrect");
} // namespace arch

#endif // WDK_ARCH_CONTROL_REGS_HPP
