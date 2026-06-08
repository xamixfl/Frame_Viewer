#ifndef DRAWER_H__
#define DRAWER_H__

class Point;


class Drawer
{
public:
    Drawer() = default;
    virtual ~Drawer() = 0;

    virtual void draw_line(const Point &first, const Point &second) = 0;
    virtual void clear_scene() = 0;
};

#endif
