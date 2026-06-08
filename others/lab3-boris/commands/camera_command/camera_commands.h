#ifndef CAMERA_COMANDS_H__
#define CAMERA_COMANDS_H__

#include "base_command.h"
#include "scene_manager.h"
#include "transformer.h"
#include "concepts.h"


class Object;


template<ReceiverAddCamera Recevier>
class AddCamera : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(std::shared_ptr<Object>);

public:
    AddCamera() = default;
    explicit AddCamera(std::shared_ptr<Object> _obj);
    ~AddCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> obj;
    action method;
};


template<ReceiverRemoveCamera Recevier>
class RemoveCamera : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(std::size_t);

public:
    RemoveCamera() = default;
    explicit RemoveCamera(std::size_t _id);
    ~RemoveCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::size_t id;
    action method;
};


template<ReceiverGetCamera Recevier>
class GetCamera : public BaseCommand<Recevier>
{
    using action = std::shared_ptr<Object> (Recevier::*)();

public:
    GetCamera() = default;
    explicit GetCamera(std::shared_ptr<Object>& _obj);
    ~GetCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> &obj;
    action method;
};


template<ReceiverSetCamera Recevier>
class SetCamera : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(std::size_t);

public:
    SetCamera() = default;
    explicit SetCamera(std::size_t _id);
    ~SetCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::size_t id;
    action method;
};


template<ReceiverLoadFile Recevier>
class LoadFileCamera : public BaseCommand<Recevier>
{
    using action = std::shared_ptr<Object> (Recevier::*)(std::size_t, std::string);

public:
    LoadFileCamera() = default;
    explicit LoadFileCamera(std::shared_ptr<Object>& _obj, std::string _filename);
    ~LoadFileCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> &obj;
    std::string filename;
    action method;
};


template<ReceiverLoadBin Recevier>
class LoadBinCamera : public BaseCommand<Recevier>
{
    using action = std::shared_ptr<Object> (Recevier::*)(std::size_t, std::string);

public:
    LoadBinCamera() = default;
    explicit LoadBinCamera(std::shared_ptr<Object>& _obj, std::string _filename);
    ~LoadBinCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> &obj;
    std::string filename;
    action method;
};


template<ReceiverMove Recevier>
class MoveCamera : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(Transformer);

public:
    MoveCamera() = default;
    explicit MoveCamera(Transformer _transform);
    ~MoveCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    Transformer transform;
    action method;
};


template<ReceiverScale Recevier>
class ScaleCamera : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(Transformer);

public:
    ScaleCamera() = default;
    explicit ScaleCamera(Transformer _transform);
    ~ScaleCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    Transformer transform;
    action method;
};


template<ReceiverRotate Recevier>
class RotateCamera : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(Transformer);

public:
    RotateCamera() = default;
    explicit RotateCamera(Transformer _transform);
    ~RotateCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    Transformer transform;
    action method;
};


template<ReceiverTransform Recevier>
class TransformCamera : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(std::shared_ptr<Object>&);

public:
    TransformCamera() = default;
    explicit TransformCamera(std::shared_ptr<Object> _obj);
    ~TransformCamera() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> obj;
    action method;
};

#include "camera_commands.hpp"

#endif
