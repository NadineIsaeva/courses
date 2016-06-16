#ifndef CHOOSECOLOR_H
#define CHOOSECOLOR_H

#include <QColorDialog>

namespace Ui {
class ChooseColor;
}

class ChooseColor : public QColorDialog
{
    Q_OBJECT

public:
    explicit ChooseColor(QWidget *parent = 0);
    ~ChooseColor();

private:
    Ui::ChooseColor *ui;
};

#endif // CHOOSECOLOR_H
