#include "history_commands.h"


template<RecevierSaveState Recevier>
AddState<Recevier>::AddState(std::shared_ptr<Object> _obj)
    : obj(std::move(_obj))
{
    method = &Recevier::save;
}

template<RecevierSaveState Recevier>
void AddState<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)(obj);
}

template<RecevierSaveState Recevier>
std::string AddState<Recevier>::info()
{
    return "SaveState";
}


template<RecevierUndoState Recevier>
UndoState<Recevier>::UndoState()
{
    method = &Recevier::undo;
}

template<RecevierUndoState Recevier>
void UndoState<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)();
}

template<RecevierUndoState Recevier>
std::string UndoState<Recevier>::info()
{
    return "UndoState";
}


template<RecevierRedoState Recevier>
RedoState<Recevier>::RedoState()
{
    method = &Recevier::redo;
}

template<RecevierRedoState Recevier>
void RedoState<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)();
}

template<RecevierRedoState Recevier>
std::string RedoState<Recevier>::info()
{
    return "RedoState";
}
