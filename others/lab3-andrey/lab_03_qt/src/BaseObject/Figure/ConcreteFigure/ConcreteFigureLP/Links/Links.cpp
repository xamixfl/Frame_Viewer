//
// Created by nuelex on 08/05/25.
//

#include "Links.hpp"

#include "../../../../../Exceptions/Figure/LinksException.hpp"

void Links::AddLink(const std::size_t &beginID, const std::size_t &endID)
{
    try
    {
        links.emplace_back(beginID, endID);
    }
    catch (std::bad_alloc &e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorLinks_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

Links& Links::operator=(const Links& links_copy)
{
    links = links_copy.links;
    return *this;
}
