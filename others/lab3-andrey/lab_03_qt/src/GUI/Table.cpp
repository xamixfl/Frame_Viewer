//
// Created by nuelex on 22/05/25.
//

#include "Table.hpp"

#include "../Exceptions/GUI/TableException.hpp"

void Table::pushItem(const QString &object_name)
{
    if (_table == nullptr)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTable_no_table(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    try
    {
        int newRow = _table->rowCount();
        _table->insertRow(newRow);

        QTableWidgetItem* nameItem = new QTableWidgetItem(object_name);

        _table->setItem(newRow, 0, nameItem);
    }
    catch (std::bad_alloc &e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTable_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

void Table::removeItem(const size_t id)
{
    if (_table == nullptr)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTable_no_table(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    if (id >= _table->rowCount())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTable_invalid_data(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    _table->removeRow(id);
}

void Table::setTable(QTableWidget *table)
{
    if (table == nullptr || table->columnCount() != 1)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTable_invalid_table(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    _table = table;
}

QSet<int> Table::selectedItems() const
{
    QList<QTableWidgetItem*> items = _table->selectedItems();
    QSet<int> rows;

    for (const QTableWidgetItem* item : items)
    {
        rows.insert(item->row());
    }

    return rows;
}



