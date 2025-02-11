#ifndef ANIMATEDWIDGET_H
#define ANIMATEDWIDGET_H

#include <QPropertyAnimation>
#include <QWidget>
#include <functional>

class AnimatedWidget : public QWidget
{
    Q_OBJECT
public:
    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)

    explicit AnimatedWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
    }

    QPoint position() const { return m_position; };
    void setPosition(const QPoint position)
    {
        // qDebug() << "setPosition. oldValue=" << m_position << " to " << position << (m_position == position);
        if (m_position == position) {
            return;
        }
        m_position = position;
        this->move(m_position);
        emit positionChanged(m_position);
    }
    // animated
    void setPositionA(const QPoint position, int durationMs = 350, std::function<void()> onFinished = nullptr)
    {
        if (positionAnimation) {
            positionAnimation->stop();
            delete positionAnimation;
        }
        auto anim = new QPropertyAnimation(this, "position");
        this->positionAnimation = anim;
        anim->setEasingCurve(QEasingCurve::InOutCubic);
        anim->setDuration(durationMs);
        anim->setStartValue(m_position);
        anim->setEndValue(position);
        anim->start();
        if (onFinished != nullptr) {
            anim->connect(anim, &QPropertyAnimation::finished, this, [=]()
                          { onFinished(); });
        }
    }

signals:
    void positionChanged(const QPoint point);

private:
    QPoint m_position = QPoint(0, 0);
    QPropertyAnimation *positionAnimation = nullptr;
};

#endif // ANIMATEDWIDGET_H
