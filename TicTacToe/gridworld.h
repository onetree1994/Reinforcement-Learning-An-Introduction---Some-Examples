#ifndef GRIDWORLD_H
#define GRIDWORLD_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class GridWorld;
}

class GridWorld : public QDialog
{
    Q_OBJECT

public:
    explicit GridWorld(QWidget *parent = 0);
    ~GridWorld();

private:
    Ui::GridWorld *ui;
    QButtonGroup gridTypeBG;

private slots:
//    void gridTypeBGToggled(int, bool);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // GRIDWORLD_H
