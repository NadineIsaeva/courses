#include "memeswindow.h"
#include "ui_memeswindow.h"
#include "QPainter"
#include "QPixmap"
#include "QGraphicsScene"
#include "QImage"
#include "QLabel"

MemesWindow::MemesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemesWindow)
{
    ui->setupUi(this);


}

MemesWindow::~MemesWindow()
{
    delete ui;
}

void MemesWindow::on_lineEdit_2_textEdited(const QString &arg1)
{

}

void MemesWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QImage myImage;
    myImage.load("kursach.jpg");
    myImage = myImage.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);

    QPainter painter(&myImage);
    QRect rect = QRect(0, 0, myImage.width(), myImage.height()/4);
    QFont font = QFont("Impact",myImage.height()/8);

    painter.setFont(font);
    painter.drawText(rect,Qt::AlignCenter,arg1.toUpper());

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);

    QPainterPath path;
    path.addText(rect,Qt::AlignCenter,arg1.toUpper());
    painter.drawPath(path);






    painter.setFont(font);
    painter.setPen(pen);

     //Adjust the position

    ui->label->setPixmap(QPixmap::fromImage(myImage));
}
