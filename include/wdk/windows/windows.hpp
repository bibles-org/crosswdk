// safe windows wrappers and helper functions for extended functionality
#ifndef WDK_WINDOWS_HPP
#define WDK_WINDOWS_HPP
#include "declarations.hpp"

namespace win {
    constexpr std::uint32_t pool_tag = 0x44434241;

    template <typename... Ts>
    ALWAYS_INLINE ntstatus print(const char* fmt, Ts&&... args) {
        return win::DbgPrint(fmt, std::forward<Ts>(args)...);
    }

    template <crosswdk::utils::is_enum_or_integral T1, crosswdk::utils::is_enum_or_integral T2, typename... Ts>
        requires(sizeof(T1) <= sizeof(std::uint32_t)) && (sizeof(T2) <= sizeof(std::uint32_t))
    ALWAYS_INLINE ntstatus print(T1 component_id, T2 level, const char* fmt, Ts&&... args) {
        return win::DbgPrintEx(
                static_cast<std::uint32_t>(component_id), static_cast<std::uint32_t>(level), fmt,
                std::forward<Ts>(args)...
        );
    }


    ALWAYS_INLINE void send_nmi(const std::uint32_t processor_index) {
        win::AFFINITY_EX affinity;
        win::KeInitializeAffinityEx(affinity);
        win::KeAddProcessorAffinityEx(affinity, processor_index);
        win::HalSendNMI(affinity);
    }

    template <std::predicate<std::uint32_t> T>
    ALWAYS_INLINE bool iterate_active_processors(T&& cb) {
        const std::uint32_t active_processors{win::KeQueryActiveProcessorCount()};
        for (std::uint32_t i{}; i < active_processors; ++i) {
            const auto original_affinity = win::KeSetSystemAffinityThreadEx(1ull << i);

            const bool keep_iterating = std::invoke(cb, i);

            win::KeRevertToUserAffinityThreadEx(original_affinity);
            if (!keep_iterating)
                return false;
        }
        return true;
    }
} // namespace win

// TODO: https://en.cppreference.com/w/cpp/memory/new/operator_new.html
inline void* operator new(std::size_t n) {
    return win::ExAllocatePoolWithTag(win::pool_type::NonPagedPoolNx, n, win::pool_tag);
}

inline void* operator new[](std::size_t n) {
    return win::ExAllocatePoolWithTag(win::pool_type::NonPagedPoolNx, n, win::pool_tag);
}

inline void operator delete(void* p) {
    if (p)
        win::ExFreePool(p);
}

inline void operator delete[](void* p) {
    if (p)
        win::ExFreePool(p);
}

#endif // WDK_WINDOWS_HPP
