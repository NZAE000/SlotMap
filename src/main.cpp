#include "util/memoryviewer.hpp"
#include "slotmap.hpp"
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

namespace ENGINE {

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

} // namespace ENGINE 

namespace GAME {

struct SomeCmp_t : ENGINE::Component_t<SomeCmp_t>{

    SomeCmp_t() = default;
    explicit SomeCmp_t(char const* any) 
    : Component_t{} { 
        std::memcpy(some, any, 8); 
    }

    char some[8] = {"none"};
};

template<typename TYPE>
struct PositionCmp_t : ENGINE::Component_t<PositionCmp_t<TYPE>>{
    TYPE x{}, y{}, z{};
};

} // namespace GAME 

int main(void)
{
    ENGINE::Slotmap_t<GAME::SomeCmp_t, 4> sltmap_of_somecmp{};
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));

// Fill
    [[maybe_unused]] auto key0 = sltmap_of_somecmp.insert(GAME::SomeCmp_t("cmp0"));
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user0 (%ld %ld)\n", key0.id_, key0.gen_);

    [[maybe_unused]] auto key1 = sltmap_of_somecmp.insert(GAME::SomeCmp_t{"cmp1"});
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user1 (%ld %ld)\n", key1.id_, key1.gen_);

    [[maybe_unused]] auto key2 = sltmap_of_somecmp.insert(GAME::SomeCmp_t{"cmp2"});
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user2 (%ld %ld)\n", key2.id_, key2.gen_);

    [[maybe_unused]] auto key3 = sltmap_of_somecmp.insert(GAME::SomeCmp_t{"cmp3"});
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user3 (%ld %ld)\n\n", key3.id_, key3.gen_);

    //std::printf("type of somecmp : %ld\n", GAME::SomeCmp_t::getTypeID());
    //std::printf("type of int : %ld\n", ENGINE::Component_t<int>::getTypeID());
    //[[maybe_unused]] auto key5 = sltmap_of_somecmp.insert(GAME::SomeCmp_t{"cmp5"});

// Delete some keys!
    std::printf("ERASE key_user0 (%ld %ld)\n", key0.id_, key0.gen_);
    if (sltmap_of_somecmp.erase(key0)){
        MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    }

//    std::printf("ERASE key_user0 (%ld %ld)\n", key0.id_, key0.gen_);
//    if (!sltmap_of_somecmp.erase(key0)){
//        std::printf("invalid key\n\n");
//    }

    std::printf("ERASE key_user2 (%ld %ld)\n", key2.id_, key2.gen_);
    if (sltmap_of_somecmp.erase(key2)){
        MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    }

    std::printf("ERASE key_user3 (%ld %ld)\n", key3.id_, key3.gen_);
    if (sltmap_of_somecmp.erase(key3)){
        MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    }

// Add other
    [[maybe_unused]] auto key4 = sltmap_of_somecmp.insert(GAME::SomeCmp_t{"cmp4"});
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user4 (%ld %ld)\n", key4.id_, key4.gen_);

// Iterate
    for (auto const& cmp : sltmap_of_somecmp) std::printf("%s ", cmp.some);

// Get cmp of some key
    GAME::SomeCmp_t const& cmp1  = sltmap_of_somecmp[key1];
    std::printf("\ncmp getted: %s\n", cmp1.some);

    //GAME::SomeCmp_t& cmp3  = sltmap_of_somecmp[key3];  // BAD! CMP3 DELETED ABOVE
    //std::printf("\ncmp getted: %s\n", cmp3.some);

//// To show all data members of Vect_t (stack)
//    Vect_t m_vec { .vec {1, 2, 4, 8, 16, 32} };
//    MEMVIEWER::show(m_vec, sizeof(m_vec));
//
//// To show only data members of std::vector (stack)
//    MEMVIEWER::show(m_vec.vec, sizeof(m_vec.vec));
//
//// To show the data stored by std::vector (heap)
//    MEMVIEWER::show(*m_vec.vec.begin(), 48);

//    // To show how the array is stored in memory (stack).
//    uint32_t a { 128 };
//    std::array<uint32_t, 7> arr { 1, 2, 4, 8, 16, 32, 64 };
//    std::printf("addr a: %16p\n", (void*)(&a));
//    std::printf("data: %16p\n", (void*)(arr.data()));
//    std::printf("data end: %16p\n", (void*)(arr.end()));
//    MEMVIEWER::show(arr, 48);
//
//    // To show how the vector(var members) is stored in memory (stack).
//    std::vector vec { 1, 2, 4, 8, 16, 32 }; // remember: vector { ptr_first_elem, ptr_post_end_elem, ptr_end_capacity}
//    MEMVIEWER::show(vec, sizeof(vec));
//
//    std::printf("begin vec = %16p\n", (void*)(&*vec.begin())); // * to access to content, then with & to access to his address.
//    std::printf("end vec   = %16p\n", (void*)(&*vec.end()));
//    std::printf("cap vec   = %16p\n",  &*vec.begin() + vec.capacity());
//
//    // To show the elements of vector (heap)
//    MEMVIEWER::show(*vec.begin(), 512);
//
//    vec.push_back(64);
//    MEMVIEWER::show(vec, sizeof(vec));
//
//    std::printf("begin vec = %16p\n", (void*)(&*vec.begin())); // * to access to content, then with & to access to his address.
//    std::printf("end vec   = %16p\n", (void*)(&*vec.end()));
//    std::printf("cap vec   = %16p\n",  &*vec.begin() + vec.capacity());
//
//    MEMVIEWER::show(*vec.begin(), 28);
//
    return 0;
}