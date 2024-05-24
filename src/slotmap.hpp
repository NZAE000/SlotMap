#pragma once 
#include<cstdint>
#include<array>

namespace ENGINE {

template<typename DATA_TYPE, std::size_t CAPACITY>
struct Slotmap_t {

    using element_type = DATA_TYPE;
    using uint_type    = std::size_t;
    using key_type     = struct { uint_type id_; uint_type gen_; };

    explicit constexpr Slotmap_t() noexcept
    {
        freeElements_init();
    }

    [[nodiscard]] constexpr uint_type size()     const noexcept { return size_;    } // Attibute 'nodiscard': means that the return of method can't be ignored.
    [[nodiscard]] constexpr uint_type capacity() const noexcept { return CAPACITY; }

    [[nodiscard]] constexpr key_type insert(element_type&& element) noexcept
    {
        uint_type key_pos { occupyFreeKey() };

        // Insert element
        data_[size_]  = std::move(element); // Move resource
        erase_[size_] = key_pos;

        // Do key for user
        key_type key_user { key_pos, generation_ };

        // Update generation and size
        ++generation_; ++size_;
    
        return key_user;  // Return key for the user
    }

private:

    [[nodiscard]] constexpr uint_type occupyFreeKey() noexcept
    {
        uint_type free_pos { freelist_ };           // Save the unoccupied key position
        key_type& free_key { indices_[free_pos] };  // Get unoccupied key
        freelist_ = free_key.id_;                   // Update freelist
    
        // Occupy key
        free_key.id_  = size_;          // size_ is the position of the new element in data[]!
        free_key.gen_ = generation_;

        return free_pos;
    }

    constexpr void freeElements_init() noexcept
    {
        // Set next_free for each key
        uint_type next_free {1};
        for (auto& key : indices_) 
            key.id_ = next_free++;
        freelist_ = 0;
    }

    char const b_indice[16] = "INDICES########";
    std::array<key_type,     CAPACITY> indices_{};

    char const b_data[16]   = "DATA###########";
    std::array<element_type, CAPACITY> data_{};      // Cmps!

    char const b_erase[16]   = "ERASE##########";
    std::array<uint_type,    CAPACITY> erase_{};

    char const b_gen[8]    = "GEN####";
    uint_type generation_{0};

    char const b_free[8]   = "FREE###";
    uint_type freelist_{0};

    char const b_size[8]   = "SIZE###";
    uint_type size_{0};
};

} // namespace ENGINE