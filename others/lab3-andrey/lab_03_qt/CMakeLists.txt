cmake_minimum_required(VERSION 3.31)
project(lab_03_qt)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
set(LibArchive_INCLUDE_DIR "/opt/homebrew/Cellar/libarchive/3.8.7/include")
set(LibArchive_LIBRARY "/opt/homebrew/Cellar/libarchive/3.8.7/lib/libarchive.dylib")
set(LibArchive_LIBRARIES ${LibArchive_LIBRARY})
find_package(LibArchive REQUIRED)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-w)
endif()

add_executable(lab_03_qt main.cpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Links/Links.cpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Links/Links.hpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Links/LinksIterator.hpp
        src/Exceptions/BaseException.hpp
        src/Exceptions/Figure/LinksException.hpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Point/Points.cpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Point/Points.hpp
        src/Exceptions/Figure/PointsException.hpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Point/PointsIterator.hpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/FigureLP.cpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/FigureLP.hpp
        src/BaseObject/Figure/ConcreteFigure/BaseConcreteFigureLP.hpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/ConcreteFigureLP.cpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/ConcreteFigureLP.hpp
        src/BaseObject/Figure/Figure.cpp
        src/BaseObject/Figure/Figure.hpp
        src/Transforms/Transforms.cpp
        src/Transforms/Transforms.hpp
        src/BaseObject/BaseObject.cpp
        src/BaseObject/BaseObject.hpp
        src/BaseObject/Composite/CompositeObject.cpp
        src/BaseObject/Composite/CompositeObject.hpp
        src/BaseObject/Camera/CameraPTU.cpp
        src/BaseObject/Camera/CameraPTU.hpp
        src/Exceptions/BaseObject/CompositeException.hpp
        src/Managers/SceneManager/Scene/Scene/Scene.cpp
        src/Managers/SceneManager/Scene/Scene/Scene.hpp
        mainwindow.cpp
        mainwindow.hpp
        mainwindow.ui
        src/Exceptions/Scene/SceneException.hpp
        src/Managers/SceneManager/SceneManager.cpp
        src/Managers/SceneManager/SceneManager.hpp
        src/Managers/BaseManager.hpp
        src/Managers/SceneManager/History/BaseHistory.hpp
        src/Managers/SceneManager/History/History.cpp
        src/Managers/SceneManager/History/History.hpp
        src/Facade/Facade.cpp
        src/Facade/Facade.hpp
        src/Factory/BaseFactory.hpp
        src/Factory/ManagerFactory/ManagerFactory.cpp
        src/Factory/ManagerFactory/ManagerFactory.hpp
        src/Factory/ManagerFactory/ManagerFactoryInterface.hpp
        src/Exceptions/Factory/ManagerFactoryException.hpp
        src/Exceptions/Facade/FacadeException.hpp
        src/Commands/BaseCommand.hpp
        src/Managers/LoadManager/LoadManager.cpp
        src/Managers/LoadManager/LoadManager.hpp
        src/Managers/DrawManager/DrawManager.cpp
        src/Managers/DrawManager/DrawManager.hpp
        src/Managers/TransformManager/TransformManager.cpp
        src/Managers/TransformManager/TransformManager.hpp
        src/Builders/Readers/LPReaders/BaseLPReader.hpp
        src/Builders/Readers/LPReaders/txt/TXTLPReader.cpp
        src/Builders/Readers/LPReaders/txt/TXTLPReader.hpp
        src/Exceptions/Reader/ReaderException.hpp
        src/Builders/Readers/LPReaders/LPReaderSolution.cpp
        src/Builders/Readers/LPReaders/LPReaderSolution.hpp
        src/Exceptions/Factory/ReaderFactoryException.hpp
        src/Builders/Directors/FigureDirector/FigureLPDirector.cpp
        src/Builders/Directors/FigureDirector/FigureLPDirector.hpp
        src/Builders/Readers/LPReaders/LPReaderCreator.hpp
        src/Exceptions/Directors/DirectorException.hpp
        src/Builders/Builders/FigureLPBuilder/BaseFigureLPBuilder.hpp
        src/Builders/Builders/FigureLPBuilder/FigureLPBuilder.cpp
        src/Builders/Builders/FigureLPBuilder/FigureLPBuilder.hpp
        src/Exceptions/Builders/BuildersException.hpp
        src/Exceptions/Builders/BuildersCreatorException.hpp
        src/Exceptions/Managers/LoadManagerException.hpp
        src/Builders/Directors/CameraDirector/CameraPTUDirector.cpp
        src/Builders/Directors/CameraDirector/CameraPTUDirector.hpp
        src/Builders/Readers/PTUReader/BasePTUReader.hpp
        src/Builders/Readers/PTUReader/cmr/CMRPTUReader.cpp
        src/Builders/Readers/PTUReader/cmr/CMRPTUReader.hpp
        src/Builders/Readers/PTUReader/PTUReaderCreator.hpp
        src/Builders/Readers/PTUReader/PTUReaderSolution.cpp
        src/Builders/Readers/PTUReader/PTUReaderSolution.hpp
        src/Builders/Builders/CameraPTUBuilder/BaseCameraPTUBuilder.hpp
        src/BaseObject/Camera/BaseCameraPTU.hpp
        src/Builders/Builders/CameraPTUBuilder/CameraPTUBuilder.cpp
        src/Builders/Builders/CameraPTUBuilder/CameraPTUBuilder.hpp
        src/BaseObject/Camera/Camera.hpp
        src/Exceptions/Hashes/BaseObjectHashException.hpp
        src/Exceptions/Managers/TransformManager/TransformManagerException.hpp
        src/Exceptions/Managers/TransformManager/TransformActionSolutionException.hpp
        src/Exceptions/Actions/ActionException.hpp
        src/Drawer/Drawer/BaseDrawer.hpp
        src/Drawer/Drawer/QtDrawer.hpp
        src/Drawer/Factory/AbstractDrawerFactory.hpp
        src/Drawer/Factory/QtDrawerFactory.hpp
        src/Drawer/Factory/QtDrawerFactory.cpp
        src/Exceptions/Drawer/DrawerException.hpp
        src/Visitors/Transform/Move/MoveObjectVisitor.cpp
        src/Visitors/Transform/Move/MoveObjectVisitor.hpp
        src/Visitors/Transform/BaseTransformVisitor.hpp
        src/Visitors/Transform/Rotate/RotateObjectVisitor.cpp
        src/Visitors/Transform/Rotate/RotateObjectVisitor.hpp
        src/Visitors/Transform/Scale/ScaleObjectVisitor.cpp
        src/Visitors/Transform/Scale/ScaleObjectVisitor.hpp
        src/Exceptions/Visitors/VisitorException.hpp
        src/Visitors/Transform/TransformVisitorSolution.cpp
        src/Visitors/Transform/TransformVisitorSolution.hpp
        src/Visitors/Transform/TransformVisitorHash.hpp
        src/Visitors/Transform/TransformVisitorCreator.hpp
        src/Exceptions/Managers/DrawManagerException.hpp
        src/Visitors/Draw/Solution/DrawVisitorSolution.cpp
        src/Visitors/Draw/Solution/DrawVisitorSolution.hpp
        src/Visitors/Draw/Solution/DrawVisitorHash.hpp
        src/Visitors/Draw/Solution/DrawVisitorCreator.hpp
        "src/Commands/ManagerCommand/Transform manager/TransformManagerCommandRequest/TransformManagerCommandRequest.cpp"
        "src/Commands/ManagerCommand/Transform manager/TransformManagerCommandRequest/TransformManagerCommandRequest.hpp"
        src/Commands/FigureCommand/Remove/FigureRemoveCommand.cpp
        src/Commands/FigureCommand/Remove/FigureRemoveCommand.hpp
        src/Transforms/Vec.cpp
        src/Transforms/Vec.hpp
        src/Transforms/CameraTransformer/CameraPTU/CameraPTUTransformer.cpp
        src/Transforms/CameraTransformer/CameraPTU/CameraPTUTransformer.hpp
        src/Transforms/CameraTransformer/BaseCameraTransformer.hpp
        src/Exceptions/transform/TransformerException.hpp
        src/Exceptions/transform/VecException.hpp
        src/Transforms/CameraTransformer/Solution/CameraTransformerSolution.cpp
        src/Transforms/CameraTransformer/Solution/CameraTransformerSolution.hpp
        src/Transforms/CameraTransformer/Solution/CameraTransformerHash.hpp
        src/Transforms/CameraTransformer/Solution/CameraTransformerCreator.hpp
        src/Commands/DrawCommand/DrawCommand.cpp
        src/Commands/DrawCommand/DrawCommand.hpp
        src/Commands/DrawCommand/CleanCommand.cpp
        src/Commands/DrawCommand/CleanCommand.hpp
        src/Commands/CameraCommand/Add/CameraCommandAdd.cpp
        src/Commands/CameraCommand/Add/CameraCommandAdd.hpp
        src/GUI/Table.cpp
        src/GUI/Table.hpp
        src/Exceptions/GUI/TableException.hpp
        src/Commands/CameraCommand/Remove/CameraRemoveCommand.cpp
        src/Commands/CameraCommand/Remove/CameraRemoveCommand.hpp
        src/Commands/CameraCommand/Set/CameraSetCommand.cpp
        src/Commands/CameraCommand/Set/CameraSetCommand.hpp
        src/Commands/DrawCommand/BaseDrawCommand.hpp
        src/Commands/CameraCommand/BaseCameraCommand.hpp
        src/Commands/FigureCommand/BaseFigureCommand.hpp
        consts.hpp
        src/Commands/FigureCommand/GetByID/FigureCommandGetById.cpp
        src/Commands/FigureCommand/GetByID/FigureCommandGetById.hpp
        src/Commands/CameraCommand/GetById/CameraCommandGetById.cpp
        src/Commands/CameraCommand/GetById/CameraCommandGetById.hpp
        src/Commands/CameraCommand/GetActive/CameraCommandGetActive.cpp
        src/Commands/CameraCommand/GetActive/CameraCommandGetActive.hpp
        src/Commands/FigureCommand/Load/FigureCommandLoad.cpp
        src/Commands/FigureCommand/Load/FigureCommandLoad.hpp
        src/Commands/ManagerCommand/BaseManagerCommand.hpp
        "src/Commands/ManagerCommand/Transform manager/BaseTransformManagerCommand.hpp"
        "src/Commands/ManagerCommand/Transform manager/TransformManagerCommandSetParams/TransformManagerCommandSetParams.cpp"
        "src/Commands/ManagerCommand/Transform manager/TransformManagerCommandSetParams/TransformManagerCommandSetParams.hpp"
        "src/Commands/ManagerCommand/Scene Manager/BaseSceneManagerCommand.hpp"
        "src/Commands/ManagerCommand/Scene Manager/GetScene/SceneManagerCommandGetScene.cpp"
        "src/Commands/ManagerCommand/Scene Manager/GetScene/SceneManagerCommandGetScene.hpp"
        src/Builders/Moderators/BaseLoadModerator.hpp
        src/Builders/Moderators/Solution/LoadModeratorSolution.cpp
        src/Builders/Moderators/Solution/LoadModeratorSolution.hpp
        src/Builders/Moderators/Solution/LoadModeratorCreator.hpp
        src/Exceptions/Moderator/ModeratorException.hpp
        src/Builders/Moderators/Moderators/FigureLP/FigureLPModerator.cpp
        src/Builders/Moderators/Moderators/FigureLP/FigureLPModerator.hpp
        src/Builders/Moderators/Moderators/CameraPTU/CameraPTUModerator.cpp
        src/Builders/Moderators/Moderators/CameraPTU/CameraPTUModerator.hpp
        src/Builders/Directors/FigureDirector/BaseFigureLPDirector.hpp
        src/Builders/Directors/CameraDirector/BaseCameraPTUDirector.hpp
        src/BaseObject/Camera/CameraPTUImpl.cpp
        src/BaseObject/Camera/CameraPTUImpl.hpp
        src/BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/AbstractFigureLP.hpp
        src/BaseObject/Camera/BaseCameraPTUImpl.hpp
        src/Builders/Readers/LPReaders/csv/CSVLPReader.cpp
        src/Builders/Readers/LPReaders/csv/CSVLPReader.hpp
        src/Builders/Readers/PTUReader/csv/CSVPTUReader.cpp
        src/Builders/Readers/PTUReader/csv/CSVPTUReader.hpp
        src/Builders/Readers/LPReaders/bin/BINLPReader.cpp
        src/Builders/Readers/LPReaders/bin/BINLPReader.hpp
        src/Builders/Readers/PTUReader/bin/BINPTUReader.cpp
        src/Builders/Readers/PTUReader/bin/BINPTUReader.hpp
        src/Builders/Readers/ArchiveReaders/BaseArchiveReader.hpp
        src/Builders/Readers/ArchiveReaders/targz/TARGZReader.cpp
        src/Builders/Readers/ArchiveReaders/targz/TARGZReader.hpp
        src/Builders/Moderators/Moderators/Composite/CompositeLoadModerator.cpp
        src/Builders/Moderators/Moderators/Composite/CompositeLoadModerator.hpp
        src/GUI/Combiner.cpp
        src/GUI/Combiner.hpp
        src/Exceptions/GUI/CombinerException.hpp
        src/Visitors/Draw/FigureLP/DrawFigureLPVisitor.cpp
        src/Commands/FigureCommand/Add/FigureCommandAdd.cpp
        src/BaseObject/Camera/Camera.cpp
        "src/Commands/ManagerCommand/Scene Manager/UndoCommand.hpp"
        "src/Commands/ManagerCommand/Scene Manager/RedoCommand.hpp"
        "src/Commands/ManagerCommand/Scene Manager/SceneManagerSaveSnapshotCommand.hpp"
        src/HLR/Faces.hpp
        src/HLR/BaseHLRStrategy.hpp
        src/HLR/AllEdgesStrategy.hpp
        src/HLR/BackFaceCullingStrategy.hpp
        src/InternalRepresentation/InternalDataVisitor.hpp
        src/InternalRepresentation/InternalDataVisitor.cpp
        src/InternalRepresentation/FigureCommandGetInternalData.hpp
        src/InternalRepresentation/ObjectDataDialog.hpp
        src/Commands/CameraCommand/Load/CameraCommandLoad.cpp
        src/Commands/CameraCommand/Load/CameraCommandLoad.hpp
)

target_link_libraries(lab_03_qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        LibArchive::LibArchive
)

