#ifndef RATIONALITY_H
#define RATIONALITY_H

#include <QMainWindow>
#include <QResizeEvent>
#include "folderview.h"
#include "leftbar.h"
#include "filterbar.h"
#include "searchbar.h"

namespace Ui {
    class Rationality;
}

class Rationality : public QMainWindow {
    Q_OBJECT
public:
    Rationality(QWidget *parent = 0);
    ~Rationality();

protected:
    void changeEvent(QEvent *e);
    void resizeEvent(QResizeEvent *);
private:
    LeftBar * lbar;
    FilterBar * fb;
    FolderView *fview;
    Ui::Rationality *ui;
    SearchBar *sb;

private slots:
};

#endif // RATIONALITY_H
