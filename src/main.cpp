#include <util/memoryviewer.hpp>
#include <util/slotmap.hpp>
#include<array>
#include<vector>
#include<cstdio>

//#define NDEBUG
#include<cassert>

//struct Vect_t {
//    char const begin[16] = "##BEGIN-VECTOR#";
//    std::vector<int> vec;
//    char const end[16] = "###END-VECTOR##";
//};

namespace engine {

using CmpType_t = std::size_t;

struct ComponentBase_t {

protected:
    inline static std::size_t NEXT_CMP_TYPE {0};
};

template<typename CMP_t>
struct Component_t : ComponentBase_t {

    explicit Component_t()
	: ComponentBase_t{}
	{}

    static CmpType_t getTypeID() {
        static CmpType_t type { ++NEXT_CMP_TYPE };
        return type;
    }
};

} // namespace engine 

namespace game {

struct SomeCmp_t : engine::Component_t<SomeCmp_t>{

    SomeCmp_t() = default;
    
    explicit SomeCmp_t(char const* any) 
    : Component_t{} { 
        std::memcpy(some_, any, 8); 
    }

    char some_[8] = {"any"};
};

template<typename TYPE>
struct PositionCmp_t : engine::Component_t<PositionCmp_t<TYPE>> {
    TYPE x_{}, y_{}, z_{};
};

} // namespace game 

int main(void)
{
    engine::Slotmap_t<game::SomeCmp_t, 4> sltmap_of_somecmp{};
    memviewer::print(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));

// Fill
    [[maybe_unused]] auto key0 = sltmap_of_somecmp.insert(game::SomeCmp_t("cmp0"));
    memviewer::print(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user0 (%ld %ld)\n", key0.id_, key0.gen_);

    [[maybe_unused]] auto key1 = sltmap_of_somecmp.insert(game::SomeCmp_t{"cmp1"});
    memviewer::print(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user1 (%ld %ld)\n", key1.id_, key1.gen_);

    [[maybe_unused]] auto key2 = sltmap_of_somecmp.insert(game::SomeCmp_t{"cmp2"});
    memviewer::print(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user2 (%ld %ld)\n", key2.id_, key2.gen_);

    [[maybe_unused]] auto key3 = sltmap_of_somecmp.insert(game::SomeCmp_t{"cmp3"});
    memviewer::print(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user3 (%ld %ld)\n\n", key3.id_, key3.gen_);

    //std::printf("type of somecmp : %ld\n", game::SomeCmp_t::getTypeID());
    //std::printf("type of int : %ld\n", engine::Component_t<int>::getTypeID());
    //[[maybe_unused]] auto key5 = sltmap_of_somecmp.insert(game::SomeCmp_t{"cmp5"});

// Delete some keys!
    std::printf("ERASE key_user0 (%ld %ld)\n", key0.id_, key0.gen_);
    sltmap_of_somecmp.erase(key0);
    memviewer::print(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    
//// Test assertion.
//    std::printf("ERASE key_user0 (%ld %ld)\n", key0.id_, key0.gen_);
//    sltmap_of_somecmp.erase(key0);
//    

    std::printf("ERASE key_user2 (%ld %ld)\n", key2.id_, key2.gen_);
    sltmap_of_somecmp.erase(key2);
    memviewer::print(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    

    std::printf("ERASE key_user3 (%ld %ld)\n", key3.id_, key3.gen_);
    sltmap_of_somecmp.erase(key3);
    memviewer::print(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    

// Add other
    [[maybe_unused]] auto key4 = sltmap_of_somecmp.insert(game::SomeCmp_t{"cmp4"});
    memviewer::print(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user4 (%ld %ld)\n", key4.id_, key4.gen_);

// Iterate
    for (auto const& cmp : sltmap_of_somecmp) std::printf("%s ", cmp.some_);

// Get cmp of some key
    game::SomeCmp_t const& cmp1  = sltmap_of_somecmp[key1];
    std::printf("\ncmp getted: %s\n", cmp1.some_);

    //game::SomeCmp_t& cmp3  = sltmap_of_somecmp[key3];  // BAD! CMP3 DELETED ABOVE
    //std::printf("\ncmp getted: %s\n", cmp3.some);

//    // To show how the array is stored in memory (stack).
//    uint32_t                a   { 128 };
//    std::array<uint32_t, 7> arr { 1, 2, 4, 8, 16, 32, 64 };
//    auto const*             ptr { &arr };
//    std::printf("\nAddress a   = %p\n", (void*)(&a));
//    std::printf("Address ptr = %p\n", (void*)(&ptr));
//    std::printf("data begin  = %p\n", (void*)(arr.data()));
//    std::printf("data end    = %p\n", (void*)(arr.end()));
//    memviewer::print(arr, 50);
//    memviewer::print(*(reinterpret_cast<uint8_t*>(&arr)-8), 50); // Show value of ptr (8 bytes before).
//
//    // To show how the vector(var members) is stored in memory (stack).
//    std::vector vec { 1, 2, 4, 8, 16, 32 };
//    std::printf("\nbegin vec = %p\n", (void*)(&*vec.begin())); // * to access to content, then with & to access to his address.
//    std::printf("end vec   = %p\n", (void*)(&*vec.end()));
//    std::printf("cap vec   = %p\n", (void*)(&*vec.begin() + vec.capacity()));
//    memviewer::print(vec); // To show of vector's atributtes: vector { ptr_begin_elem, ptr_post_end_elem, ptr_end_capacity} = 24bytes (x86-64 o ARM64).
//    memviewer::print(*vec.begin(), sizeof(int) * vec.size() + 16); // To show the elements of vector (heap)
//    
//    vec.push_back(64);
//
//    // Addresses changed!
//    std::printf("begin vec = %16p\n", (void*)(&*vec.begin()));
//    std::printf("end vec   = %16p\n", (void*)(&*vec.end()));
//    std::printf("cap vec   = %16p\n", (void*)(&*vec.begin() + vec.capacity()));
//    memviewer::print(vec); 
//    memviewer::print(*vec.begin(), sizeof(int) * vec.size() + 16);
//
//
//    memviewer::print(*vec.begin(), 28);

//// To show all data members of Vect_t (stack)
//    Vect_t m_vec { .vec {1, 2, 4, 8, 16, 32} };
//    memviewer::print(m_vec, sizeof(m_vec));
//
//// To show only data members of std::vector (stack)
//    memviewer::print(m_vec.vec, sizeof(m_vec.vec));
//
//// To show the data stored by std::vector (heap)
//    memviewer::print(*m_vec.vec.begin(), 48);
//
    return 0;
}