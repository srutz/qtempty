#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QGridLayout>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto window = make_unique<QWidget>();  // QWidget* als smart-pointer
    window->setWindowTitle("Layouts Beispiel");
    window->move(100, 100);

    const auto PER_ROW = 8;
    auto layout = new QGridLayout(window.get());
    for (int c = '0', i = 0; c <= 'Z'; c++, i++) {
        auto text = QString("%1").arg(QChar((c)));
        auto label = new QLabel(text, window.get());
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("color: #000000; min-width: 64px; background-color: #f1f1f1; font-size: 64px;");
        label->setContentsMargins(QMargins(16, 16, 16, 16));
        auto row = i / PER_ROW;
        auto column = i % PER_ROW;
        layout->addWidget(label, row, column);
    }
    window->show();
    return app.exec();
}

