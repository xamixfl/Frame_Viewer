#ifndef LOADER_H__
#define LOADER_H__


class Loader
{
public:
    Loader() = default;
    virtual ~Loader() = 0;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual double read() = 0;

    virtual bool is_open() = 0;
};

#endif
