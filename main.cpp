#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QStringBuilder>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <cstdlib>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Sql Beispiel");
    window.setGeometry(100, 100, 600, 500);
    auto layout = new QVBoxLayout(&window);
    auto output = new QPlainTextEdit();
    output->setReadOnly(true);
    layout->addWidget(output);

    auto db = QSqlDatabase::addDatabase("QPSQL"); // QPSQL für PostgreSQL
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("template1");
    db.setUserName("sr");
    db.setPassword("test");
    if (!db.open()) {
        qDebug() << "Failed to connect to the database:" << db.lastError().text();
        return EXIT_FAILURE;
    }

    QString s;
    QSqlQuery query;
    QString sql = R"(SELECT table_schema, table_name FROM information_schema.tables order by 1, 2)";
    if (!query.exec(sql)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return EXIT_FAILURE;
    }
    while (query.next()) {
        auto tableSchema = query.value("table_schema").toString();
        auto tableName = query.value("table_name").toString();
        s += tableSchema + "." + tableName + "\r\n";
    }
    db.close();
    output->setPlainText(s);

    window.show();
    return app.exec();
}

