#include "TriangleBuilder.h"

TriangleBuilder::TriangleBuilder(std::shared_ptr<AbstractReader> reader)
{
    this->reader = reader;

    this->reader->open();
}

TriangleBuilder::~TriangleBuilder()
{
    if (this->reader)
    {
        if (!this->reader->is_open())
        {
            this->reader->close();
        }
    }
}

bool TriangleBuilder::build_points()
{
    this->stage = 1;
    int number_of_points = int(reader->read());
    bool correct = true;

    for (int i = 0; correct && i < number_of_points; i++)
    {
        double x, y, z;
        x = this->reader->read();
        y = this->reader->read();
        z = this->reader->read();

        this->points.push_back(Point(x, y, z));
    }

    return correct;
}

bool TriangleBuilder::build_links()
{
    if (stage != 1)
    {
        return false;
    }

    bool correct = true;
    int number_of_links = int(this->reader->read());
    for (int i = 0; correct && i < number_of_links; i++)
    {
        int A, B, C;
        A = this->reader->read();
        B = this->reader->read();
        C = this->reader->read();

        this->indices.push_back(std::array{A, B, C});
    }

    return correct;
}

void TriangleBuilder::create_model()
{
    if (!this->model)
    {
        this->model = std::make_shared<TriangleCarcas>(this->points, this->indices);
    }
}

std::shared_ptr<Model> TriangleBuilder::build()
{
    this->create_model();

    return std::make_shared<Model>(this->model);
}
