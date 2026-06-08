#ifndef CONCRETECREATOR_H
#define CONCRETECREATOR_H

#include <concepts>
#include <memory>
#include <type_traits>

#include "builder/BaseBuilder.h"
#include "creator/BaseCreator.h"
#include "reader/AutoReader.h"

template<typename T>
concept ValidBuilder =
    std::derived_from<T, BaseBuilder> &&
    !std::is_abstract_v<T> &&
    std::constructible_from<T, std::unique_ptr<BaseReader>>;

template<typename TDirector, typename TBuilder>
concept ValidDirectorFor =
    std::derived_from<TDirector, BaseDirector> &&
    !std::is_abstract_v<TDirector> &&
    std::constructible_from<TDirector, std::unique_ptr<TBuilder>>;

template<ValidBuilder TBuilder, ValidDirectorFor<TBuilder> TDirector>
class ConcreteCreator final : public BaseCreator {
public:
    ConcreteCreator() noexcept = default;
    ~ConcreteCreator() override = default;

    [[nodiscard]] std::unique_ptr<BaseDirector> createDirector() override {
        auto reader  = std::make_unique<AutoReader>();
        auto builder = std::make_unique<TBuilder>(std::move(reader));
        return std::make_unique<TDirector>(std::move(builder));
    }
};

#endif // CONCRETECREATOR_H
