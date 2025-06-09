#ifndef WDK_ARCH_SEGMENTS_HPP
#define WDK_ARCH_SEGMENTS_HPP

namespace arch {
    enum class table_indicator : std::uint16_t {
        global,
        local
    };

    struct segment_selector {
        MAKE_SCALAR_CONVERTIBLE(segment_selector, std::uint16_t)

        std::uint16_t requestor_privilege_level : 2 {};
        table_indicator table                   : 1 {};
        std::uint16_t index                     : 13 {};
    } __attribute__((packed));

    struct segment_attributes {
        MAKE_SCALAR_CONVERTIBLE(segment_attributes, std::uint16_t)

        // TODO: implement attributes bitfield
        std::uint16_t value{};
    };
} // namespace arch

#endif // WDK_ARCH_SEGMENTS_HPP
