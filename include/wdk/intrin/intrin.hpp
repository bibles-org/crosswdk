#ifndef WDK_INTRINSICS_HPP
#define WDK_INTRINSICS_HPP

#include "../arch/arch.hpp"
#include "../utils.hpp"

#include "amd.hpp"
#include "intel.hpp"

#include <array>

namespace intrin {
    ALWAYS_INLINE void halt() {
        asm volatile("hlt;");
    }

    ALWAYS_INLINE void cli() {
        asm volatile("cli;");
    }

    ALWAYS_INLINE void sti() {
        asm volatile("sti;");
    }

    ALWAYS_INLINE void nop() {
        asm volatile("nop;");
    }

    ALWAYS_INLINE void pause() {
        asm volatile("pause;");
    }

    template <int N>
    ALWAYS_INLINE void int_() {
        asm volatile("int %[vec];"
                     :
                     : [vec] "i"(N));
    }

    ALWAYS_INLINE void int3() {
        return int_<3>();
    }

    ALWAYS_INLINE void iret() {
        asm volatile("iret;");
    }

    ALWAYS_INLINE std::uint64_t rdmsr(const std::uint32_t msr) {
        std::uint32_t low, high;
        asm volatile("rdmsr;"
                     : "=a"(low), "=d"(high)
                     : "c"(msr));
        return (static_cast<std::uint64_t>(high) << 32) | low;
    }

    template <arch::is_msr T>
    ALWAYS_INLINE T rdmsr() {
        return rdmsr(T::number);
    }

    ALWAYS_INLINE void wrmsr(const std::uint32_t msr, const std::uint64_t value) {
        std::uint32_t low = static_cast<std::uint32_t>(value);
        std::uint32_t high = static_cast<std::uint32_t>(value >> 32);

        asm volatile("wrmsr;"
                     :
                     : "c"(msr), "a"(low), "d"(high)
                     : "memory");
    }

    template <arch::is_msr T>
    ALWAYS_INLINE void wrmsr(const T& value) {
        return wrmsr(T::number, static_cast<std::uint64_t>(value));
    }

    ALWAYS_INLINE void invlpg(const arch::address address) {
        asm volatile("invlpg (%[addr]);"
                     :
                     : [addr] "r"(address)
                     : "memory");
    }

    ALWAYS_INLINE void lfence() {
        asm volatile("lfence;"
                     :
                     :
                     : "memory");
    }

    ALWAYS_INLINE void sfence() {
        asm volatile("sfence;"
                     :
                     :
                     : "memory");
    }

    ALWAYS_INLINE void mfence() {
        asm volatile("mfence;"
                     :
                     :
                     : "memory");
    }

    ALWAYS_INLINE std::uint64_t rdtsc() {
        std::uint32_t low, high;
        asm volatile("rdtsc;"
                     : "=a"(low), "=d"(high));
        return (static_cast<std::uint64_t>(high) << 32) | low;
    }

