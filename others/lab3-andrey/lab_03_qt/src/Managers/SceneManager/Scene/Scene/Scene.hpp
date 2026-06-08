#ifndef SCENE_HPP
#define SCENE_HPP
#include <memory>
#include <vector>

#include "../../../../BaseObject/BaseObject.hpp"

class Scene final
{
public:
    using value_type     = std::shared_ptr<BaseObject>;
    using size_type      = std::vector<value_type>::size_type;
    using iterator       = std::vector<value_type>::iterator;
    using const_iterator = std::vector<value_type>::const_iterator;

    Scene() = default;
    Scene(const Scene&) = default;
    ~Scene() = default;

    Scene& operator=(const Scene&) = default;

    void addObject(const value_type& object) { _objects.push_back(object); }
    void addCamera(const value_type& camera) { _cameras.push_back(camera); }

    void removeObject(const iterator& it) { _objects.erase(it); }
    void removeCamera(const iterator& it) { _cameras.erase(it); }

    iterator objectsBegin() { return _objects.begin(); }
    iterator objectsEnd()   { return _objects.end();   }
    iterator camerasBegin() { return _cameras.begin(); }
    iterator camerasEnd()   { return _cameras.end();   }

    [[nodiscard]] const_iterator objectsBegin()  const { return _objects.cbegin(); }
    [[nodiscard]] const_iterator objectsEnd()    const { return _objects.cend();   }
    [[nodiscard]] const_iterator camerasBegin()  const { return _cameras.cbegin(); }
    [[nodiscard]] const_iterator camerasEnd()    const { return _cameras.cend();   }

    [[nodiscard]] size_type objectsSize() const { return _objects.size(); }
    [[nodiscard]] size_type camerasSize() const { return _cameras.size(); }

private:
    std::vector<value_type> _objects;
    std::vector<value_type> _cameras;
};

#endif //SCENE_HPP
