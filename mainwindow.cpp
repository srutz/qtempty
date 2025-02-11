#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QTimer>
#include "mymodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto layout = new QVBoxLayout(this->centralWidget());
    auto tableView = new QTableView(this);
    auto mymodel = new MyModel(this);
    mymodel->addPerson({ .email = "frank@gmx.de", .age = 20 });
    mymodel->addPerson({ .email = "hans@gmx.de",  });
    mymodel->addPerson({ .email = "jürgen@gmx.de", .age = 40 });

    tableView->setModel(mymodel);
    //tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    for (auto y = 0; y < model->rowCount(); y++) {
        for (auto x = 0; x < model->columnCount(); x++) {
            model->setData(model->index(y, x), QVariant("abc"));
        }
    }
    connect(model, &QAbstractItemModel::dataChanged, this, [this] (const QModelIndex &topLeft, const QModelIndex &bottomRight) {
        qDebug() << "lambda: " << topLeft << ", " << bottomRight;
    });
    connect(model, &QAbstractItemModel::dataChanged, this, &MainWindow::tableDataChanged);

    layout->addWidget(tableView);
}

void MainWindow::tableDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    qDebug() << " slot:" << topLeft << ", " << bottomRight;

}

MainWindow::~MainWindow()
{
    delete ui;
}
