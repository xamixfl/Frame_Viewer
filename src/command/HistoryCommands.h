#ifndef HISTORYCOMMANDS_H
#define HISTORYCOMMANDS_H

#include "command/BaseCommand.h"

class HistoryManager;

class UndoCommand final : public BaseCommand {
public:
    explicit UndoCommand(HistoryManager& historyMgr) noexcept : _historyMgr(historyMgr) {}
    ~UndoCommand() override = default;

    void execute() override;
    [[nodiscard]] std::string name() const override { return "Undo"; }

private:
    HistoryManager& _historyMgr;
};

class RedoCommand final : public BaseCommand {
public:
    explicit RedoCommand(HistoryManager& historyMgr) noexcept : _historyMgr(historyMgr) {}
    ~RedoCommand() override = default;

    void execute() override;
    [[nodiscard]] std::string name() const override { return "Redo"; }

private:
    HistoryManager& _historyMgr;
};

#endif 
