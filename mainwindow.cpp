#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto layout = new QVBoxLayout(this->centralWidget());
    const int N_ROWS = 10000;
    auto model = new QStandardItemModel(N_ROWS, 3, this);
    model->setHorizontalHeaderLabels({"Number", "Square", "Delta Previous Square"});
    for (auto i = 0; i < N_ROWS; ++i) {
        auto number = i + 1;
        auto square = number * number;
        auto previousSquare = (number - 1) * (number - 1);
        auto item1 = new QStandardItem(QString::number(number));
        item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        auto item2 = new QStandardItem(QString::number(square));
        item2->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        auto item3 = new QStandardItem(QString::number(square - previousSquare));
        item3->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        model->setItem(i, 0, item1);
        model->setItem(i, 1, item2);
        model->setItem(i, 2, item3);
    }

    auto tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    layout->addWidget(tableView, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
