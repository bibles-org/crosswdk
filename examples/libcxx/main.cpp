#include <support.h>
#include <wdk/wdk.hpp>

#include <cstddef>
#include <memory_resource>
#include <vector>

class driver_memory_resource final : public std::pmr::memory_resource {
private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        (void)alignment;
        return ::malloc(bytes);
    }

    void do_deallocate(void* p, std::size_t, std::size_t) override {
        ::free(p);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

static driver_memory_resource g_driver_mr;

extern "C" win::ntstatus DriverEntry(win::DRIVER_OBJECT* driver_object, win::UNICODE_STRING*) {
    win::print_ex(0, 0, "driver loaded\n");

    driver_object->DriverUnload = [](win::DRIVER_OBJECT*) static {
        win::print_ex(0, 0, "driver unloaded\n");
        return win::ntstatus::success;
    };

    std::pmr::vector<int> vec{&g_driver_mr};

    for (int i = 0; i < 16; ++i) {
        vec.push_back(i * 10);
    }

    win::print_ex(0, 0, "pmr::vector size: %zu\n", static_cast<std::size_t>(vec.size()));

    win::print_ex(0, 0, "pmr::vector contents:");
    for (int v : vec) {
        win::print_ex(0, 0, " %d", v);
    }
    win::print_ex(0, 0, "\n");

    return win::ntstatus::success;
}
