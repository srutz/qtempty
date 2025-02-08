#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>

class CustomTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    CustomTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return N_ROWS;
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 3;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        int row = index.row();
        int col = index.column();
        int number = row + 1;
        int square = number * number;
        int previousSquare = (number - 1) * (number - 1);

        switch (col) {
        case 0: return QString::number(number);
        case 1: return QString::number(square);
        case 2: return QString::number(square - previousSquare);
        default: return QVariant();
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return QString("Number");
            case 1: return QString("Square");
            case 2: return QString("Delta Previous Square");
            default: return QVariant();
            }
        }
        return QVariant();
    }

private:
    static const int N_ROWS = 1E6;
};

#endif // MODEL_H
