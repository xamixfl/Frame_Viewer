#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <string>

class BaseCommand {
public:
    BaseCommand() noexcept = default;
    virtual ~BaseCommand() = default;

    virtual void execute() = 0;

    [[nodiscard]] virtual std::string name() const = 0;
};

#endif // BASECOMMAND_H
