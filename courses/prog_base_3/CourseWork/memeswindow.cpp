#include "memeswindow.h"
#include "ui_memeswindow.h"
#include "memescollection.h"
#include "QDialog"
#include "QPainter"
#include "QPixmap"
#include "QImage"
#include "QMediaPlayer"
#include "QVideoWidget"
#include "QMediaPlaylist"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlRecord"
#include "time.h"
#include "choosecategory.h"

MemesWindow::MemesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemesWindow)
{
    ui->setupUi(this);
    this->setFixedSize(943, 675);
    //QVideoWidget *videoWidget = new QVideoWidget(this);

    //videoWidget->setGeometry(30, 70, 640, 512);
    //videoWidget->show();
    //player->setVideoOutput(videoWidget);
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile("Rick Astley – Never Gonna Give You Up.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Enjoykin - Он показывал писюн.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Enjoykin - Я ламповая няша.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Kavinsky – Nightcall.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("PHARAOH - BLACK SIEMENS.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("PSY - Gangnam Style.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Ranetki - Sad music.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Shia LaBeouf - Just Do It!.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Tobi King - Loli Mou.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Userdie - Не выходи из комнаты.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("X-Files - Main Theme.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Игорь Николаев - Выпьем за любовь.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Научно-технический реп - Демидович.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Пика - Патимейкер.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("Свинка Пеппа - Я свинка Пеппа.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("George Michael – Careless Whisper.mp3"));

    player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->play();

    meme_file_to_edit = "kurs.jpeg";
    meme_to_edit.load(meme_file_to_edit);
    meme_to_edit = meme_to_edit.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(meme_to_edit));

    meme_text_color = Qt::white;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT path FROM memes_collection");

    ui->pushButton_4->setEnabled(false);
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
    qDebug()<< font_size1_px;
    while ((font_size1_px/2) * (arg1.length() + 5) > meme_to_edit.width()){
        font_size1_px -= 1;
    }
    double font_size1_pt = font_size1_px * 0.75;
    QFont font1 = QFont("Impact", font_size1_pt);

    double font_size2_px = meme_to_edit.height()/8;
    while ((font_size2_px/2) * (ui->lineEdit->text().length() + 5) > meme_to_edit.width()){
        font_size2_px -= 1;
    }
    double font_size2_pt = font_size2_px * 0.75;
    QFont font2 = QFont("Impact", font_size2_pt);

    QPoint point_up = QPoint(meme_to_edit.width()/2 - (font_size1_px/4)*arg1.length(), meme_to_edit.height()/12 + font_size1_px);
    QPoint point_down = QPoint(meme_to_edit.width()/2 - (font_size2_px/4)*ui->lineEdit->text().length(), meme_to_edit.height()*10/12 + font_size2_px);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    QPainterPath path;
    path.addText(point_up, font1, arg1.toUpper());
    path.addText(point_down, font2, ui->lineEdit->text().toUpper());
    painter.drawPath(path);

    pen.setColor(meme_text_color);
    painter.setPen(pen);
    painter.setFont(font1);
    painter.drawText(point_up, arg1.toUpper());
    painter.setFont(font2);
    painter.drawText(point_down,ui->lineEdit->text().toUpper());

    ui->label->setPixmap(QPixmap::fromImage(meme_to_edit));
}

void MemesWindow::on_lineEdit_textChanged(const QString &arg1)
{
    meme_to_edit.load(meme_file_to_edit);
    meme_to_edit = meme_to_edit.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio);

    QPainter painter(&meme_to_edit);

    double font_size1_px = meme_to_edit.height()/8;
    while ((font_size1_px/2) * (ui->lineEdit_2->text().length() + 5) > meme_to_edit.width()){
        font_size1_px -= 1;
    }
    double font_size1_pt = font_size1_px * 0.75;
    QFont font1 = QFont("Impact", font_size1_pt);

    double font_size2_px = meme_to_edit.height()/8;
    while ((font_size2_px/2) * (arg1.length() + 5) > meme_to_edit.width()){
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
    painter.setFont(font1);
    painter.drawText(point_up,ui->lineEdit_2->text().toUpper());
    painter.setFont(font2);
    painter.setFont(font2);
    painter.drawText(point_down,arg1.toUpper());

    ui->label->setPixmap(QPixmap::fromImage(meme_to_edit));
}

void MemesWindow::on_pushButton_clicked()
{
    meme_file_to_edit = choose_local_meme_window.getOpenFileName();

    meme_to_edit.load(meme_file_to_edit);
    meme_to_edit = meme_to_edit.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(meme_to_edit));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT path FROM memes_collection");

    while(query->next()){
        QSqlRecord record = query->record();
        if (meme_file_to_edit.compare(record.value(0).toString()) == 0){
            ui->pushButton_4->setText("IN COLLECTION");
            ui->pushButton_4->setEnabled(false);
            break;
        }
        else if (meme_file_to_edit.compare("") == 0){
            ui->pushButton_4->setEnabled(false);
        }
        else{
            ui->pushButton_4->setText("ADD TO COLLECTION");
            ui->pushButton_4->setEnabled(true);
        }
    }
}

void MemesWindow::on_pushButton_2_clicked()
{
    meme_text_color = choose_color_window.getColor();
}

void MemesWindow::on_pushButton_3_clicked()
{
    collection_w = new MemesCollection();
    collection_w->exec();

    meme_file_to_edit = collection_w->choosed_meme_path;

    meme_to_edit.load(meme_file_to_edit);
    meme_to_edit = meme_to_edit.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(meme_to_edit));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT path FROM memes_collection");

    while(query->next()){
        QSqlRecord record = query->record();
        if (meme_file_to_edit.compare(record.value(0).toString()) == 0){
            ui->pushButton_4->setText("IN COLLECTION");
            ui->pushButton_4->setEnabled(false);
            break;
        }
        else if (meme_file_to_edit.compare("") == 0){
            ui->pushButton_4->setEnabled(false);
        }
        else{
            ui->pushButton_4->setText("ADD TO COLLECTION");
            ui->pushButton_4->setEnabled(true);
        }
    }
}

