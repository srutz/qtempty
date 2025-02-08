#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(300, 200);
    window.move(100, 100);

    auto layout = new QVBoxLayout(&window);
    const int N_ROWS = 10000;
    auto table = new QTableWidget(N_ROWS, 3, &window);
    table->setHorizontalHeaderLabels({"Number", "Square", "Delta Previous Square"});
    for (auto i = 0; i < N_ROWS; ++i) {
        auto number = i + 1;
        auto square = number * number;
        auto previousSquare = (number - 1) * (number - 1);
        auto item1 = new QTableWidgetItem(QString::number(number));
        item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        auto item2 = new QTableWidgetItem(QString::number(square));
        item2->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        auto item3 = new QTableWidgetItem(QString::number(square - previousSquare));
        item3->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        table->setItem(i, 0, item1);
        table->setItem(i, 1, item2);
        table->setItem(i, 2, item3);
    }
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    
    layout->addWidget(table, 1);
    window.show();
    return app.exec();
}

