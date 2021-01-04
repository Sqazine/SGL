#pragma once
#include <memory>
#include "Macros.h"
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
    Component(uint32_t updateOrder);
    ~Component();

    
private:
    friend class Entity;
    uint32_t m_UpdateOrder;
    std::weak_ptr<class Entity> m_Owner;
};