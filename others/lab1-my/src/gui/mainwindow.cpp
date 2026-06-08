#include <cmath>
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->sidePanelWidget->hide();

    setupMenuConnections();
    setupColorConnections();
    setupMoveConnections();
    setupRotateConnections();
    setupScaleConnection();
}

MainWindow::~MainWindow() {
    Request_t req;
    req.action = ACTION_QUIT;
    task_manager(&req);
    delete ui;
}

void MainWindow::setupMenuConnections() {
    connect(ui->enableSlidersAction, &QAction::triggered, this, [this]() {
        ui->sidePanelWidget->setVisible(ui->sidePanelWidget->isHidden());
    });

    connect(ui->openFileAction, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(ui->saveFileAction, &QAction::triggered, this, &MainWindow::onSaveFile);
    connect(ui->exitProgramAction, &QAction::triggered, this, &MainWindow::onExit);
    connect(ui->aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
    connect(ui->authorAction, &QAction::triggered, this, &MainWindow::onAuthor);
}

void MainWindow::setupColorConnections() {
    connect(ui->bgColorAction, &QAction::triggered, this, [this]() {
        QColor color = QColorDialog::getColor(ui->modelView->backgroundColor(), this, tr("Выберите цвет фона"));
        if (color.isValid())
            ui->modelView->setBackgroundColor(color);
    });

    connect(ui->modelColorAction, &QAction::triggered, this, [this]() {
        QColor color = QColorDialog::getColor(ui->modelView->modelColor(), this, tr("Выберите цвет модели"));
        if (color.isValid())
            ui->modelView->setModelColor(color);
    });
}

void MainWindow::handleMoveAxis(double value, double& lastValue, Axis_t axis) {
    double delta = value - lastValue;

    if (std::abs(delta) > MATH_EPSILON) {
        Request_t req;
        req.action = ACTION_MOVE;
        req.move = {
            .delta = delta,
            .axis = axis
        };

        task_manager(&req);
        lastValue = value;
        ui->modelView->update();
    }
}

void MainWindow::handleRotateAxis(double value, double& lastValue, Axis_t axis) {
    double delta = value - lastValue;

    if (std::abs(delta) > MATH_EPSILON) {
        Request_t req;
        req.action = ACTION_ROTATE;
        req.rotate = {
            .angle = delta,
            .axis = axis
        };

        task_manager(&req);
        lastValue = value;
        ui->modelView->update();
    }
}

void MainWindow::setupMoveConnections() {
    connect(ui->moveXSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double v) {
        handleMoveAxis(v, lastMoveX, AXIS_X);
    });

    connect(ui->moveYSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double v) {
        handleMoveAxis(v, lastMoveY, AXIS_Y);
    });

    connect(ui->moveZSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double v) {
        handleMoveAxis(v, lastMoveZ, AXIS_Z);
    });
}

void MainWindow::setupRotateConnections() {
    connect(ui->rotateXSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double v) {
        handleRotateAxis(v, lastRotateX, AXIS_X);
    });

    connect(ui->rotateYSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double v) {
        handleRotateAxis(v, lastRotateY, AXIS_Y);
    });

    connect(ui->rotateZSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double v) {
        handleRotateAxis(v, lastRotateZ, AXIS_Z);
    });
}

void MainWindow::setupScaleConnection() {
    connect(ui->scaleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double value) {
        if (lastScale > MATH_EPSILON && value > MATH_EPSILON) {
            Request_t req;
            req.action = ACTION_SCALE;
            req.scale = { 
                .factor = value / lastScale 
            };

            task_manager(&req);
            lastScale = value;
            ui->modelView->update();
        }
    });
}

void MainWindow::onOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Открыть OBJ файл"),
        "",
        tr("OBJ Files (*.obj);;All Files (*)")
    );

    if (!fileName.isEmpty()) {
        QByteArray bytes = fileName.toUtf8();

        Request_t req;
        req.action = ACTION_LOAD;
        req.filename = bytes.constData();

        int rc = task_manager(&req);
        if (rc == RC_OK)
            ui->modelView->update();
    }
}

void MainWindow::onSaveFile() {
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Сохранить OBJ файл"),
        "",
        tr("OBJ Files (*.obj);;All Files (*)")
    );

    if (!fileName.isEmpty()) {
        QByteArray bytes = fileName.toUtf8();

        Request_t req;
        req.action = ACTION_SAVE;
        req.filename = bytes.constData();

        int rc = task_manager(&req);
        if (rc != RC_OK)
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось сохранить файл."));
    }
}

void MainWindow::onExit() {
    close();
}

void MainWindow::onAbout() {
    QMessageBox::about(this, tr("О программе"),
        tr("Программа для каркасного отображения моделей в формате OBJ.\n\n"
           "Используйте мышь для вращения модели, колесо для масштабирования "
           "и клавиши WASD для перемещения."));
}

void MainWindow::onAuthor() {
    QMessageBox::about(this, tr("Автор"), tr("Студент группы ИУ7-45Б\n\nКузнецов И.А."));
}
