#include "gridarea.h"
#include <iostream>
using namespace std;

GridArea::GridArea(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(550, 550);

    alpha = 0.1;
    epsilon = 0.3;
    isFirst = true;
    vToShow = 0;

    setGrids(3, 3);
    for (int i1=0; i1 < 3; i1++)
        for (int i2=0; i2 < 3; i2++)
            for (int i3=0; i3 < 3; i3++)
                for (int i4=0; i4 < 3; i4++)
                    for (int i5=0; i5 < 3; i5++)
                        for (int i6=0; i6 < 3; i6++)
                            for (int i7=0; i7 < 3; i7++)
                                for (int i8=0; i8 < 3; i8++)
                                    for (int i9=0; i9 < 3; i9++)
                                        v[i1][i2][i3][i4][i5][i6][i7][i8][i9]=0;
    setMouseTracking(true);
}

void GridArea::setGrids(unsigned int gridNumR, unsigned int gridNumC)
{
    this->gridNumR = gridNumR;
    this->gridNumC = gridNumC;

    gridW = this->width() / (double)gridNumC - 5;
    gridH = this->height() / (double)gridNumR - 5;

    for (unsigned int row = 0; row < gridNumR; row++){
        for (unsigned int col = 0; col < gridNumC; col++){
            grid[row][col] = 0;
        }
    }
    repaint();
}

void GridArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (unsigned int row = 0; row < gridNumR; row++){
        for (unsigned int col = 0; col < gridNumC; col++){
            switch(grid[row][col]){
            case 0:{;break;}
            case 1:{painter.drawLine(gridW*col, gridH*row, gridW*col+gridW, gridH*row+gridH);painter.drawLine(gridW*col+gridW, gridH*row, gridW*col, gridH*row+gridH);break;}
            case 2:{painter.drawEllipse(gridW*col, gridH*row, gridW, gridH);break;}
            }
            painter.drawRect(gridW*col, gridH*row, gridW, gridH);
        }
    }
    painter.drawText(this->width() / 2, this->height(), QString("%1").arg(vToShow));

}

void GridArea::mousePressEvent(QMouseEvent *e)
{
    unsigned int rowGrdIdx = e->y() / gridH;
    unsigned int colGrdIdx = e->x() / gridW;

    if (rowGrdIdx < gridNumR && colGrdIdx < gridNumC){
        int gridType = grid[rowGrdIdx][colGrdIdx];
        if (gridType == 0){
            float newCurV = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
            grid[rowGrdIdx][colGrdIdx] = 1;
            if(isTerminal() == 1){
                v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = 1.0;
            }
            newCurV += alpha*(v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] - newCurV);
            grid[rowGrdIdx][colGrdIdx] = 0;
            v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = newCurV;
            grid[rowGrdIdx][colGrdIdx] = 1;
            cout << v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] << " ";
            cout << newCurV << endl;
        }
    }

    if (isTerminal() == 3){
        aiAutoMove();
//        rlAutoMoveAndImprove();
    }

    repaint();
}

void GridArea::mouseMoveEvent(QMouseEvent *e)
{
    unsigned int rowGrdIdx = e->y() / gridH;
    unsigned int colGrdIdx = e->x() / gridW;

    if (grid[rowGrdIdx][colGrdIdx] == 0){
        grid[rowGrdIdx][colGrdIdx] = 1;
        vToShow = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
        grid[rowGrdIdx][colGrdIdx] = 0;
        repaint();

    }else{
        if (vToShow != v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]]){
            vToShow = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
            repaint();
        }
    }
}

