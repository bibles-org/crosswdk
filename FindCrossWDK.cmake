if (DEFINED WDK_LIB_PATH)
    message(STATUS "Using user-defined WDK_LIB_PATH: ${WDK_LIB_PATH}")
    file(GLOB WDK_LIB_FILES
            "${WDK_LIB_PATH}/*.lib"
    )
else ()
    # find the wdk libs if the path is not provided
    if (DEFINED ENV{WDKContentRoot})
        file(GLOB WDK_LIB_FILES
                "$ENV{WDKContentRoot}/Lib/*/km/x64/*.lib"  # WDK 10
                "$ENV{WDKContentRoot}/Lib/km/x64/*.lib"    # WDK 8.x
        )
    else ()
        file(GLOB WDK_LIB_FILES
                "C:/Program Files*/Windows Kits/*/Lib/*/km/x64/*.lib"  # WDK 10
                "C:/Program Files*/Windows Kits/*/Lib/km/x64/*.lib"    # WDK 8.x
                "D:/Program Files*/Windows Kits/*/Lib/*/km/x64/*.lib"  # WDK 10 on D:
                "D:/Program Files*/Windows Kits/*/Lib/km/x64/*.lib"    # WDK 8.x on D:
        )
    endif ()
endif ()

if (NOT WDK_LIB_FILES)
    message(FATAL_ERROR "No WDK .lib files found in the specified paths.")
endif ()

if (DEFINED ENV{LIBCXX_FREESTANDING_INSTALL_DIR})
    set(LIBCXX_INSTALL_DIR "$ENV{LIBCXX_FREESTANDING_INSTALL_DIR}")
    message(STATUS "Found freestanding libc++ at: ${LIBCXX_INSTALL_DIR}")

    set(LIBCXX_INCLUDE_DIR "${LIBCXX_INSTALL_DIR}/include/c++/v1")
    set(LIBCXX_LIBRARY_PATH "${LIBCXX_INSTALL_DIR}/lib/libc++.a")

    if (NOT EXISTS "${LIBCXX_INCLUDE_DIR}")
        message(FATAL_ERROR "libc++ include directory not found: ${LIBCXX_INCLUDE_DIR}")
    endif()
    if (NOT EXISTS "${LIBCXX_LIBRARY_PATH}")
        message(FATAL_ERROR "libc++ static library not found: ${LIBCXX_LIBRARY_PATH}")
    endif()

    add_library(libcxx::freestanding STATIC IMPORTED)
    set_target_properties(libcxx::freestanding PROPERTIES
        IMPORTED_LOCATION "${LIBCXX_LIBRARY_PATH}"
        INTERFACE_INCLUDE_DIRECTORIES "${LIBCXX_INCLUDE_DIR}"
    )
endif()

list(SORT WDK_NTOSKRNL_LIB COMPARE NATURAL)

# import targets for all the libraries present in WDK_LIB_FILES
foreach (LIBRARY_PATH IN LISTS WDK_LIB_FILES)
    get_filename_component(LIBRARY_NAME_WE ${LIBRARY_PATH} NAME_WE)
    string(TOUPPER ${LIBRARY_NAME_WE} LIBRARY_NAME_UPPER)

    add_library(WDK::${LIBRARY_NAME_UPPER} UNKNOWN IMPORTED)
    set_target_properties(WDK::${LIBRARY_NAME_UPPER} PROPERTIES
            IMPORTED_LOCATION "${LIBRARY_PATH}"
    )
endforeach ()

foreach (_dir ${CMAKE_MODULE_PATH})
    if (EXISTS "${_dir}/FindCrossWDK.cmake")
        set(CROSSWDK_DIR "${_dir}")
        message(STATUS "CROSSWDK_DIR found: ${CROSSWDK_DIR}")
        break()
    endif ()
endforeach ()

if (NOT DEFINED CROSSWDK_DIR)
    message(WARNING "Failed to find CrossWDK.cmake in CMAKE_MODULE_PATH! Did you add the correct directory to CMAKE_MODULE_PATH?")
endif ()

set(WDK_COMPILE_FLAGS
        -ffreestanding
        -fno-threadsafe-statics
        -fmerge-all-constants
        -fno-rtti
        -fno-exceptions
        -fno-stack-protector
        -fno-stack-check
        -mno-stack-arg-probe
        -mstack-alignment=16

        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wpointer-arith
        -Wstrict-overflow=5
        -Wnull-dereference
        -Wformat=2
        -Wcast-align
        -Wstrict-aliasing=2
)

if (DEFINED ENV{LIBCXX_FREESTANDING_INSTALL_DIR})
    list(APPEND WDK_COMPILE_FLAGS
            -nostdlibinc
            -nostdinc++
    )
endif()

if (CMAKE_LINKER MATCHES ".*lld-link.*")
    set(WDK_LINK_FLAGS
            -nostdlib
            -nodefaultlibs
            "-Xlinker"
            "/ENTRY:_start"
    )
else ()
    set(WDK_LINK_FLAGS
            -nostdlib
            -nodefaultlibs
            -Wl,-e,_start
            -Wl,--stack=16384
    )
endif ()

if(NOT WIN32)
    list(APPEND WDK_COMPILE_FLAGS
            --target=x86_64-w64-windows-gnu
    )

    list(APPEND WDK_LINK_FLAGS
            --target=x86_64-w64-windows-gnu
    )
endif()

function(wdk_add_driver target_name)
    # wdk_add_driver(
    #   source1.cpp
    #   SOURCES source2.cpp
    #   MODULES module1.[cpp/ixx/cppm/...]
    # )
    cmake_parse_arguments(WDK_DRIVER
        ""
        ""
        "SOURCES;MODULES"
        ${ARGN}
    )

    if(NOT WDK_DRIVER_SOURCES AND WDK_DRIVER_UNPARSED_ARGUMENTS)
        set(WDK_DRIVER_SOURCES ${WDK_DRIVER_UNPARSED_ARGUMENTS})
    endif()

    add_executable(${target_name}
        ${WDK_DRIVER_SOURCES}
        ${CROSSWDK_DIR}/main.cpp
        ${CROSSWDK_DIR}/support.cpp
    )

    target_compile_options(${target_name} PRIVATE ${WDK_COMPILE_FLAGS})

    if(WDK_DRIVER_MODULES)
        set_property(TARGET ${target_name} PROPERTY CXX_SCAN_FOR_MODULES ON)

        target_compile_options(${target_name} PRIVATE ${WDK_MODULE_COMPILE_FLAGS})

        target_sources(${target_name} PUBLIC
            FILE_SET CXX_MODULES FILES ${WDK_DRIVER_MODULES}
        )
    endif()

    set_target_properties(${target_name} PROPERTIES
        SUFFIX ".sys"
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
    )

    target_link_options(${target_name} PRIVATE ${WDK_LINK_FLAGS})
    target_link_libraries(${target_name}
        WDK::NTOSKRNL
    )

    if (DEFINED ENV{LIBCXX_FREESTANDING_INSTALL_DIR})
        target_link_libraries(${target_name}
            libcxx::freestanding
        )
    endif()

    target_include_directories(${target_name} SYSTEM PRIVATE
        "${LIBCXX_INCLUDE_DIR}"
        "${CROSSWDK_DIR}/include/wdk/cpp"
        "${CROSSWDK_DIR}/include"
    )
endfunction()
