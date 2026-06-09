#include "ui/MainWindow.h"

#include "factory/QtDrawerFactory.h"
#include "facade/Facade.h"
#include "manager/LoadManager.h"
#include "manager/SceneManager.h"
#include "manager/TransformManager.h"
#include "manager/DrawManager.h"
#include "manager/HistoryManager.h"
#include "manager/LoadId.h"
#include "command/ModelCommands.h"
#include "command/CameraCommands.h"
#include "command/SceneCommands.h"
#include "command/TransformCommands.h"
#include "command/HistoryCommands.h"
#include "composite/Model.h"
#include "composite/Camera.h"
#include "composite/BaseObject.h"
#include "data/Transform.h"
#include "solution/Solution.h"
#include "creator/CreatorMaker.h"
#include "director/CarcasModelDirector.h"
#include "director/CarcasCameraDirector.h"
#include "director/SceneDirector.h"
#include "director/AssimpDirector.h"
#include "builder/CarcasModelBuilder.h"
#include "builder/CarcasCameraBuilder.h"
#include "builder/SceneBuilder.h"
#include "builder/AssimpModelBuilder.h"
#include "composite/Light.h"
#include "bridge/LightImpl.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QAbstractItemView>
#include <QListWidget>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QStatusBar>
#include <Qt>

namespace {

std::unique_ptr<Solution> buildLoadSolution() {
    return std::make_unique<Solution>(std::initializer_list<std::pair<std::size_t, Solution::CreatorFactory>>{
        { static_cast<std::size_t>(LoadId::Model),
          &CreatorMaker::make<CarcasModelBuilder, CarcasModelDirector> },
        { static_cast<std::size_t>(LoadId::Camera),
          &CreatorMaker::make<CarcasCameraBuilder, CarcasCameraDirector> },
        { static_cast<std::size_t>(LoadId::Scene),
          &CreatorMaker::make<SceneBuilder, SceneDirector> },
        { static_cast<std::size_t>(LoadId::AssimpModel), 
        []() { return CreatorMaker::make<AssimpModelBuilder, AssimpDirector>(); } }
    });
}

} // namespace

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    _setupUi();

    _gscene = new QGraphicsScene(this);
    _gscene->setSceneRect(-400, -300, 800, 600);
    _view->setScene(_gscene);

    _factory = std::make_unique<QtDrawerFactory>(*_gscene);

    auto loadMgr      = std::make_unique<LoadManager>(buildLoadSolution());
    auto sceneMgr     = std::make_unique<SceneManager>();
    auto transformMgr = std::make_unique<TransformManager>();
    auto drawMgr      = std::make_unique<DrawManager>(*_factory);
    auto historyMgr   = std::make_unique<HistoryManager>();

    _facade = std::make_unique<Facade>(
        std::move(loadMgr),
        std::move(sceneMgr),
        std::move(transformMgr),
        std::move(drawMgr),
        std::move(historyMgr)
    );

    auto impl = std::make_unique<LightImpl>();
    impl->setPosition({100, 100, 100});
    impl->setIntensity(1.0f);

    auto light = std::make_shared<Light>(std::move(impl));

    _facade->getSceneManager().addObject(light);

    _ensureCamera();
    _refreshObjectList();
    _refreshHistory();

    setWindowTitle("Frame Viewer");
    resize(1100, 700);
}

MainWindow::~MainWindow() = default;

