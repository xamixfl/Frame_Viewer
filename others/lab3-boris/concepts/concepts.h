#ifndef CONCEPTS_H__
#define CONCEPTS_H__

#include <concepts>
#include <memory>
#include <string>
#include "transformer.h"

class Object;
class Scene;
class Camera;
class Memento;

template<typename T>
concept ConstructibleDouble = std::is_constructible_v<T, double, double, double>;

template<typename T>
concept ConstructibleInt = std::is_constructible_v<T, int, int>;

template<typename Class, typename From>
concept ConstructibleFrom = std::constructible_from<Class, From>;

template<typename Derived, typename Base>
concept Derivative = std::is_base_of_v<Base, Derived>;

template<typename Class>
concept NotAbstract = !std::is_abstract_v<Class>;

template<typename Derived, typename Base>
concept ValidClass = Derivative<Derived, Base> && NotAbstract<Derived>;


template<typename T>
concept HasAddObject = requires(T t, std::shared_ptr<Object> obj)
{
    t.add_object(obj);
};

template<typename T>
concept HasRemoveModel = requires(T t, std::size_t id)
{
    t.remove_model(id);
};

template<typename T>
concept HasGetObject = requires(T t, std::size_t id)
{
    { t.get_object(id) } -> std::same_as<std::shared_ptr<Object>>;
};

template<typename T>
concept HasCreateGroup = requires(T t)
{
    { t.create_group() } -> std::same_as<std::shared_ptr<Object>>;
};

template<typename T>
concept HasAddCamera = requires(T t, std::shared_ptr<Object> obj)
{
    t.add_object(obj);
};

template<typename T>
concept HasRemoveCamera = requires(T t, std::size_t id)
{
    t.remove_camera(id);
};

template<typename T>
concept HasGetCamera = requires(T t)
{
    { t.get_active_camera() } -> std::same_as<std::shared_ptr<Object>>;
};

template<typename T>
concept HasSetCamera = requires(T t, std::size_t id)
{
    t.set_camera(id);
};

template<typename T>
concept HasClearScene = requires(T t)
{
    t.clear_scene();
};

template<typename T>
concept HasGetScene = requires(T t)
{
    { t.get_active_scene() } -> std::same_as<std::shared_ptr<Scene>>;
};


template<typename T>
concept HasLoadFile = requires(T t, std::size_t id, std::string filename)
{
    { t.template load<struct FileLoader>(id, filename) }
        -> std::same_as<std::shared_ptr<Object>>;
};

template<typename T>
concept HasLoadBin = requires(T t, std::size_t id, std::string filename)
{
    { t.template load<struct BinLoader>(id, filename) }
        -> std::same_as<std::shared_ptr<Object>>;
};


template<typename T>
concept HasSetVisitorMove = requires(T t, Transformer tr)
{
    t.template set_visitor<struct MoveVisitor>(tr);
};

template<typename T>
concept HasSetVisitorScale = requires(T t, Transformer tr)
{
    t.template set_visitor<struct ScaleVisitor>(tr);
};

template<typename T>
concept HasSetVisitorRotate = requires(T t, Transformer tr)
{
    t.template set_visitor<struct RotateVisitor>(tr);
};

template<typename T>
concept HasTransform = requires(T t, std::shared_ptr<Object> obj)
{
    t.transform(obj);
};


template<typename T>
concept HasDraw = requires(T t, std::shared_ptr<Object> obj, std::shared_ptr<Camera> cam)
{
    t.draw(obj, cam);
};

template<typename T>
concept HasSave = requires(T t, std::shared_ptr<Object> obj)
{
    t.save(obj);
};

template<typename T>
concept HasUndo = requires(T t)
{
    t.undo();
};

template<typename T>
concept HasRedo = requires(T t)
{
    t.redo();
};


template<typename T>
concept ReceiverAddModel = HasAddObject<T>;

template<typename T>
concept ReceiverRemoveModel = HasRemoveModel<T>;

template<typename T>
concept ReceiverGetModel = HasGetObject<T>;

template<typename T>
concept ReceiverGroupModel = HasCreateGroup<T>;

template<typename T>
concept ReceiverLoadFile = HasLoadFile<T>;

template<typename T>
concept ReceiverLoadBin = HasLoadBin<T>;

template<typename T>
concept ReceiverRotate = HasSetVisitorRotate<T>;

template<typename T>
concept ReceiverScale= HasSetVisitorScale<T>;

template<typename T>
concept ReceiverMove = HasSetVisitorMove<T>;

template<typename T>
concept ReceiverTransform = HasTransform<T>;

template<typename T>
concept ReceiverAddCamera = HasAddCamera<T>;

template<typename T>
concept ReceiverRemoveCamera = HasRemoveCamera<T>;

template<typename T>
concept ReceiverGetCamera = HasGetCamera<T>;

template<typename T>
concept ReceiverSetCamera = HasSetCamera<T>;

template<typename T>
concept ReceiverClearScene = HasClearScene<T>;

template<typename T>
concept RecevierClearDrawScene = HasClearScene<T>;

template<typename T>
concept ReceiverGetScene = HasGetScene<T>;

template<typename T>
concept ReceiverDrawScene = HasDraw<T>;

template<typename T>
concept RecevierSaveState = HasSave<T>;

template<typename T>
concept RecevierUndoState = HasUndo<T>;

template<typename T>
concept RecevierRedoState = HasRedo<T>;

#endif
