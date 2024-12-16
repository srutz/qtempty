#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWebEngineView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Webview"); window.setGeometry(50, 100, 920, 800);
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
    QWidget::connect(makebutton("Memory"),  &QPushButton::clicked, &window, [=]() {
        webView->setUrl(QUrl("https://srutz.github.io/vuememory/"));
    });
    QWidget::connect(makebutton("Solitaire"),  &QPushButton::clicked, &window, [=]() {
        webView->setUrl(QUrl("https://srutz.github.io/vuesolitaire/"));
    });
    QWidget::connect(makebutton("GFU"),  &QPushButton::clicked, &window, [=]() {
        webView->setUrl(QUrl("https://www.gfu.net/seminare.html"));
    });
    QWidget::connect(makebutton("Say hi from Javascript"),  &QPushButton::clicked, &window, [=]() {
        webView->page()->runJavaScript("alert('Hello from Qt');");
    });
    QWidget::connect(makebutton("Call JS-Function"),  &QPushButton::clicked, &window, [=]() {
        webView->page()->runJavaScript("Math.pow(2, 10)", [=] (auto result) {
            output->setText(QString("The result is %1").arg(result.toDouble()));
        });
    });
    toolbarLayout->addStretch(1);
    layout->addWidget(toolbar); layout->addWidget(webView, 1); layout->addWidget(output);
    webView->setUrl(QUrl("https://srutz.github.io/vuesolitaire/"));
    window.show(); return app.exec();
}

