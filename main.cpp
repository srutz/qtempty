#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "mydesignerdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.move(100, 100);

    auto layout = new QVBoxLayout(&window);
    auto button = new QPushButton("Show Dialog from Designer", &window);
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [button]{
        MyDesignerDialog dialog(button);
        dialog.exec();
    });
    window.show();
    return app.exec();
}

