#ifndef BASEVECTOR_H
#define BASEVECTOR_H

#include <cstddef>

class BaseVector {
public:
    using size_type = size_t;

    virtual ~BaseVector() = 0;

    [[nodiscard]] virtual size_type size() const noexcept { return _size; }

protected:
    size_type _size = 0;
};

#endif // BASEVECTOR_H
