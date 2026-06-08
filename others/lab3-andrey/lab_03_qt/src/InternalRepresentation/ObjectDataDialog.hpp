#ifndef OBJECTDATADIALOG_HPP
#define OBJECTDATADIALOG_HPP

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>

#include "FigureCommandGetInternalData.hpp"

class ObjectDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ObjectDataDialog(const FigureInternalData& data,
                              const QString& objectName,
                              QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Internal Representation: " + objectName);
        setMinimumSize(600, 500);

        auto* mainLayout = new QVBoxLayout(this);

        mainLayout->addWidget(new QLabel(
            QString("Points: %1").arg(data.points.size())));

        auto* pointsTable = new QTableWidget(
            static_cast<int>(data.points.size()), 4, this);
        pointsTable->setHorizontalHeaderLabels({"#", "X", "Y", "Z"});
        pointsTable->horizontalHeader()->setStretchLastSection(true);
        pointsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for (int i = 0; i < static_cast<int>(data.points.size()); ++i)
        {
            pointsTable->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
            pointsTable->setItem(i, 1, new QTableWidgetItem(
                QString::number(data.points[i].GetX(), 'f', 4)));
            pointsTable->setItem(i, 2, new QTableWidgetItem(
                QString::number(data.points[i].GetY(), 'f', 4)));
            pointsTable->setItem(i, 3, new QTableWidgetItem(
                QString::number(data.points[i].GetZ(), 'f', 4)));
        }
        mainLayout->addWidget(pointsTable);

        mainLayout->addWidget(new QLabel(
            QString("Links: %1").arg(data.links.size())));

        auto* linksTable = new QTableWidget(
            static_cast<int>(data.links.size()), 3, this);
        linksTable->setHorizontalHeaderLabels({"#", "Begin", "End"});
        linksTable->horizontalHeader()->setStretchLastSection(true);
        linksTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for (int i = 0; i < static_cast<int>(data.links.size()); ++i)
        {
            linksTable->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
            linksTable->setItem(i, 1, new QTableWidgetItem(
                QString::number(data.links[i].first)));
            linksTable->setItem(i, 2, new QTableWidgetItem(
                QString::number(data.links[i].second)));
        }
        mainLayout->addWidget(linksTable);
    }
};

#endif //OBJECTDATADIALOG_HPP
