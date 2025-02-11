#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <vector>


using std::vector;

struct Person {
    QString email;
    int age = 33;
};

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
    vector<Person> m_persons;
public:
    explicit MyModel(QObject *parent = nullptr);
    void addPerson(Person person) { m_persons.push_back(person); }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 2; }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return m_persons.size(); }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) {
            return QVariant();
        }
        QVariant returnValue;
        if (role == Qt::DisplayRole) {
            auto p = m_persons.at(index.row());
            switch (index.column()) {
            case 0:
                returnValue = QVariant(p.email);
                break;
            case 1:
                returnValue = QVariant(p.age);
                break;
            }
        }
        return returnValue;
    }
signals:
};

#endif // MYMODEL_H
