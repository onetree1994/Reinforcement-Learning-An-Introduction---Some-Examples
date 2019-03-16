#ifndef CURVE_H
#define CURVE_H

#include <QWidget>
#include <QVector>
#include <QMouseEvent>
#include <QPainter>

class Curve : public QWidget
{
    Q_OBJECT
public:
    explicit Curve(QWidget *parent = 0);
    QVector<float> curveVec;

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // CURVE_H
