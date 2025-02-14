#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QAction>
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto layout = new QVBoxLayout(this->centralWidget());
    auto text = new QTextEdit("Hello World", this);
    layout->addWidget(text);

    text->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(text, &QWidget::customContextMenuRequested, this, [this,text] (const QPoint &pos) {
        this->showContextMenu(text, pos);
    });

}

void MainWindow::showContextMenu(QWidget *parent, const QPoint &pos) {
    QMenu menu(parent);
    {
        auto action1 = new QAction("&Action 1", &menu);
        action1->setIcon(QIcon::fromTheme("audio-card"));
        menu.addAction(action1);
        QObject::connect(action1, &QAction::triggered, this, [] {
            qDebug() << "action1 triggered";
        });
    }
    {
        auto action2 = new QAction("A&ction 2", &menu);
        action2->setIcon(QIcon::fromTheme("edit-clear"));
        menu.addAction(action2);
        QObject::connect(action2, &QAction::triggered, this, [this] {
            qDebug() << "action2 triggered";
        });
    }
    menu.exec(parent->mapToGlobal(pos));
}



MainWindow::~MainWindow()
{
    delete ui;
}
