//
// Created by nuelex on 08/05/25.
//

#ifndef LINKSITERATOR_HPP
#define LINKSITERATOR_HPP

#include <vector>

template <class T, class U>
class LinksIterator
{
    typedef typename std::vector<T>::iterator iterator_type;

public:
    explicit LinksIterator(U &data) : iter_data(data)
    {
        current = iter_data.links.begin();
    }
    void First()
    {
        current = iter_data.links.begin();
    }
    void Next()
    {
        ++current;
    }
    bool IsDone()
    {
        return (current == iter_data.links.end());
    }
    iterator_type Current()
    {
        return current;
    }

private:
    U &iter_data;
    iterator_type current;
};

template <class T, class U>
class ConstLinksIterator
{
    typedef typename std::vector<T>::const_iterator iterator_type;

public:
    explicit ConstLinksIterator(const U &data) : iter_data(data)
    {
        current = iter_data.links.cbegin();
    };
    void First()
    {
        current = iter_data.links.cbegin();
    }
    void Next()
    {
        ++current;
    }
    bool IsDone()
    {
        return (current == iter_data.links.cend());
    }
    iterator_type Current()
    {
        return current;
    }

private:
    const U &iter_data;
    iterator_type current;
};

#endif //LINKSITERATOR_HPP
