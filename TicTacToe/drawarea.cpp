#include "drawarea.h"
#include "ui_drawarea.h"

DrawArea::DrawArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawArea)
{
    ui->setupUi(this);
}

DrawArea::~DrawArea()
{
    delete ui;
}
