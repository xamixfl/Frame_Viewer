#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cstddef>
#include <memory>
#include <vector>
#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class QListWidget;
class QDoubleSpinBox;
class QLabel;
class QPushButton;
class QComboBox;

class Facade;
class QtDrawerFactory;

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onLoadModel();
    void onLoadCamera();
    void onAddDefaultCamera();
    void onAddDefaultLight();
    void onRemoveSelected();
    void onSwitchCamera();
    void onSetMaterial();
    void onClearScene();
    void onMove();
    void onRotate();
    void onScale();
    void onUndo();
    void onRedo();

private:
    std::unique_ptr<QtDrawerFactory> _factory;
    std::unique_ptr<Facade> _facade;

    QGraphicsScene* _gscene  = nullptr;
    QGraphicsView*  _view    = nullptr;
    QListWidget*    _objectList = nullptr;
    QListWidget*    _historyList = nullptr;
    QPushButton*    _undoBtn = nullptr;
    QPushButton*    _redoBtn = nullptr;
    QLabel*         _activeCameraLabel = nullptr;
    QDoubleSpinBox* _xSpin = nullptr;
    QDoubleSpinBox* _ySpin = nullptr;
    QDoubleSpinBox* _zSpin = nullptr;
    QComboBox*      _reprCombo = nullptr;
    QComboBox* _materialCombo;

    void _setupUi();
    void _redraw();
    void _refreshObjectList();
    void _refreshHistory();
    void _ensureCamera();
    void _safeExecute(std::unique_ptr<class BaseCommand> cmd, const QString& errorTitle);

    [[nodiscard]] long long _selectedId() const noexcept;
    [[nodiscard]] std::vector<size_t> _selectedIds() const;
};

#endif 
