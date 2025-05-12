#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>// библиотека для работы с файлами
#include <QMessageBox>
#include <QCloseEvent>
#include <QDir>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_open_triggered();

    void on_action_Saveas_triggered();

    void closeEvent(QCloseEvent *event); // изменяем обработчик создания файла

    void on_action_create_triggered();

    void on_action_Save_triggered();

    void on_action_exit_triggered();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QString currentFile; // открытый файл
    bool izm = false; // несохраненные изменения файла


};

#endif // MAINWINDOW_H
