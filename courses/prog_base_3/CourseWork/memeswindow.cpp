#include "memeswindow.h"
#include "ui_memeswindow.h"
#include "chooselocalmeme.h"
#include "QPainter"
#include "QPixmap"
#include "QGraphicsScene"
#include "QImage"
#include "qDebug"
#include "QLabel"

MemesWindow::MemesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemesWindow)
{
    ui->setupUi(this);
    meme_file_to_edit = "kurs.jpeg";
    meme_to_edit.load(meme_file_to_edit);
    meme_to_edit = meme_to_edit.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(meme_to_edit));

    meme_text_color = Qt::white;
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
    meme_to_edit.load(meme_file_to_edit);
    meme_to_edit = meme_to_edit.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);

    QPainter painter(&meme_to_edit);

    double font_size1_px = meme_to_edit.height()/8;
    while ((font_size1_px/2) * arg1.length() > meme_to_edit.width()){
        font_size1_px -= 1;
    }
    double font_size1_pt = font_size1_px * 0.75;
    QFont font1 = QFont("Impact", font_size1_pt);
    painter.setFont(font1);

    double font_size2_px = meme_to_edit.height()/8;
    while ((font_size2_px/2) * ui->lineEdit->text().length() > meme_to_edit.width()){
        font_size2_px -= 1;
    }
    double font_size2_pt = font_size2_px * 0.75;
    QFont font2 = QFont("Impact", font_size2_pt);

    QPoint point_up = QPoint(meme_to_edit.width()/2 -  (font_size1_px/4)*arg1.length(), meme_to_edit.height()/12 + font_size1_px);
    QPoint point_down = QPoint(meme_to_edit.width()/2 -  (font_size2_px/4)*ui->lineEdit->text().length(), meme_to_edit.height()*10/12 + font_size2_px);


    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    QPainterPath path;
    path.addText(point_up,font1,arg1.toUpper());
    path.addText(point_down,font2,ui->lineEdit->text().toUpper());
    painter.drawPath(path);

    pen.setColor(meme_text_color);
    painter.setPen(pen);
    painter.setFont(font1);
    painter.drawText(point_up,arg1.toUpper());
    painter.setFont(font2);
    painter.drawText(point_down,ui->lineEdit->text().toUpper());

    ui->label->setPixmap(QPixmap::fromImage(meme_to_edit));
}

void MemesWindow::on_lineEdit_textChanged(const QString &arg1)
{
    meme_to_edit.load(meme_file_to_edit);
    meme_to_edit = meme_to_edit.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);

    QPainter painter(&meme_to_edit);

    double font_size1_px = meme_to_edit.height()/8;
    while ((font_size1_px/2) * ui->lineEdit_2->text().length() > meme_to_edit.width()){
        font_size1_px -= 1;
    }
    double font_size1_pt = font_size1_px * 0.75;
    QFont font1 = QFont("Impact", font_size1_pt);
    painter.setFont(font1);

    double font_size2_px = meme_to_edit.height()/8;
    while ((font_size2_px/2) * arg1.length() > meme_to_edit.width()){
        font_size2_px -= 1;
    }
    double font_size2_pt = font_size2_px * 0.75;
    QFont font2 = QFont("Impact", font_size2_pt);

    QPoint point_up = QPoint(meme_to_edit.width()/2 -  (font_size1_px/4)*ui->lineEdit_2->text().length(), meme_to_edit.height()/12 + font_size1_px);
    QPoint point_down = QPoint(meme_to_edit.width()/2 -  (font_size2_px/4)*arg1.length(), meme_to_edit.height()*10/12 + font_size2_px);


    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    QPainterPath path;
    path.addText(point_up,font1,ui->lineEdit_2->text().toUpper());
    path.addText(point_down,font2,arg1.toUpper());
    painter.drawPath(path);

    pen.setColor(meme_text_color);
    painter.setPen(pen);
    painter.setFont(font1);
    painter.drawText(point_up,ui->lineEdit_2->text().toUpper());
    painter.setFont(font2);
    painter.drawText(point_down,arg1.toUpper());

    ui->label->setPixmap(QPixmap::fromImage(meme_to_edit));
}

void MemesWindow::on_pushButton_clicked()
{
    meme_file_to_edit = choose_local_meme_window.getOpenFileName();
    meme_to_edit.load(meme_file_to_edit);
    meme_to_edit = meme_to_edit.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(meme_to_edit));
}

void MemesWindow::on_pushButton_2_clicked()
{
    meme_text_color = choose_color_window.getColor();
}
