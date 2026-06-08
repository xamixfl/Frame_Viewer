#ifndef DIRECTORSOLUTION_HPP
#define DIRECTORSOLUTION_HPP
#include <memory>
#include <unordered_map>

#include "../Creator/DirectorCreator.hpp"
#include "../../../Managers/LoadManager/LoadId.hpp"

class DirectorSolution
{
public:
    DirectorSolution();
    ~DirectorSolution() = default;

    [[nodiscard]] std::shared_ptr<DirectorCreator> create(LoadId id) const;

private:
    void reg(LoadId id, const std::shared_ptr<DirectorCreator>& creator);

    std::unordered_map<LoadId, std::shared_ptr<DirectorCreator>> _creators;
};

#endif //DIRECTORSOLUTION_HPP
