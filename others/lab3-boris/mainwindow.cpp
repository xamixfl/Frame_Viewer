#include <QMessageBox>
#include <QFileDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "director_creator_maker.h"
#include "model_director.h"
#include "camera_director.h"
#include "model_builder.h"
#include "camera_builder.h"
#include "qfactory.h"
#include "model_commands.h"
#include "camera_commands.h"
#include "scene_commands.h"
#include "history_commands.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupScene()
{
    _scene = std::make_shared<QGraphicsScene>(this);

    ui->graphicsView->setScene(_scene.get());
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    auto cont = ui->graphicsView->contentsRect();
    _scene->setSceneRect(0, 0, cont.width(), cont.height());

    auto myScene = std::make_shared<Scene>();

    DirectorSolution solution(
    {
        {
            1,
            DirectorCreatorMaker::create_director_creator<ModelDirector, WireframeModelBuilder>
        },
        {
            2,
            DirectorCreatorMaker::create_director_creator<CameraDirector, CameraBuilder>
        },
        {
            3,
            DirectorCreatorMaker::create_director_creator<ModelDirector, AdjMatrixModelBuilder>
        }
    });
    
    std::shared_ptr<DirectorSolution> solptr = std::make_shared<DirectorSolution>(solution);

    auto view = ui->graphicsView;

    SceneManager scene = SceneManager(myScene);
    TransformManager transform = TransformManager();
    LoadManager loader = LoadManager(solptr);
    DrawManager drawer = DrawManager(std::make_shared<QFactory>(_scene, view), cont.width(), cont.height());
    HistoryManager history = HistoryManager();

    _facade = std::make_shared<Facade>(loader, drawer, transform, scene, history);

    const double INF = 1e9;
    for (auto *sb : {ui->xDSB, ui->yDSB, ui->zDSB})
    {
        sb->setMinimum(-INF);
        sb->setMaximum( INF);
        sb->setSingleStep(1.0);
    }
}

void MainWindow::updateScene()
{
    ClearDrawScene<DrawManager> clear_cmd;
    _facade->execute(clear_cmd);

    std::shared_ptr<Scene> sc;
    std::shared_ptr<Object> cam;

    GetScene<SceneManager> get(sc);
    _facade->execute(get);

    GetCamera<SceneManager> get_cam(cam);
    _facade->execute(get_cam);

    DrawScene<DrawManager> cmd(sc, std::dynamic_pointer_cast<Camera>(cam));
    _facade->execute(cmd);
}

void MainWindow::checkCamExist()
{
    if (_cameras.empty())
    {
        throw std::runtime_error("No camera found.");
    }
}

void MainWindow::checkModelsExist()
{
    if (_models.empty())
    {
        throw std::runtime_error("No models found.");
    }
}

void MainWindow::checkCamDelete()
{
    if (_cameras.size() <= 1 && !_models.empty())
    {
        throw std::runtime_error("Can not delete the last camera with the loaded models");
    }
}

void MainWindow::on_loadModelBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Добавьте камеру!");
        return;
    }

    std::setlocale(LC_NUMERIC, "C");

    auto path = QFileDialog::getOpenFileName(this, "Загрузка модели", "", "Все файлы (*.txt *.bin);;Текстовые (*.txt);;Бинарные (*.bin)");

    if (path.isNull()) return;

    std::string filename = path.toStdString();
    std::shared_ptr<Object> obj;

    try
    {
        if (path.endsWith(".bin", Qt::CaseInsensitive))
        {
            LoadBinModel<LoadManager> cmd(obj, filename);
            _facade->execute(cmd);
        }
        else
        {
            LoadFileModel<LoadManager> cmd(obj, filename);
            _facade->execute(cmd);
        }

        AddModel<SceneManager> add(obj);
        _facade->execute(add);

        _models.push_back(obj->get_id());
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при загрузке файла: %1").arg(error.what()));
        return;
    }

    updateScene();
    model_id++;
    QString name = QString("Model%1").arg(model_id);
    ui->modelCB->addItem(name);
    ui->modelCB->setCurrentIndex(ui->modelCB->count() - 1);
}

