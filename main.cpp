#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QVBoxLayout>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Layouts"); window.setGeometry(100, 100, 500, 300);
    if (argc != 2) {
        QMessageBox::critical(&window, "Falscher Aufruf", "Aufruf mit Bild als erster Parameter");
        QApplication::exit(1);
    }
    QByteArray data;
    {
        QFile f(argv[1]);
        if (!f.exists() || !f.fileName().toLower().endsWith("png")) {
            QMessageBox::critical(&window, "Falscher Aufruf", "png file muss beim Start angegeben werden.");
            QApplication::exit(1);
        }
        f.open(QFile::ReadOnly);
        data = f.readAll();
    }

    auto mainLayout = new QVBoxLayout(&window);
    mainLayout->setSpacing(0);

    auto headerArea = new QWidget(&window);
    auto headerAreaLayout = new QHBoxLayout(headerArea);
    auto pathLabel = new QLabel(argv[1]);
    pathLabel->setStyleSheet("font-style: bold;");
    pathLabel->setTextInteractionFlags(Qt::TextSelectableByMouse); // selektierbar
    headerAreaLayout->addWidget(pathLabel, 0, Qt::AlignCenter);

    auto imageArea = new QWidget(&window);
    auto imageAreaLayout = new QHBoxLayout(imageArea);
    auto imageLabel = new QLabel();
    QPixmap pixmap;
    pixmap.loadFromData(data);
    if (pixmap.height() > 300) pixmap = pixmap.scaledToHeight(300, Qt::SmoothTransformation);
    imageLabel->setPixmap(pixmap);

    imageArea->setStyleSheet("background-color: #eeeeee;");
    imageAreaLayout->addWidget(imageLabel, 1, Qt::AlignCenter);

    mainLayout->addWidget(headerArea, 0);
    mainLayout->addWidget(imageArea, 1); // stretch

    window.show(); return app.exec();
}

