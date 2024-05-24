#include "util/memoryviewer.hpp"
#include "slotmap.hpp"
#include<array>
#include<vector>
#include<cstdio>

//struct Vect_t {
//    char const begin[16] = "##BEGIN-VECTOR#";
//    std::vector<int> vec;
//    char const end[16] = "###END-VECTOR##";
//};

struct SomeCmp_t {
    char some[8] = {"none"};
};

int main(void)
{
    ENGINE::Slotmap_t<SomeCmp_t, 4> sltmap_of_somecmp{};
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));

    [[maybe_unused]] auto key1 = sltmap_of_somecmp.insert(SomeCmp_t{"cmp1"});
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user1 (%ld %ld)\n", key1.id_, key1.gen_);

    [[maybe_unused]] auto key2 = sltmap_of_somecmp.insert(SomeCmp_t{"cmp2"});
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user2 (%ld %ld)\n", key2.id_, key2.gen_);

    [[maybe_unused]] auto key3 = sltmap_of_somecmp.insert(SomeCmp_t{"cmp3"});
    MEMVIEWER::show(sltmap_of_somecmp, sizeof(sltmap_of_somecmp));
    std::printf("key_user3 (%ld %ld)\n", key3.id_, key3.gen_);

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
//    std::array arr { 1, 2, 4, 8, 16, 32, 64};
//    showMemoryObject(arr, sizeof(arr));
//
//    // To show how the vector is stored in memory (stack).
//    std::vector vec { 1, 2, 4, 8, 16, 32}; // remember: vector { ptr_first_elem, ptr_post_end_elem, ptr_end_capacity}
//    showMemoryObject(vec, sizeof(vec));
//
//    std::printf("begin vec = %16p\n", (void*)(&*vec.begin())); // * to access to content, then with & to access to his address.
//    std::printf("end vec   = %16p\n", (void*)(&*vec.end()));
//
//    // To show the elements of vector (heap)
//    showMemoryObject(*vec.begin(), 48);
//
//    vec.push_back(64);
//    showMemoryObject(vec, sizeof(vec));
//
//    std::printf("begin vec = %16p\n", (void*)(&*vec.begin())); // * to access to content, then with & to access to his address.
//    std::printf("end vec   = %16p\n", (void*)(&*vec.end()));
//
//    showMemoryObject(*vec.begin(), 48);

    return 0;
}