void MainWindow::_setupUi() {
    auto* central = new QWidget(this);
    auto* mainLayout = new QHBoxLayout(central);

    _view = new QGraphicsView();
    _view->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(_view, 1);

    auto* sidebar = new QVBoxLayout();
    mainLayout->addLayout(sidebar, 0);

    auto* loadBox    = new QGroupBox("Загрузка");
    auto* loadLayout = new QVBoxLayout(loadBox);

    auto* reprLayout = new QHBoxLayout();
    reprLayout->addWidget(new QLabel("Представление:"));
    _reprCombo = new QComboBox();
    _reprCombo->addItem("Список рёбер",      static_cast<qulonglong>(LoadId::Model));
    _reprCombo->addItem("Матрица смежности", static_cast<qulonglong>(LoadId::ModelMatrix));
    reprLayout->addWidget(_reprCombo, 1);
    loadLayout->addLayout(reprLayout);

    auto* loadModelBtn  = new QPushButton("Загрузить модель…");
    auto* loadCameraBtn = new QPushButton("Загрузить камеру…");
    auto* addCameraBtn  = new QPushButton("Добавить камеру по умолчанию");
    auto* addLightBtn   = new QPushButton("Добавить свет");
    auto* clearBtn      = new QPushButton("Очистить сцену");
    loadLayout->addWidget(loadModelBtn);
    loadLayout->addWidget(loadCameraBtn);
    loadLayout->addWidget(addCameraBtn);
    loadLayout->addWidget(addLightBtn);
    loadLayout->addWidget(clearBtn);
    sidebar->addWidget(loadBox);

    auto* listBox    = new QGroupBox("Объекты сцены");
    auto* listLayout = new QVBoxLayout(listBox);
    _objectList = new QListWidget();
    _objectList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listLayout->addWidget(_objectList);
    auto* removeBtn    = new QPushButton("Удалить выбранный");
    auto* switchCamBtn = new QPushButton("Сделать активной камерой");
    listLayout->addWidget(removeBtn);
    listLayout->addWidget(switchCamBtn);
    _activeCameraLabel = new QLabel("Активная камера: нет");
    listLayout->addWidget(_activeCameraLabel);
    sidebar->addWidget(listBox, 1);

    auto* transformBox = new QGroupBox("Трансформация выбранного");
    auto* tLayout      = new QVBoxLayout(transformBox);

    auto* coordLayout = new QHBoxLayout();
    _xSpin = new QDoubleSpinBox();
    _ySpin = new QDoubleSpinBox();
    _zSpin = new QDoubleSpinBox();
    for (auto* sb : {_xSpin, _ySpin, _zSpin}) {
        sb->setRange(-1000.0, 1000.0);
        sb->setDecimals(3);
        sb->setSingleStep(0.1);
    }
    coordLayout->addWidget(new QLabel("X:"));
    coordLayout->addWidget(_xSpin);
    coordLayout->addWidget(new QLabel("Y:"));
    coordLayout->addWidget(_ySpin);
    coordLayout->addWidget(new QLabel("Z:"));
    coordLayout->addWidget(_zSpin);
    tLayout->addLayout(coordLayout);

    auto* moveBtn   = new QPushButton("Move");
    auto* rotateBtn = new QPushButton("Rotate (радианы)");
    auto* scaleBtn  = new QPushButton("Scale");
    tLayout->addWidget(moveBtn);
    tLayout->addWidget(rotateBtn);
    tLayout->addWidget(scaleBtn);
    sidebar->addWidget(transformBox);

    auto* historyBox    = new QGroupBox("История операций");
    auto* historyLayout = new QVBoxLayout(historyBox);
    _historyList = new QListWidget();
    historyLayout->addWidget(_historyList);
    _undoBtn = new QPushButton("Отменить");
    _redoBtn = new QPushButton("Повторить");
    historyLayout->addWidget(_undoBtn);
    historyLayout->addWidget(_redoBtn);
    sidebar->addWidget(historyBox, 1);

    sidebar->addStretch(0);

    setCentralWidget(central);
    statusBar()->showMessage("Готов");

    connect(loadModelBtn,  &QPushButton::clicked, this, &MainWindow::onLoadModel);
    connect(loadCameraBtn, &QPushButton::clicked, this, &MainWindow::onLoadCamera);
    connect(addCameraBtn,  &QPushButton::clicked, this, &MainWindow::onAddDefaultCamera);
    connect(addLightBtn, &QPushButton::clicked, this, &MainWindow::onAddDefaultLight);
    connect(clearBtn,      &QPushButton::clicked, this, &MainWindow::onClearScene);
    connect(removeBtn,     &QPushButton::clicked, this, &MainWindow::onRemoveSelected);
    connect(switchCamBtn,  &QPushButton::clicked, this, &MainWindow::onSwitchCamera);
    connect(moveBtn,       &QPushButton::clicked, this, &MainWindow::onMove);
    connect(rotateBtn,     &QPushButton::clicked, this, &MainWindow::onRotate);
    connect(scaleBtn,      &QPushButton::clicked, this, &MainWindow::onScale);
    connect(_undoBtn,      &QPushButton::clicked, this, &MainWindow::onUndo);
    connect(_redoBtn,      &QPushButton::clicked, this, &MainWindow::onRedo);
}

void MainWindow::_redraw() {
    _gscene->clear();
    _facade->execute(std::make_unique<DrawSceneCommand>(
        _facade->getSceneManager(), _facade->getDrawManager()));
}

