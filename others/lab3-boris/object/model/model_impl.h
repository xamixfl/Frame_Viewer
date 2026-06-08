#ifndef MODEL_IMPL_H__
#define MODEL_IMPL_H__

#include <memory>
#include <vector>

#include "point.h"
#include "edge.h"
#include "memento.h"

using Face = std::vector<int>;


class ModelImpl
{
public:
    ModelImpl() = default;
    virtual ~ModelImpl() = 0;
    
    virtual std::vector<Point>& get_points() = 0;
    virtual std::vector<Edge> get_edges() = 0;
    virtual std::vector<std::vector<int>> get_faces() = 0;

    virtual void add_point(const Point &point) = 0;
    virtual void add_edge(const Edge &edge) = 0;
    virtual void add_face(const std::vector<int> &face) = 0;

    virtual Point& get_center() = 0;
    virtual void move_to_center() = 0;
    virtual void move_back() = 0;

    virtual std::vector<Edge> get_visible_edges(const Point &camera_pos) = 0;

    virtual std::shared_ptr<ModelImpl> clone() const = 0;

    virtual std::shared_ptr<Memento> create_snapshot() = 0;
    virtual void restore_snapshot(std::shared_ptr<Memento> snapshot) = 0;
};


class WireframeModelImpl : public ModelImpl
{
public:
    WireframeModelImpl() = default;
    WireframeModelImpl(std::vector<Point> pts, std::vector<Edge> eds, std::vector<std::vector<int>> fcs);
    ~WireframeModelImpl() override = default;

    std::vector<Point>& get_points() override;
    std::vector<Edge> get_edges() override;
    std::vector<Face> get_faces() override;

    void add_point(const Point &point) override;
    void add_edge(const Edge &edge) override;
    void add_face(const Face &face) override;

    Point& get_center() override;
    void move_to_center() override;
    void move_back() override;

    std::vector<Edge> get_visible_edges(const Point &camera_pos) override;

    std::shared_ptr<ModelImpl> clone() const override;

    std::shared_ptr<Memento> create_snapshot() override;
    void restore_snapshot(std::shared_ptr<Memento> snapshot) override;

private:
    std::vector<Point> points;
    std::vector<Edge> edges;
    std::vector<Face> faces;
    Point center;

    void calc_center();
    bool face_visible(const Face &face, const Point &cam_pos) const;
    bool edge_in_face(const Edge &edge, const Face &face) const;
};


class AdjMatrixModelImpl : public ModelImpl
{
public:
    AdjMatrixModelImpl() = default;
    AdjMatrixModelImpl(std::vector<Point> pts, std::vector<std::vector<bool>> mtx, std::vector<std::vector<int>> fcs);
    ~AdjMatrixModelImpl() override = default;

    std::vector<Point>& get_points() override;
    std::vector<Edge> get_edges() override;
    std::vector<Face> get_faces() override;

    void add_point(const Point &point) override;
    void add_edge(const Edge &edge) override;
    void add_face(const Face &face) override;

    Point& get_center() override;
    void move_to_center() override;
    void move_back() override;

    std::vector<Edge> get_visible_edges(const Point &camera_pos) override;

    std::shared_ptr<ModelImpl> clone() const override;

    std::shared_ptr<Memento> create_snapshot() override;
    void restore_snapshot(std::shared_ptr<Memento> snapshot) override;

private:
    std::vector<Point> points;
    std::vector<std::vector<bool>> adj;
    std::vector<Face> faces;
    Point center;

    void ensure_matrix_size();
    void calc_center();
    bool face_visible(const Face &face, const Point &cam_pos) const;
    bool edge_in_face(int ea, int eb, const Face &face) const;
};

#endif
