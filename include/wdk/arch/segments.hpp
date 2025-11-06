#ifndef WDK_ARCH_SEGMENTS_HPP
#define WDK_ARCH_SEGMENTS_HPP

namespace arch {
    enum class table_indicator : std::uint16_t {
        global,
        local
    };

    struct segment_selector : crosswdk::utils::bits16 {
        using crosswdk::utils::bits16::bits16;
        using crosswdk::utils::bits16::operator=;

        CROSSWDK_BITFIELD_PROXY(value, requestor_privilege_level, std::uint16_t, 0, 2)
        CROSSWDK_BITFIELD_PROXY1(value, table, table_indicator, 3)
        CROSSWDK_BITFIELD_PROXY(value, index, std::uint16_t, 4, 15)
    };

    struct segment_attributes : crosswdk::utils::bits16 {
        using crosswdk::utils::bits16::bits16;
        using crosswdk::utils::bits16::operator=;

        // TODO: implement attribute fields
    };
} // namespace arch

#endif // WDK_ARCH_SEGMENTS_HPP
