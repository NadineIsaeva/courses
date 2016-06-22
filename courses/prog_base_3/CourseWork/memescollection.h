#ifndef MEMESCOLLECTION_H
#define MEMESCOLLECTION_H

#include <QDialog>
#include <QScrollArea>
#include <vector>
#include <map>
#include "memeitem.h"

using namespace std;

namespace Ui {
class MemesCollection;
}

class MemesCollection : public QDialog
{
    Q_OBJECT

public:
    QString choosed_meme_path;
    explicit MemesCollection(QWidget *parent = 0);
    ~MemesCollection();

private slots:
    void setChoosedItem(QString meme_path = 0);
private:
    Ui::MemesCollection *ui;
    vector<MemeItem*> memeItems;
    QScrollArea *scroll_all_catogories;
    QScrollArea *scroll_memes_and_animals;
    QScrollArea *scroll_memes_and_people;
    QScrollArea *scroll_sad_memes;
    QScrollArea *scroll_strange_memes;
    QScrollArea *scroll_your_memes;
};

#endif // MEMESCOLLECTION_H
