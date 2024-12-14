#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Layouts Beispiel");
    window.move(100, 100);

    auto layout = new QVBoxLayout(&window);
    auto label1 = new QLabel("Label 1");
    layout->addWidget(label1);
    window.show();
    return app.exec();
}

