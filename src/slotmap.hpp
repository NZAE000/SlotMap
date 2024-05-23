#pragma once 
#include<cstdint>
#include<array>

namespace ENGINE {

template<typename DATA_TYPE, std::size_t CAPACITY>
struct Slotmap_t {

    using element_type = DATA_TYPE;
    using uint_type    = uint32_t;
    using key_type     = struct { uint_type id_; uint_type gen_; };

    [[nodiscard]] constexpr uint_type size()     const noexcept { return size_;    } // Attibute 'nodiscard': means that the return of method can't be ignored.
    [[nodiscard]] constexpr uint_type capacity() const noexcept { return CAPACITY; }

    //[[nodiscard]] key_type insert(element_type&& element) noexcept
    //{
    //    // Get available position in the data array
    //    
    //}

private:

    char const b_indice[8] = "INDICES";
    std::array<key_type,     CAPACITY> indices_{};

    char const b_data[8]   = "DATA###";
    std::array<element_type, CAPACITY> data_{};      // Cmps!

    char const b_erase[8]  = "ERASE##";
    std::array<uint_type,    CAPACITY> erase_{};

    char const b_gen[8]    = "GEN####";
    uint_type generation_{};

    char const b_free[8]   = "FREE###";
    uint_type freelist_{};

    char const b_size[8]   = "SIZE###";
    uint_type size_{};
};

} // namespace ENGINE