#ifndef DIRECTORCREATOR_HPP
#define DIRECTORCREATOR_HPP
#include <memory>
#include <type_traits>

#include "../Base/BaseDirector.hpp"
#include "../../Readers/Base/BaseReader.hpp"

class DirectorCreator
{
public:
    virtual ~DirectorCreator() = default;
    [[nodiscard]] virtual std::shared_ptr<BaseDirector> createDirector(const std::shared_ptr<BaseReader>& reader) const = 0;
};

template <typename TDirector, typename TBuilder>
requires std::is_base_of_v<BaseDirector, TDirector>
      && (!std::is_abstract_v<TDirector>)
      && (!std::is_abstract_v<TBuilder>)
class ConcreteDirectorCreator final : public DirectorCreator
{
public:
    ~ConcreteDirectorCreator() override = default;

    [[nodiscard]] std::shared_ptr<BaseDirector> createDirector(const std::shared_ptr<BaseReader>& reader) const override
    {
        auto builder = std::make_shared<TBuilder>(reader);
        return std::make_shared<TDirector>(builder);
    }
};

#endif //DIRECTORCREATOR_HPP
