#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QDebug>
#include <QComboBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.move(100, 100);

    auto layout = new QVBoxLayout(&window);
    auto button1 = new QPushButton("Button 1", &window);
    layout->addWidget(button1);

    auto button2 = new QPushButton("Flat Button", &window);
    button2->setFlat(true);
    layout->addWidget(button2);

    auto button3 = new QPushButton("Disabled Button", &window);
    button3->setDisabled(true);
    layout->addWidget(button3);

    auto checkbox = new QCheckBox("Check me", &window);
    QObject::connect(checkbox, &QCheckBox::checkStateChanged, &window, [checkbox] {
        qDebug() << "checkbox changed: " << checkbox->checkState();
    });
    layout->addWidget(checkbox);

    auto combobox = new QComboBox(&window);
    combobox->setEditable(false);
    combobox->addItem("Option1", 1);
    combobox->addItem("Option2", 2);
    combobox->addItem("Option3", QVariant::fromValue(3));
    QObject::connect(combobox, &QComboBox::currentIndexChanged, &window, [combobox] {
        qDebug() << "combobox changed: " << combobox->currentIndex() << combobox->currentData();
    });
    layout->addWidget(combobox);

    window.show();
    return app.exec();
}

