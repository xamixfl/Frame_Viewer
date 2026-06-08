#include "model_commands.h"
#include "file_loader.h"
#include "bin_loader.h"
#include "load_manager.h"
#include "scene_manager.h"
#include "transform_manager.h"


template<ReceiverAddModel Recevier>
AddModel<Recevier>::AddModel(std::shared_ptr<Object> _obj)
    : obj(std::move(_obj))
{
    method = &Recevier::add_object;
}

template<ReceiverAddModel Recevier>
void AddModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(obj);
}

template<ReceiverAddModel Recevier>
std::string AddModel<Recevier>::info()
{
    return "AddModel";
}


template<ReceiverRemoveModel Recevier>
RemoveModel<Recevier>::RemoveModel(std::size_t _id)
    : id(std::move(_id))
{
    method = &Recevier::remove_model;
}

template<ReceiverRemoveModel Recevier>
void RemoveModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(id);
}

template<ReceiverRemoveModel Recevier>
std::string RemoveModel<Recevier>::info()
{
    return "RemoveModel: id = " + std::to_string(id);
}


template<ReceiverGetModel Recevier>
GetModel<Recevier>::GetModel(std::shared_ptr<Object> &_obj, std::size_t _id)
    : obj(_obj), id(std::move(_id))
{
    method = &Recevier::get_object;
}

template<ReceiverGetModel Recevier>
void GetModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    obj = ((*r).*method)(id);
}

template<ReceiverGetModel Recevier>
std::string GetModel<Recevier>::info()
{
    return "GetModel: id = " + std::to_string(id);
}


template<ReceiverGroupModel Recevier>
GroupModel<Recevier>::GroupModel(std::shared_ptr<Object> &_obj)
    : obj(_obj)
{
    method = &Recevier::create_group;
}

template<ReceiverGroupModel Recevier>
void GroupModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    obj = ((*r).*method)();
}

template<ReceiverGroupModel Recevier>
std::string GroupModel<Recevier>::info()
{
    return "GroupModel";
}


template<ReceiverLoadFile Recevier>
LoadFileModel<Recevier>::LoadFileModel(std::shared_ptr<Object> &_obj, std::string _filename)
    : obj(_obj), filename(std::move(_filename))
{
    method = &Recevier::template load<FileLoader>;
}

template<ReceiverLoadFile Recevier>
void LoadFileModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    obj = ((*r).*method)(1, filename);
}

template<ReceiverLoadFile Recevier>
std::string LoadFileModel<Recevier>::info()
{
    return "LoadFileModel: filename = " + filename;
}


template<ReceiverLoadBin Recevier>
LoadBinModel<Recevier>::LoadBinModel(std::shared_ptr<Object> &_obj, std::string _filename)
    : obj(_obj), filename(std::move(_filename))
{
    method = &Recevier::template load<BinLoader>;
}

template<ReceiverLoadBin Recevier>
void LoadBinModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    obj = ((*r).*method)(1, filename);
}

template<ReceiverLoadBin Recevier>
std::string LoadBinModel<Recevier>::info()
{
    return "LoadBinModel: filename = " + filename;
}


template<ReceiverRotate Recevier>
RotateModel<Recevier>::RotateModel(Transformer _transform)
    : transform(std::move(_transform))
{
    method = &Recevier::template set_visitor<RotateVisitor>;
}

template<ReceiverRotate Recevier>
void RotateModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(transform);
}

template<ReceiverRotate Recevier>
std::string RotateModel<Recevier>::info()
{
    return "RotateModel: ax, ay, az = " + std::to_string(transform.get_x()) + std::to_string(transform.get_y()) + std::to_string(transform.get_z());
}


template<ReceiverScale Recevier>
ScaleModel<Recevier>::ScaleModel(Transformer _transform)
    : transform(std::move(_transform))
{
    method = &Recevier::template set_visitor<ScaleVisitor>;
}

template<ReceiverScale Recevier>
void ScaleModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(transform);
}

template<ReceiverScale Recevier>
std::string ScaleModel<Recevier>::info()
{
    return "ScaleModel: kx, ky, kz = " + std::to_string(transform.get_x()) + std::to_string(transform.get_y()) + std::to_string(transform.get_z());
}


template<ReceiverMove Recevier>
MoveModel<Recevier>::MoveModel(Transformer _transform)
    : transform(std::move(_transform))
{
    method = &Recevier::template set_visitor<MoveVisitor>;
}

template<ReceiverMove Recevier>
void MoveModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(transform);
}

template<ReceiverMove Recevier>
std::string MoveModel<Recevier>::info()
{
    return "MoveModel: dx, dy, dz = " + std::to_string(transform.get_x()) + std::to_string(transform.get_y()) + std::to_string(transform.get_z());
}


template<ReceiverTransform Recevier>
TransformModel<Recevier>::TransformModel(std::shared_ptr<Object> _obj)
    : obj(std::move(_obj))
{
    method = &Recevier::transform;
}

template<ReceiverTransform Recevier>
void TransformModel<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(obj);
}

template<ReceiverTransform Recevier>
std::string TransformModel<Recevier>::info()
{
    return "TransformModel";
}
