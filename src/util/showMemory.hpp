#pragma once
#include<cstdio>
#include<cstdint>

static constexpr std::size_t DEFAULT_NUM_LINES {16};

std::size_t calculateNumLines(std::size_t size, std::size_t width);
void showMemLine(uint8_t const* ptr, std::size_t width);
void showMemory(uint8_t const* ptr, std::size_t size, std::size_t width = DEFAULT_NUM_LINES);

template<typename OBJ>
void showMemoryObject(OBJ const& obj, std::size_t size)
{   
    std::printf("\n************************* Size object: %lu ************************\n\n", size);
    auto* ptr { reinterpret_cast<uint8_t const*>(&obj) };
    showMemory(ptr, size);
}

