#include "model_impl.h"


ModelImpl::~ModelImpl() {}


WireframeModelImpl::WireframeModelImpl(std::vector<Point> pts, std::vector<Edge> eds, std::vector<std::vector<int>> fcs)
    : points(std::move(pts)), edges(std::move(eds)), faces(std::move(fcs))
{
    calc_center();
}

std::vector<Point>& WireframeModelImpl::get_points()
{
    return points;
}

std::vector<Edge> WireframeModelImpl::get_edges()
{
    return edges;
}

std::vector<Face> WireframeModelImpl::get_faces()
{
    return faces;
}

void WireframeModelImpl::add_point(const Point &point)
{
    points.push_back(point);
    calc_center();
}

void WireframeModelImpl::add_edge(const Edge &edge)
{
    edges.push_back(edge);
}

void WireframeModelImpl::add_face(const Face &face)
{
    faces.push_back(face);
}

Point& WireframeModelImpl::get_center()
{
    return center;
}

void WireframeModelImpl::move_to_center()
{
    for (auto &point : points)
    {
        point.set_x(point.get_x() - center.get_x());
        point.set_y(point.get_y() - center.get_y());
        point.set_z(point.get_z() - center.get_z());
    }
}

void WireframeModelImpl::move_back()
{
    for (auto &point : points)
    {
        point.set_x(point.get_x() + center.get_x());
        point.set_y(point.get_y() + center.get_y());
        point.set_z(point.get_z() + center.get_z());
    }

    calc_center();
}

void WireframeModelImpl::calc_center()
{
    double x = 0, y = 0, z = 0;

    for (auto &point : points)
    {
        x += point.get_x();
        y += point.get_y();
        z += point.get_z();
    }

    double size = static_cast<double>(points.size());

    center.set_x(x / size);
    center.set_y(y / size);
    center.set_z(z / size);
}

bool WireframeModelImpl::face_visible(const Face &face, const Point &cam_pos) const
{
    if (face.size() < 3)
        return true;
 
    const Point &a = points[face[0]];
    const Point &b = points[face[1]];
    const Point &c = points[face[2]];
 
    Point normal = (b - a).crossproduct(c - a);
    Point to_cam = cam_pos - a;
 
    return normal.dotproduct(to_cam) > 0;
}

bool WireframeModelImpl::edge_in_face(const Edge &edge, const Face &face) const
{
    int ea = edge.get_first();
    int eb = edge.get_second();
    int n = static_cast<int>(face.size());
 
    for (int k = 0; k < n; ++k)
    {
        int fa = face[k];
        int fb = face[(k + 1) % n];
 
        if ((fa == ea && fb == eb) || (fa == eb && fb == ea))
            return true;
    }

    return false;
}

std::vector<Edge> WireframeModelImpl::get_visible_edges(const Point &camera_pos)
{
    if (faces.empty())
        return edges;
 
    std::vector<bool> face_vis(faces.size());

    for (std::size_t f = 0; f < faces.size(); ++f)
    {
        face_vis[f] = face_visible(faces[f], camera_pos);
    }

    std::vector<Edge> visible;
 
    for (const auto &edge : edges)
    {
        bool has_any_face = false;
        bool has_visible_face = false;
 
        for (std::size_t f = 0; f < faces.size(); ++f)
        {
            if (!edge_in_face(edge, faces[f])) continue;
 
            has_any_face = true;
            if (face_vis[f])
            {
                has_visible_face = true;
                break;
            }
        }
 
        if (!has_any_face || has_visible_face)
            visible.push_back(edge);
    }
 
    return visible;
}

std::shared_ptr<ModelImpl> WireframeModelImpl::clone() const
{
    return std::make_shared<WireframeModelImpl>(*this);
}

std::shared_ptr<Memento> WireframeModelImpl::create_snapshot()
{
    return std::shared_ptr<ModelMemento>(new ModelMemento(points));
}

void WireframeModelImpl::restore_snapshot(std::shared_ptr<Memento> snapshot)
{
    std::shared_ptr<ModelMemento> memento = std::dynamic_pointer_cast<ModelMemento>(snapshot);

    if (memento)
    {
        points = memento->points;
    }
}



AdjMatrixModelImpl::AdjMatrixModelImpl(std::vector<Point> pts, std::vector<std::vector<bool>> matrix, std::vector<std::vector<int>> fcs)
    : points(std::move(pts)), adj(std::move(matrix)), faces(std::move(fcs))
{
    calc_center();
}

std::vector<Point>& AdjMatrixModelImpl::get_points()
{
    return points;
}

