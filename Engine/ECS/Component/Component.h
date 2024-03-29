#pragma once
#include <memory>

#define COMPONENT_DECLARATION(parentComponent, childComponent)                         \
protected:                                                                            \
    static std::string m_ComponentType = std::string(TO_STRING(childComponent));      \
    friend class Entity;                                                              \
    virtual bool IsSameComponentType(const std::string &componentType) const override \
    {                                                                                 \
        if (childComponent::m_ComponentType.compare(component) == 0)                  \
            return true;                                                              \
        return parentComponent::IsSameComponentType(componentType);                   \
    }

class Component
{
public:
    Component(uint32_t priority);
    ~Component();


    void SetPriority(uint32_t priority);
    uint32_t GetPriority() const;    
private:
    friend class Entity;
    uint32_t m_Priority;
    std::weak_ptr<class Entity> m_Owner;
};