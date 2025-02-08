#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(400, 150); window.move(100, 100);
    auto layout = new QVBoxLayout(&window);

    // Text input
    auto textInput = new QLineEdit(&window);
    textInput->setPlaceholderText("Enter text here");
    layout->addWidget(textInput);
    QObject::connect(textInput, &QLineEdit::textChanged, &window, [textInput] {
        qDebug() << "textchanged=" << textInput->text();
    });
    // Masked input for IBAN
    auto maskedInput = new QLineEdit(&window);
    maskedInput->setInputMask("AA99 9999 9999 9999 9999 9999 999");
    maskedInput->setPlaceholderText("Enter IBAN");
    layout->addWidget(maskedInput);
    // Date input
    auto dateInput = new QDateEdit(&window);
    dateInput->setDisplayFormat("yyyy-MM-dd");
    layout->addWidget(dateInput);
    layout->addStretch(1);

    window.show();
    return app.exec();
}

