#ifndef SCENE_H__
#define SCENE_H__

#include "object.h"


class Scene
{
public:
    using size_type = std::vector<std::shared_ptr<Object>>::size_type;
    using iterator = std::vector<std::shared_ptr<Object>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Object>>::const_iterator;

    Scene() = default;
    explicit Scene(std::vector<std::shared_ptr<Object>> objects);
    ~Scene() = default;

    void add_object(const std::shared_ptr<Object> &obj);
    void remove_object(const iterator &it);

    void clear_scene();

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    size_type size() const;

private:
    std::vector<std::shared_ptr<Object>> objects;
};


#endif
