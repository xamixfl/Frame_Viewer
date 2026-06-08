#ifndef OBJECT_H__
#define OBJECT_H__

#include <memory>
#include <vector>

#include "base_visitor.h"
#include "memento.h"


class Object
{
public:
    using iterator = std::vector<std::shared_ptr<Object>>::iterator;

    Object() { id = nextid++; }
    virtual ~Object() = 0;

    virtual bool is_composite() { return false; }
    virtual bool is_drawable() { return false; }

    virtual bool add(const std::shared_ptr<Object> &obj) { return false; }
    virtual bool remove(const iterator &it) { return false; }

    virtual iterator begin() { return iterator(); }
    virtual iterator end() { return iterator(); }

    virtual void accept(const std::shared_ptr<BaseVisitor> &visitor) = 0;

    virtual std::shared_ptr<Memento> create_snapshot() = 0;
    virtual void restore_snapshot(std::shared_ptr<Memento> snapshot) = 0;

    std::size_t get_id() { return id; }

protected:
    std::size_t id;
    static std::size_t nextid;
};


class DrawableObject : public Object
{
public:
    DrawableObject() = default;
    ~DrawableObject() override = default;

    bool is_drawable() override { return true; }
};


class UndrawableObject : public Object
{
public:
    UndrawableObject() = default;
    ~UndrawableObject() override = default;

    bool is_drawable() override { return false; }
};


class Composite : public Object
{
public:
    using iterator = Object::iterator;
    using value_type = Object;
    using iterator_tag = std::random_access_iterator_tag;
    using reference = Object&;
    using pointer = std::shared_ptr<Object>;

    Composite() = default;
    explicit Composite(const std::shared_ptr<Object> &obj);
    explicit Composite(const std::vector<std::shared_ptr<Object>> &vec);

    ~Composite() override = default;

    bool add(const std::shared_ptr<Object> &obj) override;
    bool remove(const iterator &it) override;

    bool is_composite() override { return true; }
    bool is_drawable() override { return true; }

    void accept(const std::shared_ptr<BaseVisitor> &visitor) override;

    std::shared_ptr<Memento> create_snapshot() override;
    void restore_snapshot(std::shared_ptr<Memento> snapshot) override;

    iterator begin() override;
    iterator end() override;

private:
    std::vector<std::shared_ptr<Object>> elems;
};

#endif
