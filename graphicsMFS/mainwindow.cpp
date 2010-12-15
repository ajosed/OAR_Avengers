#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    proc.setProcessChannelMode(QProcess::MergedChannels);
    connect(&proc, SIGNAL(readyRead()), this, SLOT(on_cmdExec_data_available()));
    connect(&proc, SIGNAL(finished(int)), this, SLOT(on_cmdExec_finish(int)));

    this->path_mfs = "mfs.exe";
    //this->path_mfs = "/media/Disco_Local/OAR/graphicsMFS/mfs";
    //ui->lineEdit_disco2->setText("/media/Disco_Local/OAR/mfs-build-desktop/disco.dat");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_tags_currentRowChanged(int currentRow)
{
    if(this->ui->listWidget_tags->currentRow()==0)
        return;

    if(currentRow==1)
    {
        QString comando = "-lf " + path_disco;
        proc.start(path_mfs,comando.split(" "));
    }
    else
    {
        QString tag = ui->listWidget_tags->currentItem()->text();
        QStringList comando;
        comando << "-s" << tag << path_disco;
        proc.start(path_mfs,comando);
    }
//    QString x;
//    x="Disco TAL "+QString::number(ui->listWidget_tags->currentRow());
//    this->ui->label_8->setText(x);
//    if(currentRow==0)
//    {
//        QMessageBox temp;
//        temp.setText("NO PODES TENER ESTE VALOR");
//        temp.exec();
//    }

//TQpUN5

}

void MainWindow::on_pushButton_getopen_clicked()
{
    ui->lineEdit_disco2->setText(QFileDialog::getOpenFileName(this,tr("Abrir Disco"),
                                                              "D:/OAR/graphicsMFS/debug", tr("Discos de musica (*.dat)")));

}

void MainWindow::on_pushButton_ir_a_crear_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_cmdExec_data_available()
{
    this->output=proc.readAll();
}

void MainWindow::on_cmdExec_finish(int a)
{
    valor_del_return = a;
    if(ui->stackedWidget->currentIndex()==4)
    {
        ui->textEdit_resultados->append(output+"\n");
        output="";
        return;
    }
    if(a!=0)
    {
        int esto = ui->stackedWidget->currentIndex();
        if(esto==1 || esto==3)
        {
            QMessageBox b;
            b.setText(output);
            b.exec();
        }
    }
    else
    {
        if(output=="")
        {
            QMessageBox y;
            if(_c=='c')
                y.setText("Disco creado exitosamente\n");

            if(_c=='a')
            {
                y.setText("Archivo agregado al disco\n");
                this->on_listWidget_tags_currentRowChanged(ui->listWidget_tags->currentRow());
            }

            if(_c=='e')
                y.setText("Exportacion terminada\n");

            if(_c=='d')
            {
                y.setText("El archivo fue eliminado\n");
                this->on_listWidget_tags_currentRowChanged(ui->listWidget_tags->currentRow());
            }

            if(_c=='t')
            {
                y.setText("Se agregago el tag exitosamente\n");
                QStringList comando;
                comando << "-l" << path_disco;
                proc.start(path_mfs,comando);
            }

            y.exec();
            return;
        }

        output = output.left(output.indexOf("\n"));

        if(output.left(output.indexOf(":"))=="-l")
        {
            this->clear_tags();
//            QMessageBox a;
//            a.setText("|"+output+"|\n"+QString::number(output.length()));
//            a.exec();
            output.replace(0,3,"");
            this->mostrar_tags();
        }

        if(output.left(output.indexOf(":"))=="-lf")
        {
            this->clear_songs();
            this->output.replace(0,4,"");
            this->mostrar_songs();
        }

        if(output.left(output.indexOf(":"))=="-s")
        {
            this->clear_songs();
            output.replace(0,3,"");

            output2 = output;
            int pos_coma = output2.indexOf(",");

            QString comando = "-ss "+output2.left(pos_coma)+" "+path_disco;
            proc.start(path_mfs,comando.split(" "));

            output2.replace(0,pos_coma+1,"");
        }

        if(output.left(output.indexOf(":"))=="-ss")
        {
            output.replace(0,4,"");
            output.replace(output.length()-1,1,"");
            if(output.length()>=4)
                this->ui->listWidget_songs->addItem(output);

            if(output2.length()!=1)
            {
                int pos_coma = output2.indexOf(",");

                QString comando = "-ss "+output2.left(pos_coma)+" "+path_disco;
                proc.start(path_mfs,comando.split(" "));

                output2.replace(0,pos_coma+1,"");
            }

        }
        output = "";
    }


}

void MainWindow::on_pushButton_ir_a_abrir_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_crear_clicked()
{
    QString disco,fe,te,bloques,comando;

    disco = path_disco + ui->lineEdit_disco->text();
    fe = ui->lineEdit_FE->text();
    te = ui->lineEdit_TE->text();
    bloques = ui->lineEdit_bloques->text();
    comando = "-c "+bloques+" "+fe+" "+te+" "+disco;

    _c = 'c';
    proc.start(this->path_mfs,comando.split(" "));
}

void MainWindow::on_pushButton_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_back2_clicked()
{
    this->on_pushButton_back_clicked();
}

void MainWindow::on_pushButton_getDir_clicked()
{
    path_disco = QFileDialog::getExistingDirectory(this,tr("Abrir Disco"), "D:/OAR/graphicsMFS/debug") + "/";
}

void MainWindow::on_pushButton_abrir_clicked()
{
    if(!this->ui->lineEdit_disco2->text().isEmpty())
    {
        this->ui->stackedWidget->setCurrentIndex(3);
        path_disco = ui->lineEdit_disco2->text();

        ui->label_8->setText("Disco: " + path_disco);

        QStringList comando;
        comando << "-l" << path_disco;
        proc.start(path_mfs,comando);

    }
}

