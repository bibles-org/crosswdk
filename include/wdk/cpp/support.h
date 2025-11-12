#ifndef WDK_LIBCXX_SUPPORT_HPP
#define WDK_LIBCXX_SUPPORT_HPP

#ifdef __cplusplus
extern "C" {
#endif
typedef __SIZE_TYPE__ wdk_size_t;
typedef __PTRDIFF_TYPE__ wdk_ptrdiff_t;

#ifndef WDK_SIZE_T_DEFINED
#define WDK_SIZE_T_DEFINED
typedef wdk_size_t size_t;
typedef wdk_ptrdiff_t ptrdiff_t;
#endif

typedef struct {
    unsigned __state;
} mbstate_t;

#ifndef _WDK_HAS_WCHAR
#define _WDK_HAS_WCHAR 1
#endif

#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif

typedef unsigned int wint_t;

#ifndef EOF
#define EOF (-1)
#endif

#ifndef WEOF
#define WEOF ((wint_t) - 1)
#endif

void* memcpy(void* dst, const void* src, wdk_size_t n);
void* memmove(void* dst, const void* src, wdk_size_t n);
void* memset(void* dst, int ch, wdk_size_t n);
int memcmp(const void* a, const void* b, wdk_size_t n);
void* memchr(const void* s, int ch, wdk_size_t n);

wchar_t* wcschr(const wchar_t* s, wchar_t c);
wchar_t* wcsrchr(const wchar_t* s, wchar_t c);
wchar_t* wcspbrk(const wchar_t* s, const wchar_t* accept);
wchar_t* wcsstr(const wchar_t* s, const wchar_t* needle);
wchar_t* wmemchr(const wchar_t* s, wchar_t c, wdk_size_t n);

void* malloc(wdk_size_t size);
void* calloc(wdk_size_t nmemb, wdk_size_t size);
void* realloc(void* ptr, wdk_size_t size);
void free(void* ptr);

int remove(const char* pathname);

#ifdef __cplusplus
}
#endif

#endif /* WDK_LIBCXX_SUPPORT_HPP */
