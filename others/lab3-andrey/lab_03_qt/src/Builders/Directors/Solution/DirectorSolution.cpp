#include "DirectorSolution.hpp"

#include "../FigureDirector/FigureLPDirector.hpp"
#include "../CameraDirector/CameraPTUDirector.hpp"
#include "../../Builders/FigureLPBuilder/FigureLPBuilder.hpp"
#include "../../Builders/CameraPTUBuilder/CameraPTUBuilder.hpp"

DirectorSolution::DirectorSolution()
{
    reg(LoadId::Figure, std::make_shared<ConcreteDirectorCreator<FigureLPDirector, FigureLPBuilder>>());
    reg(LoadId::Camera, std::make_shared<ConcreteDirectorCreator<CameraPTUDirector, CameraPTUBuilder>>());
}

void DirectorSolution::reg(LoadId id, const std::shared_ptr<DirectorCreator>& creator)
{
    _creators[id] = creator;
}

std::shared_ptr<DirectorCreator> DirectorSolution::create(LoadId id) const
{
    const auto it = _creators.find(id);
    if (it == _creators.end())
        return nullptr;
    return it->second;
}
