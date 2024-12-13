#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Layouts Beispiel");

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *label1 = new QLabel("Label 1");
    QLabel *label2 = new QLabel("Label 2");
    QLabel *label3 = new QLabel("Label 3");

    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);

    window.show();

    return app.exec();
}

