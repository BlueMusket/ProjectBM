#include "HandlerRegistry.h"
#include "Handler.h"

CHandlerRegistry::CHandlerRegistry()
{
}

CHandlerRegistry::~CHandlerRegistry()
{
    for (auto itor : m_List)
    {
        delete itor.second;
    }
}

void CHandlerRegistry::Resist(int id, CHandler* handler)
{
    m_List.insert(std::make_pair(id, handler));
}

CHandler* CHandlerRegistry::Find(int id)
{
    auto findItor = m_List.find(id);

    if (findItor == m_List.end())
    {
        return nullptr;
    }

    return findItor->second;
}
