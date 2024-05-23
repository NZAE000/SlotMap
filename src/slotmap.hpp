#pragma once 
#include<cstdint>
#include<array>

namespace ENGINE {

template<typename DATA_TYPE, std::size_t CAPACITY>
struct Slotmap_t {

    using element_type = DATA_TYPE;
    using uint_type    = uint32_t;
    using key_type     = struct { uint_type id; uint_type gen; };

private:

    std::array<key_type,     CAPACITY> indices{};
    std::array<element_type, CAPACITY> data{};      // Cmps!
    std::array<uint_type,    CAPACITY> erase{};

    uint_type generation{};
    uint_type freelist{};
    uint_type size{};
};

} // namespace ENGINE