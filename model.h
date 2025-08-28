#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QHash>
#include <QMap>
#include <QVariant>
#include <QPoint>
#include <QFont>
#include <QColor>

static QFont boldFont("Times New Roman", 14, QFont::Bold);

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
        if (!index.isValid()) {
            return QVariant();
        }
        Coord key(index.row(), index.column());
        if (role == Qt::FontRole) {
            return boldFont;
        } else if (role == Qt::TextAlignmentRole) {
            return QVariant(Qt::AlignRight | Qt::AlignVCenter);
        } else if (role == Qt::ForegroundRole) {
            // show negative numbers in red
            auto val = m_map[key];
            bool ok = false;
            auto v = val.toDouble(&ok);
            if (ok && v < 0) {
                return QColor(255, 0, 0);
            } else if (ok && v > 0) {
                return QColor(0, 128, 0);
            }
            return QVariant();
        } else if (role == Qt::DisplayRole) {
            if (!m_map.contains(key)) {
                return QVariant();
            }
            return m_map[key];
        }
        return QVariant();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override {
        Coord coord(index.row(), index.column());
        auto oldValue = m_map[coord];
        qDebug() << "set value" << index << oldValue << value << value.typeId();
        if (!value.isValid() || (value.typeId() == 10 && value.toString().trimmed().size() == 0)) {
            m_map.remove(coord);
        } else {
            m_map[coord] = value;
        }
        return true;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole)
            return QVariant();
        return QVariant(section + 1);
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        if (!index.isValid()) {
            return Qt::NoItemFlags;
        }
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }


};

#endif // MODEL_H
