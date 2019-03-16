#ifndef GRIDAREA_H
#define GRIDAREA_H

#include <QWidget>
#include <QPainter>
#include <iostream>
#include <QMouseEvent>

class GridArea : public QWidget
{
    Q_OBJECT
public:
    explicit GridArea(QWidget *parent = 0);

    void setGrids(unsigned int gridNumW, unsigned int gridNumH);
//    int currentGridType; // 0空白, 1电脑， 2RL或人类
    bool isFirst; // rl或者人类是否先手
    float alpha;
    float epsilon;
    int train(bool show); // 训练一轮
    void clear();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    unsigned int gridNumR, gridNumC;
    int grid[3][3]; // 描述场地
    float v[3][3][3][3][3][3][3][3][3]; // 描述值函数
    double gridW;
    double gridH;
    void aiAutoMove(); // 这里写ai的策略
    void rlAutoMoveAndImprove(); // 根据rl算法走一步到s'并更新v(s)
    int isTerminal(); // 是否终止，如果输了，返回0，如果赢了，返回1，如果单纯结束，返回2，如果正常，返回3
    float vToShow;

signals:

public slots:
};

#endif // GRIDAREA_H
