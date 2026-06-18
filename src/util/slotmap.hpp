#pragma once 
#include<cstdint>
#include<array>
#include<stdexcept>

//#define NDEBUG
#include<cassert>

namespace engine {

template<typename DATA_TYPE, std::size_t CAPACITY=10, typename INDEX_TYPE=std::size_t>
struct Slotmap_t {

    using  data_type = DATA_TYPE;
    using  uint_type = INDEX_TYPE;
    struct key_type { uint_type id_{}; uint_type gen_{}; };

    explicit constexpr Slotmap_t() noexcept
    {
        freeKeysInit(); // Initialize free keys.
    }

    [[nodiscard]] constexpr uint_type size()     const noexcept { return size_;    } // Attibute 'nodiscard': means that the return of method can't be ignored.
    [[nodiscard]] constexpr uint_type capacity() const noexcept { return CAPACITY; }

// ITERATORS TO DATA
    [[nodiscard]] constexpr typename std::array<DATA_TYPE, CAPACITY>::iterator begin()              noexcept { return data_.begin();          }
    [[nodiscard]] constexpr typename std::array<DATA_TYPE, CAPACITY>::iterator end()                noexcept { return data_.begin() + size_;  }
    [[nodiscard]] constexpr typename std::array<DATA_TYPE, CAPACITY>::const_iterator cbegin() const noexcept { return data_.cbegin();         }
    [[nodiscard]] constexpr typename std::array<DATA_TYPE, CAPACITY>::const_iterator cend()   const noexcept { return data_.cbegin() + size_; }

// INSERT
    [[nodiscard]] constexpr key_type insert(data_type&& element) // R-values only!, no universal reference (the type is deducted already).
    {
        // The key index reserverd is returned.
        uint_type const key_idx { occupyFreeKey() };

        // Insert element.
        data_ [size_- 1] = std::move(element); // Move resource (appropriate).
        erase_[size_- 1] = key_idx;            // Store key position.

        // Make key for user.
        return key_type { key_idx, generation_ };
    }

// ERASE
    constexpr void erase(key_type const& key_user) noexcept
    {
        assert( isValid(key_user) && "[Slotmap]: invalid key user" ); // Verify only debugging.

        uint_type idx_data { freeKey(key_user) };
        eraseData(idx_data);
        --size_;            // Update size.
    }

// ACCESS TO ELEMENT WITH KEY
    constexpr data_type const& operator[](key_type const& key_user) const noexcept
    {
        assert( isValid(key_user) && "[Slotmap]: invalid key user" ); // Verify only debugging

        // Accessing the key object and get id_ (position if data to get)
        uint_type pos_data { indices_[key_user.id_].id_ };

        return data_[pos_data];
    }

    constexpr data_type& operator[](key_type const& key_user) noexcept
    {
        data_type const& element { const_cast<Slotmap_t const*>(this)->operator[](key_user) };
        return *const_cast<data_type*>(&element);
    }

private:

    constexpr void freeKeysInit() noexcept
    {
        // Set next_free for each key
        uint_type next_free {1};
        for (auto& key : indices_) 
            key.id_ = next_free++;
        freelist_ = 0;
    }

    [[nodiscard]] constexpr uint_type occupyFreeKey()
    {   
        //if (size_ >= CAPACITY) throw std::runtime_error("Insufficient capacity in slotmap"); // Run time error.
        // Only verify with debug.
        assert(size_ < CAPACITY && "[Slotmap]: insufficient capacity (size_ >= CAPACITY).");
        assert(freelist_ < CAPACITY && "[Slotmap]: insufficient capacity (freelist_ >= CAPACITY).");

        // Update free list.
        uint_type key_idx  { freelist_         };  // Get free key position.
        key_type& free_key { indices_[key_idx] };  // Get free slot key.
        freelist_ = free_key.id_;                  // Update to next free.
    
        // Occupy key, update generation and size.
        free_key.id_  = size_++;          // Set position to new element in data[]!
        free_key.gen_ = ++generation_;    // Tracing.

        return key_idx;
    }

    constexpr bool isValid(key_type const& key_user) const noexcept
    {
        // Index within the range of capacity and valid generation.
        return (key_user.id_ < CAPACITY && indices_[key_user.id_].gen_ == key_user.gen_);
    }


    [[nodiscard]] constexpr uint_type freeKey(key_type const& key_user) noexcept
    {
        //assert( isValid(key_user) ); // Verify only debugging

        // Accessing the slot key to free.
        key_type& key_to_free { indices_[key_user.id_] };

        // Before to free, store id_ (corresponds to the position where the data to be removed is, and value to return).
        uint_type idx_data { key_to_free.id_ };

        // Free key and update freelist.
        key_to_free.id_  = freelist_;
        key_to_free.gen_ = MAX_VALUE_;    // Assuming that the generation never reaches the maximum value!.
        freelist_        = key_user.id_;

        return idx_data;
    }

    constexpr void eraseData(uint_type idx_data) noexcept
    {
        // Get position of end element
        uint_type end_pos {size_ - 1};

        // If the element is in the mid, replace it with the end element.
        if (idx_data < end_pos) 
        {
            // Copy end element to current.
            data_[idx_data]  = data_[end_pos];
            erase_[idx_data] = erase_[end_pos];

            // Then, update the new slot key position associated with the data.
            indices_[erase_[idx_data]].id_ = idx_data;

        } // The element is the end, nothing to do.
    }

    char const b_indice[16] = "INDICES########";
    std::array<key_type,     CAPACITY> indices_{};

    char const b_data[16]   = "DATA###########";
    std::array<data_type, CAPACITY> data_{};      // Cmps!

    char const b_erase[16]   = "ERASE##########";
    std::array<uint_type,    CAPACITY> erase_{};

    char const b_free[8]   = "FREE###";
    uint_type freelist_{0};

    char const b_gen[8]    = "GEN####";
    uint_type generation_{0};

    char const b_size[8]   = "SIZE###";
    uint_type size_{0};

    char const b_capacity[8] = "CAPA###";
    uint_type capa_{CAPACITY};

    static constexpr uint_type MAX_VALUE_ { std::numeric_limits<uint_type>::max() };
};

} // namespace engine