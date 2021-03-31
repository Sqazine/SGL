#pragma once
#include <vector>
#include "texture/Texture.h"
class Material
{
public:
    Material(/* args */);
    ~Material();

private:
    std::vector<Texture> m_Textures;
    std::shared_ptr<>
};