#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sheetpanel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void tableDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    SheetPanel *m_sheetPanel;
    QWidget *m_sheetContent = nullptr;
private slots:
    void showContextMenu(QWidget *parent, const QPoint &pos);
};
#endif // MAINWINDOW_H
