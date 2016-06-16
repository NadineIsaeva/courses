#ifndef MEMESWINDOW_H
#define MEMESWINDOW_H

#include <QDialog>
#include "chooselocalmeme.h"

namespace Ui {
class MemesWindow;
}

class MemesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MemesWindow(QWidget *parent = 0);
    ~MemesWindow();

private slots:
    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MemesWindow *ui;
    ChooseLocalMeme w;
    QImage meme_to_edit;
    QString meme_file_to_edit;
};

#endif // MEMESWINDOW_H
