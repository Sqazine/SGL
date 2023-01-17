#pragma once
#include <string>
#include <vector>
#include <type_traits>
#include <cassert>
#include "stb_image.h"

template <typename T>
struct Image2D
{
    std::vector<T> pixels;
    int32_t width, height, channel;
    Image2D() : width(0), height(0), channel(0) {}
};


namespace IO
{
    std::string LoadText(const std::string& filePath);
    template<typename T>
    Image2D<T> LoadImage2D(const std::string& filePath,bool isFlip)
    {
        Image2D<T> result;
        stbi_set_flip_vertically_on_load(isFlip);

        if constexpr (std::is_same_v<T, float>)
        {
            float* data = stbi_loadf(filePath.c_str(), &result.width, &result.height, &result.channel, STBI_default);
            assert(data != nullptr);
            result.pixels.assign(data, data + result.width * result.height * result.channel);
            stbi_image_free(data);
        }
        else if constexpr (std::is_same_v<T, uint8_t>)
        {
            uint8_t* data = stbi_load(filePath.c_str(), &result.width, &result.height, &result.channel, STBI_default);
            assert(data != nullptr);
            result.pixels.assign(data, data + result.width * result.height * result.channel);
            stbi_image_free(data);
        }
        else
        {
            static_assert(std::is_same_v<T, float> || std::is_same_v<T, uint8_t>, "LoadImage2D only supports uint8_t or float");
        }

        return result;
    }
}

typedef Image2D<uint8_t> Image2Du8;
typedef Image2D<float> Image2Df;