void MainWindow::_refreshObjectList() {
    _objectList->clear();

    auto& sceneMgr = _facade->getSceneManager();
    for (const auto& obj : sceneMgr.getObjects()) {
        QString type;
        if (std::dynamic_pointer_cast<Model>(obj))       type = "Model";
        else if (std::dynamic_pointer_cast<Camera>(obj)) type = "Camera";
        else                                             type = "Light";

        const QString text = QString("[id=%1] %2").arg(obj->getId()).arg(type);
        auto* item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, static_cast<qulonglong>(obj->getId()));
        _objectList->addItem(item);
    }

    if (auto cam = sceneMgr.getActiveCamera()) {
        _activeCameraLabel->setText(QString("Активная камера: id=%1").arg(cam->getId()));
    } else {
        _activeCameraLabel->setText("Активная камера: нет");
    }
}

long long MainWindow::_selectedId() const noexcept {
    auto* item = _objectList->currentItem();
    if (!item) {
        return -1;
    }
    return static_cast<long long>(item->data(Qt::UserRole).toULongLong());
}

std::vector<size_t> MainWindow::_selectedIds() const {
    std::vector<size_t> ids;
    const auto items = _objectList->selectedItems();
    ids.reserve(items.size());
    for (auto* item : items) {
        ids.push_back(static_cast<size_t>(item->data(Qt::UserRole).toULongLong()));
    }
    return ids;
}

void MainWindow::_refreshHistory() {
    _historyList->clear();
    auto& historyMgr = _facade->getHistoryManager();
    for (const auto& n : historyMgr.names()) {
        _historyList->addItem(QString::fromStdString(n));
    }
    if (auto* item = _historyList->item(_historyList->count() - 1)) {
        _historyList->setCurrentItem(item);
    }
    _undoBtn->setEnabled(historyMgr.canUndo());
    _redoBtn->setEnabled(historyMgr.canRedo());
}

void MainWindow::_ensureCamera() {
    auto& sceneMgr = _facade->getSceneManager();
    if (sceneMgr.getActiveCamera()) {
        return;
    }
    for (const auto& obj : sceneMgr.getObjects()) {
        if (auto cam = std::dynamic_pointer_cast<Camera>(obj)) {
            _safeExecute(std::make_unique<SwitchCameraCommand>(sceneMgr, cam->getId()), "Ошибка");
            return;
        }
    }
    _safeExecute(std::make_unique<AddDefaultCameraCommand>(sceneMgr), "Ошибка");
}

void MainWindow::_safeExecute(std::unique_ptr<BaseCommand> cmd, const QString& errorTitle) {
    try {
        _facade->execute(std::move(cmd));
    } catch (const std::exception& e) {
        QMessageBox::warning(this, errorTitle, e.what());
    }
}

void MainWindow::onLoadModel() {
    const QString fname = QFileDialog::getOpenFileName(this, "Загрузить модель", QString(), "*.obj *.txt *.bin");
    if (fname.isEmpty()) {
        return;
    }

    const auto loadId = fname.endsWith(".obj", Qt::CaseInsensitive) 
                      ? LoadId::AssimpModel 
                      : static_cast<LoadId>(_reprCombo->currentData().toULongLong());

    _safeExecute(std::make_unique<LoadModelCommand>(
        _facade->getLoadManager(), _facade->getSceneManager(),
        fname.toStdString(), loadId), "Ошибка загрузки модели");
    _refreshObjectList();
    _refreshHistory();
    _redraw();
    statusBar()->showMessage(QString("Загружена модель: %1 [%2]").arg(fname, _reprCombo->currentText()));
}

void MainWindow::onLoadCamera() {
    const QString fname = QFileDialog::getOpenFileName(this, "Загрузить камеру", QString(), "*.txt *.bin");
    if (fname.isEmpty()) {
        return;
    }
    _safeExecute(std::make_unique<LoadCameraCommand>(
        _facade->getLoadManager(), _facade->getSceneManager(),
        fname.toStdString()), "Ошибка загрузки камеры");
    _ensureCamera();
    _refreshObjectList();
    _refreshHistory();
    _redraw();
    statusBar()->showMessage(QString("Загружена камера: %1").arg(fname));
}

void MainWindow::onAddDefaultCamera() {
    _safeExecute(std::make_unique<AddDefaultCameraCommand>(_facade->getSceneManager()), "Ошибка");
    _refreshObjectList();
    _refreshHistory();
    _redraw();
    statusBar()->showMessage("Добавлена камера по умолчанию (активна)");
}

