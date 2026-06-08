#pragma once

#include <QMainWindow>

#include "common_types.h"
#include "task_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    double lastMoveX = 0.0;
    double lastMoveY = 0.0;
    double lastMoveZ = 0.0;
    double lastScale = 1.0;
    double lastRotateX = 0.0;
    double lastRotateY = 0.0;
    double lastRotateZ = 0.0;

    void setupMenuConnections();
    void setupColorConnections();
    void setupMoveConnections();
    void setupRotateConnections();
    void setupScaleConnection();

    void handleMoveAxis(double value, double& lastValue, Axis_t axis);
    void handleRotateAxis(double value, double& lastValue, Axis_t axis);

private slots:
    void onOpenFile();
    void onSaveFile();
    void onExit();
    void onAbout();
    void onAuthor();
};