void MainWindow::mostrar_tags()
{
    QString tags;

//    for(int i=2 ; i<ui->listWidget_tags->count() ; i++)
//        ui->listWidget_tags->takeItem(i);

    /*ui->listWidget_tags->clear();

    ui->listWidget_tags->addItem("Show All Songs...");

    QFont algo("MS Shell Dlg 2",8);
    algo.setItalic(true);
    ui->listWidget_tags->item(0)->setFont(algo);

    ui->listWidget_tags->setCurrentRow(0);*/

    tags = output;
    int pos = tags.indexOf(",");

    if(pos==-1)
        return;

    QStringList temp = tags.split(",");
    for(int i=0 ; i<temp.count()-1 ; i++)
        ui->listWidget_tags->addItem(temp.at(i));

//    while(temp!="")
//    {
//        tags = tags.right(tags.indexOf(","));
//        ui->listWidget_tags->addItem(temp);
//        temp = tags.left(tags.indexOf(","));
//    }

}

void MainWindow::mostrar_songs()
{
    QString songs;
//    for(int i=1 ; i<ui->listWidget_songs->count() ; i++)
//        ui->listWidget_songs->takeItem(i);

    if(this->ui->listWidget_tags->currentRow()==1)
    {
        songs = output;

        if(songs.indexOf(",")==-1)
            return;

        QStringList temp;
        temp = songs.split(",");
        
        for(int i=0 ; i<temp.count()-1 ; i++)
        {
            QString temp2 = temp.at(i);
            if(temp2.lastIndexOf("/")==-1)
                this->ui->listWidget_songs->addItem(temp.at(i));
            else
            {
                temp2.replace(0,temp2.lastIndexOf("/")+1,"");
                ui->listWidget_songs->addItem(temp2);
            }
        }

    }
    else
    {

    }

}

void MainWindow::on_pushButton_goback3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    this->clear_songs();
    this->clear_tags();
}

void MainWindow::on_pushButton_next_page_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_previous_page_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_exec_clicked()
{
    proc.start(path_mfs,ui->lineEdit_comando->text().split(" "));

    this->ui->lineEdit_comando->clear();
}


void MainWindow::clear_songs()
{
    while(ui->listWidget_songs->count()!=1)
        for(int i=1 ; i<ui->listWidget_songs->count() ; i++)
            ui->listWidget_songs->takeItem(i);
}

void MainWindow::clear_tags()
{
    while(ui->listWidget_tags->count()!=2)
        for(int i=2 ; i<ui->listWidget_tags->count() ; i++)
            ui->listWidget_tags->takeItem(i);
    ui->listWidget_tags->setCurrentRow(0);
}


void MainWindow::on_pushButton_searSong_clicked()
{
    QString temp = QFileDialog::getOpenFileName(this,tr("Abrir Disco"),
                                                "D:/OAR/graphicsMFS/debug", tr("Archivos de musikita (*.mp3)"));
    //temp.replace(0,temp.lastIndexOf("/")+1,"");
    ui->lineEdit_mp3->setText(temp);
}

void MainWindow::on_pushButton_addSong_clicked()
{
    if(ui->lineEdit_mp3->text().isEmpty())
    {
        QMessageBox a;
        a.setText("El lineEdit del mp3 esta vacio!!!");
        a.exec();
        return;
    }
    QStringList comando;
    comando << "-a" << ui->lineEdit_mp3->text() << path_disco;

    ui->lineEdit_mp3->clear();

    _c = 'a';
    proc.start(path_mfs,comando);
}

void MainWindow::on_pushButton_export_clicked()
{
    if(ui->listWidget_songs->currentRow()==0)
    {
        QMessageBox a;
        a.setText("Seleccione un mp3 de la lista!!!");
        a.exec();
        return;
    }

    if(ui->lineEdit_mp3_exportado->text().isEmpty())
    {
        QMessageBox a;
        a.setText("El lineEdit del mp3 a exportar esta vacio!!!");
        a.exec();
        return;
    }

    QStringList comando;
    QString path = QFileDialog::getExistingDirectory(this,tr("Abrir Disco"), "/home/moises/") + "/";
    path = path+ui->lineEdit_mp3_exportado->text();
    comando << "-e" << ui->listWidget_songs->currentItem()->text() << path << path_disco;

    _c = 'e';
    proc.start(path_mfs,comando);
    ui->lineEdit_mp3_exportado->clear();
}

void MainWindow::on_pushButton_delete_clicked()
{
    if(ui->listWidget_songs->currentRow()==0)
    {
        QMessageBox a;
        a.setText("Seleccione un mp3 de la lista!!!");
        a.exec();
        return;
    }

    QStringList comando;
    QString song = ui->listWidget_songs->currentItem()->text();

    comando << "-d" << song << path_disco;

    _c = 'd';
    proc.start(path_mfs,comando);
}

void MainWindow::on_pushButton_tag_clicked()
{
    if(ui->listWidget_songs->currentRow()==0)
    {
        QMessageBox a;
        a.setText("Seleccione un mp3 de la lista!!!");
        a.exec();
        return;
    }

    if(ui->lineEdit_tag->text().isEmpty())
    {
        QMessageBox a;
        a.setText("El lineEdit del tag esta vacio!!!");
        a.exec();
        return;
    }

    QStringList comando;
    comando << "-t" << ui->lineEdit_tag->text();
    comando << ui->listWidget_songs->currentItem()->text() << path_disco;

    _c = 't';
    proc.start(path_mfs,comando);
}
