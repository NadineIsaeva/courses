#ifndef MEMESWINDOW_H
#define MEMESWINDOW_H

#include "choosecolor.h"
#include "chooselocalmeme.h"
#include "memescollection.h"
#include <QMediaPlayer>

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

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MemesWindow *ui;
    ChooseLocalMeme choose_local_meme_window;
    ChooseColor choose_color_window;
    QImage meme_to_edit;
    QString meme_file_to_edit;
    QColor meme_text_color;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    MemesCollection *collection_w;
};

#endif // MEMESWINDOW_H
