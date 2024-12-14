#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "mybutton.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); QWidget window;
    window.setWindowTitle("Slots"); window.setGeometry(100, 100, 500, 300);

    auto mainLayout = new QVBoxLayout(&window);
    auto button = new MyButton("Button");
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(button,0, Qt::AlignHCenter);
    window.show(); return app.exec();
}
