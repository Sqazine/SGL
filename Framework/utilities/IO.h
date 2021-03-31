#pragma once
#include <string>
template <typename T>
struct Image2D
{
    std::vector<T> pixels;
    uint32_t width, height, channel;
    Image2D() : width(0), height(0), channel(0) {}
};


namespace IO
{
    std::string LoadText(const std::string& filePath);
    template<typename T>
    Image2D<T> LoadImage2D(const std::string& filePath,bool isFlip);
}

typedef Image2D<uint8_t> Image2Du8;
typedef Image2D<float> Image2Df;
