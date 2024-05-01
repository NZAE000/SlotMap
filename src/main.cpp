#include "util/showMemory.hpp"
#include<array>
#include<vector>

struct Vect_t {
    char const begin[16] = "##BEGIN-VECTOR#";
    std::vector<int> vec;
    char const end[16] = "###END-VECTOR##";
};

int main(void)
{
    Vect_t m_vec { .vec {1, 2, 4, 8, 16, 32} };
    showMemoryObject(m_vec);
    showMemoryObject(m_vec.vec);

    std::size_t size {48};
    std::printf("\n************************* Size object: %lu ************************\n\n", size);
    showMemory(reinterpret_cast<uint8_t const*>(&*m_vec.vec.begin()), size);

    //// To show how the array is stored in memory(stack).
    //std::array arr { 1, 2, 4, 8, 16, 32, 64};
    //showMemoryObject(arr);
//
    //// To show how the vector is stored in memory(stack).
    //std::vector vec { 1, 2, 4, 8, 16, 32}; // remember: vector { ptr_first_elem, ptr_post_end_elem, ptr_end_capacity}
    //showMemoryObject(vec);
//
    //std::printf("begin vec = %16p\n", (void*)(&*vec.begin())); // * to access to content, then with & to access to his address.
    //std::printf("end vec   = %16p\n", (void*)(&*vec.end()));
//
    //// To show the elements of vector
    //std::size_t size {48};
    //std::printf("\n************************* Size object: %lu ************************\n\n", size);
    //showMemory(reinterpret_cast<uint8_t const*>(&*vec.begin()), size);
//
    //vec.push_back(64);
    //showMemoryObject(vec);
//
    //std::printf("begin vec = %16p\n", (void*)(&*vec.begin())); // * to access to content, then with & to access to his address.
    //std::printf("end vec   = %16p\n", (void*)(&*vec.end()));
//
    //std::printf("\n************************* Size object: %lu ************************\n\n", size);
    //showMemory(reinterpret_cast<uint8_t const*>(&*vec.begin()), size);
//
    return 0;
}