#include "sheetpanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QTimer>
#include <QResizeEvent>
#include <QPushButton>
#include <QIcon>

SheetPanel::SheetPanel(QWidget *parent): QWidget(parent) {
    m_destination = nullptr;
    m_backdrop = new AnimatedWidget(this);
    m_sidepanel = new AnimatedWidget(this);
    resize(0, 0);

    m_backdrop->setBackgroundColor(QColor::fromRgbF(0, 0, 0, 0.0));
    m_backdrop->hide();

    // Set sidepanel to white background
    auto sidepanelPalette = m_sidepanel->palette();
    sidepanelPalette.setColor(QPalette::Window, Qt::white);
    m_sidepanel->setAutoFillBackground(true);
    m_sidepanel->setPalette(sidepanelPalette);

    // Layout sidepanel on the right side with width 400 on top of backdrop
    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_backdrop);
    layout->addWidget(m_sidepanel);
    layout->setStretch(0, 1); // Make backdrop take the remaining space
    layout->setStretch(1, 0); // Fix sidepanel width
    m_sidepanel->hide();

    setLayout(layout);

    // buttonsbar
    m_buttonBar = new QWidget(this);
    auto buttonBarLayout = new QHBoxLayout(m_buttonBar);
    buttonBarLayout->addStretch();
    auto closeButton = new QPushButton(this);
    connect(closeButton, &QPushButton::clicked, this, [this] {
        this->hideSheet(true);
    });
    closeButton->setFlat(true);
    closeButton->setIcon(QIcon::fromTheme("window-close-symbolic"));
    buttonBarLayout->addWidget(closeButton);
}

SheetPanel::~SheetPanel() {
}

void SheetPanel::showSheet(QWidget *destination, QWidget *content) {
    if (!destination) {
        hideSheet(false);
        return;
    }
    // remove all children from the sidepanel
    while (auto child = m_sidepanel->findChild<QWidget *>()) {
        child->setParent(nullptr);
    }
    auto contentLayout = new QVBoxLayout(m_sidepanel);
    contentLayout->setContentsMargins(QMargins(0, 0, 0, 0));
    m_buttonBar->setParent(m_sidepanel);
    contentLayout->addWidget(m_buttonBar, 0);
    if (content) {
        content->setParent(m_sidepanel);
        contentLayout->addWidget(content, 1);
    } else {
        contentLayout->addStretch();
    }
    // show the panel backdeop all over the destination widget
    // animate the color, also slide in the sidepanel on top
    // of the backdrop
    m_destination = destination;
    m_backdrop->setParent(destination);
    m_backdrop->show();
    m_sidepanel->setParent(destination);
    m_sidepanel->show();
    connect(destination, &QWidget::destroyed, [this] {
        hideSheet(false);
    });
    layout();
    m_sidepanel->setPosition(QPoint(m_backdrop->width(), 0));
    m_backdrop->setBackgroundColor(QColor::fromRgb(0, 0, 0, 0));
    QTimer::singleShot(0, [this]() { layout(); });
}

void SheetPanel::hideSheet(bool animated) {
    m_destination = nullptr;
    if (animated) {
        m_sidepanel->setPositionA(QPoint(m_backdrop->width(), 0), 500, [this] {
            m_backdrop->hide();
            m_sidepanel->hide();
        });
        m_backdrop->setBackgroundColorA(QColor::fromRgb(0, 0, 0, 0), 500);
    } else {
        m_backdrop->hide();
        m_sidepanel->hide();
        m_backdrop->setBackgroundColor(QColor::fromRgb(0, 0, 0, 0));
    }
}

void SheetPanel::layout() {
    if (m_destination) {
        // resize the backdrop to full size of the destination widget
        m_backdrop->resize(m_destination->size());
        m_backdrop->move(0, 0);
        // layout the sidepanel on the right side of the backdrop
        // with a width of 400
        const auto panelWidth = 400;
        m_sidepanel->resize(panelWidth, m_backdrop->size().height());
        m_sidepanel->setPositionA(QPoint(m_backdrop->width() - panelWidth, 0));
        m_backdrop->setBackgroundColorA(QColor::fromRgb(0, 0, 0, 192));
        qDebug() << "layout " << m_backdrop->size() << m_backdrop->pos();
    }
}