    ALWAYS_INLINE arch::address read_dr0() {
        std::uint64_t value;
        asm volatile("mov %%dr0, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE arch::address read_dr1() {
        std::uint64_t value;
        asm volatile("mov %%dr1, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE arch::address read_dr2() {
        std::uint64_t value;
        asm volatile("mov %%dr2, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE arch::address read_dr3() {
        std::uint64_t value;
        asm volatile("mov %%dr3, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE arch::dr6 read_dr6() {
        std::uint64_t value;
        asm volatile("mov %%dr6, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE arch::dr7 read_dr7() {
        std::uint64_t value;
        asm volatile("mov %%dr7, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    `

            ALWAYS_INLINE void
            write_dr1(arch::address value) {
        asm volatile("mov %[val], %%dr1;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE void write_dr2(arch::address value) {
        asm volatile("mov %[val], %%dr2;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE void write_dr3(arch::address value) {
        asm volatile("mov %[val], %%dr3;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE void write_dr6(std::uint64_t value) {
        asm volatile("mov %[val], %%dr6;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE void write_dr7(std::uint64_t value) {
        asm volatile("mov %[val], %%dr7;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE arch::cr0 read_cr0() {
        std::uint64_t value;
        asm volatile("mov %%cr0, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE arch::cr2 read_cr2() {
        std::uint64_t value;
        asm volatile("mov %%cr2, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE arch::cr3 read_cr3() {
        std::uint64_t value;
        asm volatile("mov %%cr3, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE arch::cr4 read_cr4() {
        std::uint64_t value;
        asm volatile("mov %%cr4, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE arch::cr8 read_cr8() {
        std::uint64_t value;
        asm volatile("mov %%cr8, %[val];"
                     : [val] "=r"(value));
        return value;
    }

    ALWAYS_INLINE void write_cr0(std::uint64_t value) {
        asm volatile("mov %[val], %%cr0;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE void write_cr2(std::uint64_t value) {
        asm volatile("mov %[val], %%cr2;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE void write_cr3(std::uint64_t value) {
        asm volatile("mov %[val], %%cr3;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE void write_cr4(std::uint64_t value) {
        asm volatile("mov %[val], %%cr4;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE void write_cr8(std::uint64_t value) {
        asm volatile("mov %[val], %%cr8;"
                     :
                     : [val] "r"(value));
    }

    ALWAYS_INLINE void lidt(const arch::interrupt_descriptor_table& idt) {
        asm volatile("lidt %[idt];"
                     :
                     : [idt] "m"(idt));
    }

    ALWAYS_INLINE arch::interrupt_descriptor_table sidt() {
        arch::interrupt_descriptor_table idt{};
        asm volatile("sidt %[idt];"
                     : [idt] "=m"(idt)
                     :
                     : "memory");
        return idt;
    }

    ALWAYS_INLINE void lgdt(const arch::global_descriptor_table& gdt) {
        asm volatile("lgdt %[gdt];"
                     :
                     : [gdt] "m"(gdt));
    }

    ALWAYS_INLINE arch::global_descriptor_table sgdt() {
        arch::global_descriptor_table gdt{};
        asm volatile("sgdt %[gdt];"
                     : [gdt] "=m"(gdt)
                     :
                     : "memory");
        return gdt;
    }

    ALWAYS_INLINE void lldt(arch::segment_selector ldt) {
        asm volatile("lldt %[ldt_sel];"
                     :
                     : [ldt_sel] "r"(ldt));
    }

    ALWAYS_INLINE arch::segment_selector sldt() {
        arch::segment_selector ldt{};
        asm volatile("sldt %[ldt_sel];"
                     : [ldt_sel] "=r"(ldt));
        return ldt;
    }


    ALWAYS_INLINE void ltr(arch::segment_selector tr) {
        asm volatile("ltr %[tr_sel];"
                     :
                     : [tr_sel] "r"(tr));
    }

    ALWAYS_INLINE arch::segment_selector str() {
        arch::segment_selector tr{};
        asm volatile("str %[tr_sel];"
                     : [tr_sel] "=r"(tr));
        return tr;
    }

    ALWAYS_INLINE std::uint32_t stmxcsr() {
        std::uint32_t value;
        asm volatile("stmxcsr %[val];"
                     : [val] "=m"(value)
                     :
                     : "memory");
        return value;
    }

    ALWAYS_INLINE void ldmxcsr(const std::uint32_t value) {
        asm volatile("ldmxcsr %[val];"
                     :
                     : [val] "m"(value));
    }

    ALWAYS_INLINE void outb(std::uint16_t port, std::uint8_t value) {
        asm volatile("outb %[val], %[port];"
                     :
                     : [val] "a"(value), [port] "Nd"(port));
    }

    ALWAYS_INLINE void outw(std::uint16_t port, std::uint16_t value) {
        asm volatile("outw %[val], %[port];"
                     :
                     : [val] "a"(value), [port] "Nd"(port));
    }

    ALWAYS_INLINE void outl(std::uint16_t port, std::uint32_t value) {
        asm volatile("outl %[val], %[port];"
                     :
                     : [val] "a"(value), [port] "Nd"(port));
    }

    ALWAYS_INLINE std::uint8_t inb(std::uint16_t port) {
        std::uint8_t value;
        asm volatile("inb %[port], %[val];"
                     : [val] "=a"(value)
                     : [port] "Nd"(port));
        return value;
    }

    ALWAYS_INLINE std::uint16_t inw(std::uint16_t port) {
        std::uint16_t value;
        asm volatile("inw %[port], %[val];"
                     : [val] "=a"(value)
                     : [port] "Nd"(port));
        return value;
    }

    ALWAYS_INLINE std::uint32_t inl(std::uint16_t port) {
        std::uint32_t value;
        asm volatile("inl %[port], %[val];"
                     : [val] "=a"(value)
                     : [port] "Nd"(port));
        return value;
    }

    ALWAYS_INLINE std::array<std::uint32_t, 4> cpuid(std::uint32_t leaf, std::uint32_t subleaf = 0) {
        std::array<std::uint32_t, 4> result{};
        asm volatile("cpuid;"
                     : "=a"(result[0]), "=b"(result[1]), "=c"(result[2]), "=d"(result[3])
                     : "a"(leaf), "c"(subleaf));
        return result;
    }

} // namespace intrin
#endif // WDK_INTRINSICS_HPP
