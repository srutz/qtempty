#ifndef MYDESIGNERDIALOG_H
#define MYDESIGNERDIALOG_H

#include <QDialog>

namespace Ui {
class MyDesignerDialog;
}

class MyDesignerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDesignerDialog(QWidget *parent = nullptr);
    ~MyDesignerDialog();

private:
    Ui::MyDesignerDialog *ui;
};

#endif // MYDESIGNERDIALOG_H
