#pragma once
#include <string>
#include <memory>
class Entity
{
public:
    
protected:
    std::string m_Name;
    std::weak_ptr<class Scene> m_Owner;
    std::unique_ptr<>
};