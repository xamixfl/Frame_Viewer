#include "model_builder.h"


WireframeModelBuilder::WireframeModelBuilder(std::shared_ptr<Loader> _loader)
{
    loader = std::move(_loader);
    loader->open();
}

WireframeModelBuilder::~WireframeModelBuilder()
{
    if (loader)
    {
        if (loader->is_open())
        {
            loader->close();
        }
    }
}

void WireframeModelBuilder::create_points()
{
    int count = static_cast<int>(loader->read());

    for (int i = 0; i < count; i++)
    {
        double x, y, z;
        x = loader->read();
        y = loader->read();
        z = loader->read();

        points.push_back(Point(x, y, z));
    }
}

void WireframeModelBuilder::create_edges()
{
    int count = static_cast<int>(loader->read());

    for (int i = 0; i < count; i++)
    {
        double first, second;
        first = loader->read();
        second = loader->read();

        edges.push_back(Edge(first, second));
    }
}

void WireframeModelBuilder::create_faces()
{
    int count = static_cast<int>(loader->read());

    for (int i = 0; i < count; ++i)
    {
        int n = static_cast<int>(loader->read());
        std::vector<int> indices;
        indices.reserve(n);

        for (int k = 0; k < n; ++k)
        {
            indices.push_back(static_cast<int>(loader->read()));
        }

        faces.emplace_back(std::move(indices));
    }
}

void WireframeModelBuilder::build()
{
    if (!loader->is_open())
        loader->open();

    create_points();
    create_edges();
    create_faces();

    std::shared_ptr<ModelImpl> impl = std::make_shared<WireframeModelImpl>(points, edges, faces);
    obj = std::make_shared<Model>(impl);

    loader->close();
}

std::shared_ptr<Object> WireframeModelBuilder::get_result()
{
    return obj;
}


AdjMatrixModelBuilder::AdjMatrixModelBuilder(std::shared_ptr<Loader> _loader)
{
    loader = std::move(_loader);
    loader->open();
}

AdjMatrixModelBuilder::~AdjMatrixModelBuilder()
{
    if (loader)
    {
        if (loader->is_open())
        {
            loader->close();
        }
    }
}

void AdjMatrixModelBuilder::create_points()
{
    int count = static_cast<int>(loader->read());

    for (int i = 0; i < count; i++)
    {
        double x, y, z;
        x = loader->read();
        y = loader->read();
        z = loader->read();

        points.push_back(Point(x, y, z));
    }
}

void AdjMatrixModelBuilder::create_adj()
{
    int n = static_cast<int>(loader->read());

    adj.assign(n, std::vector<bool>(n, false));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            adj[i][j] = static_cast<bool>(loader->read());
        }
    }
}

void AdjMatrixModelBuilder::create_faces()
{
    int count = static_cast<int>(loader->read());

    for (int i = 0; i < count; ++i)
    {
        int n = static_cast<int>(loader->read());
        std::vector<int> indices;
        indices.reserve(n);

        for (int k = 0; k < n; ++k)
        {
            indices.push_back(static_cast<int>(loader->read()));
        }

        faces.emplace_back(std::move(indices));
    }
}

void AdjMatrixModelBuilder::build()
{
    if (!loader->is_open())
        loader->open();

    create_points();
    create_adj();
    create_faces();

    std::shared_ptr<ModelImpl> impl = std::make_shared<AdjMatrixModelImpl>(points, adj, faces);
    obj = std::make_shared<Model>(impl);

    loader->close();
}

std::shared_ptr<Object> AdjMatrixModelBuilder::get_result()
{
    return obj;
}
