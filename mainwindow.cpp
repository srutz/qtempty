#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QTimer>
#include <QSplitter>
#include <QTextEdit>
#include "mymodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto layout = new QVBoxLayout(this->centralWidget());
    auto splitter = new QSplitter(Qt::Horizontal, this);
    layout->addWidget(splitter);
    auto tableView = new QTableView(this);
    auto mymodel = new MyModel(this);
    mymodel->addPerson({ .email = "frank@gmx.de", .age = 20 });
    mymodel->addPerson({ .email = "hans@gmx.de",  });
    mymodel->addPerson({ .email = "jürgen@gmx.de", .age = 40 });
    mymodel->addPerson({ .email = "erna@gmx.de", .age = 70, .city = "Gelsenkirchen" });
    mymodel->addPerson({ .email = "michael@gmx.de", .age = 15 });

    tableView->setModel(mymodel);

    connect(mymodel, &QAbstractItemModel::dataChanged, this, &MainWindow::tableDataChanged);
    splitter->addWidget(tableView);

    // ein zweites views, welches die älteste Person anzeigt
    auto text = new QTextEdit(this);
    auto initText = [text,mymodel] (const QModelIndex &topLeft, const QModelIndex &bottomRight) {
        auto oldestIndex = -1;
        for (auto i = 0, n = mymodel->rowCount(); i < n; i++) {
            auto p = mymodel->getPerson(i);
            if (oldestIndex == -1) {
                oldestIndex = i;
            } else {
                auto previousOldest = mymodel->getPerson(oldestIndex);
                if (p.age > previousOldest.age) {
                    oldestIndex = i;
                }
            }
        }
        text->setText(oldestIndex == -1 ? "-" : QString("Alterspräsident: ") + mymodel->getPerson(oldestIndex).email);
    };
    initText(mymodel->index(0, 0), mymodel->index(0, 0));
    connect(mymodel, &QAbstractItemModel::dataChanged, this, initText);
    splitter->addWidget(text);

}

void MainWindow::tableDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    qDebug() << "  slot:" << topLeft << ", " << bottomRight ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
