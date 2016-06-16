#ifndef CHOOSELOCALMEME_H
#define CHOOSELOCALMEME_H

#include <QFileDialog>

namespace Ui {
class ChooseLocalMeme;
}

class ChooseLocalMeme : public QFileDialog
{
    Q_OBJECT

public:
    explicit ChooseLocalMeme(QWidget *parent = 0);
    ~ChooseLocalMeme();

private:
    Ui::ChooseLocalMeme *ui;
};

#endif // CHOOSELOCALMEME_H
