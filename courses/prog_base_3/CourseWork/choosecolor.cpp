#include "choosecolor.h"
#include "ui_choosecolor.h"

ChooseColor::ChooseColor(QWidget *parent) :
    QColorDialog(parent),
    ui(new Ui::ChooseColor)
{
    ui->setupUi(this);
}

ChooseColor::~ChooseColor()
{
    delete ui;
}
