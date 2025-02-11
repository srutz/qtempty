#ifndef SHEETPANEL_H
#define SHEETPANEL_H

#include <QWidget>
#include "animatedwidget.h"

class SheetPanel : public QWidget
{
    Q_OBJECT

    QWidget *m_destination;
    QWidget *m_backdrop;
    AnimatedWidget *m_sidepanel;
    QWidget *m_buttonBar;

public:
    SheetPanel(QWidget *parent = nullptr);
    ~SheetPanel();

    void showSheet(QWidget *destination, QWidget *content);
    void hideSheet(bool animated);
    void layout();

};

#endif // SHEETPANEL_H
