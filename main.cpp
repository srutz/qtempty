#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QAbstractTableModel>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <utility>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(300, 200);
    window.move(100, 100);

    auto db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("template1");
    db.setUserName("sr");
    db.setPassword("test99");
    if (!db.open()) {
        qDebug() << "connect error" << db.lastError(); QApplication::exit(1);
    }
    QSqlQuery q;
    q.prepare("select 100 * 10 as tausend, table_schema, table_name, table_type from information_schema.tables order by 1");
    if (!q.exec()) {
        qDebug() << "query error" << q.lastError(); QApplication::exit(1);
    }
    auto layout = new QVBoxLayout(&window);
    auto model = new QSqlQueryModel(&window);
    model->setQuery(std::move(q));

    auto tableView = new QTableView(&window);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    layout->addWidget(tableView, 1);
    window.show();
    return app.exec();
}
