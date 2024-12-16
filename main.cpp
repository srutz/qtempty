#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWebEngineView>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QObject::connect(&app, &QApplication::lastWindowClosed, [] { QApplication::quit(); });

    QWidget window;
    window.setWindowTitle("Webview"); window.setGeometry(50, 100, 950, 800);

    auto layout = new QVBoxLayout(&window);
    auto webView = new QWebEngineView(&window);
    auto output = new QLabel(&window);
    auto toolbar = new QWidget(&window);
    auto toolbarLayout = new QHBoxLayout(toolbar);
    auto makebutton = [=] (const QString &t) {
        auto b = new QPushButton(t, toolbar);
        b->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        toolbarLayout->addWidget(b);
        return b;
    };
    auto makeurlbutton = [=] (const QString &t, const QString &url) {
        auto button = makebutton(t);
        QObject::connect(button,  &QPushButton::clicked, button, [=]() { webView->setUrl(QUrl(url)); });
    };
    makeurlbutton("Memory", "https://srutz.github.io/vuememory/");
    makeurlbutton("Solitaire", "https://srutz.github.io/vuesolitaire/");
    makeurlbutton("GFU", "https://www.gfu.net/seminare.html");
    QObject::connect(makebutton("Say hi from Javascript"),  &QPushButton::clicked, &window, [=]() {
        webView->page()->runJavaScript("alert('Hello from Qt');");
    });
    QObject::connect(makebutton("Call JS-Function"),  &QPushButton::clicked, &window, [=]() {
        webView->page()->runJavaScript("Math.pow(2, 10)", [=] (auto result) {
            output->setText(QString("The result is %1").arg(result.toDouble()));
            QTimer::singleShot(5000, [=]() {output->setText(""); });
        });
    });
    toolbarLayout->addStretch(1);
    layout->addWidget(toolbar); layout->addWidget(webView, 1); layout->addWidget(output);
    QTimer::singleShot(1, [=]() { webView->setUrl(QUrl("https://srutz.github.io/vuesolitaire/")); });
    window.show(); return app.exec();
}

