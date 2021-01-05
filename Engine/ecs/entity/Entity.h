#pragma once
#include <string>
#include <memory>
#include <vector>
#include "ecs/component/Component.h"
class Entity
{
public:
    Entity();
    Entity(const std::string &name);

    void AddComponent(const std::shared_ptr<Component> &component);

    template <typename T, typename... Args>
    void AddComponent(Args &&...params);

    template <typename T>
    void RemoveComponent();

    void ClearComponents();

    template <typename T>
    const std::shared_ptr<T> &GetComponent();

    void SetName();
    const std::string& GetName();
protected:
    std::string m_Name;
    std::weak_ptr<class Scene> m_Owner;
    std::vector<std::shared_ptr<class Component>> m_Components;
};