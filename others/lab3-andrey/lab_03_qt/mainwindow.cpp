#include "mainwindow.hpp"

#include <QFileDialog>
#include "ui_mainwindow.h"

#include "src/InternalRepresentation/ObjectDataDialog.hpp"
#include "src/Drawer/Factory/QtDrawerFactory.hpp"
#include "src/HLR/AllEdgesStrategy.hpp"
#include "src/HLR/BackFaceCullingStrategy.hpp"
#include "src/Builders/Readers/LPReaders/txt/TXTLPReader.hpp"
#include "src/Builders/Readers/LPReaders/csv/CSVLPReader.hpp"
#include "src/Builders/Readers/LPReaders/bin/BINLPReader.hpp"
#include "src/Builders/Readers/PTUReader/cmr/CMRPTUReader.hpp"
#include "src/Builders/Readers/PTUReader/csv/CSVPTUReader.hpp"
#include "src/Builders/Readers/PTUReader/bin/BINPTUReader.hpp"
#include "consts.hpp"

static bool parseDouble(const QString& text, double& val)
{
    const QString t = text.trimmed();
    if (t.isEmpty()) { val = 0.0; return true; }
    bool ok = false;
    val = t.toDouble(&ok);
    return ok;
}

mainwindow::mainwindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow)
    , _hlrStrategy(std::make_shared<AllEdgesStrategy>())
{
    ui->setupUi(this);

    QGraphicsView* view = graphicsViewWidget();
    view->setRenderHint(QPainter::Antialiasing);
    view->setFrameShape(QFrame::NoFrame);

    try
    {
        objectTableInit();
        cameraTableInit();

        auto qtScene = new QGraphicsScene(view);
        qtScene->setSceneRect(-HALF_SCENE_WIDTH, -HALF_SCENE_HEIGHT,
                              SCENE_WIDTH, SCENE_HEIGHT);
        view->setScene(qtScene);

        _factory = std::make_shared<QtDrawerFactory>(qtScene, QPen(Qt::black, 1));
        _facade  = std::make_unique<Facade>();

        initialization_check = true;
    }
    catch (...) { initialization_check = false; }
}

mainwindow::~mainwindow() { delete ui; }

QGraphicsView* mainwindow::graphicsViewWidget() const { return ui->graphicsView; }
QWidget*       mainwindow::objectContainer()    const { return ui->ObjectContainer; }
QWidget*       mainwindow::cameraContainer()    const { return ui->CameraContainer; }

QString mainwindow::readCenterX() const { return ui->LineEditX->text(); }
QString mainwindow::readCenterY() const { return ui->LineEditY->text(); }
QString mainwindow::readCenterZ() const { return ui->LineEditZ->text(); }

QString mainwindow::readDx() const { return ui->LineEditDx->text(); }
QString mainwindow::readDy() const { return ui->LineEditDy->text(); }
QString mainwindow::readDz() const { return ui->LineEditDz->text(); }

QString mainwindow::readOx() const { return ui->LineEditOx->text(); }
QString mainwindow::readOy() const { return ui->LineEditOy->text(); }
QString mainwindow::readOz() const { return ui->LineEditOz->text(); }

QString mainwindow::readKx() const { return ui->LineEditKx->text(); }
QString mainwindow::readKy() const { return ui->LineEditKy->text(); }
QString mainwindow::readKz() const { return ui->LineEditKz->text(); }

QString mainwindow::readDxCam() const { return ui->LineEditDx_Cam->text(); }
QString mainwindow::readDyCam() const { return ui->LineEditDy_Cam->text(); }
QString mainwindow::readDzCam() const { return ui->LineEditDz_Cam->text(); }

QString mainwindow::readOxCam() const { return ui->LineEditOx_Cam->text(); }
QString mainwindow::readOyCam() const { return ui->LineEditOy_Cam->text(); }
QString mainwindow::readOzCam() const { return ui->LineEditOz_Cam->text(); }

// ── Высокоуровневое ───────────────────────────────────────────────────────────

void mainwindow::redraw()
{
    _facade->render(_factory, _hlrStrategy);
}

