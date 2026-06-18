#pragma once
#include<cstdio>
#include<cstdint>


namespace memviewer {

constexpr std::size_t DEFAULT_WIDTH_LINE {16};

std::size_t calculateNumLines(std::size_t size, std::size_t width = DEFAULT_WIDTH_LINE);
void        printMemLine(uint8_t const* ptr, std::size_t width = DEFAULT_WIDTH_LINE);
void        printMemory(uint8_t const* ptr, std::size_t size, std::size_t width = DEFAULT_WIDTH_LINE);

template<typename OBJ>
void print(OBJ const& obj, std::size_t size=sizeof(obj))
{   
    std::printf("\n************************* Size object: %lu ************************\n\n", size);
    auto* ptr { reinterpret_cast<uint8_t const*>(&obj) };
    printMemory(ptr, size);
}

} // namespace VIEWER 