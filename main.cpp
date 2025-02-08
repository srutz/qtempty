#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QAbstractTableModel>
#include <QString>

#include "model.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(300, 200);
    window.move(100, 100);

    auto layout = new QVBoxLayout(&window);
    auto model = new CustomTableModel(&window);

    auto tableView = new QTableView(&window);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    layout->addWidget(tableView, 1);
    window.show();
    return app.exec();
}
