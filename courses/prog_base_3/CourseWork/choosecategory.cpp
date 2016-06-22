#include "choosecategory.h"
#include "ui_choosecategory.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "qDebug"

ChooseCategory::ChooseCategory(QWidget *parent, QString query_str) :
    QDialog(parent),
    ui(new Ui::ChooseCategory)
{
    ui->setupUi(this);
    this->query_str = query_str;
}

ChooseCategory::~ChooseCategory()
{
    delete ui;
}

void ChooseCategory::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);

    query->exec(query_str + "1)");

    db.close();
    this->close();
}
void ChooseCategory::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);

    query->exec(query_str + "2)");

    db.close();
    this->close();
}

void ChooseCategory::on_pushButton_3_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);

    query->exec(query_str + "3)");

    db.close();
    this->close();
}

void ChooseCategory::on_pushButton_4_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);

    query->exec(query_str + "4)");

    db.close();
    this->close();
}

void ChooseCategory::on_pushButton_5_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    db.open();

    QSqlQuery *query = new QSqlQuery(db);

    query->exec(query_str + "5)");

    db.close();
    this->close();
}
