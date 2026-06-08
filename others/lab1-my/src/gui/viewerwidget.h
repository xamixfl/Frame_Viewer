#pragma once

#include <QWidget>
#include <QColor>

#include "common_types.h"
#include "task_manager.h"

class ViewerWidget : public QWidget {
    Q_OBJECT

public:
    explicit ViewerWidget(QWidget* parent = nullptr);

    void setBackgroundColor(const QColor& color);
    void setModelColor(const QColor& color);
    QColor backgroundColor() const { return bgColor; }
    QColor modelColor() const { return mdlColor; }

signals:
    void modelChanged();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    QPoint lastMousePos;
    QColor bgColor = Qt::black;
    QColor mdlColor = Qt::white;

    void sendMove(double delta, Axis_t axis);
    void sendRotate(double angle_deg, Axis_t axis);
    void sendScale(double factor);
};
