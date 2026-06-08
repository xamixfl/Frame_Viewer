#include "FigureLPBuilder.hpp"

#include "../../../Exceptions/Builders/BuildersException.hpp"

FigureLPBuilder::FigureLPBuilder(std::shared_ptr<BaseLPReader> reader) noexcept
    : BaseFigureLPBuilder(std::move(reader))
{
}

void FigureLPBuilder::build()
{
    _checkReader();
    _initFigure();
    _readPoints();
    _readLinks();
    _readFaces();
}

std::shared_ptr<AbstractFigureLP> FigureLPBuilder::getResult() noexcept
{
    return std::move(_figure);
}

void FigureLPBuilder::_checkReader() const
{
    if (!_reader || !_reader->is_open())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorBuilder_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

void FigureLPBuilder::_initFigure()
{
    try
    {
        _figure = std::make_shared<FigureLP>();
    }
    catch (std::bad_alloc&)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorBuilder_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

void FigureLPBuilder::_readPoints()
{
    const std::size_t n = static_cast<std::size_t>(_reader->read());
    if (n == 0)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorBuilder_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    Points points{};
    for (std::size_t i = 0; i < n; ++i)
    {
        const double x = _reader->read();
        const double y = _reader->read();
        const double z = _reader->read();
        points.AddPoint(Point{x, y, z});
    }
    _figure->setPoints(std::move(points));
}

void FigureLPBuilder::_readLinks()
{
    const std::size_t m = static_cast<std::size_t>(_reader->read());
    const std::size_t pointCount = _figure->getPoints().size();

    Links links{};
    for (std::size_t i = 0; i < m; ++i)
    {
        const std::size_t a = static_cast<std::size_t>(_reader->read());
        const std::size_t b = static_cast<std::size_t>(_reader->read());
        if (a == b || a >= pointCount || b >= pointCount)
        {
            const time_t cur_time = time(nullptr);
            throw ErrorBuilder_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
        }
        links.AddLink(Link{a, b});
    }
    _figure->setLinks(std::move(links));
}

void FigureLPBuilder::_readFaces()
{
    if (_reader->eof())
        return;

    std::size_t k = 0;
    try
    {
        k = static_cast<std::size_t>(_reader->read());
    }
    catch (...)
    {
        return;
    }
    if (k == 0)
        return;

    Faces faces{};
    for (std::size_t i = 0; i < k; ++i)
    {
        const std::size_t count = static_cast<std::size_t>(_reader->read());
        if (count < 3)
        {
            const time_t cur_time = time(nullptr);
            throw ErrorBuilder_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
        }

        std::vector<std::size_t> idx;
        idx.reserve(count);
        for (std::size_t j = 0; j < count; ++j)
            idx.push_back(static_cast<std::size_t>(_reader->read()));

        faces.addFace(Face{std::move(idx)});
    }
    _figure->setFaces(std::move(faces));
}
