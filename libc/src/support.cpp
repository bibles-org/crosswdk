#include <support.h>
#include <wdk/windows/windows.hpp>

#include <cstdarg>
#include <new>

constexpr auto pool_tag = static_cast<std::uint32_t>('ppck');

extern "C" {

void* malloc(size_t size) {
    if (size == 0) {
        size = 1;
    }
    return win::ExAllocatePoolWithTag(win::pool_type::NonPagedPoolNx, size, pool_tag);
}

void free(void* ptr) {
    if (ptr) {
        win::ExFreePool(ptr);
    }
}

void* calloc(size_t num, size_t size) {
    const size_t total_size = num * size;
    if (total_size == 0) {
        return nullptr;
    }
    void* ptr = malloc(total_size);
    if (ptr) {
        win::RtlFillMemory(ptr, total_size, 0);
    }
    return ptr;
}

void* realloc(void* ptr, size_t new_size) {
    if (ptr == nullptr) {
        return malloc(new_size);
    }
    if (new_size == 0) {
        free(ptr);
        return nullptr;
    }

    return nullptr;
}

void* memcpy(void* dst, const void* src, size_t n) {
    win::RtlCopyMemory(dst, src, n);
    return dst;
}

void* memmove(void* dst, const void* src, size_t n) {
    win::RtlMoveMemory(dst, src, n);
    return dst;
}

void* memset(void* dst, int ch, size_t n) {
    win::RtlFillMemory(dst, n, static_cast<unsigned char>(ch));
    return dst;
}

int memcmp(const void* a, const void* b, size_t n) {
    const auto* p1 = static_cast<const unsigned char*>(a);
    const auto* p2 = static_cast<const unsigned char*>(b);
    for (size_t i = 0; i < n; ++i) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }
    return 0;
}

void* memchr(const void* s, int c, size_t n) {
    auto p = static_cast<const unsigned char*>(s);
    for (size_t i = 0; i < n; ++i) {
        if (p[i] == static_cast<unsigned char>(c)) {
            return const_cast<void*>(static_cast<const void*>(p + i));
        }
    }
    return nullptr;
}

wchar_t* wcschr(const wchar_t* s, wchar_t c) {
    while (*s != L'\0') {
        if (*s == c) {
            return const_cast<wchar_t*>(s);
        }
        s++;
    }
    return (*s == c) ? const_cast<wchar_t*>(s) : nullptr;
}

wchar_t* wcsrchr(const wchar_t* s, wchar_t c) {
    const wchar_t* last = nullptr;
    do {
        if (*s == c) {
            last = s;
        }
    } while (*s++ != L'\0');
    return const_cast<wchar_t*>(last);
}

wchar_t* wcspbrk(const wchar_t* s, const wchar_t* accept) {
    while (*s != L'\0') {
        for (const wchar_t* a = accept; *a != L'\0'; ++a) {
            if (*s == *a) {
                return const_cast<wchar_t*>(s);
            }
        }
        s++;
    }
    return nullptr;
}

wchar_t* wcsstr(const wchar_t* s, const wchar_t* needle) {
    if (*needle == L'\0') {
        return const_cast<wchar_t*>(s);
    }
    for (; *s != L'\0'; ++s) {
        const wchar_t* h = s;
        const wchar_t* n = needle;
        while (*h != L'\0' && *n != L'\0' && *h == *n) {
            h++;
            n++;
        }
        if (*n == L'\0') {
            return const_cast<wchar_t*>(s);
        }
    }
    return nullptr;
}

wchar_t* wmemchr(const wchar_t* s, wchar_t c, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == c) {
            return const_cast<wchar_t*>(s + i);
        }
    }
    return nullptr;
}

int atexit(void (*)(void)) {
    return 0;
}

int remove(const char*) {
    return -1;
}

void abort() {
    win::KeBugCheckEx(0xDEADBEEF, 0, 0, 0, 0);
}

void __cxa_pure_virtual() {
    win::KeBugCheckEx(0xDEADBEEF, 1, 0, 0, 0);
}

} // extern "C"

void std::__libcpp_verbose_abort(char const* format, ...) noexcept {
    va_list args;
    va_start(args, format);
    win::vprint_ex(0, 0, format, args);
    va_end(args);

    win::KeBugCheckEx(0xDEADBEEF, 2, reinterpret_cast<uintptr_t>(format), 0, 0);

    // to satisfy noreturn
    std::unreachable();
}

void* operator new(std::size_t size) {
    return malloc(size);
}


void* operator new[](std::size_t size) {
    return malloc(size);
}

void* operator new(std::size_t size, std::align_val_t alignment) {
    if (static_cast<std::size_t>(alignment) <= 16) {
        return win::ExAllocatePoolWithTag(win::pool_type::NonPagedPoolNx, size, pool_tag);
    }
    return win::ExAllocatePoolWithTag(win::pool_type::NonPagedPoolNxCacheAligned, size, pool_tag);
}

void* operator new[](std::size_t size, std::align_val_t alignment) {
    return operator new(size, alignment);
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

void operator delete(void* ptr, std::size_t) noexcept {
    free(ptr);
}

void operator delete[](void* ptr, std::size_t) noexcept {
    free(ptr);
}

void operator delete(void* ptr, std::align_val_t) noexcept {
    free(ptr);
}

void operator delete[](void* ptr, std::align_val_t) noexcept {
    free(ptr);
}

void operator delete(void* ptr, std::size_t, std::align_val_t) noexcept {
    free(ptr);
}

void operator delete[](void* ptr, std::size_t, std::align_val_t) noexcept {
    free(ptr);
}
