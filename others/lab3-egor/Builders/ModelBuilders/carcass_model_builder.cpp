#include "carcass_model_builder.h"

CarcassModelBuilder::CarcassModelBuilder(std::shared_ptr<ModelDataSource> dataSource)
{
	m_dataSource = dataSource;
	m_dataSource->open();
}

void CarcassModelBuilder::buildPoints()
{
	if (m_dataSource)
	{
		auto points = m_dataSource->readPoints();

		for (auto &point : points)
			m_model->addPoint(point);
	}
}

void CarcassModelBuilder::buildEdges()
{
	if (m_dataSource)
	{
		auto edges = m_dataSource->readEdges();

		for (auto &edge : edges)
			m_model->addEdge(edge);
	}
}

void CarcassModelBuilder::buildFaces()
{
	if (m_dataSource)
	{
		auto faces = m_dataSource->readFaces();
		for (auto &face : faces)
			m_model->addFace(face);
	}
}


void CarcassModelBuilder::buildCenter()
{
	if (m_dataSource)
	{
		Point center = m_dataSource->findCenter();
		m_model->setCenter(center);
	}
}

std::shared_ptr<CarcassModel> CarcassModelBuilder::getModel()
{
	return std::make_shared<CarcassModel>(m_model);
}

void CarcassModelBuilder::buildLinkages()
{
	m_model->linkEdgesAndFaces();
}