void MainWindow::on_loadCameraBtn_clicked()
{
    std::setlocale(LC_NUMERIC, "C");

    auto path = QFileDialog::getOpenFileName(
        this,
        "Загрузка камеры",
        "",
        "Все файлы (*.txt *.bin);;Текстовые (*.txt);;Бинарные (*.bin)"
    );

    if (path.isNull()) return;

    std::string filename = path.toStdString();
    std::shared_ptr<Object> obj;

    try
    {
        if (path.endsWith(".bin", Qt::CaseInsensitive))
        {
            LoadBinCamera<LoadManager> cmd(obj, filename);
            _facade->execute(cmd);
        }
        else
        {
            LoadFileCamera<LoadManager> cmd(obj, filename);
            _facade->execute(cmd);
        }

        AddCamera<SceneManager> add(obj);
        _facade->execute(add);

        _cameras.push_back(obj->get_id());
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при загрузке камеры: %1").arg(error.what()));
        return;
    }

    updateScene();
    camera_id++;
    QString name  = QString("Camera%1").arg(camera_id);
    ui->cameraCB->addItem(name);
    ui->cameraCB->setCurrentIndex(ui->cameraCB->count() - 1);
}

void MainWindow::on_removeModelBtn_clicked()
{
    try
    {
        checkModelsExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", "Нет загруженных моделей!");
        return;
    }

    if (group_id.has_value())
    {
        QMessageBox::critical(this, "Ошибка", "Сначала разгруппируйте модели!");
        return;
    }

    int index = ui->modelCB->currentIndex();
    
    try
    {
        RemoveModel<SceneManager> cmd(_models[index]);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при удалении модели: %1").arg(error.what()));
        return;
    }

    _models.erase(_models.begin() + index);
    ui->modelCB->removeItem(index);

    if (!_models.empty())
    {
        active_model_index = std::min(active_model_index, static_cast<int>(_models.size()) - 1);
    }
    else
    {
        active_model_index = 0;
    }

    updateScene();
}

void MainWindow::on_removeCameraBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", "Нет камер!");
        return;
    }

    try
    {
        checkCamDelete();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", "Нельзя удалить последнюю камеру пока есть модели!");
        return;
    }

    int index = ui->cameraCB->currentIndex();

    try
    {
        RemoveCamera<SceneManager> cmd(_cameras[index]);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при удалении камеры: %1").arg(error.what()));
        return;
    }

    _cameras.erase(_cameras.begin() + index);
    ui->cameraCB->removeItem(index);

    if (!_cameras.empty())
    {
        int new_index = ui->cameraCB->currentIndex();

        SetCamera<SceneManager> set(_cameras[new_index]);
        _facade->execute(set);
    }

    updateScene();
}

void MainWindow::on_groupModelBtn_clicked()
{
    try
    {
        checkModelsExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", "Нет моделей!");
        return;
    }

    if (group_id.has_value())
    {
        QMessageBox::critical(this, "Ошибка", "Группа уже существует!");
        return;
    }

    std::shared_ptr<Object> group;

    try
    {
        GroupModel<SceneManager> cmd(group);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при группировке: %1").arg(error.what()));
        return;
    }

    group_id = group->get_id();
    _models.push_back(group->get_id());

    ui->modelCB->addItem("[ Group ]");
    ui->modelCB->setCurrentIndex(ui->modelCB->count() - 1);

    updateScene();
}

void MainWindow::on_ungroupModelBtn_clicked()
{
    if (!group_id.has_value()) return;

    try
    {
        RemoveModel<SceneManager> cmd(group_id.value());
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при разгруппировке: %1").arg(error.what()));
        return;
    }

    auto it = std::find(_models.begin(), _models.end(), group_id.value());
    if (it != _models.end())
    {
        _models.erase(it);
    }

    group_id.reset();

    for (int i = 0; i < ui->modelCB->count(); ++i)
    {
        if (ui->modelCB->itemText(i) == "[ Group ]")
        {
            ui->modelCB->removeItem(i);
            break;
        }
    }

    updateScene();
}

void MainWindow::on_cameraCB_currentIndexChanged(int index)
{
    if (_cameras.empty() || index < 0) return;

    try
    {
        SetCamera<SceneManager> cmd(_cameras[index]);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при смене камеры: %1").arg(error.what()));
        return;
    }

    updateScene();
}

void MainWindow::on_modelCB_currentIndexChanged(int index)
{
    active_model_index = index;
}

