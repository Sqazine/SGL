#pragma once
#include <string>
#include <vector>
#include <memory>
class Scene
{
public:
    Scene();
    Scene(const std::string& name);

    void SetName();
    const std::string& GetName();
private:
    std::string m_Name;
    std::vector<std::shared_ptr<class Entity>> m_Entities;
};
