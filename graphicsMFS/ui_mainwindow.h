/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 14. Dec 10:39:51 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page_menu;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_ir_a_crear;
    QPushButton *pushButton_ir_a_abrir;
    QWidget *page_crear;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton_crear;
    QPushButton *pushButton_back;
    QLineEdit *lineEdit_bloques;
    QLabel *label_12;
    QLineEdit *lineEdit_FE;
    QLineEdit *lineEdit_TE;
    QLineEdit *lineEdit_disco;
    QPushButton *pushButton_getDir;
    QWidget *page_arbir;
    QLabel *label_7;
    QLineEdit *lineEdit_disco2;
    QPushButton *pushButton_getopen;
    QPushButton *pushButton_abrir;
    QPushButton *pushButton_back2;
    QWidget *page_explorar;
    QLabel *label_8;
    QListWidget *listWidget_tags;
    QListWidget *listWidget_songs;
    QFrame *line;
    QPushButton *pushButton_addSong;
    QPushButton *pushButton_export;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_tag;
    QPushButton *pushButton_next_page;
    QPushButton *pushButton_goback3;
    QLineEdit *lineEdit_mp3;
    QLineEdit *lineEdit_tag;
    QLabel *label_10;
    QLabel *label_13;
    QPushButton *pushButton_searSong;
    QLabel *label_14;
    QLineEdit *lineEdit_mp3_exportado;
    QWidget *page_comandos;
    QLabel *label_9;
    QLabel *label_11;
    QLineEdit *lineEdit_comando;
    QTextEdit *textEdit_resultados;
    QPushButton *pushButton_previous_page;
    QPushButton *pushButton_exec;
    QPushButton *pushButton_textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 500);
        MainWindow->setMinimumSize(QSize(700, 500));
        MainWindow->setMaximumSize(QSize(700, 500));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 700, 461));
        page_menu = new QWidget();
        page_menu->setObjectName(QString::fromUtf8("page_menu"));
        label = new QLabel(page_menu);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 50, 140, 40));
        label_2 = new QLabel(page_menu);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(280, 110, 130, 40));
        pushButton_ir_a_crear = new QPushButton(page_menu);
        pushButton_ir_a_crear->setObjectName(QString::fromUtf8("pushButton_ir_a_crear"));
        pushButton_ir_a_crear->setGeometry(QRect(100, 320, 100, 26));
        pushButton_ir_a_abrir = new QPushButton(page_menu);
        pushButton_ir_a_abrir->setObjectName(QString::fromUtf8("pushButton_ir_a_abrir"));
        pushButton_ir_a_abrir->setGeometry(QRect(380, 320, 130, 26));
        stackedWidget->addWidget(page_menu);
        page_crear = new QWidget();
        page_crear->setObjectName(QString::fromUtf8("page_crear"));
        label_3 = new QLabel(page_crear);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(290, 30, 100, 15));
        label_4 = new QLabel(page_crear);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 260, 150, 16));
        label_5 = new QLabel(page_crear);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(90, 150, 120, 15));
        label_6 = new QLabel(page_crear);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(90, 200, 130, 15));
        pushButton_crear = new QPushButton(page_crear);
        pushButton_crear->setObjectName(QString::fromUtf8("pushButton_crear"));
        pushButton_crear->setGeometry(QRect(350, 360, 80, 26));
        pushButton_back = new QPushButton(page_crear);
        pushButton_back->setObjectName(QString::fromUtf8("pushButton_back"));
        pushButton_back->setGeometry(QRect(100, 370, 30, 30));
        lineEdit_bloques = new QLineEdit(page_crear);
        lineEdit_bloques->setObjectName(QString::fromUtf8("lineEdit_bloques"));
        lineEdit_bloques->setGeometry(QRect(260, 90, 113, 25));
        label_12 = new QLabel(page_crear);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(90, 90, 130, 20));
        lineEdit_FE = new QLineEdit(page_crear);
        lineEdit_FE->setObjectName(QString::fromUtf8("lineEdit_FE"));
        lineEdit_FE->setGeometry(QRect(260, 140, 113, 25));
        lineEdit_TE = new QLineEdit(page_crear);
        lineEdit_TE->setObjectName(QString::fromUtf8("lineEdit_TE"));
        lineEdit_TE->setGeometry(QRect(260, 200, 113, 25));
        lineEdit_disco = new QLineEdit(page_crear);
        lineEdit_disco->setObjectName(QString::fromUtf8("lineEdit_disco"));
        lineEdit_disco->setGeometry(QRect(260, 260, 113, 25));
        pushButton_getDir = new QPushButton(page_crear);
        pushButton_getDir->setObjectName(QString::fromUtf8("pushButton_getDir"));
        pushButton_getDir->setGeometry(QRect(390, 260, 30, 26));
        stackedWidget->addWidget(page_crear);
        page_arbir = new QWidget();
        page_arbir->setObjectName(QString::fromUtf8("page_arbir"));
        label_7 = new QLabel(page_arbir);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(50, 110, 210, 30));
        lineEdit_disco2 = new QLineEdit(page_arbir);
        lineEdit_disco2->setObjectName(QString::fromUtf8("lineEdit_disco2"));
        lineEdit_disco2->setGeometry(QRect(260, 110, 113, 30));
        pushButton_getopen = new QPushButton(page_arbir);
        pushButton_getopen->setObjectName(QString::fromUtf8("pushButton_getopen"));
        pushButton_getopen->setGeometry(QRect(400, 110, 31, 31));
        pushButton_abrir = new QPushButton(page_arbir);
        pushButton_abrir->setObjectName(QString::fromUtf8("pushButton_abrir"));
        pushButton_abrir->setGeometry(QRect(240, 210, 80, 26));
        pushButton_back2 = new QPushButton(page_arbir);
        pushButton_back2->setObjectName(QString::fromUtf8("pushButton_back2"));
        pushButton_back2->setGeometry(QRect(180, 310, 30, 26));
        stackedWidget->addWidget(page_arbir);
        page_explorar = new QWidget();
        page_explorar->setObjectName(QString::fromUtf8("page_explorar"));
        label_8 = new QLabel(page_explorar);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(190, 10, 400, 21));
        listWidget_tags = new QListWidget(page_explorar);
        QFont font;
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget_tags);
        __qlistwidgetitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qlistwidgetitem->setFont(font);
        QFont font1;
        font1.setItalic(true);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget_tags);
        __qlistwidgetitem1->setFont(font1);
        listWidget_tags->setObjectName(QString::fromUtf8("listWidget_tags"));
        listWidget_tags->setGeometry(QRect(30, 60, 310, 250));
        listWidget_songs = new QListWidget(page_explorar);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget_songs);
        __qlistwidgetitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qlistwidgetitem2->setFont(font);
        listWidget_songs->setObjectName(QString::fromUtf8("listWidget_songs"));
        listWidget_songs->setGeometry(QRect(360, 60, 310, 250));
        line = new QFrame(page_explorar);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(350, 60, 3, 250));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton_addSong = new QPushButton(page_explorar);
        pushButton_addSong->setObjectName(QString::fromUtf8("pushButton_addSong"));
        pushButton_addSong->setGeometry(QRect(30, 340, 110, 26));
        pushButton_export = new QPushButton(page_explorar);
        pushButton_export->setObjectName(QString::fromUtf8("pushButton_export"));
        pushButton_export->setGeometry(QRect(210, 340, 110, 26));
        pushButton_delete = new QPushButton(page_explorar);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(380, 340, 110, 26));
        pushButton_tag = new QPushButton(page_explorar);
        pushButton_tag->setObjectName(QString::fromUtf8("pushButton_tag"));
        pushButton_tag->setGeometry(QRect(560, 340, 110, 26));
        pushButton_next_page = new QPushButton(page_explorar);
        pushButton_next_page->setObjectName(QString::fromUtf8("pushButton_next_page"));
        pushButton_next_page->setGeometry(QRect(630, 430, 40, 26));
        pushButton_goback3 = new QPushButton(page_explorar);
        pushButton_goback3->setObjectName(QString::fromUtf8("pushButton_goback3"));
        pushButton_goback3->setGeometry(QRect(30, 430, 40, 26));
        lineEdit_mp3 = new QLineEdit(page_explorar);
        lineEdit_mp3->setObjectName(QString::fromUtf8("lineEdit_mp3"));
        lineEdit_mp3->setGeometry(QRect(60, 390, 230, 20));
        lineEdit_tag = new QLineEdit(page_explorar);
        lineEdit_tag->setObjectName(QString::fromUtf8("lineEdit_tag"));
        lineEdit_tag->setGeometry(QRect(280, 430, 200, 20));
        label_10 = new QLabel(page_explorar);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 390, 30, 13));
        label_13 = new QLabel(page_explorar);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(250, 430, 30, 13));
        pushButton_searSong = new QPushButton(page_explorar);
        pushButton_searSong->setObjectName(QString::fromUtf8("pushButton_searSong"));
        pushButton_searSong->setGeometry(QRect(290, 390, 30, 23));
        label_14 = new QLabel(page_explorar);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(380, 390, 140, 13));
        lineEdit_mp3_exportado = new QLineEdit(page_explorar);
        lineEdit_mp3_exportado->setObjectName(QString::fromUtf8("lineEdit_mp3_exportado"));
        lineEdit_mp3_exportado->setGeometry(QRect(520, 390, 150, 20));
        stackedWidget->addWidget(page_explorar);
        page_comandos = new QWidget();
        page_comandos->setObjectName(QString::fromUtf8("page_comandos"));
        label_9 = new QLabel(page_comandos);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(250, 20, 100, 20));
        label_11 = new QLabel(page_comandos);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(70, 110, 80, 20));
        lineEdit_comando = new QLineEdit(page_comandos);
        lineEdit_comando->setObjectName(QString::fromUtf8("lineEdit_comando"));
        lineEdit_comando->setGeometry(QRect(160, 110, 290, 20));
        textEdit_resultados = new QTextEdit(page_comandos);
        textEdit_resultados->setObjectName(QString::fromUtf8("textEdit_resultados"));
        textEdit_resultados->setGeometry(QRect(70, 150, 380, 210));
        pushButton_previous_page = new QPushButton(page_comandos);
        pushButton_previous_page->setObjectName(QString::fromUtf8("pushButton_previous_page"));
        pushButton_previous_page->setGeometry(QRect(90, 390, 40, 26));
        pushButton_exec = new QPushButton(page_comandos);
        pushButton_exec->setObjectName(QString::fromUtf8("pushButton_exec"));
        pushButton_exec->setGeometry(QRect(480, 110, 60, 26));
        pushButton_textEdit = new QPushButton(page_comandos);
        pushButton_textEdit->setObjectName(QString::fromUtf8("pushButton_textEdit"));
        pushButton_textEdit->setGeometry(QRect(480, 180, 75, 23));
        stackedWidget->addWidget(page_comandos);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; text-decoration: underline;\">MFS</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">  (Music File System)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:600;\">Menu Principal</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_ir_a_crear->setText(QApplication::translate("MainWindow", "Crear un Disco!", 0, QApplication::UnicodeUTF8));
        pushButton_ir_a_abrir->setText(QApplication::translate("MainWindow", "Abrir un Disco!", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Crear disco", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Nombre y dir. del disco:  ", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "No. de File Entries: ", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "No. de Tag Entries: ", 0, QApplication::UnicodeUTF8));
        pushButton_crear->setText(QApplication::translate("MainWindow", "Create it!", 0, QApplication::UnicodeUTF8));
        pushButton_back->setText(QApplication::translate("MainWindow", "<--", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Cantidad de bloques", 0, QApplication::UnicodeUTF8));
        pushButton_getDir->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Escriba la direccion de su disco: ", 0, QApplication::UnicodeUTF8));
        lineEdit_disco2->setText(QApplication::translate("MainWindow", "disco.dat", 0, QApplication::UnicodeUTF8));
        pushButton_getopen->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        pushButton_abrir->setText(QApplication::translate("MainWindow", "Explorar", 0, QApplication::UnicodeUTF8));
        pushButton_back2->setText(QApplication::translate("MainWindow", "<--", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "DIsco ", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget_tags->isSortingEnabled();
        listWidget_tags->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_tags->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "TAGS", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_tags->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "Show All Songs...", 0, QApplication::UnicodeUTF8));
        listWidget_tags->setSortingEnabled(__sortingEnabled);


        const bool __sortingEnabled1 = listWidget_songs->isSortingEnabled();
        listWidget_songs->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem2 = listWidget_songs->item(0);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", "SONGS", 0, QApplication::UnicodeUTF8));
        listWidget_songs->setSortingEnabled(__sortingEnabled1);

        pushButton_addSong->setText(QApplication::translate("MainWindow", "Agregar Cancion", 0, QApplication::UnicodeUTF8));
        pushButton_export->setText(QApplication::translate("MainWindow", "Exportar", 0, QApplication::UnicodeUTF8));
        pushButton_delete->setText(QApplication::translate("MainWindow", "Eliminar", 0, QApplication::UnicodeUTF8));
        pushButton_tag->setText(QApplication::translate("MainWindow", "Agregar TAG", 0, QApplication::UnicodeUTF8));
        pushButton_next_page->setText(QApplication::translate("MainWindow", "-->", 0, QApplication::UnicodeUTF8));
        pushButton_goback3->setText(QApplication::translate("MainWindow", "<--", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Mp3:", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Tag:", 0, QApplication::UnicodeUTF8));
        pushButton_searSong->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Nombre del mp3 a exportar: ", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "DISCO TAL", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Comando:", 0, QApplication::UnicodeUTF8));
        pushButton_previous_page->setText(QApplication::translate("MainWindow", "<--", 0, QApplication::UnicodeUTF8));
        pushButton_exec->setText(QApplication::translate("MainWindow", "Ejecutar", 0, QApplication::UnicodeUTF8));
        pushButton_textEdit->setText(QApplication::translate("MainWindow", "Limpiar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
