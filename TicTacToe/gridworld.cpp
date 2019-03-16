#include "gridworld.h"
#include "ui_gridworld.h"
#include <iostream>
using namespace std;

GridWorld::GridWorld(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GridWorld)
{
    ui->setupUi(this);
    // 固定窗口尺寸
    this->setFixedSize(1000, 600);
    // grid类型groupbutton
//    ui->radioButton->setChecked(true);
//    gridTypeBG.addButton(ui->radioButton, 1);
//    gridTypeBG.addButton(ui->radioButton_2, 2);
//    gridTypeBG.addButton(ui->radioButton_3, 3);
//    connect(&gridTypeBG, SIGNAL(buttonToggled(int,bool)), this, SLOT(gridTypeBGToggled(int,bool)));
}

GridWorld::~GridWorld()
{
    delete ui;
}

//void GridWorld::gridTypeBGToggled(int id, bool)
//{
//    ui->drawArea->currentGridType = id;
//}



void GridWorld::on_pushButton_clicked()
{
    int times = 1;
    float avrScore = 0;
    if (ui->lineEdit->text().toInt()>1)
        times = ui->lineEdit->text().toInt();
    for (int i = 0; i < times; i++){
        int score = ui->drawArea->train(false);
        switch(score){
        case 0:score = -1;break;
        case 1:break;
        case 2:score = 0;break;
        }
        avrScore += score / 100.0;
        if(i%100==99){
            ui->widget->curveVec.push_back(avrScore);
            avrScore = 0;
        }
    }
    ui->widget->repaint();
    ui->drawArea->train(true);
}

void GridWorld::on_pushButton_2_clicked()
{
    ui->drawArea->clear();
}
