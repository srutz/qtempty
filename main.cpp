#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Layouts");
    window.setGeometry(100, 100, 500, 300);

    auto layout = new QVBoxLayout(&window);
    auto label1 = new QLabel("Label 1");
    label1->setStyleSheet("color: white; padding: 4px; background-color: red;");
    auto label2 = new QLabel("Label 2");
    label2->setStyleSheet("color: white; padding: 4px; background-color: green;");
    auto label3 = new QLabel("Label 3");
    label3->setStyleSheet("color: white; padding: 4px; background-color: blue;");
    auto label4 = new QLabel("Label 4");
    label4->setStyleSheet("color: white; padding: 4px; background-color: orange;");

    layout->setSpacing(0);
    layout->addStretch();
    layout->addWidget(label1, 0, Qt::AlignLeft);
    layout->addWidget(label2, 0, Qt::AlignHCenter);
    layout->addWidget(label3, 0, Qt::AlignRight);
    layout->addWidget(label4, 0);
    layout->addStretch();

    window.show();
    return app.exec();
}
