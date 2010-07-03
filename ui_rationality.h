/********************************************************************************
** Form generated from reading UI file 'rationality.ui'
**
** Created: Tue Jun 29 13:46:41 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RATIONALITY_H
#define UI_RATIONALITY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Rationality
{
public:
    QAction *actionNuova_finestra;
    QAction *actionChiudi;
    QAction *actionTag;
    QAction *actionTaglia;
    QAction *actionIncola;
    QAction *actionInformazioni;
    QAction *actionIcone;
    QAction *actionDettagli;
    QAction *actionAbout;
    QAction *actionHelp;
    QAction *actionAbout_2;
    QAction *actionAiuto;
    QWidget *centralWidget;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *Rationality)
    {
        if (Rationality->objectName().isEmpty())
            Rationality->setObjectName(QString::fromUtf8("Rationality"));
        Rationality->resize(601, 336);
        actionNuova_finestra = new QAction(Rationality);
        actionNuova_finestra->setObjectName(QString::fromUtf8("actionNuova_finestra"));
        actionChiudi = new QAction(Rationality);
        actionChiudi->setObjectName(QString::fromUtf8("actionChiudi"));
        actionTag = new QAction(Rationality);
        actionTag->setObjectName(QString::fromUtf8("actionTag"));
        actionTaglia = new QAction(Rationality);
        actionTaglia->setObjectName(QString::fromUtf8("actionTaglia"));
        actionIncola = new QAction(Rationality);
        actionIncola->setObjectName(QString::fromUtf8("actionIncola"));
        actionInformazioni = new QAction(Rationality);
        actionInformazioni->setObjectName(QString::fromUtf8("actionInformazioni"));
        actionIcone = new QAction(Rationality);
        actionIcone->setObjectName(QString::fromUtf8("actionIcone"));
        actionDettagli = new QAction(Rationality);
        actionDettagli->setObjectName(QString::fromUtf8("actionDettagli"));
        actionAbout = new QAction(Rationality);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionHelp = new QAction(Rationality);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionAbout_2 = new QAction(Rationality);
        actionAbout_2->setObjectName(QString::fromUtf8("actionAbout_2"));
        actionAiuto = new QAction(Rationality);
        actionAiuto->setObjectName(QString::fromUtf8("actionAiuto"));
        centralWidget = new QWidget(Rationality);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Rationality->setCentralWidget(centralWidget);
        toolBar = new QToolBar(Rationality);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMinimumSize(QSize(32, 32));
        toolBar->setMovable(false);
        Rationality->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(Rationality);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        Rationality->addToolBar(Qt::TopToolBarArea, toolBar_2);

        retranslateUi(Rationality);

        QMetaObject::connectSlotsByName(Rationality);
    } // setupUi

    void retranslateUi(QMainWindow *Rationality)
    {
        Rationality->setWindowTitle(QApplication::translate("Rationality", "Rationality", 0, QApplication::UnicodeUTF8));
        actionNuova_finestra->setText(QApplication::translate("Rationality", "Nuova finestra", 0, QApplication::UnicodeUTF8));
        actionChiudi->setText(QApplication::translate("Rationality", "Chiudi", 0, QApplication::UnicodeUTF8));
        actionTag->setText(QApplication::translate("Rationality", "Copia", 0, QApplication::UnicodeUTF8));
        actionTaglia->setText(QApplication::translate("Rationality", "Taglia", 0, QApplication::UnicodeUTF8));
        actionIncola->setText(QApplication::translate("Rationality", "Incola", 0, QApplication::UnicodeUTF8));
        actionInformazioni->setText(QApplication::translate("Rationality", "Informazioni", 0, QApplication::UnicodeUTF8));
        actionIcone->setText(QApplication::translate("Rationality", "Icone", 0, QApplication::UnicodeUTF8));
        actionDettagli->setText(QApplication::translate("Rationality", "Dettagli", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("Rationality", "Razionalizza", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("Rationality", "Impostazioni", 0, QApplication::UnicodeUTF8));
        actionAbout_2->setText(QApplication::translate("Rationality", "Circa", 0, QApplication::UnicodeUTF8));
        actionAiuto->setText(QApplication::translate("Rationality", "Aiuto in linea", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("Rationality", "toolBar", 0, QApplication::UnicodeUTF8));
        toolBar_2->setWindowTitle(QApplication::translate("Rationality", "toolBar_2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Rationality: public Ui_Rationality {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RATIONALITY_H
