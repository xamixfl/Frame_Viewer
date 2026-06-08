#ifndef BASEITERATOR_H
#define BASEITERATOR_H

#include <cstddef>

class BaseIterator {
public:
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    virtual ~BaseIterator() = 0;

protected:
    size_type size = 0;
    difference_type index = 0;
};

#endif // BASEITERATOR_H
