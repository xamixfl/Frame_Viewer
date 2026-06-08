#ifndef TRANSFORMER_H__
#define TRANSFORMER_H__


class Transformer
{
public:
    Transformer() = default;
    explicit Transformer(double _x, double _y, double _z);
    ~Transformer() = default;

    double get_x() const;
    double get_y() const;
    double get_z() const;

private:
    double x, y, z;
};

#endif
