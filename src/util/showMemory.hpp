#pragma once
#include<cstdio>
#include<cstdint>

constexpr std::size_t DEFAULT_WIDTH_LINE {16};

std::size_t calculateNumLines(std::size_t size, std::size_t width = DEFAULT_WIDTH_LINE);
void showMemLine(uint8_t const* ptr, std::size_t width = DEFAULT_WIDTH_LINE);
void showMemory(uint8_t const* ptr, std::size_t size, std::size_t width = DEFAULT_WIDTH_LINE);

template<typename OBJ>
void showMemoryObject(OBJ const& obj, std::size_t size)
{   
    std::printf("\n************************* Size object: %lu ************************\n\n", size);
    auto* ptr { reinterpret_cast<uint8_t const*>(&obj) };
    showMemory(ptr, size);
}

