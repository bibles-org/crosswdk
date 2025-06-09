#ifndef WDK_AMD_INTRINSICS_HPP
#define WDK_AMD_INTRINSICS_HPP

namespace intrin::amd {
    ALWAYS_INLINE void stgi() {
        asm volatile("stgi;");
    }

    ALWAYS_INLINE void clgi() {
        asm volatile("clgi;");
    }
} // namespace intrin::amd
#endif // WDK_AMD_INTRINSICS_HPP
