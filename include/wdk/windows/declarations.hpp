// windows function declarations
#ifndef WDK_WINDOWS_DECLARATIONS_HPP
#define WDK_WINDOWS_DECLARATIONS_HPP
#include "types.hpp"

namespace win {
    // variables
    extern "C" {
    extern std::uint8_t* KeNumberProcessors;
    extern arch::address MmBadPointer;
    extern std::uint32_t NtBuildNumber;
    extern /*tmp*/ arch::address PsInitialSystemProcess;
    extern /*tmp*/ arch::address PsLoadedModuleList;
    } // extern "C"


    // functions
    extern "C" {
    // output parameters are taken by reference when they are expected, taken by a pointer when optional and defaulted
    // if applicable
    ntstatus DbgPrint(const char* fmt, ...);

    ntstatus DbgPrintEx(std::uint32_t component_id, std::uint32_t level, const char* fmt, ...);

    std::uint32_t KeQueryActiveProcessorCount(std::uint64_t* active_processors_affinity = nullptr);

    std::uint64_t KeSetSystemAffinityThreadEx(std::uint64_t affinity);

    void KeRevertToUserAffinityThreadEx(std::uint64_t affinity);

    arch::address ExAllocatePoolWithTag(pool_type type, std::size_t size, std::uint32_t tag);

    void ExFreePool(arch::address pool_address);

    arch::address MmGetPhysicalAddress(arch::address virtual_address);

    arch::address MmGetVirtualForPhysical(arch::address physical_address);

    bool MmIsAddressValid(arch::address virtual_address);

    ntstatus RtlGetVersion(OSVERSIONINFO& version_output);

    arch::address RtlFindExportedRoutineByName(arch::address image_base_address, const char* export_name);
    } // extern "C"
} // namespace win
#endif // WDK_WINDOWS_DECLARATIONS_HPP
