//#include "csv_model_data_source.h"
//#include "model_exception.h"
//
//CsvModelDataSource::~CsvModelDataSource()
//{
//	if (doc)
//		doc.reset();
//}
//
//CsvModelDataSource::CsvModelDataSource(std::string filename)
//{
//	fileName = filename;
//}
//
//void CsvModelDataSource::open()
//{
//	if (!doc)
//	{
//		rapidcsv::SeparatorParams sepParams{';'};
//		doc = std::make_unique<rapidcsv::Document>(fileName, rapidcsv::LabelParams(-1, -1), sepParams);
//		if (!doc)
//			throw FileOpenException(__FILE__, __LINE__, __func__, "Unable to open csv file");
//	}
//}
//
//void CsvModelDataSource::close()
//{
//	if (doc)
//		doc.reset();
//}
//
//bool CsvModelDataSource::isOpen() const
//{
//	return doc != nullptr;
//}
//
//std::vector<Point> CsvModelDataSource::readPoints()
//{
//	if (!isOpen())
//		return {};
//
//	std::vector<Point> points;
//	size_t rowCount = doc->GetRowCount();
//
//	if (rowCount < 2)
//		throw FileBadFormatException(__FILE__, __LINE__, __func__, "File too short");
//
//	auto header0 = doc->GetCell<std::string>(0, 0);
//	auto header1 = doc->GetCell<std::string>(1, 0);
//	auto header2 = doc->GetCell<std::string>(2, 0);
//
//	if (header0 != "x" || header1 != "y" || header2 != "z")
//		throw FileBadFormatException(__FILE__, __LINE__, __func__, "Wrong column names");
//
//	size_t row = 1;
//	while (row < rowCount)
//	{
//		try
//		{
//			auto firstCell = doc->GetCell<std::string>(0, row);
//			if (firstCell.empty())
//				break;
//
//			auto x = doc->GetCell<double>(0, row);
//			auto y = doc->GetCell<double>(1, row);
//			auto z = doc->GetCell<double>(2, row);
//			points.emplace_back(x, y, z);
//			++row;
//		}
//		catch (const std::exception &e)
//		{
//			throw FileBadFormatException(__FILE__, __LINE__, __func__, "Wrong data format in points section");
//		}
//	}
//
//	return points;
//}
//
//std::vector<Edge> CsvModelDataSource::readEdges()
//{
//	if (!isOpen())
//		return {};
//
//	std::vector<Edge> edges;
//	size_t rowCount = doc->GetRowCount();
//	size_t row = 1;
//
//	while (row < rowCount)
//	{
//		try
//		{
//			auto firstCell = doc->GetCell<std::string>(0, row);
//			if (firstCell.empty())
//				break;
//			++row;
//		}
//		catch (const std::exception &e)
//		{
//			++row;
//		}
//	}
//
//	while (row < rowCount)
//	{
//		try
//		{
//			std::string firstCell = doc->GetCell<std::string>(0, row);
//			if (!firstCell.empty())
//				break;
//			++row;
//		}
//		catch (const std::exception &e)
//		{
//			++row;
//		}
//	}
//
//	if (row < rowCount)
//	{
//		try
//		{
//			auto header0 = doc->GetCell<std::string>(0, row);
//			auto header1 = doc->GetCell<std::string>(1, row);
//
//			if (header0 != "first" || header1 != "second")
//				throw FileBadFormatException(__FILE__, __LINE__, __func__, "Wrong edge column names");
//
//			++row;
//		}
//		catch (const std::exception &e)
//		{
//			throw FileBadFormatException(__FILE__, __LINE__, __func__, "Wrong edge section format");
//		}
//	}
//
//	while (row < rowCount)
//	{
//		try
//		{
//			auto first = doc->GetCell<size_t>(0, row);
//			auto second = doc->GetCell<size_t>(1, row);
//			edges.emplace_back(first, second);
//			++row;
//		}
//		catch (const std::exception &e)
//		{
//			break;
//		}
//	}
//	return edges;
//}
//
//std::vector<Face> CsvModelDataSource::readFaces()
//{
//	if (!isOpen())
//		return {};
//
//	std::vector<Face> faces;
//	size_t rowCount = doc->GetRowCount();
//	size_t row = 1;
//
//	while (row < rowCount)
//	{
//		try
//		{
//			if (doc->GetCell<std::string>(0, row).empty()) break;
//			++row;
//		}
//		catch (...)
//		{ ++row; }
//	}
//
//	while (row < rowCount && doc->GetCell<std::string>(0, row).empty()) ++row;
//
//	while (row < rowCount)
//	{
//		try
//		{
//			if (!doc->GetCell<std::string>(0, row).empty()) break;
//			++row;
//		}
//		catch (...)
//		{ ++row; }
//	}
//
//	while (row < rowCount)
//	{
//		try
//		{
//			if (doc->GetCell<std::string>(0, row).empty()) break;
//			++row;
//		}
//		catch (...)
//		{ ++row; }
//	}
//
//	while (row < rowCount && doc->GetCell<std::string>(0, row).empty()) ++row;
//
//	if (row < rowCount)
//	{
//		try
//		{
//			auto header = doc->GetCell<std::string>(0, row);
//			if (header == "faces")
//			{
//				++row;
//			}
//		}
//		catch (...)
//		{
//		}
//	}
//
//	while (row < rowCount)
//	{
//		try
//		{
//			std::string faceData = doc->GetCell<std::string>(0, row);
//			if (faceData.empty()) break;
//
//			std::istringstream iss(faceData);
//			std::vector<size_t> indices;
//			std::string indexStr;
//
//			while (std::getline(iss, indexStr, ','))
//			{
//				try
//				{
//					size_t index = std::stoul(indexStr);
//					indices.push_back(index);
//				}
//				catch (...)
//				{
//				}
//			}
//
//			if (!indices.empty())
//			{
//				faces.emplace_back(indices);
//			}
//
//			++row;
//		}
//		catch (...)
//		{
//			++row;
//		}
//	}
//
//	return faces;
//}
#include "csv_model_data_source.h"
#include "model_exception.h"
#include <sstream>

