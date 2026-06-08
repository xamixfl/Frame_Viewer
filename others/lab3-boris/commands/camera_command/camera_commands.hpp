#include "camera_commands.h"
#include "scene_manager.h"
#include "transform_manager.h"
#include "load_manager.h"
#include "facade.h"
#include "file_loader.h"
#include "bin_loader.h"


template<ReceiverAddCamera Recevier>
AddCamera<Recevier>::AddCamera(std::shared_ptr<Object> _obj)
    : obj(std::move(_obj))
{
    method = &Recevier::add_object;
}

template<ReceiverAddCamera Recevier>
void AddCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(obj);
}

template<ReceiverAddCamera Recevier>
std::string AddCamera<Recevier>::info()
{
    return "AddCamera";
}


template<ReceiverRemoveCamera Recevier>
RemoveCamera<Recevier>::RemoveCamera(std::size_t _id)
    : id(std::move(_id))
{
    method = &Recevier::remove_camera;
}

template<ReceiverRemoveCamera Recevier>
void RemoveCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(id);
}

template<ReceiverRemoveCamera Recevier>
std::string RemoveCamera<Recevier>::info()
{
    return "RemoveCamera: id = " + std::to_string(id);
}


template<ReceiverGetCamera Recevier>
GetCamera<Recevier>::GetCamera(std::shared_ptr<Object>& _obj)
    : obj(_obj)
{
    method = &Recevier::get_active_camera;
}

template<ReceiverGetCamera Recevier>
void GetCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    obj = ((*r).*method)();
}

template<ReceiverGetCamera Recevier>
std::string GetCamera<Recevier>::info()
{
    return "GetCamera";
}


template<ReceiverSetCamera Recevier>
SetCamera<Recevier>::SetCamera(std::size_t _id)
    : id(std::move(_id))
{
    method = &Recevier::set_camera;
}

template<ReceiverSetCamera Recevier>
void SetCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(id);
}

template<ReceiverSetCamera Recevier>
std::string SetCamera<Recevier>::info()
{
    return "SetCamera: id = " + std::to_string(id);
}


template<ReceiverLoadFile Recevier>
LoadFileCamera<Recevier>::LoadFileCamera(std::shared_ptr<Object>& _obj, std::string _filename)
    : obj(_obj), filename(std::move(_filename))
{
    method = &Recevier::template load<FileLoader>;
}

template<ReceiverLoadFile Recevier>
void LoadFileCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    obj = ((*r).*method)(2, filename);
}

template<ReceiverLoadFile Recevier>
std::string LoadFileCamera<Recevier>::info()
{
    return "LoadFileCamera: filename = " + filename;
}


template<ReceiverLoadBin Recevier>
LoadBinCamera<Recevier>::LoadBinCamera(std::shared_ptr<Object>& _obj, std::string _filename)
    : obj(_obj), filename(std::move(_filename))
{
    method = &Recevier::template load<BinLoader>;
}

template<ReceiverLoadBin Recevier>
void LoadBinCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    obj = ((*r).*method)(2, filename);
}

template<ReceiverLoadBin Recevier>
std::string LoadBinCamera<Recevier>::info()
{
    return "LoadBinCamera: filename = " + filename;
}


template<ReceiverMove Recevier>
MoveCamera<Recevier>::MoveCamera(Transformer _transform)
    : transform(std::move(_transform))
{
    method = &Recevier::template set_visitor<MoveVisitor>;
}

template<ReceiverMove Recevier>
void MoveCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(transform);
}

template<ReceiverMove Recevier>
std::string MoveCamera<Recevier>::info()
{
    return "MoveCamera: dx, dy, dz = " + std::to_string(transform.get_x()) + std::to_string(transform.get_y()) + std::to_string(transform.get_z());
}


template<ReceiverScale Recevier>
ScaleCamera<Recevier>::ScaleCamera(Transformer _transform)
    : transform(std::move(_transform))
{
    method = &Recevier::template set_visitor<ScaleVisitor>;
}

template<ReceiverScale Recevier>
void ScaleCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(transform);
}

template<ReceiverScale Recevier>
std::string ScaleCamera<Recevier>::info()
{
    return "ScaleCamera: kx, ky, kz = " + std::to_string(transform.get_x()) + std::to_string(transform.get_y()) + std::to_string(transform.get_z());
}


template<ReceiverRotate Recevier>
RotateCamera<Recevier>::RotateCamera(Transformer _transform)
    : transform(std::move(_transform))
{
    method = &Recevier::template set_visitor<RotateVisitor>;
}

template<ReceiverRotate Recevier>
void RotateCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(transform);
}

template<ReceiverRotate Recevier>
std::string RotateCamera<Recevier>::info()
{
    return "RotateCamera: ax, ay, az = " + std::to_string(transform.get_x()) + std::to_string(transform.get_y()) + std::to_string(transform.get_z());
}


template<ReceiverTransform Recevier>
TransformCamera<Recevier>::TransformCamera(std::shared_ptr<Object> _obj)
    : obj(std::move(_obj))
{
    method = &Recevier::transform;
}

template<ReceiverTransform Recevier>
void TransformCamera<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(obj);
}

template<ReceiverTransform Recevier>
std::string TransformCamera<Recevier>::info()
{
    return "TransformCamera";
}
