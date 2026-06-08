//
// Created by nuelex on 08/05/25.
//

#ifndef LINKS_HPP
#define LINKS_HPP

#include <vector>
#include <cstddef>
#include <utility>

#include "LinksIterator.hpp"

class Link
{
private:
    std::size_t BeginID;
    std::size_t EndID;
public:
    Link() = default;
    explicit Link(const Link& other) { BeginID = other.BeginID; EndID = other.EndID; }
    explicit Link(const std::pair<std::size_t, std::size_t> &pseudo) : BeginID(pseudo.first), EndID(pseudo.second) {}
    Link(const std::size_t &beginID, const std::size_t &endID) : BeginID(beginID), EndID(endID) {}

    Link &operator=(const Link& other) { BeginID = other.BeginID; EndID = other.EndID; return *this; }

    std::pair<std::size_t, std::size_t> Get() { return std::make_pair(BeginID, EndID); }
    [[nodiscard]] std::size_t GetBeginID() const noexcept { return BeginID; }
    [[nodiscard]] std::size_t GetEndID() const noexcept { return EndID; }
    void SetBeginID(const std::size_t &beginID) noexcept { BeginID = beginID; }
    void SetEndID(const std::size_t &endID) noexcept { EndID = endID; }
};

class Links
{
private:
    std::vector<Link> links;

protected:
    std::vector<Link>::iterator end() { return links.end(); }

public:
    using link_type = Link;
    using iterator = LinksIterator<link_type, Links>;
    using const_iterator = ConstLinksIterator<link_type, Links>;

    friend class LinksIterator<link_type, Links>;
    friend class ConstLinksIterator<link_type, Links>;

    Links() = default;
    explicit Links(const Links &links_copy) { links = links_copy.links; }
    Links(Links &&links_copy) noexcept { links = std::move(links_copy.links); }
    ~Links() = default;

    Links& operator =(const Links &links_copy);
    Links& operator =(Links &&links_copy) noexcept { links = std::move(links_copy.links); return *this; }

    void AddLink(const std::size_t &beginID, const std::size_t &endID);
    void AddLink(const Link &link) { this->AddLink(link.GetBeginID(), link.GetEndID()); }

    [[nodiscard]] std::size_t size() const noexcept { return links.size(); }
    [[nodiscard]] bool empty() const noexcept { return links.empty(); }

    [[nodiscard]] iterator CreateIterator() { return iterator(*this); }
    [[nodiscard]] const_iterator CreateConstIterator() const { return const_iterator(*this); }
};

#endif //LINKS_HPP