void MemesWindow::on_pushButton_4_clicked()
{
    ChooseCategory w(0, "INSERT INTO memes_collection(path, category_id) VALUES('" + meme_file_to_edit + "',");
    w.exec();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT path FROM memes_collection");

    while(query->next()){
        QSqlRecord record = query->record();
        if (meme_file_to_edit.compare(record.value(0).toString()) == 0){
            ui->pushButton_4->setText("IN COLLECTION");
            ui->pushButton_4->setEnabled(false);
            break;
        }
        else if (meme_file_to_edit.compare("") == 0){
            ui->pushButton_4->setEnabled(false);
        }
        else{
            ui->pushButton_4->setText("ADD TO COLLECTION");
            ui->pushButton_4->setEnabled(true);
        }
    }
    db.close();
}

void MemesWindow::on_pushButton_5_clicked()
{
    srand(time(0));
    int rand_index = rand()%16;
    playlist->setCurrentIndex(rand_index);
}

void MemesWindow::on_pushButton_6_clicked()
{
    if (ui->pushButton_6->text().compare(QString::fromUtf8("STOP")) == 0){
        player->stop();
        ui->pushButton_6->setText("PLAY");
        ui->pushButton_5->setEnabled(false);
    }
    else if (ui->pushButton_6->text().compare(QString::fromUtf8("PLAY")) == 0){
        srand(time(0));
        int rand_index = rand()%16;
        playlist->setCurrentIndex(rand_index);
        player->play();
        ui->pushButton_6->setText("STOP");
        ui->pushButton_5->setEnabled(true);
    }
}

void MemesWindow::on_pushButton_7_clicked()
{
    meme_to_edit.save(choose_local_meme_window.getSaveFileName() + ".png");
}
