# CrossWDK

CMake module for (cross)compiling Windows drivers with the WDK.

---

## Introduction

CrossWDK allows building Windows kernel drivers using the WDK and CMake.

**Requirements:**

* WDK 8.0 or higher
* CMake 3.0 or higher
* Ninja build system (recommended)

---

## Usage

Add the path to `FindCrossWDK.cmake` to your `CMAKE_MODULE_PATH`, then:

```cmake
# Specify the path to the WDK libraries if:
# - it is not installed in a common path like in C: or D: in the case of windows.
# - you are compiling on linux so you must specify the path manually.
set(WDK_LIB_PATH "/usr/wdk/x64/lib/")

list(APPEND CMAKE_MODULE_PATH "<path_to_CrossWDK>")
find_package(CrossWDK REQUIRED)
```

**How CrossWDK locates libraries:**

* If `WDK_LIB_PATH` is defined, it searches `${WDK_LIB_PATH}/*.lib`.
* Otherwise, it tries environment variable `WDKContentRoot` and common install locations on C: and D:.

If no `.lib` files are found, configuration fails with an error.

---

## Header Library

This project includes a lightweight header library designed to provide essential types, macros, and compiler intrinsics commonly needed for kernel development. It serves as a minimal alternative to Microsoft's official headers, ensuring compatibility with Clang and GCC.

---

## Adding a kernel driver target

```cmake
wdk_add_driver(<target_name> source1 [source2 ...])
```

This creates an executable with `.sys` as the file extension, sets compiler and linker flags, links against `WDK::NTOSKRNL` by default, and includes a header library shipped with this project.

Example:

```cmake
wdk_add_driver(${PROJECT_NAME} main.cpp)
```

---

## Linking additional WDK libraries

CrossWDK automatically creates imported targets for all WDK `.lib` files found, named `WDK::<LIBNAME_UPPER>`.

To link additional libraries:

```cmake
target_link_libraries(${PROJECT_NAME} WDK::FLTMGR)
```

---

## Credit
This project is a heavily modified and rebranded version of [@SergiusTheBest/FindWDK](https://github.com/SergiusTheBest/FindWDK).