CsvModelDataSource::~CsvModelDataSource()
{
	if (doc)
		doc.reset();
}

CsvModelDataSource::CsvModelDataSource(std::string filename)
{
	fileName = filename;
}

void CsvModelDataSource::open()
{
	if (!doc)
	{
		rapidcsv::SeparatorParams sepParams{','};  // Используем запятую как разделитель
		doc = std::make_unique<rapidcsv::Document>(fileName, rapidcsv::LabelParams(-1, -1), sepParams);
		if (!doc)
			throw FileOpenException(__FILE__, __LINE__, __func__, "Unable to open csv file");
	}
}

void CsvModelDataSource::close()
{
	if (doc)
		doc.reset();
}

bool CsvModelDataSource::isOpen() const
{
	return doc != nullptr;
}

std::vector<Point> CsvModelDataSource::readPoints()
{
	if (!isOpen())
		return {};

	std::vector<Point> points;
	size_t rowCount = doc->GetRowCount();

	if (rowCount < 2)
		throw FileBadFormatException(__FILE__, __LINE__, __func__, "File too short");

	try
	{
		// Первая строка содержит количество точек
		int pointCount = doc->GetCell<int>(0, 0);

		if (pointCount <= 0 || rowCount < pointCount + 1)
			throw FileBadFormatException(__FILE__, __LINE__, __func__, "Invalid point count");

		points.reserve(pointCount);

		// Читаем точки начиная со второй строки
		for (int i = 1; i <= pointCount; ++i)
		{
			double x = doc->GetCell<double>(0, i);
			double y = doc->GetCell<double>(1, i);
			double z = doc->GetCell<double>(2, i);
			points.emplace_back(x, y, z);
		}
	}
	catch (const std::exception &e)
	{
		throw FileBadFormatException(__FILE__, __LINE__, __func__, "Wrong data format in points section");
	}

	return points;
}

std::vector<Edge> CsvModelDataSource::readEdges()
{
	if (!isOpen())
		return {};

	std::vector<Edge> edges;
	size_t rowCount = doc->GetRowCount();

	try
	{
		// Первая строка - количество точек
		int pointCount = doc->GetCell<int>(0, 0);

		// Пропускаем точки
		size_t currentRow = pointCount + 1;

		if (currentRow >= rowCount)
			return edges;  // Нет рёбер

		// Читаем количество рёбер
		int edgeCount = doc->GetCell<int>(0, currentRow);

		if (edgeCount <= 0)
			return edges;

		if (currentRow + edgeCount >= rowCount)
			throw FileBadFormatException(__FILE__, __LINE__, __func__, "Invalid edge count");

		edges.reserve(edgeCount);

		// Читаем рёбра
		for (int i = 1; i <= edgeCount; ++i)
		{
			size_t first = doc->GetCell<size_t>(0, currentRow + i);
			size_t second = doc->GetCell<size_t>(1, currentRow + i);
			// Приводим к 0-based индексации (как в txt reader)
			edges.emplace_back(first - 1, second - 1);
		}
	}
	catch (const std::exception &e)
	{
		throw FileBadFormatException(__FILE__, __LINE__, __func__, "Wrong data format in edges section");
	}

	return edges;
}

std::vector<Face> CsvModelDataSource::readFaces()
{
	if (!isOpen())
		return {};

	std::vector<Face> faces;
	size_t rowCount = doc->GetRowCount();

	try
	{
		// Первая строка - количество точек
		int pointCount = doc->GetCell<int>(0, 0);

		// Пропускаем точки
		size_t currentRow = pointCount + 1;

		if (currentRow >= rowCount)
			return faces;

		// Пропускаем рёбра
		int edgeCount = doc->GetCell<int>(0, currentRow);
		currentRow += edgeCount + 1;

		if (currentRow >= rowCount)
			return faces;  // Нет граней

		// Читаем количество граней
		int faceCount = doc->GetCell<int>(0, currentRow);

		if (faceCount <= 0)
			return faces;

		faces.reserve(faceCount);

		// Читаем грани
		for (int i = 1; i <= faceCount && (currentRow + i) < rowCount; ++i)
		{
			std::string faceData = doc->GetCell<std::string>(0, currentRow + i);

			if (faceData.empty())
				continue;

			std::istringstream iss(faceData);
			std::vector<size_t> indices;
			std::string indexStr;

			// Разбираем строку с индексами (разделённые пробелами или запятыми)
			while (iss >> indexStr)
			{
				try
				{
					size_t index = std::stoul(indexStr);
					indices.push_back(index - 1);  // Приводим к 0-based индексации
				}
				catch (...)
				{
					// Игнорируем некорректные индексы
				}
			}

			if (!indices.empty())
			{
				faces.emplace_back(indices);
			}
		}
	}
	catch (const std::exception &e)
	{
		throw FileBadFormatException(__FILE__, __LINE__, __func__, "Wrong data format in faces section");
	}

	return faces;
}