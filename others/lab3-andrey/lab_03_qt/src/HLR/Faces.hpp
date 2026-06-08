#ifndef FACES_HPP
#define FACES_HPP

#include <vector>
#include <cstddef>
#include <stdexcept>

class Face
{
public:
    Face() = default;
    explicit Face(std::vector<size_t> indices) : _indices(std::move(indices))
    {
        if (_indices.size() < 3)
            throw std::invalid_argument("Face must have at least 3 vertices");
    }

    [[nodiscard]] const std::vector<size_t>& getIndices() const noexcept { return _indices; }
    [[nodiscard]] size_t size() const noexcept { return _indices.size(); }

    // Содержит ли ребро (a, b) данная грань?
    [[nodiscard]] bool containsEdge(size_t a, size_t b) const noexcept
    {
        const size_t n = _indices.size();
        for (size_t i = 0; i < n; ++i)
        {
            size_t j = (i + 1) % n;
            if ((_indices[i] == a && _indices[j] == b) ||
                (_indices[i] == b && _indices[j] == a))
                return true;
        }
        return false;
    }

private:
    std::vector<size_t> _indices;
};

class Faces
{
public:
    Faces() = default;
    ~Faces() = default;

    void addFace(Face face) { _faces.push_back(std::move(face)); }
    [[nodiscard]] const std::vector<Face>& getFaces() const noexcept { return _faces; }
    [[nodiscard]] size_t size() const noexcept { return _faces.size(); }
    [[nodiscard]] bool empty() const noexcept { return _faces.empty(); }

    [[nodiscard]] const Face& operator[](size_t i) const { return _faces[i]; }

private:
    std::vector<Face> _faces;
};

#endif //FACES_HPP
