#ifndef HISTORY_COMMANDS_H__
#define HISTORY_COMMANDS_H__

#include "base_command.h"


template<RecevierSaveState Recevier>
class AddState : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(std::shared_ptr<Object>);

public:
    AddState() = default;
    explicit AddState(std::shared_ptr<Object> _obj);
    ~AddState() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Object> obj;
    action method;
};


template<RecevierUndoState Recevier>
class UndoState : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)();

public:
    UndoState();
    ~UndoState() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    action method;
};


template<RecevierRedoState Recevier>
class RedoState : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)();

public:
    RedoState();
    ~RedoState() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    action method;
};

#include "history_commands.hpp"

#endif
