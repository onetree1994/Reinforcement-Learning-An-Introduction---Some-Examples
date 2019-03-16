#include "curve.h"
#include <iostream>
using namespace std;

Curve::Curve(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(350, 300);
}

void Curve::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawLine(25, 25, 25, this->height() - 25);
    painter.drawLine(25, this->height() - 25, this->width() - 25, this->height() - 25);
    if (curveVec.size() >= 2){
        float yscale = (this->height() - 50) / 1.0;
        float xscale = (this->width() - 50) / curveVec.size();
        for (int i = 0; i < curveVec.size() - 1; i++){
//            cout << "???????" << xscale * i + 25 << " " << curveVec[i]*yscale + 25 << " " << xscale * (i + 1) + 25 << " " << curveVec[i+1]*yscale + 25 << endl;
            painter.drawLine(xscale * i + 25, this->height() - (curveVec[i]*yscale + 25), xscale * (i + 1) + 25, this->height() - (curveVec[i+1]*yscale + 25));
        }
    }
}

