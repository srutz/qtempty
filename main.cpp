#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); QWidget window;
    window.setWindowTitle("Slots"); window.setGeometry(100, 100, 500, 300);

    auto mainLayout = new QVBoxLayout(&window);
    auto button = new QPushButton("Button");
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(button,0, Qt::AlignHCenter);
    QObject::connect(button, &QPushButton::clicked, [&]() {
        qDebug() << "Button wurde geklickt";
    });
    window.show(); return app.exec();
}
