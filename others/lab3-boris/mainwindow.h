#ifndef MAINWINDOW_H__
#define MAINWINDOW_H__

#include <QGraphicsScene>
#include <QMainWindow>

#include "facade.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadModelBtn_clicked();
    void on_loadCameraBtn_clicked();
    void on_removeModelBtn_clicked();
    void on_removeCameraBtn_clicked();

    void on_groupModelBtn_clicked();
    void on_ungroupModelBtn_clicked();

    void on_moveModelBtn_clicked();
    void on_scaleModelBtn_clicked();
    void on_rotateModelBtn_clicked();
    
    void on_moveCameraBtn_clicked();
    void on_scaleCameraBtn_clicked();
    void on_rotateCameraBtn_clicked();

    void on_undoBtn_clicked();
    void on_redoBtn_clicked();

    void on_cameraCB_currentIndexChanged(int index);
    void on_modelCB_currentIndexChanged(int index);

protected:
    void setupScene();
    void updateScene();
    void checkCamExist();
    void checkModelsExist();
    void checkCamDelete();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<QGraphicsScene> _scene;
    std::shared_ptr<Facade> _facade;

    std::vector<std::size_t> _models;
    std::vector<std::size_t> _cameras;
    std::size_t camera_id = 0;
    std::size_t model_id = 0;
    std::optional<std::size_t> group_id;
    int active_model_index = 0;
};
#endif
