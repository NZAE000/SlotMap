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
// To show all data members of Vect_t (stack)
    Vect_t m_vec { .vec {1, 2, 4, 8, 16, 32} };
    showMemoryObject(m_vec, sizeof(m_vec));

// To show only data members of std::vector (stack)
    showMemoryObject(m_vec.vec, sizeof(m_vec.vec));

// To show the data stored by std::vector (heap)
    showMemoryObject(*m_vec.vec.begin(), 48);

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