#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QTableWidget>

#include "src/Drawer/Factory/AbstractDrawerFactory.hpp"
#include "src/Facade/Facade.hpp"
#include "src/GUI/Table.hpp"
#include "src/HLR/BaseHLRStrategy.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget* parent = nullptr);
    ~mainwindow() override;

    [[nodiscard]] bool init_check() const noexcept { return initialization_check; }

private slots:
    void on_actionAdd_Object_triggered();
    void on_actionAdd_Camera_triggered();

    void on_DeleteObjectButton_clicked();
    void on_DeleteCameraButton_clicked();

    void on_MoveButton_clicked();
    void on_RotateButton_clicked();
    void on_ScaleButton_clicked();

    void on_SetCameraButton_clicked();
    void on_MoveButton_Cam_clicked();
    void on_RotateButton_Cam_clicked();

    void on_CombineButton_clicked();

    void on_UndoButton_clicked();
    void on_RedoButton_clicked();

    void on_HLRCheckBox_toggled(bool checked);

    void on_ShowDataButton_clicked();

private:
    Ui::mainwindow* ui;

    std::unique_ptr<Table> _objectTable;
    std::unique_ptr<Table> _cameraTable;

    bool initialization_check = false;
    std::unique_ptr<Facade> _facade;

    std::shared_ptr<AbstractDrawerFactory> _factory;
    std::shared_ptr<BaseHLRStrategy>       _hlrStrategy;

    std::vector<QString> _objectNames;
    std::vector<QString> _cameraNames;

    void redraw();
    void rebuildTablesFromScene();

    void objectTableInit();
    void cameraTableInit();

    QGraphicsView* graphicsViewWidget() const;
    QWidget*       objectContainer()    const;
    QWidget*       cameraContainer()    const;

    QString readCenterX() const;
    QString readCenterY() const;
    QString readCenterZ() const;

    QString readDx() const;
    QString readDy() const;
    QString readDz() const;

    QString readOx() const;
    QString readOy() const;
    QString readOz() const;

    QString readKx() const;
    QString readKy() const;
    QString readKz() const;

    QString readDxCam() const;
    QString readDyCam() const;
    QString readDzCam() const;

    QString readOxCam() const;
    QString readOyCam() const;
    QString readOzCam() const;

    static void toVector(std::vector<size_t>& v, const QSet<int>& set);
};

#endif //MAINWINDOW_HPP