void mainwindow::on_actionAdd_Object_triggered()
{
    const QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open Figure File"), QDir::currentPath(),
        tr("Figure Files (*.txt *.csv *.bin *.tar.gz);;All Files (*)"),
        nullptr, QFileDialog::DontUseNativeDialog);
    if (fileName.isEmpty()) return;

    const QString relativePath = QDir().relativeFilePath(fileName);
    const std::string path = relativePath.toStdString();
    const QString ext = QFileInfo(fileName).suffix().toLower();
    const QString completeExt = QFileInfo(fileName).completeSuffix().toLower();

    bool ok = false;
    if (ext == "txt")
        ok = _facade->loadObject<TXTLPReader>(path);
    else if (ext == "csv")
        ok = _facade->loadObject<CSVLPReader>(path);
    else if (ext == "bin")
        ok = _facade->loadObject<BINLPReader>(path);
    else if (completeExt == "tar.gz" || ext == "gz")
        ok = _facade->loadComposite(path);

    if (!ok) return;

    const QString name = QFileInfo(fileName).baseName();
    _objectNames.push_back(name);
    _objectTable->pushItem(name);
    redraw();
}

void mainwindow::on_actionAdd_Camera_triggered()
{
    const QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open Camera File"), QDir::currentPath(),
        tr("Camera Files (*.cmr *.csvcmr *.bincmr);;All Files (*)"),
        nullptr, QFileDialog::DontUseNativeDialog);
    if (fileName.isEmpty()) return;

    const QString relativePath = QDir().relativeFilePath(fileName);
    const std::string path = relativePath.toStdString();
    const QString ext = QFileInfo(fileName).suffix().toLower();

    bool ok = false;
    if (ext == "cmr")
        ok = _facade->loadCamera<CMRPTUReader>(path);
    else if (ext == "csvcmr")
        ok = _facade->loadCamera<CSVPTUReader>(path);
    else if (ext == "bincmr")
        ok = _facade->loadCamera<BINPTUReader>(path);

    if (!ok) return;

    const QString name = QFileInfo(fileName).baseName();
    _cameraNames.push_back(name);
    _cameraTable->pushItem(name);
    redraw();
}

void mainwindow::on_DeleteObjectButton_clicked()
{
    const int id = _objectTable->selectedItem();
    if (id == -1) return;

    _facade->deleteObjects({ static_cast<size_t>(id) });

    _objectTable->removeItem(static_cast<size_t>(id));
    if (static_cast<size_t>(id) < _objectNames.size())
        _objectNames.erase(_objectNames.begin() + id);
    redraw();
}

void mainwindow::on_DeleteCameraButton_clicked()
{
    const int id = _cameraTable->selectedItem();
    if (id == -1) return;

    _facade->deleteCameras({ static_cast<size_t>(id) });

    _cameraTable->removeItem(static_cast<size_t>(id));
    if (static_cast<size_t>(id) < _cameraNames.size())
        _cameraNames.erase(_cameraNames.begin() + id);
    redraw();
}

void mainwindow::on_MoveButton_clicked()
{
    std::vector<size_t> ids; toVector(ids, _objectTable->selectedItems());
    if (ids.empty()) return;

    double dx, dy, dz;
    if (!parseDouble(readDx(), dx)) return;
    if (!parseDouble(readDy(), dy)) return;
    if (!parseDouble(readDz(), dz)) return;

    _facade->moveObjects(ids, dx, dy, dz);
    redraw();
}

void mainwindow::on_RotateButton_clicked()
{
    std::vector<size_t> ids; toVector(ids, _objectTable->selectedItems());
    if (ids.empty()) return;

    double ox, oy, oz, cx, cy, cz;
    if (!parseDouble(readOx(), ox)) return;
    if (!parseDouble(readOy(), oy)) return;
    if (!parseDouble(readOz(), oz)) return;
    if (!parseDouble(readCenterX(), cx)) return;
    if (!parseDouble(readCenterY(), cy)) return;
    if (!parseDouble(readCenterZ(), cz)) return;

    _facade->rotateObjects(ids, ox, oy, oz, cx, cy, cz);
    redraw();
}

void mainwindow::on_ScaleButton_clicked()
{
    std::vector<size_t> ids; toVector(ids, _objectTable->selectedItems());
    if (ids.empty()) return;

    double kx, ky, kz, cx, cy, cz;
    if (!parseDouble(readKx(), kx)) return;
    if (!parseDouble(readKy(), ky)) return;
    if (!parseDouble(readKz(), kz)) return;
    if (!parseDouble(readCenterX(), cx)) return;
    if (!parseDouble(readCenterY(), cy)) return;
    if (!parseDouble(readCenterZ(), cz)) return;

    _facade->scaleObjects(ids, kx, ky, kz, cx, cy, cz);
    redraw();
}

void mainwindow::on_SetCameraButton_clicked()
{
    const int id = _cameraTable->selectedItem();
    if (id == -1) return;
    _facade->setActiveCamera(id);
    redraw();
}

