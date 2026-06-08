#include "builder/CarcasModelBuilder.h"
#include "bridge/BaseModelImpl.h"
#include "bridge/AssimpModelImpl.h"
#include "data/Point.h"
#include "data/Edge.h"
#include "data/Face.h"
#include "exception/Exceptions.h"

CarcasModelBuilder::CarcasModelBuilder(std::unique_ptr<BaseReader> reader) noexcept
    : BaseBuilder(std::move(reader)) {}

CarcasModelBuilder::~CarcasModelBuilder() = default;

void CarcasModelBuilder::build() {
    _checkReader();
    _initModel();
    _readPoints();
    _readEdges();
    _readFaces();
}

std::unique_ptr<BaseModelImpl> CarcasModelBuilder::getResult() noexcept {
    return std::move(_model);
}

void CarcasModelBuilder::_checkReader() const {
    if (!_reader || !_reader->isOpen()) {
        throw BuilderNotReadyError(__FILE__, "CarcasModelBuilder", __FUNCTION__);
    }
}

void CarcasModelBuilder::_initModel() noexcept {
    _model = std::make_unique<AssimpModelImpl>();
}

void CarcasModelBuilder::_readPoints() const {
    const int n = static_cast<int>(_reader->read());
    if (n <= 0) {
        throw InvalidFileFormatError("point count must be positive",
            __FILE__, "CarcasModelBuilder", __FUNCTION__);
    }
    for (int i = 0; i < n; ++i) {
        const double x = _reader->read();
        const double y = _reader->read();
        const double z = _reader->read();
        _model->addPoint(Point(x, y, z));
    }
}

void CarcasModelBuilder::_readEdges() const {
    const int m = static_cast<int>(_reader->read());
    if (m < 0) {
        throw InvalidFileFormatError("edge count must be non-negative",
            __FILE__, "CarcasModelBuilder", __FUNCTION__);
    }
    const int pointCount = static_cast<int>(_model->getPoints().size());
    for (int i = 0; i < m; ++i) {
        const int a = static_cast<int>(_reader->read());
        const int b = static_cast<int>(_reader->read());
        if (a < 0 || b < 0 || a >= pointCount || b >= pointCount) {
            throw InvalidFileFormatError("edge index out of range",
                __FILE__, "CarcasModelBuilder", __FUNCTION__);
        }
        _model->addEdge(Edge(a, b));
    }
}

void CarcasModelBuilder::_readFaces() const {
    if (_reader->eof()) {
        return;
    }
    int faceCount = 0;
    try {
        faceCount = static_cast<int>(_reader->read());
    } catch (const std::exception&) {
        return;
    }
    if (_reader->eof() && faceCount == 0) {
        return;
    }
    if (faceCount < 0) {
        throw InvalidFileFormatError("face count must be non-negative",
            __FILE__, "CarcasModelBuilder", __FUNCTION__);
    }
    const int pointCount = static_cast<int>(_model->getPoints().size());
    for (int i = 0; i < faceCount; ++i) {
        const int n = static_cast<int>(_reader->read());
        if (n < 3) {
            throw InvalidFileFormatError("face must have at least 3 vertices",
                __FILE__, "CarcasModelBuilder", __FUNCTION__);
        }
        Face face;
        face.reserve(n);
        for (int k = 0; k < n; ++k) {
            const int idx = static_cast<int>(_reader->read());
            if (idx < 0 || idx >= pointCount) {
                throw InvalidFileFormatError("face index out of range",
                    __FILE__, "CarcasModelBuilder", __FUNCTION__);
            }
            face.push_back(idx);
        }
        _model->addFace(face);
    }
}
