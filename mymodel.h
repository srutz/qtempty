#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <vector>


using std::vector;

struct Person {
    QString email;
    int age = 33;
    QString city = "Saarbrücken";
    friend QDebug operator<<(QDebug dbg, const Person &person) {
        dbg.nospace() << "Person(email: " << person.email << ", age: " << person.age << ")";
        return dbg.space();
    }
    friend QTextStream& operator<<(QTextStream &out, const Person &person) {
        out << "Person(email: " << person.email << ", age: " << person.age << ", city: " << person.city << ")";
        return out;
    }
};

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
    vector<Person> m_persons;
public:
    explicit MyModel(QObject *parent = nullptr);
    void addPerson(Person person) { m_persons.push_back(person); }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 3; }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return m_persons.size(); }
    const Person& getPerson(int index) const { return m_persons.at(index); }

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
            case 2:
                returnValue = p.city;
                break;
            }
        }
        return returnValue;
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        auto& person = m_persons.at(index.row());
        Qt::ItemFlags flags = Qt::ItemIsSelectable;
        if (person.age > 30) {
            flags |= Qt::ItemIsEnabled | Qt::ItemIsEditable;
        }
        return flags;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override {
        if (role != Qt::EditRole) {
            return false;
        }
        auto result = false;
        auto& person = m_persons.at(index.row());
        auto oldValue = person;
        switch(index.column()) {
        case 0:
            person.email = value.toString();
            result = true;
            break;
        case 1:
            {
                auto success = false;
                auto i = value.toInt(&success);
                if (success) {
                    person.age = i;
                    result = true;
                }
            }
            break;
        case 2:
            person.city= value.toString();
            result = true;
            break;
        }
        //qDebug() << "person dump";
        //for (const auto &person : m_persons) { qDebug() << person.email << ", " << person.age; }
        if (result) {
            QList<int> roles;
            roles << Qt::EditRole;
            emit dataChanged(index, index, roles);
            emit editValue(index, oldValue, person);
        }
        return result;
    }


signals:
    void editValue(QModelIndex index, Person oldValue, Person newValue);
};

#endif // MYMODEL_H
