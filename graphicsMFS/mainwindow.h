#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QString>
#include <QStringList>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>
#include <QListWidgetItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    char _c;
    QProcess proc;
    QString output,output2,path_disco;
    int valor_del_return;
    QString path_mfs;

private slots:
    void on_pushButton_tag_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_export_clicked();
    void on_pushButton_addSong_clicked();
    void on_pushButton_searSong_clicked();
    void on_pushButton_exec_clicked();
    void on_pushButton_previous_page_clicked();
    void on_pushButton_next_page_clicked();
    void on_pushButton_goback3_clicked();
    void on_pushButton_abrir_clicked();
    void on_pushButton_getDir_clicked();
    void on_pushButton_back2_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_crear_clicked();
    void on_pushButton_ir_a_abrir_clicked();
    void on_cmdExec_finish(int a);
    void on_cmdExec_data_available();
    void on_pushButton_ir_a_crear_clicked();
    void on_pushButton_getopen_clicked();
    void on_listWidget_tags_currentRowChanged(int currentRow);
    void mostrar_tags();
    void mostrar_songs();
    void clear_tags();
    void clear_songs();
};

#endif // MAINWINDOW_H
