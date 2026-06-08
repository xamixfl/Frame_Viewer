//
// Created by nuelex on 08/05/25.
//

#ifndef POINTSITERATOR_HPP
#define POINTSITERATOR_HPP

#include <vector>

#include "Points.hpp"

template <class T, class U>
class PointsIterator
{
    typedef typename std::vector<T>::iterator iterator_type;

public:
    explicit PointsIterator(U &data) : iter_data(data)
    {
        current = iter_data.points.begin();
    }
    void First()
    {
        current = iter_data.points.begin();
    }
    void Next()
    {
        ++current;
    }
    bool IsDone()
    {
        return (current == iter_data.points.end());
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
class ConstPointsIterator
{
    typedef typename std::vector<T>::const_iterator iterator_type;

public:
    explicit ConstPointsIterator(const U &data) : iter_data(data)
    {
        current = iter_data.points.cbegin();
    }
    void First()
    {
        current = iter_data.points.cbegin();
    }
    void Next()
    {
        ++current;
    }
    bool IsDone()
    {
        return (current == iter_data.points.cend());
    }
    iterator_type Current()
    {
        return current;
    }

private:
    const U &iter_data;
    iterator_type current;
};

#endif //POINTSITERATOR_HPP