void GridArea::aiAutoMove()
{
    // ai的策略分为三种，以一定概率顺序动作，以一定概率令对方胜率最小动作，以一定概率完全随机
    float rnd = rand()/(double)RAND_MAX;
    if (rnd < 0.2)
    {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
            {
                if (grid[row][col] == 0){
                    float newCurV = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
                    grid[row][col] = 2;
                    if(isTerminal() == 0){
                        v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = -1.0;
                    }
                    newCurV += alpha*(v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] - newCurV);
                    grid[row][col] = 0;
                    v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = newCurV;
                    grid[row][col] = 2;
                    return;
                }
            }
    }else if(rnd < -1.1){
        float minNextV = 2;
        int nextPos = -1;
        for(int pos = 0; pos < 9; pos++){
            if (grid[pos / 3][pos % 3] == 0){
                grid[pos / 3][pos % 3] = 2;
                float curNextV = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
                if (curNextV < minNextV){
                    minNextV = curNextV;
                    nextPos = pos;
                }
                grid[pos / 3][pos % 3] = 0;
            }
        }
        if (nextPos > -1){ // 更新v(s)
            float newCurV = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
            grid[nextPos / 3][nextPos % 3] = 2;
            if(isTerminal() == 0){
                v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = -1.0;
            }
            newCurV += alpha*(v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] - newCurV);
            grid[nextPos / 3][nextPos % 3] = 0;
            v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = newCurV;
            grid[nextPos / 3][nextPos % 3] = 2;
        }
    }
    else{
        while(true){
            int pos = rand() % 9;
            int row = pos/3;
            int col = pos%3;
            if (grid[row][col] == 0){
                float newCurV = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
                grid[row][col] = 2;
                if(isTerminal() == 0){
                    v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = -1.0;
                }
                newCurV += alpha*(v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] - newCurV);
                grid[row][col] = 0;
                v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = newCurV;
                grid[row][col] = 2;
                return;
            }
        }
    }
}


void GridArea::rlAutoMoveAndImprove()
{
//    float * curVPt = &v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
//    float curV = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
//    if (curNextV > maxNextV){
    float rnd = rand()/(double)RAND_MAX;
    float maxNextV = -1;
    int nextPos = -1;
    if (rnd > epsilon){ // epsilon贪婪策略
        // 根据v走最优的步骤
        for(int pos = 0; pos < 9; pos++){
            if (grid[pos / 3][pos % 3] == 0){
                grid[pos / 3][pos % 3] = 1;
                float curNextV = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
                if (curNextV > maxNextV){
                    maxNextV = curNextV;
                    nextPos = pos;
                }
                grid[pos / 3][pos % 3] = 0;
            }
        }
    }
    else{
        int pos;
        while(true){
            pos = rand()%9;
            if (grid[pos / 3][pos % 3] == 0){
                nextPos = pos;
                break;
            }
        }
    }
    if (nextPos > -1){ // 更新v(s)
        float newCurV = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
        grid[nextPos / 3][nextPos % 3] = 1;
        if(isTerminal() == 1){
            v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = 1.0;
        }
        newCurV += alpha*(v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] - newCurV);
        cout << v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] << " ";
        cout << newCurV << endl;
        grid[nextPos / 3][nextPos % 3] = 0;
        v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] = newCurV;
        grid[nextPos / 3][nextPos % 3] = 1;
    }
}

int GridArea::train(bool show)
{
    clear();
    while(true){
        if(isFirst){
            rlAutoMoveAndImprove();
            if (isTerminal() != 3)break;
            aiAutoMove();
            if (isTerminal() != 3)break;
        }else{
            aiAutoMove();
            if (isTerminal() != 3)break;
            rlAutoMoveAndImprove();
            if (isTerminal() != 3)break;
        }
//        cout << v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]] << endl;
    }
    if(show){
        vToShow = v[grid[0][0]][grid[0][1]][grid[0][2]][grid[1][0]][grid[1][1]][grid[1][2]][grid[2][0]][grid[2][1]][grid[2][2]];
        repaint();
    }
    return isTerminal();
}

void GridArea::clear()
{
    for (int row = 0; row < 3; row++)
        for (int col  = 0; col < 3; col++)
            grid[row][col]=0;
    repaint();
}

int GridArea::isTerminal()
{
    // 是否赢了
    for (int i = 0; i < 3; i++){
        if(grid[i][0] == 1 && grid[i][1] == 1 && grid[i][2] == 1)return 1; // 行
        if(grid[0][i] == 1 && grid[1][i] == 1 && grid[2][i] == 1)return 1; // 列
    }
    if(grid[0][0] == 1 && grid[1][1] == 1 && grid[2][2] == 1)return 1;
    if(grid[0][2] == 1 && grid[1][1] == 1 && grid[2][0] == 1)return 1;
    // 是否输了
    for (int i = 0; i < 3; i++){
        if(grid[i][0] == 2 && grid[i][1] == 2 && grid[i][2] == 2)return 0; // 行
        if(grid[0][i] == 2 && grid[1][i] == 2 && grid[2][i] == 2)return 0; // 列
    }
    // 是否没单纯结束
    for (int row = 0; row < 3; row++)
        for (int col  = 0; col < 3; col++)
            if(grid[row][col]==0)
                return 3;
    return 2;
}
