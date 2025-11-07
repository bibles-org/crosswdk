module;
#include <wdk/wdk.hpp>

export module memory;

/*
 * NOTE: This is pseudocode that unless modified, is not functional without the assumptions below.
 * Assume @param pml4 is the base address of the pml4 table taken from cr3
 * Assume direct access to physical memory is possible
 */
export namespace memory {
    arch::address translation_example(const arch::address pml4, const arch::address linear_address) {
        const auto pml4e = static_cast<arch::pml4e*>(pml4)[linear_address.p4_index()];
        if (pml4e.present() == false) {
            return nullptr;
        }
        const auto pdpe_large = static_cast<arch::pdpe_1gb*>(
                static_cast<arch::address>(pml4e.page_frame_number()) << 12ull
        )[linear_address.p3_index()];
        if (pml4e.present() == false) {
            return nullptr;
        }

        // 1gb mapping
        if (pdpe_large.page_size() == true) {
            return (static_cast<arch::address>(pdpe_large.page_frame_number()) << 30ull) + linear_address.offset_1gb();
        }

        const arch::pdpe pdpe{pdpe_large};
        const auto pde_large = static_cast<arch::pde_2mb*>(
                static_cast<arch::address>(pdpe.page_frame_number()) << 12ull
        )[linear_address.p2_index()];
        if (pde_large.present() == false) {
            return nullptr;
        }

        // 2mb mapping
        if (pde_large.page_size() == true) {
            return (static_cast<arch::address>(pde_large.page_frame_number()) << 21ull) + linear_address.offset_2mb();
        }

        const arch::pde pde{pde_large};
        const auto pte = static_cast<arch::pte*>(
                static_cast<arch::address>(pde.page_frame_number()) << 12ull
        )[linear_address.p1_index()];
        if (pte.present() == false) {
            return nullptr;
        }

        // 4kb mapping
        return (static_cast<arch::address>(pte.page_frame_number()) << 12ull) + linear_address.offset_4kb();
    }
} // namespace memory
