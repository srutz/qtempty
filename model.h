#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QHash>
#include <QMap>
#include <QVariant>
#include <QPoint>

/* Class for kex in values-hashmap
 * can be used in QMap and QHash
 */
struct Coord {
    int m_row, m_col;
    Coord(int row, int col): m_row(row), m_col(col) { }

    bool operator<(const Coord& other) const {
        if (m_row != other.m_row) {
            return m_row < other.m_row;
        }
        return m_col < other.m_col;
    }

    bool operator==(const Coord& other) const {
        return m_row == other.m_row && m_col == other.m_col;
    }
};

inline uint qHash(const Coord& coord, uint seed = 0) {
    int values[] = {coord.m_row, coord.m_col};
    return qHashRange(values, values + 2, seed);
}


class CustomTableModel : public QAbstractTableModel {
    Q_OBJECT
    QHash<Coord,QVariant> m_map;

public:
    CustomTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {
        m_map[Coord(2, 2)] = QString("Frank");
        m_map[Coord(5, 1)] = 30;
        m_map[Coord(998, 998)] = false;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return 1000;
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 1000;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }
        Coord key(index.row(), index.column());
        if (!m_map.contains(key)) {
            return QVariant();
        }
        return m_map[key];
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole)
            return QVariant();
        return QVariant(section + 1);
    }
};

#endif // MODEL_H
