#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.move(100, 100);

    auto layout = new QVBoxLayout(&window);

    // Show Message Button
    auto b1 = new QPushButton("Show Message", &window);
    QObject::connect(b1, &QPushButton::clicked, [&](){
        QMessageBox::information(&window, "Message", "This is a simple message.");
    });
    layout->addWidget(b1);

    // Show Confirm Dialog Button
    auto b2 = new QPushButton("Show Confirm Dialog", &window);
    QObject::connect(b2, &QPushButton::clicked, [&](){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(&window, "Confirm", "Are you sure you want to proceed?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QMessageBox::information(&window, "Confirmed", "You chose Yes.");
        } else {
            QMessageBox::information(&window, "Cancelled", "You chose No.");
        }
    });
    layout->addWidget(b2);

    // Show Alert Dialog Button
    auto b3 = new QPushButton("Show Alert Dialog", &window);
    QObject::connect(b3, &QPushButton::clicked, [&](){
        QMessageBox::warning(&window, "Alert", "This is an alert message.");
    });
    layout->addWidget(b3);
    layout->addStretch();
    window.show();
    return app.exec();
}