void MainWindow::on_moveModelBtn_clicked()
{
    try 
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
        return;
    }

    std::size_t id = _models[active_model_index];
    std::shared_ptr<Object> obj;

    try
    {
        GetModel<SceneManager> get(obj, id);
        _facade->execute(get);

        AddState<HistoryManager> state(obj);
        _facade->execute(state);

        Transformer tr(ui->xDSB->value(), ui->yDSB->value(), ui->zDSB->value());

        MoveModel<TransformManager> set(tr);
        _facade->execute(set);

        TransformModel<TransformManager> cmd(obj);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при перемещении: %1").arg(error.what()));
        return;
    }

    updateScene();
}

void MainWindow::on_scaleModelBtn_clicked()
{
    try 
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
        return;
    }

    std::size_t id = _models[active_model_index];
    std::shared_ptr<Object> obj;

    try
    {
        GetModel<SceneManager> get(obj, id);
        _facade->execute(get);

        AddState<HistoryManager> state(obj);
        _facade->execute(state);

        Transformer tr(ui->xDSB->value(), ui->yDSB->value(), ui->zDSB->value());

        ScaleModel<TransformManager> set(tr);
        _facade->execute(set);

        TransformModel<TransformManager> cmd(obj);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при перемещении: %1").arg(error.what()));
        return;
    }

    updateScene();
}

void MainWindow::on_rotateModelBtn_clicked()
{
    try 
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
        return;
    }

    std::size_t id = _models[active_model_index];
    std::shared_ptr<Object> obj;

    try
    {
        GetModel<SceneManager> get(obj, id);
        _facade->execute(get);

        AddState<HistoryManager> state(obj);
        _facade->execute(state);

        Transformer tr(ui->xDSB->value(), ui->yDSB->value(), ui->zDSB->value());

        RotateModel<TransformManager> set(tr);
        _facade->execute(set);

        TransformModel<TransformManager> cmd(obj);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при перемещении: %1").arg(error.what()));
        return;
    }

    updateScene();
}

void MainWindow::on_moveCameraBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", "Нет камер!");
        return;
    }

    std::shared_ptr<Object> obj;

    try
    {
        GetCamera<SceneManager> get(obj);
        _facade->execute(get);

        AddState<HistoryManager> state(obj);
        _facade->execute(state);

        Transformer tr(ui->xDSB->value(), ui->yDSB->value(), ui->zDSB->value());

        MoveCamera<TransformManager> set(tr);
        _facade->execute(set);

        TransformCamera<TransformManager> cmd(obj);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при перемещении камеры: %1").arg(error.what()));
        return;
    }

    updateScene();
}

void MainWindow::on_scaleCameraBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", "Нет камер!");
        return;
    }

    std::shared_ptr<Object> obj;

    try
    {
        GetCamera<SceneManager> get(obj);
        _facade->execute(get);

        AddState<HistoryManager> state(obj);
        _facade->execute(state);

        Transformer tr(ui->xDSB->value(), ui->yDSB->value(), ui->zDSB->value());

        ScaleCamera<TransformManager> set(tr);
        _facade->execute(set);

        TransformCamera<TransformManager> cmd(obj);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при перемещении камеры: %1").arg(error.what()));
        return;
    }

    updateScene();
}

void MainWindow::on_rotateCameraBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", "Нет камер!");
        return;
    }

    std::shared_ptr<Object> obj;

    try
    {
        GetCamera<SceneManager> get(obj);
        _facade->execute(get);

        AddState<HistoryManager> state(obj);
        _facade->execute(state);

        Transformer tr(ui->xDSB->value(), ui->yDSB->value(), ui->zDSB->value());

        RotateCamera<TransformManager> set(tr);
        _facade->execute(set);

        TransformCamera<TransformManager> cmd(obj);
        _facade->execute(cmd);
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при перемещении камеры: %1").arg(error.what()));
        return;
    }

    updateScene();
}

void MainWindow::on_undoBtn_clicked()
{
    try
    {
        UndoState<HistoryManager> cmd;
        _facade->execute(cmd);
    }
    catch (const std::exception& error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Невозможно отменить действие"));
        return;
    }

    updateScene();
}

void MainWindow::on_redoBtn_clicked()
{
    try
    {
        RedoState<HistoryManager> cmd;
        _facade->execute(cmd);
    }
    catch (const std::exception& error)
    {
        QMessageBox::critical(this, "Ошибка", QString("Невозможно вернуть отмененной действие"));
        return;
    }

    updateScene();
}
