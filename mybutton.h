#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton {
    Q_OBJECT

public:
    MyButton(const QString &text, QWidget *parent = nullptr) : QPushButton(text, parent) {
        QObject::connect(this, &QPushButton::clicked, this, &MyButton::onClicked);
    }

public slots:
    void onClicked() {
        qDebug() << "Button wurde geklickt";
    }
};

#endif // MYBUTTON_H
