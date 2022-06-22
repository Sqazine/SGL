#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../Component/Component.h"
class Entity
{
public:
    Entity();
    Entity(const std::string &name);

    template <typename T, typename... Args>
    void AddComponent(Args &&...params);

    template <typename T, typename... Args>
    void AddComponents(uint32_t compNum, Args &&...params);

    template <typename T>
    void RemoveComponent();

    void ClearComponents();

    template <typename T>
    const std::shared_ptr<T> &GetComponent();

    void SetName(const std::string &name);
    const std::string &GetName() const;

    void SetTag(const std::string &tag);
    const std::string &GetTag() const;

    void SetActive(bool isActive);
    bool IsActive() const;

    void AddSubEntity(const std::shared_ptr<Entity> &subEntity);
    void AddSubEntities(uint32_t entityNum, ...);

protected:
    std::string m_Name;
    std::string m_Tag;
    bool m_IsActive;
    std::weak_ptr<class Scene> m_Owner;
    std::vector<std::shared_ptr<class Component>> m_Components;
    std::vector<std::shared_ptr<Entity>> m_SubEntities;
};