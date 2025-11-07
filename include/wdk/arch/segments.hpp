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

        static constexpr crosswdk::utils::bitfield_descriptor<std::uint8_t, 0, 2> requestor_privilege_level_;
        static constexpr crosswdk::utils::bitfield_descriptor<table_indicator, 3> table_;
        static constexpr crosswdk::utils::bitfield_descriptor<std::uint16_t, 4, 15> index_;

        auto requestor_privilege_level(this auto&& self) noexcept {
            return self[requestor_privilege_level_];
        }

        auto table(this auto&& self) noexcept {
            return self[table_];
        }

        auto index(this auto&& self) noexcept {
            return self[index_];
        }
    };

    struct segment_attributes : crosswdk::utils::bits16 {
        using crosswdk::utils::bits16::bits16;
        using crosswdk::utils::bits16::operator=;

        // TODO: implement attribute fields
    };
} // namespace arch

#endif // WDK_ARCH_SEGMENTS_HPP
