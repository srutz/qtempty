#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QDir>
#include <QStandardPaths>
#include <QPdfView>
#include <QPdfDocument>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QObject::connect(&app, &QApplication::lastWindowClosed, [] { QApplication::quit(); });
    QWidget window;
    window.setWindowTitle("PdfViewer Beispiel");
    window.setGeometry(100, 100, 900, 600);
    auto layout = new QVBoxLayout(&window);
    QString filePath;
    if (argc == 2) {
        filePath = QString(argv[1]);
    } else {
        QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        QDir documentsDir(documentsPath);
        filePath = documentsDir.filePath("cv.pdf");
    }
    auto viewer = new QPdfView(&window);
    auto *document = new QPdfDocument(&window);
    document->load(filePath);
    viewer->setDocument(document);
    layout->setContentsMargins(QMargins(0, 0, 0, 0));
    layout->addWidget(viewer);
    window.show();
    return app.exec();
}

