#ifndef WDK_INTEL_INTRINSICS_HPP
#define WDK_INTEL_INTRINSICS_HPP
#include <optional>

namespace intrin::intel {
    ALWAYS_INLINE std::optional<std::uint64_t> vmread(std::uint64_t field) {
        std::uint64_t value{};
        bool success{};

        asm volatile("vmread %[field], %[value];"
                     "setnz %[success];"
                     : [value] "=r"(value), [success] "=r"(success)
                     : [field] "r"(field)
                     : "cc", "memory");

        if (success)
            return value;
        else
            return std::nullopt;
    }

    ALWAYS_INLINE bool vmwrite(std::uint64_t field, std::uint64_t value) {
        bool success{};

        asm volatile("vmwrite %[value], %[field];"
                     "setnz %[success];"
                     : [success] "=r"(success)
                     : [field] "r"(field), [value] "r"(value)
                     : "cc", "memory");

        return success;
    }


} // namespace intrin::intel
#endif // WDK_INTEL_INTRINSICS_HPP
