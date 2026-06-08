#ifndef ASSIMPDIRECTOR_H
#define ASSIMPDIRECTOR_H

#include "director/BaseDirector.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "builder/AssimpModelBuilder.h"

class AssimpDirector : public BaseDirector {
public:
    explicit AssimpDirector(std::unique_ptr<AssimpModelBuilder> builder);
    std::shared_ptr<BaseObject> construct(const std::string& filename) override;

private:
    std::unique_ptr<AssimpModelBuilder> _builder;
    void processNode(aiNode* node, const aiScene* scene, AssimpModelBuilder& builder);

    
};

#endif
