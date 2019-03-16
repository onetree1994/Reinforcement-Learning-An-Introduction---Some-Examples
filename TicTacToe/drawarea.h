#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>

namespace Ui {
class DrawArea;
}

class DrawArea : public QWidget
{
    Q_OBJECT

public:
    explicit DrawArea(QWidget *parent = 0);
    ~DrawArea();

private:
    Ui::DrawArea *ui;
};

#endif // DRAWAREA_H
