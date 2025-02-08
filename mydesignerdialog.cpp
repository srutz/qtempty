#include "mydesignerdialog.h"
#include "ui_mydesignerdialog.h"

MyDesignerDialog::MyDesignerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyDesignerDialog)
{
    ui->setupUi(this);
}

MyDesignerDialog::~MyDesignerDialog()
{
    delete ui;
}
