#include "rationality.h"
#include "ui_rationality.h"
#include "searchbutton.h"
#include "panelbutton.h"
#include "backbutton.h"
#include "forwardbutton.h"
#include "filterbutton.h"

#include <QLineEdit>
#include <QGridLayout>

#include <QDebug>

Rationality::Rationality(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Rationality)
{
    ui->setupUi(this);

    this->setMinimumWidth(130+150+20);
    this->setMinimumHeight(35+200);
    QSize size;
    ui->toolBar->setMinimumHeight(31);
    ui->toolBar->setMaximumHeight(32);
    ui->toolBar->setStyleSheet("padding: 0px;");
    size.setHeight(32);
    size.setWidth(this->width());
    //ui->toolBar->setIconSize(size);

    QGridLayout * l= new QGridLayout(ui->centralWidget);
    l->setSpacing(0);
    l->setMargin(0);

    fb = new FilterBar(ui->toolBar);
    fb->setFixedHeight(32);
    fb->setFixedWidth(ui->toolBar->width());


    BackButton *bb= new BackButton(ui->toolBar_2);
    bb->setFixedSize(32,32);
    bb->setEnabled(false);

    ForwardButton *ff = new ForwardButton(ui->toolBar_2);
    ff->setFixedSize(32,32);
    ff->setEnabled(false);


    FilterButton *f = new FilterButton(ui->toolBar_2);
    f->setFixedSize(32,32);


    SearchButton *b = new SearchButton(ui->toolBar_2);
    b->setFixedSize(32,32);
    ui->toolBar_2->setFixedHeight(32);
    ui->toolBar_2->setStyleSheet("padding: 0px;");
    ui->toolBar_2->setMovable(false);
    ui->toolBar_2->setLayoutDirection(Qt::RightToLeft);


    ui->toolBar->addWidget(fb);
    ui->toolBar_2->addWidget(b);
    ui->toolBar_2->addWidget(f);
    ui->toolBar_2->addWidget(ff);
    ui->toolBar_2->addWidget(bb);



    lbar = new LeftBar(this);
    lbar->setFixedWidth(130);
    l->addWidget(lbar,0,0);


    PanelButton * pb=new PanelButton(lbar);
    pb->setGeometry(0,0,135,32);
    pb->setFixedSize(135,32);
    pb->addItem("Preferiti");
    pb->addItem("Popolari");

    fview=new FolderView(this);
    l->addWidget(fview,0,1);

    ui->centralWidget->setLayout(l);
    sb = new SearchBar(this);
    sb->setGeometry(width()-250,32,250,37);
    sb->hide();


    connect(b,SIGNAL(clicked(bool)),sb,SLOT(setShown(bool)));
    connect(bb,SIGNAL(clicked()),fb,SLOT(back()));
    connect(ff,SIGNAL(clicked()),fb,SLOT(forward()));

    connect(fb,SIGNAL(isFirst(bool)),bb,SLOT(setEnabled(bool)));
    connect(fb,SIGNAL(isLast(bool)),ff,SLOT(setEnabled(bool)));

    connect(fview, SIGNAL(currentDir(QString)),fb,SLOT(open(QString)));
    connect(fb,SIGNAL(currentDir(QString,bool)),fview, SLOT(open(QString,bool)));

    connect(fview,SIGNAL(isFiltred(bool)),f,SLOT(setChecked(bool)));
    connect(fview,SIGNAL(setFilter(QString)),fb,SLOT(filter(QString)));
    connect(bb,SIGNAL(clicked()),f,SLOT(setChecked(bool)));
    connect(bb,SIGNAL(clicked()),fb,SLOT(setHistory()));




//    QLineEdit *le = new QLineEdit(sb);
//    le->setGeometry(10,4,250-20-5,32-8);

}

Rationality::~Rationality()
{
    delete ui;
}

void Rationality::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);

    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }

}

void Rationality::resizeEvent(QResizeEvent *e){
    fview->updateGrid();
    //ui->toolBar_2->setGeometry(width()-ui->toolBar_2->width(),ui->toolBar_2->y(),ui->toolBar_2->width(),ui->toolBar_2->height());
    //fb->setFixedWidth(this->width()-ui->toolBar_2->width());
    fb->setFixedWidth(ui->toolBar->width());
    bool visible=sb->isVisible();
    sb->setGeometry(this->width()-250,32,250,37);
    sb->setShown(visible);

    e->accept();
}