void MainWindow::onAddDefaultLight() {
    auto impl = std::make_unique<LightImpl>();
    impl->setPosition({100, 100, 100});
    impl->setIntensity(1.0f);

    auto light = std::make_shared<Light>(std::move(impl));

    _facade->getSceneManager().addObject(light);

    _refreshObjectList();
    _redraw();
    statusBar()->showMessage("Добавлен свет");
}

void MainWindow::onRemoveSelected() {
    const auto ids = _selectedIds();
    if (ids.empty()) {
        return;
    }
    auto& sm = _facade->getSceneManager();
    bool removedCamera = false;
    for (size_t id : ids) {
        std::shared_ptr<BaseObject> obj;
        try {
            obj = sm.getObject(id);
        } catch (...) {
            continue;
        }
        if (std::dynamic_pointer_cast<Camera>(obj)) {
            _safeExecute(std::make_unique<RemoveCameraCommand>(sm, id), "Ошибка");
            removedCamera = true;
        } else {
            _safeExecute(std::make_unique<RemoveModelCommand>(sm, id), "Ошибка");
        }
    }
    if (removedCamera) {
        _ensureCamera();
    }
    _refreshObjectList();
    _refreshHistory();
    _redraw();
}

void MainWindow::onSwitchCamera() {
    const long long id = _selectedId();
    if (id < 0) {
        return;
    }
    _safeExecute(std::make_unique<SwitchCameraCommand>(_facade->getSceneManager(), static_cast<size_t>(id)), "Ошибка переключения камеры");
    _refreshObjectList();
    _refreshHistory();
    _redraw();
}

void MainWindow::onClearScene() {
    _safeExecute(std::make_unique<ClearSceneCommand>(
        _facade->getSceneManager(), _facade->getHistoryManager()), "Ошибка очистки сцены");
    _ensureCamera();
    _refreshObjectList();
    _refreshHistory();
    _redraw();
}

void MainWindow::onMove() {
    auto ids = _selectedIds();
    if (ids.empty()) {
        return;
    }
    const Transform t(_xSpin->value(), _ySpin->value(), _zSpin->value());
    auto& sm = _facade->getSceneManager();
    auto& tm = _facade->getTransformManager();
    auto& hm = _facade->getHistoryManager();
    _safeExecute(std::make_unique<MoveCommand>(sm, tm, hm, std::move(ids), t), "Ошибка перемещения");
    _refreshHistory();
    _redraw();
}

void MainWindow::onRotate() {
    auto ids = _selectedIds();
    if (ids.empty()) {
        return;
    }
    const Transform t(_xSpin->value(), _ySpin->value(), _zSpin->value());
    auto& sm = _facade->getSceneManager();
    auto& tm = _facade->getTransformManager();
    auto& hm = _facade->getHistoryManager();
    _safeExecute(std::make_unique<RotateCommand>(sm, tm, hm, std::move(ids), t), "Ошибка поворота");
    _refreshHistory();
    _redraw();
}

void MainWindow::onScale() {
    auto ids = _selectedIds();
    if (ids.empty()) {
        return;
    }
    const Transform t(_xSpin->value(), _ySpin->value(), _zSpin->value());
    auto& sm = _facade->getSceneManager();
    auto& tm = _facade->getTransformManager();
    auto& hm = _facade->getHistoryManager();
    _safeExecute(std::make_unique<ScaleCommand>(sm, tm, hm, std::move(ids), t), "Ошибка масштабирования");
    _refreshHistory();
    _redraw();
}

void MainWindow::onUndo() {
    auto& historyMgr = _facade->getHistoryManager();
    if (!historyMgr.canUndo()) {
        statusBar()->showMessage("История пуста");
        return;
    }
    _safeExecute(std::make_unique<UndoCommand>(historyMgr), "Ошибка отмены");
    _ensureCamera();
    _refreshObjectList();
    _refreshHistory();
    _redraw();
    statusBar()->showMessage("Отмена выполнена");
}

void MainWindow::onRedo() {
    auto& historyMgr = _facade->getHistoryManager();
    if (!historyMgr.canRedo()) {
        statusBar()->showMessage("Нечего повторять");
        return;
    }
    _safeExecute(std::make_unique<RedoCommand>(historyMgr), "Ошибка повтора");
    _ensureCamera();
    _refreshObjectList();
    _refreshHistory();
    _redraw();
    statusBar()->showMessage("Повтор выполнен");
}
