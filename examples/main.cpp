#include <wdk/wdk.hpp>

// module example
import memory;

win::ntstatus DriverEntry(win::DRIVER_OBJECT* driver_object, win::UNICODE_STRING*) {
    win::print(0, 0, "Processor count: %u\n", win::KeQueryActiveProcessorCount());

    driver_object->DriverUnload = [](win::DRIVER_OBJECT*) static {
        win::print(0, 0, "DriverUnload\n");
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
    win::print(0, 0, "Running from: %p\n", entrypoint);

    auto idtr = intrin::sidt();
    for (auto& idte : idtr) {
        win::print(0, 0, "%p\n", idte.get_handler());
    }

    return win::ntstatus::success;
}
