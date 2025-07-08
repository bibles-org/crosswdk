#include <wdk/wdk.hpp>

/*
 * Assume @param pml4 is the base address of the pml4 table taken from cr3
 * Assume direct access to the physical address is possible
 */
static arch::address translation_example(const arch::address pml4, const arch::address linear_address) {
    const auto pml4e = static_cast<arch::pml4e*>(pml4)[linear_address.p4_index];
    if (pml4e.present == false) {
        return nullptr;
    }

    const auto pdpe_large = static_cast<arch::pdpe_1gb*>(
            static_cast<arch::address>(pml4e.page_frame_number) << 12
    )[linear_address.p3_index];
    if (pml4e.present == false) {
        return nullptr;
    }

    // 1gb mapping
    if (pdpe_large.page_size == true) {
        return (static_cast<arch::address>(pdpe_large.page_frame_number) << 30) + linear_address.offset_1gb();
    }

    const arch::pdpe pdpe{pdpe_large};
    const auto pde_large = static_cast<arch::pde_2mb*>(
            static_cast<arch::address>(pdpe.page_frame_number) << 12
    )[linear_address.p2_index];
    if (pde_large.present == false) {
        return nullptr;
    }

    // 2mb mapping
    if (pde_large.page_size == true) {
        return (static_cast<arch::address>(pde_large.page_frame_number) << 21) + linear_address.offset_2mb();
    }

    const arch::pde pde{pde_large};
    const auto pte =
            static_cast<arch::pte*>(static_cast<arch::address>(pde.page_frame_number) << 12)[linear_address.p1_index];
    if (pte.present == false) {
        return nullptr;
    }

    // 4kb mapping
    return (static_cast<arch::address>(pte.page_frame_number) << 12) + linear_address.offset;
}

extern win::ntstatus DriverEntry(win::DRIVER_OBJECT* driver_object, win::UNICODE_STRING*) {
    win::print_ex(0, 0, "Processor count: %u\n", win::KeQueryActiveProcessorCount());

    driver_object->DriverUnload = [](win::DRIVER_OBJECT*) static {
        win::print_ex(0, 0, "DriverUnload\n");
        return win::ntstatus::success;
    };

    // intrin::amd::clgi();
    // intrin::intel::vmread(field);
    intrin::wrmsr(0xC000'0080, intrin::rdmsr(0xC000'0080));
    intrin::write_cr3(intrin::read_cr3());

    // msr <-> 64 bit integer
    auto efer = intrin::rdmsr<arch::efer>();
    efer = intrin::rdmsr(arch::efer::number);
    intrin::wrmsr(efer);
    intrin::wrmsr(arch::efer::number, efer);

    // address <-> 64 bit integer
    // address <-> T* explicitly
    // address <-> void* implicitly
    arch::address entrypoint{nullptr};
    entrypoint = &DriverEntry;
    win::print_ex(0, 0, "Running from: %p\n", entrypoint);

    auto idtr = intrin::sidt();
    for (auto& idte : idtr) {
        win::print_ex(0, 0, "%p\n", idte.get_handler());
    }

    return win::ntstatus::success;
}
