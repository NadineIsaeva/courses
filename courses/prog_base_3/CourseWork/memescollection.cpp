#include "memescollection.h"
#include "ui_memescollection.h"
#include "QLabel"
#include "QDebug"
#include "QPushButton"
#include "QHBoxLayout"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlRecord"
#include "QtSql/QSqlQuery"
#include "QSignalMapper"

MemesCollection::MemesCollection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemesCollection)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT path, category_id FROM memes_collection");

    while(query->next()){
        QSqlRecord record = query->record();
        MemeItem *meme = new MemeItem(record.value(0).toString(),record.value(1).toInt());
        memeItems.push_back(meme);
    }

    QWidget *widget = new QWidget;
    scroll_all_catogories = new QScrollArea(this);
    scroll_all_catogories->setGeometry(this->x() + 10, this->y() + 10, this->width() - 20, this->height() - 20);
    scroll_all_catogories->setWidget(widget);
    scroll_all_catogories->setWidgetResizable(true);

    QWidget *widget1 = new QWidget;
    scroll_memes_and_animals = new QScrollArea;
    scroll_memes_and_animals->setMinimumHeight(240);
    scroll_memes_and_animals->setWidgetResizable(true);
    scroll_memes_and_animals->setWidget(widget1);

    QWidget *widget2 = new QWidget;
    scroll_memes_and_people = new QScrollArea;
    scroll_memes_and_people->setMinimumHeight(240);
    scroll_memes_and_people->setWidgetResizable(true);
    scroll_memes_and_people->setWidget(widget2);

    QWidget *widget3 = new QWidget;
    scroll_sad_memes = new QScrollArea;
    scroll_sad_memes->setMinimumHeight(240);
    scroll_sad_memes->setWidgetResizable(true);
    scroll_sad_memes->setWidget(widget3);

    QWidget *widget4 = new QWidget;
    scroll_strange_memes = new QScrollArea;
    scroll_strange_memes->setMinimumHeight(240);
    scroll_strange_memes->setWidgetResizable(true);
    scroll_strange_memes->setWidget(widget4);

    QWidget *widget5 = new QWidget;
    scroll_your_memes = new QScrollArea;
    scroll_your_memes->setMinimumHeight(240);
    scroll_your_memes->setWidgetResizable(true);
    scroll_your_memes->setWidget(widget5);

    QVBoxLayout *layout_v = new QVBoxLayout(widget);

    QHBoxLayout *layout_h_1 = new QHBoxLayout(widget1);
    QHBoxLayout *layout_h_2 = new QHBoxLayout(widget2);
    QHBoxLayout *layout_h_3 = new QHBoxLayout(widget3);
    QHBoxLayout *layout_h_4 = new QHBoxLayout(widget4);
    QHBoxLayout *layout_h_5 = new QHBoxLayout(widget5);

    QSignalMapper *signalMapper = new QSignalMapper(this);

    for (MemeItem *meme : memeItems){
        QImage img;
        img.load(meme->path);
        img = img.scaled(198,198,Qt::KeepAspectRatio);

        QIcon icon(QPixmap::fromImage(img));

        QPushButton *button = new QPushButton;
        button->setIcon(icon);
        button->setIconSize(QSize(198,198));
        button->setMinimumHeight(200);
        button->setMinimumWidth(200);

        signalMapper->setMapping(button, meme->path);
        connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(setChoosedItem(QString)));

        switch(meme->category){
        case 1:
            button->setParent(scroll_memes_and_animals);
            layout_h_1->addWidget(button);
            break;
        case 2:
            button->setParent(scroll_memes_and_people);
            layout_h_2->addWidget(button);
            break;
        case 3:
            button->setParent(scroll_sad_memes);
            layout_h_3->addWidget(button);
            break;
        case 4:
            button->setParent(scroll_strange_memes);
            layout_h_4->addWidget(button);
            break;
        case 5:
            button->setParent(scroll_your_memes);
            layout_h_5->addWidget(button);
            break;
        default:
            break;
        }
    }

    scroll_memes_and_animals->widget()->setLayout(layout_h_1);

    scroll_memes_and_people->widget()->setLayout(layout_h_2);
    scroll_sad_memes->widget()->setLayout(layout_h_3);
    scroll_strange_memes->widget()->setLayout(layout_h_4);
    scroll_your_memes->widget()->setLayout(layout_h_5);

    QLabel *label_memes_and_animals = new QLabel(scroll_all_catogories);
    label_memes_and_animals->setText("MEMES AND ANIMALS");
    label_memes_and_animals->setFont(QFont("Century Gothic", 16));
    label_memes_and_animals->setAlignment(Qt::AlignCenter);
    layout_v->addWidget(label_memes_and_animals);
    layout_v->addWidget(scroll_memes_and_animals);

    QLabel *label_memes_and_people = new QLabel(scroll_all_catogories);
    label_memes_and_people->setText("MEMES AND PEOPLE");
    label_memes_and_people->setFont(QFont("Century Gothic", 16));
    label_memes_and_people->setAlignment(Qt::AlignCenter);
    layout_v->addWidget(label_memes_and_people);
    layout_v->addWidget(scroll_memes_and_people);

    QLabel *label_sad_memes = new QLabel(scroll_all_catogories);
    label_sad_memes->setText("SAD MEMES");
    label_sad_memes->setFont(QFont("Century Gothic", 16));
    label_sad_memes->setAlignment(Qt::AlignCenter);
    layout_v->addWidget(label_sad_memes);
    layout_v->addWidget(scroll_sad_memes);

    QLabel *label_strange_memes = new QLabel(scroll_all_catogories);
    label_strange_memes->setText("STRANGE MEMES");
    label_strange_memes->setFont(QFont("Century Gothic", 16));
    label_strange_memes->setAlignment(Qt::AlignCenter);
    layout_v->addWidget(label_strange_memes);
    layout_v->addWidget(scroll_strange_memes);

    QLabel *label_your_memes = new QLabel(scroll_all_catogories);
    label_your_memes->setText("YOUR MEMES");
    label_your_memes->setFont(QFont("Century Gothic", 16));
    label_your_memes->setAlignment(Qt::AlignCenter);
    layout_v->addWidget(label_your_memes);
    layout_v->addWidget(scroll_your_memes);

    scroll_all_catogories->widget()->setLayout(layout_v);

    db.close();
}

void MemesCollection::setChoosedItem(QString meme_path){
    choosed_meme_path = meme_path;
    this->close();
}

MemesCollection::~MemesCollection()
{
    delete ui;
}
