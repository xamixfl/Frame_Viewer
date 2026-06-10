#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    Edge() noexcept : a(0), b(0) {}
    Edge(int a_, int b_) noexcept : a(a_), b(b_) {}

    [[nodiscard]] int first() const noexcept { return a; }
    [[nodiscard]] int second() const noexcept { return b; }

private:
    int a;
    int b;
};

#endif 
