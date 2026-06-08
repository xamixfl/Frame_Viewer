#ifndef BASE_COMMAND_H__
#define BASE_COMMAND_H__

#include <memory>
#include <string>
#include "concepts.h"
#include "base_manager.h"


template<typename T>
concept ValidRecevier = Derivative<T, BaseManager> && NotAbstract<T>;


template<ValidRecevier Recevier>
class BaseCommand
{
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    virtual void execute(std::shared_ptr<Recevier> r) = 0;
    virtual std::string info() = 0;
};

#endif
