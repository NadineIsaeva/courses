#ifndef CHOOSECATEGORY_H
#define CHOOSECATEGORY_H

#include <QDialog>

namespace Ui {
class ChooseCategory;
}

class ChooseCategory : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseCategory(QWidget *parent = 0, QString query_str = 0);
    ~ChooseCategory();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::ChooseCategory *ui;
    QString query_str;
};

#endif // CHOOSECATEGORY_H
