#include <filesystem>
#include <algorithm>
#include "load_manager.h"
#include "list_carcass_model_director.h"
#include "matrix_carcass_model_director.h"
#include "concrete_data_source_creator.h"
#include "manager_solution.h"
#include "scene_manager.h"

LoadManager::LoadManager()
{
	try
	{
		directorSolution = std::make_shared<CarcassModelDirectorSolution>();
		dataSourceSolution = std::make_shared<DataSourceSolution>();

		directorSolution->registrate(LIST_MODEL_DIRECTOR_ID, CreateCarcassModelCreator::create<ListCarcassModelDirector>);
		directorSolution->registrate(MATRIX_MODEL_DIRECTOR_ID, CreateCarcassModelCreator::create<MatrixCarcassModelDirector>);

		dataSourceSolution->registrate(TXT_DATA_SOURCE_ID, CreateDataSourceCreator::create<TxtModelDataSource>);
		dataSourceSolution->registrate(CSV_DATA_SOURCE_ID, CreateDataSourceCreator::create<CsvModelDataSource>);

		this->registerFileExtension(".txt", TXT_DATA_SOURCE_ID, LIST_MODEL_DIRECTOR_ID);
		this->registerFileExtension(".csv", CSV_DATA_SOURCE_ID, LIST_MODEL_DIRECTOR_ID);
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception in LoadManager constructor: " << e.what() << std::endl;
		throw;
	}
}

std::shared_ptr<BaseObject>
LoadManager::loadModelFromFile(const std::string &filename, size_t directorID, size_t dataSourceID)
{
	try
	{
		auto sceneManager = ManagerSolution::getManager<SceneManager>();
		auto scene = sceneManager->getScene();

		auto dataSourceCreator = dataSourceSolution->create(dataSourceID);
		auto dataSource = dataSourceCreator->create(filename);

		auto modelCreator = directorSolution->create(directorID, dataSource);
		auto model = modelCreator->create();

		return model;
	}
	catch (std::exception &ex)
	{
		throw std::runtime_error("Error in loadModelFromFile: " + std::string(ex.what()) + "\n");
	}
}

std::shared_ptr<BaseObject> LoadManager::loadModelFromFile(const std::string &filename)
{
	std::string extension = getFileExtension(filename);
	std::cout << "Extension: " << extension << std::endl;
	auto it = extensionMap.find(extension);
	if (it == extensionMap.end())
		throw std::runtime_error("Unsupported file extension: " + extension);

	return loadModelFromFile(filename, it->second.second, it->second.first);
}

std::string LoadManager::getFileExtension(const std::string &filePath)
{
	std::filesystem::path path(filePath);
	std::string extension = path.extension().string();

	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

	return extension;
}

void LoadManager::registerFileExtension(const std::string &extension, size_t dataSourceId, size_t directorId)
{
	std::string normalizedExtension = extension;

	if (!normalizedExtension.empty() && normalizedExtension[0] != '.')
		normalizedExtension = "." + normalizedExtension;

	std::transform(normalizedExtension.begin(), normalizedExtension.end(),
				   normalizedExtension.begin(), ::tolower);

	extensionMap[normalizedExtension] = std::make_pair(dataSourceId, directorId);
}