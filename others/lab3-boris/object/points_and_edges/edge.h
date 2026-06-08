#ifndef EDGE_H__
#define EDGE_H__


class Edge
{
public:
    Edge() noexcept = default;
    Edge(int a, int b) noexcept;
    explicit Edge(const Edge &e) noexcept;

    int get_first() const noexcept;
    int get_second() const noexcept;

    void set_first(int val) noexcept;
    void set_second(int val) noexcept;

private:
    int first, second;
};

#endif
