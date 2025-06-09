// safe windows wrappers and helper functions for extended functionality
#ifndef WDK_WINDOWS_HPP
#define WDK_WINDOWS_HPP
#include "../arch/arch.hpp"
#include "declarations.hpp"

namespace win {
    template <typename... Ts>
    ALWAYS_INLINE ntstatus print(const char* fmt, Ts&&... args) {
        return DbgPrint(fmt, std::forward<Ts>(args)...);
    }

    template <typename... Ts>
    ALWAYS_INLINE ntstatus print_ex(const std::uint32_t component_id, const std::uint32_t level, const char* fmt, Ts&&... args) {
        return DbgPrintEx(component_id, level, fmt, std::forward<Ts>(args)...);
    }

    template <std::predicate<std::uint32_t> T>
    ALWAYS_INLINE bool iterate_active_processors(T&& cb) {
        const std::uint32_t active_processors{KeQueryActiveProcessorCount()};
        for (std::uint32_t i{}; i < active_processors; ++i) {
            const auto original_affinity = KeSetSystemAffinityThreadEx(1ull << i);

            const bool keep_iterating = std::invoke(cb, i);

            KeRevertToUserAffinityThreadEx(original_affinity);
            if (!keep_iterating)
                return false;
        }
        return true;
    }
} // namespace win

inline void* operator new(const std::size_t size) {
    return win::ExAllocatePoolWithTag(pool_type::NonPagedPoolNx, size, 0x44434241);
}

inline void operator delete(void* ptr) {
    win::ExFreePool(ptr);
}

#endif // WDK_WINDOWS_HPP
