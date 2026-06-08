/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *loadCameraBtn;
    QPushButton *removeCameraBtn;
    QLabel *label;
    QComboBox *cameraCB;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *loadModelBtn;
    QPushButton *removeModelBtn;
    QPushButton *groupModelBtn;
    QPushButton *ungroupModelBtn;
    QLabel *label_2;
    QComboBox *modelCB;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *xDSB;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *yDSB;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QDoubleSpinBox *zDSB;
    QPushButton *moveModelBtn;
    QPushButton *scaleModelBtn;
    QPushButton *rotateModelBtn;
    QPushButton *moveCameraBtn;
    QPushButton *scaleCameraBtn;
    QPushButton *rotateCameraBtn;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_5;
    QPushButton *undoBtn;
    QPushButton *redoBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1476, 960);
        MainWindow->setMinimumSize(QSize(200, 200));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(graphicsView);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(340, 200));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_1 = new QGroupBox(widget);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_1->sizePolicy().hasHeightForWidth());
        groupBox_1->setSizePolicy(sizePolicy2);
        groupBox_1->setMinimumSize(QSize(0, 190));
        verticalLayout_2 = new QVBoxLayout(groupBox_1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        loadCameraBtn = new QPushButton(groupBox_1);
        loadCameraBtn->setObjectName(QString::fromUtf8("loadCameraBtn"));

        verticalLayout_2->addWidget(loadCameraBtn);

        removeCameraBtn = new QPushButton(groupBox_1);
        removeCameraBtn->setObjectName(QString::fromUtf8("removeCameraBtn"));

        verticalLayout_2->addWidget(removeCameraBtn);

        label = new QLabel(groupBox_1);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        cameraCB = new QComboBox(groupBox_1);
        cameraCB->setObjectName(QString::fromUtf8("cameraCB"));

        verticalLayout_2->addWidget(cameraCB);


        verticalLayout->addWidget(groupBox_1);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        loadModelBtn = new QPushButton(groupBox_2);
        loadModelBtn->setObjectName(QString::fromUtf8("loadModelBtn"));

        verticalLayout_3->addWidget(loadModelBtn);

        removeModelBtn = new QPushButton(groupBox_2);
        removeModelBtn->setObjectName(QString::fromUtf8("removeModelBtn"));

        verticalLayout_3->addWidget(removeModelBtn);

        groupModelBtn = new QPushButton(groupBox_2);
        groupModelBtn->setObjectName(QString::fromUtf8("groupModelBtn"));

        verticalLayout_3->addWidget(groupModelBtn);

        ungroupModelBtn = new QPushButton(groupBox_2);
        ungroupModelBtn->setObjectName(QString::fromUtf8("ungroupModelBtn"));

        verticalLayout_3->addWidget(ungroupModelBtn);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        modelCB = new QComboBox(groupBox_2);
        modelCB->setObjectName(QString::fromUtf8("modelCB"));

        verticalLayout_3->addWidget(modelCB);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        xDSB = new QDoubleSpinBox(groupBox_3);
        xDSB->setObjectName(QString::fromUtf8("xDSB"));

        horizontalLayout_2->addWidget(xDSB);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        yDSB = new QDoubleSpinBox(groupBox_3);
        yDSB->setObjectName(QString::fromUtf8("yDSB"));

        horizontalLayout_5->addWidget(yDSB);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        zDSB = new QDoubleSpinBox(groupBox_3);
        zDSB->setObjectName(QString::fromUtf8("zDSB"));

        horizontalLayout_3->addWidget(zDSB);


        verticalLayout_4->addLayout(horizontalLayout_3);

        moveModelBtn = new QPushButton(groupBox_3);
        moveModelBtn->setObjectName(QString::fromUtf8("moveModelBtn"));

        verticalLayout_4->addWidget(moveModelBtn);

        scaleModelBtn = new QPushButton(groupBox_3);
        scaleModelBtn->setObjectName(QString::fromUtf8("scaleModelBtn"));

        verticalLayout_4->addWidget(scaleModelBtn);

        rotateModelBtn = new QPushButton(groupBox_3);
        rotateModelBtn->setObjectName(QString::fromUtf8("rotateModelBtn"));

        verticalLayout_4->addWidget(rotateModelBtn);

        moveCameraBtn = new QPushButton(groupBox_3);
        moveCameraBtn->setObjectName(QString::fromUtf8("moveCameraBtn"));

        verticalLayout_4->addWidget(moveCameraBtn);

        scaleCameraBtn = new QPushButton(groupBox_3);
        scaleCameraBtn->setObjectName(QString::fromUtf8("scaleCameraBtn"));

        verticalLayout_4->addWidget(scaleCameraBtn);

        rotateCameraBtn = new QPushButton(groupBox_3);
        rotateCameraBtn->setObjectName(QString::fromUtf8("rotateCameraBtn"));

        verticalLayout_4->addWidget(rotateCameraBtn);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy2.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy2);
        groupBox_4->setMinimumSize(QSize(100, 100));
        verticalLayout_5 = new QVBoxLayout(groupBox_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        undoBtn = new QPushButton(groupBox_4);
        undoBtn->setObjectName(QString::fromUtf8("undoBtn"));

        verticalLayout_5->addWidget(undoBtn);

        redoBtn = new QPushButton(groupBox_4);
        redoBtn->setObjectName(QString::fromUtf8("redoBtn"));

        verticalLayout_5->addWidget(redoBtn);


        verticalLayout->addWidget(groupBox_4);


        horizontalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1476, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_1->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\274\320\265\321\200\321\213", nullptr));
        loadCameraBtn->setText(QCoreApplication::translate("MainWindow", "\320\264\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\272\320\260\320\274\320\265\321\200\321\203", nullptr));
        removeCameraBtn->setText(QCoreApplication::translate("MainWindow", "\321\203\320\264\320\260\320\273\320\270\321\202\321\214 \320\272\320\260\320\274\320\265\321\200\321\203", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\262\321\213\320\261\320\276\321\200 \320\260\320\272\321\202\320\270\320\262\320\275\320\276\320\271 \320\272\320\260\320\274\320\265\321\200\321\213:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\264\320\265\320\273\320\270", nullptr));
        loadModelBtn->setText(QCoreApplication::translate("MainWindow", "\320\264\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        removeModelBtn->setText(QCoreApplication::translate("MainWindow", "\321\203\320\264\320\260\320\273\320\270\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        groupModelBtn->setText(QCoreApplication::translate("MainWindow", "\321\201\320\263\321\200\321\203\320\277\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\320\270", nullptr));
        ungroupModelBtn->setText(QCoreApplication::translate("MainWindow", "\321\200\320\260\320\267\320\263\321\200\321\203\320\277\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\262\321\213\320\261\320\276\321\200 \320\260\320\272\321\202\320\270\320\262\320\275\320\276\320\271 \320\274\320\276\320\264\320\265\320\273\320\270:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        moveModelBtn->setText(QCoreApplication::translate("MainWindow", "\320\277\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        scaleModelBtn->setText(QCoreApplication::translate("MainWindow", "\320\276\321\202\320\274\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        rotateModelBtn->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        moveCameraBtn->setText(QCoreApplication::translate("MainWindow", "\320\277\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214 \320\272\320\260\320\274\320\265\321\200\321\203", nullptr));
        scaleCameraBtn->setText(QCoreApplication::translate("MainWindow", "\320\276\321\202\320\274\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\272\320\260\320\274\320\265\321\200\321\203", nullptr));
        rotateCameraBtn->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214 \320\272\320\260\320\274\320\265\321\200\321\203", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\230\321\201\321\202\320\276\321\200\320\270\321\217", nullptr));
        undoBtn->setText(QCoreApplication::translate("MainWindow", "\320\276\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\265 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\320\265", nullptr));
        redoBtn->setText(QCoreApplication::translate("MainWindow", "\320\262\320\265\321\200\320\275\321\203\321\202\321\214 \320\276\321\202\320\274\320\265\320\275\320\265\320\275\320\275\320\276\320\265 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
