#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QList>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); QWidget window;
    window.setWindowTitle("Layouts"); window.setGeometry(100, 100, 500, 300);

    auto mainLayout = new QVBoxLayout(&window);

    auto topRow = new QWidget(&window);
    auto topRowLayout = new QHBoxLayout(topRow);
    auto button1 = new QPushButton("Button 1");
    auto button2 = new QPushButton("Button 1");
    auto button3 = new QPushButton("Button 1");
    topRowLayout->addWidget(button1);
    topRowLayout->addWidget(button2);
    topRowLayout->addWidget(button3);

    auto splitter = new QSplitter(&window);
    auto label1 = new QLabel("Label 1");
    label1->setStyleSheet("color: white; padding: 4px; background-color: red;");
    label1->setAlignment(Qt::AlignCenter);
    auto label2 = new QLabel("Label 2");
    label2->setStyleSheet("color: white; padding: 4px; background-color: green;");
    label2->setAlignment(Qt::AlignCenter);
    splitter->addWidget(label1);
    splitter->addWidget(label2);
    splitter->setSizes(QList<int>{ 100, 200 }); // initiale Verteilung beim Splitter

    mainLayout->setSpacing(0);
    mainLayout->addWidget(topRow);
    mainLayout->addWidget(splitter, 1);
    mainLayout->setContentsMargins(QMargins(0, 0, 0, 0)); // keine Innenabstände

    window.show(); return app.exec();
}

