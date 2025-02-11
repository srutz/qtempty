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
            anim->connect(anim, &QPropertyAnimation::finished, this, [=]() { onFinished(); });
        }
    }

    QColor backgroundColor() const { return m_backgroundColor; };
    void setBackgroundColor(const QColor color)
    {
        if (m_backgroundColor == color) {
            return;
        }
        applyBackgroundColor(m_backgroundColor);
        emit backgroundColorChanged(m_backgroundColor);
    }

    void applyBackgroundColor(QColor color) {
        m_backgroundColor = color;
        auto backdropPalette = palette();
        backdropPalette.setColor(QPalette::Window, color);
        setAutoFillBackground(true);
        setPalette(backdropPalette);
    }

    void setBackgroundColorA(const QColor color, int durationMs = 200, std::function<void()> onFinished = nullptr)
    {
        if (backgroundColorAnimation) {
            backgroundColorAnimation->stop();
            delete backgroundColorAnimation;
        }
        auto anim = new QPropertyAnimation(this, "backgroundColor");
        this->backgroundColorAnimation = anim;
        anim->setEasingCurve(QEasingCurve::InOutCubic);
        anim->setDuration(durationMs);
        anim->setStartValue(m_backgroundColor);
        anim->setEndValue(color);
        anim->start();
        connect(anim, &QPropertyAnimation::valueChanged, this, [this,anim] {
            auto v = anim->currentValue();
            // get the color from the animation
            applyBackgroundColor(v.value<QColor>());
        });
        if (onFinished != nullptr) {
            anim->connect(anim, &QPropertyAnimation::finished, this, [=]() { onFinished(); });
        }
    }

signals:
    void positionChanged(const QPoint point);
    void backgroundColorChanged(const QColor color);

private:
    QPoint m_position = QPoint(0, 0);
    QColor m_backgroundColor = QColor(Qt::white);
    QPropertyAnimation *positionAnimation = nullptr;
    QPropertyAnimation *backgroundColorAnimation = nullptr;
};

#endif // ANIMATEDWIDGET_H
