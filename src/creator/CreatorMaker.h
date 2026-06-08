#ifndef CREATORMAKER_H
#define CREATORMAKER_H

#include <memory>

#include "creator/ConcreteCreator.h"

class CreatorMaker {
public:
    CreatorMaker() = default;
    ~CreatorMaker() = default;

    template<ValidBuilder TBuilder, ValidDirectorFor<TBuilder> TDirector>
    static std::unique_ptr<BaseCreator> make() {
        return std::make_unique<ConcreteCreator<TBuilder, TDirector>>();
    }
};

#endif // CREATORMAKER_H
