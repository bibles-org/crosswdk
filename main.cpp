#include <support.h>

#include <wdk/wdk.hpp>

using ctor_func = void (*)();
extern "C" ctor_func __CTOR_LIST__[];

void run_static_initializers() {
    for (std::size_t i = 1;; ++i) {
        const auto ctor = __CTOR_LIST__[i];
        if (ctor == nullptr) {
            return;
        }

        ctor();
    }
}

extern "C" win::ntstatus DriverEntry(win::DRIVER_OBJECT*, win::UNICODE_STRING*);

extern "C" win::ntstatus _start(win::DRIVER_OBJECT* a1, win::UNICODE_STRING* a2) {
    run_static_initializers();
    return DriverEntry(a1, a2);
}
