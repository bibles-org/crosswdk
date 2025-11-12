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

    template <typename T1, typename T2, typename... Ts>
        requires utils::is_enum_or_integral<T1> && utils::is_enum_or_integral<T2>
    ALWAYS_INLINE ntstatus print_ex(T1 component_id, T2 level, const char* fmt, Ts&&... args) {
        return DbgPrintEx(
                static_cast<std::uint32_t>(component_id), static_cast<std::uint32_t>(level), fmt,
                std::forward<Ts>(args)...
        );
    }

    template <typename T1, typename T2>
        requires utils::is_enum_or_integral<T1> && utils::is_enum_or_integral<T2>
    ALWAYS_INLINE ntstatus vprint_ex(T1 component_id, T2 level, const char* fmt, va_list args) {
        return vDbgPrintEx(static_cast<std::uint32_t>(component_id), static_cast<std::uint32_t>(level), fmt, args);
    }

    ALWAYS_INLINE bool send_nmi(const std::uint32_t processor_index) {
        win::AFFINITY_EX affinity{};
        win::KeInitializeAffinityEx(&affinity);
        win::KeAddProcessorAffinityEx(&affinity, processor_index);
        return win::HalSendNMI(&affinity);
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

#endif // WDK_WINDOWS_HPP
