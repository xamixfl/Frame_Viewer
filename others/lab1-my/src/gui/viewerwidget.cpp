#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>

#include "viewerwidget.h"

ViewerWidget::ViewerWidget(QWidget* parent) : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    setAutoFillBackground(true);
}

void ViewerWidget::setBackgroundColor(const QColor& color) {
    bgColor = color;
    update();
}

void ViewerWidget::setModelColor(const QColor& color) {
    mdlColor = color;
    update();
}

void ViewerWidget::sendMove(double delta, Axis_t axis) {
    Request_t req;
    req.action = ACTION_MOVE;
    req.move = {
        .delta = delta,
        .axis = axis
    };
    task_manager(&req);
}

void ViewerWidget::sendRotate(double angle_deg, Axis_t axis) {
    Request_t req;
    req.action = ACTION_ROTATE;
    req.rotate = {
        .angle = angle_deg,
        .axis = axis
    };
    task_manager(&req);
}

void ViewerWidget::sendScale(double factor) {
    Request_t req;
    req.action = ACTION_SCALE;
    req.scale = {
        .factor = factor
    };
    task_manager(&req);
}

void ViewerWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), bgColor);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(mdlColor);

    Request_t req;
    req.action = ACTION_DRAW;
    req.draw_req = {
        .canvas = &painter,
        .size.width = width(),
        .size.height = height()
    };

    task_manager(&req);
}

void ViewerWidget::mousePressEvent(QMouseEvent* event) {
    lastMousePos = event->pos();
}

void ViewerWidget::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint currentPos = event->pos();
        int dx = currentPos.x() - lastMousePos.x();
        int dy = currentPos.y() - lastMousePos.y();

        sendRotate(-dy * MOUSE_SENSITIVITY, AXIS_X);
        sendRotate(dx * MOUSE_SENSITIVITY, AXIS_Y);

        lastMousePos = currentPos;
        update();
        emit modelChanged();
    }
}

void ViewerWidget::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_W: sendMove(MOVE_STEP, AXIS_Y); break;
        case Qt::Key_S: sendMove(-MOVE_STEP, AXIS_Y); break;
        case Qt::Key_A: sendMove(-MOVE_STEP, AXIS_X); break;
        case Qt::Key_D: sendMove(MOVE_STEP, AXIS_X); break;
        case Qt::Key_Q: sendMove(MOVE_STEP, AXIS_Z); break;
        case Qt::Key_E: sendMove(-MOVE_STEP, AXIS_Z); break;
        default: QWidget::keyPressEvent(event); return;
    }

    update();
    emit modelChanged();
}

void ViewerWidget::wheelEvent(QWheelEvent* event) {
    double factor = (event->angleDelta().y() > 0) ? SCALE_UP : SCALE_DOWN;

    sendScale(factor);
    update();
    emit modelChanged();
    event->accept();
}
