//
// Table — добавлен метод clear() для сброса таблицы (используется в Undo/Redo)
//

#ifndef TABLE_HPP
#define TABLE_HPP
#include <QGraphicsScene>
#include <QTableWidget>

class Table
{
public:
    Table() = default;
    explicit Table(QTableWidget* table) { this->setTable(table); }
    ~Table() = default;

    void setTable(QTableWidget* table);

    void pushItem(const QString& object_name);
    void removeItem(size_t id);

    void clear()
    {
        if (_table)
            _table->setRowCount(0);
    }

    [[nodiscard]] int selectedItem() const { return _table->currentRow(); }
    [[nodiscard]] QSet<int> selectedItems() const;

private:
    QTableWidget* _table{nullptr};
};

#endif //TABLE_HPP
