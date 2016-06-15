#ifndef MEMESWINDOW_H
#define MEMESWINDOW_H

#include <QDialog>

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

private:
    Ui::MemesWindow *ui;
};

#endif // MEMESWINDOW_H