void mainwindow::on_MoveButton_Cam_clicked()
{
    std::vector<size_t> ids; toVector(ids, _cameraTable->selectedItems());
    if (ids.empty()) return;

    double dx, dy, dz;
    if (!parseDouble(readDxCam(), dx)) return;
    if (!parseDouble(readDyCam(), dy)) return;
    if (!parseDouble(readDzCam(), dz)) return;

    _facade->moveCameras(ids, dx, dy, dz);
    redraw();
}

void mainwindow::on_RotateButton_Cam_clicked()
{
    std::vector<size_t> ids; toVector(ids, _cameraTable->selectedItems());
    if (ids.empty()) return;

    double ox, oy, oz;
    if (!parseDouble(readOxCam(), ox)) return;
    if (!parseDouble(readOyCam(), oy)) return;
    if (!parseDouble(readOzCam(), oz)) return;

    _facade->rotateCameras(ids, ox, oy, oz);
    redraw();
}

void mainwindow::on_CombineButton_clicked()
{
    std::vector<size_t> ids; toVector(ids, _objectTable->selectedItems());
    if (ids.empty()) return;

    _facade->combineObjects(ids);

    std::vector<size_t> sorted = ids;
    std::ranges::sort(sorted, std::greater<>{});
    for (size_t id : sorted)
    {
        _objectTable->removeItem(id);
        if (id < _objectNames.size())
            _objectNames.erase(_objectNames.begin() + id);
    }
    _objectNames.emplace_back("Combine");
    _objectTable->pushItem("Combine");
    redraw();
}

void mainwindow::on_UndoButton_clicked()
{
    if (_facade->undo())
    {
        rebuildTablesFromScene();
        redraw();
    }
}

void mainwindow::on_RedoButton_clicked()
{
    if (_facade->redo())
    {
        rebuildTablesFromScene();
        redraw();
    }
}

void mainwindow::on_HLRCheckBox_toggled(bool checked)
{
    _hlrStrategy = checked
        ? std::static_pointer_cast<BaseHLRStrategy>(std::make_shared<BackFaceCullingStrategy>())
        : std::static_pointer_cast<BaseHLRStrategy>(std::make_shared<AllEdgesStrategy>());
    redraw();
}

void mainwindow::on_ShowDataButton_clicked()
{
    const int id = _objectTable->selectedItem();
    if (id == -1) return;

    FigureInternalData data{};
    if (!_facade->getObjectInternalData(static_cast<size_t>(id), data)) return;

    const QString name = (static_cast<size_t>(id) < _objectNames.size())
        ? _objectNames[static_cast<size_t>(id)]
        : QString("Object %1").arg(id);

    ObjectDataDialog dialog{data, name, this};
    dialog.exec();
}

void mainwindow::rebuildTablesFromScene()
{
    _objectTable->clear();
    _cameraTable->clear();
    _objectNames.clear();
    _cameraNames.clear();

    const size_t objN = _facade->objectCount();
    for (size_t i = 0; i < objN; ++i)
    {
        const QString name = QString("Object %1").arg(i);
        _objectNames.push_back(name);
        _objectTable->pushItem(name);
    }

    const size_t camN = _facade->cameraCount();
    for (size_t i = 0; i < camN; ++i)
    {
        const QString name = QString("Camera %1").arg(i);
        _cameraNames.push_back(name);
        _cameraTable->pushItem(name);
    }

    _facade->setActiveCamera(camN > 0 ? 0 : -1);
}

void mainwindow::objectTableInit()
{
    auto* table = new QTableWidget();
    table->setColumnCount(1);
    table->setColumnWidth(0, 379);
    table->setUpdatesEnabled(true);
    table->setHorizontalHeaderLabels({"Object name"});
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QWidget* container = objectContainer();
    auto* layout = new QVBoxLayout(container);
    layout->addWidget(table);
    container->setLayout(layout);
    _objectTable = std::make_unique<Table>(table);
}

void mainwindow::cameraTableInit()
{
    auto* table = new QTableWidget();
    table->setColumnCount(1);
    table->setColumnWidth(0, 379);
    table->setUpdatesEnabled(true);
    table->setHorizontalHeaderLabels({"Camera name"});
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QWidget* container = cameraContainer();
    auto* layout = new QVBoxLayout(container);
    layout->addWidget(table);
    container->setLayout(layout);
    _cameraTable = std::make_unique<Table>(table);
}

void mainwindow::toVector(std::vector<size_t>& v, const QSet<int>& set)
{
    for (const int id : set)
        if (id >= 0) v.push_back(static_cast<size_t>(id));
    std::ranges::sort(v);
}
