#ifndef MODEL_COMMANDS_H__
#define MODEL_COMMANDS_H__

#include <vector>
#include <string>
#include "base_command.h"
#include "transformer.h"
#include "concepts.h"


class Object;


template<ReceiverAddModel Recevier>
class AddModel : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(std::shared_ptr<Object>);

public:
    AddModel() = default;
    explicit AddModel(std::shared_ptr<Object> _obj);
    ~AddModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> obj;
    action method;
};


template<ReceiverRemoveModel Recevier>
class RemoveModel : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(std::size_t);

public:
    RemoveModel() = default;
    explicit RemoveModel(std::size_t _id);
    ~RemoveModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::size_t id;
    action method;
};


template<ReceiverGetModel Recevier>
class GetModel : public BaseCommand<Recevier>
{
    using action = std::shared_ptr<Object> (Recevier::*)(std::size_t);

public:
    GetModel() = default;
    explicit GetModel(std::shared_ptr<Object> &_obj, std::size_t _id);
    ~GetModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> &obj;
    std::size_t id;
    action method;
};


template<ReceiverGroupModel Recevier>
class GroupModel : public BaseCommand<Recevier>
{
    using action = std::shared_ptr<Object> (Recevier::*)();

public:
    GroupModel() = default;
    explicit GroupModel(std::shared_ptr<Object> &_obj);
    ~GroupModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> &obj;
    action method;
};


template<ReceiverLoadFile Recevier>
class LoadFileModel : public BaseCommand<Recevier>
{
    using action = std::shared_ptr<Object> (Recevier::*)(std::size_t, std::string);

public:
    LoadFileModel() = default;
    explicit LoadFileModel(std::shared_ptr<Object> &_obj, std::string _filename);
    ~LoadFileModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> &obj;
    std::string filename;
    action method;
};


template<ReceiverLoadBin Recevier>
class LoadBinModel : public BaseCommand<Recevier>
{
    using action = std::shared_ptr<Object> (Recevier::*)(std::size_t, std::string);

public:
    LoadBinModel() = default;
    explicit LoadBinModel(std::shared_ptr<Object> &_obj, std::string _filename);
    ~LoadBinModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> &obj;
    std::string filename;
    action method;
};


template<ReceiverRotate Recevier>
class RotateModel : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(Transformer);

public:
    RotateModel() = default;
    explicit RotateModel(Transformer _transform);
    ~RotateModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    Transformer transform;
    action method;
};


template<ReceiverScale Recevier>
class ScaleModel : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(Transformer);

public:
    ScaleModel() = default;
    explicit ScaleModel(Transformer _transform);
    ~ScaleModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    Transformer transform;
    action method;
};


template<ReceiverMove Recevier>
class MoveModel : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(Transformer);

public:
    MoveModel() = default;
    explicit MoveModel(Transformer _transform);
    ~MoveModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    Transformer transform;
    action method;
};


template<ReceiverTransform Recevier>
class TransformModel : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(std::shared_ptr<Object>&);

public:
    TransformModel() = default;
    explicit TransformModel(std::shared_ptr<Object> _obj);
    ~TransformModel() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> obj;
    action method;
};

#include "model_commands.hpp"

#endif
