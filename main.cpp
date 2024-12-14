#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); QWidget window;
    window.setWindowTitle("Layouts"); window.setGeometry(100, 100, 500, 300);

    QVBoxLayout *layout = new QVBoxLayout(&window);
    QLabel *label1 = new QLabel("Label 1");
    label1->setStyleSheet("color: white; padding: 4px; background-color: red;");
    QLabel *label2 = new QLabel("Label 2");
    label2->setStyleSheet("color: white; padding: 4px; background-color: green;");
    QLabel *label3 = new QLabel("Label 3");
    label3->setStyleSheet("color: white; padding: 4px; background-color: blue;");
    layout->setSpacing(0);
    layout->addStretch();
    layout->addWidget(label1, 0, Qt::AlignLeft);
    layout->addWidget(label2, 0, Qt::AlignHCenter);
    layout->addWidget(label3, 0, Qt::AlignRight);
    layout->addStretch();

    window.show(); return app.exec();
}

