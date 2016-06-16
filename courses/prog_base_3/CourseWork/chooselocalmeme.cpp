#include "chooselocalmeme.h"
#include "ui_chooselocalmeme.h"

ChooseLocalMeme::ChooseLocalMeme(QWidget *parent) :
    QFileDialog(parent),
    ui(new Ui::ChooseLocalMeme)
{
    ui->setupUi(this);
}

ChooseLocalMeme::~ChooseLocalMeme()
{
    delete ui;
}