std::vector<Edge> AdjMatrixModelImpl::get_edges()
{
    std::vector<Edge> edges;

    for (std::size_t i = 0; i < adj.size(); i++)
    {
        for (std::size_t j = i + 1; j < adj[i].size(); j++)
        {
            if (adj[i][j])
            {
                edges.emplace_back(static_cast<int>(i), static_cast<int>(j));
            }
        }
    }

    return edges;
}

std::vector<Face> AdjMatrixModelImpl::get_faces()
{
    return faces;
}

void AdjMatrixModelImpl::add_point(const Point &point)
{
    points.push_back(point);
    ensure_matrix_size();
    calc_center();
}

void AdjMatrixModelImpl::add_edge(const Edge &edge)
{
    ensure_matrix_size();
    adj[edge.get_first()][edge.get_second()] = true;
    adj[edge.get_second()][edge.get_first()] = true;
}

void AdjMatrixModelImpl::add_face(const Face &face)
{
    faces.push_back(face);
}

Point& AdjMatrixModelImpl::get_center()
{
    return center;
}

void AdjMatrixModelImpl::move_to_center()
{
    for (auto &point : points)
    {
        point.set_x(point.get_x() - center.get_x());
        point.set_y(point.get_y() - center.get_y());
        point.set_z(point.get_z() - center.get_z());
    }
}

void AdjMatrixModelImpl::move_back()
{
    for (auto &point : points)
    {
        point.set_x(point.get_x() + center.get_x());
        point.set_y(point.get_y() + center.get_y());
        point.set_z(point.get_z() + center.get_z());
    }

    calc_center();
}

void AdjMatrixModelImpl::calc_center()
{
    double x = 0, y = 0, z = 0;

    for (auto &point : points)
    {
        x += point.get_x();
        y += point.get_y();
        z += point.get_z();
    }

    double size = static_cast<double>(points.size());

    center.set_x(x / size);
    center.set_y(y / size);
    center.set_z(z / size);
}

bool AdjMatrixModelImpl::face_visible(const Face &face, const Point &cam_pos) const
{
    if (face.size() < 3)
        return true;
 
    const Point &a = points[face[0]];
    const Point &b = points[face[1]];
    const Point &c = points[face[2]];
 
    Point normal = (b - a).crossproduct(c - a);
    Point to_cam = cam_pos - a;
 
    return normal.dotproduct(to_cam) > 0;
}

bool AdjMatrixModelImpl::edge_in_face(int ea, int eb, const Face &face) const
{
    int n = static_cast<int>(face.size());

    for (int k = 0; k < n; ++k)
    {
        int fa = face[k];
        int fb = face[(k + 1) % n];
 
        if ((fa == ea && fb == eb) || (fa == eb && fb == ea))
            return true;
    }

    return false;
}

std::vector<Edge> AdjMatrixModelImpl::get_visible_edges(const Point &camera_pos)
{
    if (faces.empty())
        return get_edges();
 
    std::vector<bool> face_vis(faces.size());

    for (std::size_t f = 0; f < faces.size(); ++f)
    {
        face_vis[f] = face_visible(faces[f], camera_pos);
    }
 
    std::vector<Edge> visible;
 
    for (std::size_t i = 0; i < adj.size(); ++i)
    {
        for (std::size_t j = i + 1; j < adj[i].size(); ++j)
        {
            if (!adj[i][j]) continue;
 
            int ea = static_cast<int>(i);
            int eb = static_cast<int>(j);
 
            bool has_any_face    = false;
            bool has_visible_face = false;
 
            for (std::size_t f = 0; f < faces.size(); ++f)
            {
                if (!edge_in_face(ea, eb, faces[f]))
                    continue;
 
                has_any_face = true;
                if (face_vis[f])
                {
                    has_visible_face = true;
                    break;
                }
            }
 
            if (!has_any_face || has_visible_face)
                visible.emplace_back(ea, eb);
        }
    }
 
    return visible;
}

void AdjMatrixModelImpl::ensure_matrix_size()
{
    std::size_t n = points.size();

    if (adj.size() == n) return;

    adj.resize(n);

    for (auto &row : adj)
    {
        row.resize(n, false);
    }
}

std::shared_ptr<ModelImpl> AdjMatrixModelImpl::clone() const
{
    return std::make_shared<AdjMatrixModelImpl>(*this);
}

std::shared_ptr<Memento> AdjMatrixModelImpl::create_snapshot()
{
    return std::shared_ptr<ModelMemento>(new ModelMemento(points));
}

void AdjMatrixModelImpl::restore_snapshot(std::shared_ptr<Memento> snapshot)
{
    std::shared_ptr<ModelMemento> memento = std::dynamic_pointer_cast<ModelMemento>(snapshot);

    if (memento)
    {
        points = memento->points;
    }
}
