#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); // привязка textedit
    setWindowTitle("Блокнот"); // название

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered() // открытие файла
{
    bool Flag = true; // отслеживание отсутствия файла
    if(izm)// проверка на сохранение изменений
    {
        QMessageBox msg; // 3 ной мессаджбокс
        msg.setText("Вы хотите сохранить изменения?");
        msg.setWindowTitle("Блокнот");
        msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard|QMessageBox::Cancel);
        switch(msg.exec())
        {
        case QMessageBox::Save:  // кнопка сохранить и продолжить
        {
            // сохраниение
            QString filename;

            if(currentFile.isEmpty())
            {
                filename = QFileDialog::getSaveFileName(this, "Сохранить файл","C:/Users/student/Documents/177", tr("Text files(*.txt)"));
                if (filename.isEmpty())
                {
                    Flag = false;
                    // QMessageBox::information(this,"Error","Файл не выбран");
                }
                else
                {
                    currentFile = filename;
                }
            }
            else
            {
                filename = currentFile;
            }
            if (Flag){
                QFile file(filename);
                QFileInfo filenamen(filename);
                setWindowTitle(filenamen.fileName()); // название окна

                file.setFileName(filename); // связываем с файлом
                file.open(QIODevice::WriteOnly);

                file.write((ui->textEdit->toPlainText().toLocal8Bit()));//запись

                file.close();
                izm = false;
                // открытие
                QString filename2;
                filename2= QFileDialog::getOpenFileName(this,tr("Открыть файл"), "C:/Users/student/Documents/177", tr("Text files(*.txt)")); // двойной слеш или обратный

                if (filename2.isEmpty())
                {

                    //QMessageBox::information(this,"Error","Файл не выбран");
                }
                else
                {
                    currentFile = filename2;
                    ui->textEdit->clear();
                    QFile file;
                    file.setFileName(filename2); // связываем с файлом
                    file.open(QIODevice::ReadOnly);
                    QFileInfo filenamen(filename2);
                    setWindowTitle(filenamen.fileName());// название окна

                    QByteArray ba; // массив для передачи
                    long long size;
                    ba.clear();
                    size=file.size(); // размер
                    ba=file.read(size); // чтение в массив
                    ui->textEdit->append(QString(ba)); // помещаем в редактор

                    file.close();
                    izm = false;
                }
            }
        }
            break;
        case QMessageBox::Discard: // открыть без сохранения изменений
        {
            QString filename2;
            filename2= QFileDialog::getOpenFileName(this,tr("Открыть файл"), "C:/Users/student/Documents/177", tr("Text files(*.txt)")); // двойной слеш или обратный

            if(filename2.isEmpty())
            {
                //QMessageBox::information(this,"Error","Файл не выбран");
            }
            else
            {
                currentFile = filename2;
                ui->textEdit->clear();
                QFile file;
                file.setFileName(filename2); // связываем с файлом
                file.open(QIODevice::ReadOnly);
                QFileInfo filenamen(filename2);
                setWindowTitle(filenamen.fileName());// название окна

                QByteArray ba; // массив для передачи
                long long size;
                ba.clear();
                size=file.size(); // размер
                ba=file.read(size); // чтение в массив
                ui->textEdit->append(QString(ba)); // помещаем в редактор

                file.close();
                izm = false;
            }

        }
            break;


        default:

            break;

        }
    }
    // без изменений
    else
    {
        QString filename;
        filename= QFileDialog::getOpenFileName(this,tr("Открыть файл"), "C:/Users/student/Documents/177", tr("Text files(*.txt)")); // двойной слеш или обратный


        if(filename.isEmpty())
        {
            //QMessageBox::information(this,"Error","Файл не выбран");
        }
        else
        {
            currentFile = filename;
            ui->textEdit->clear();
            QFile file;
            file.setFileName(filename); // связываем с файлом
            file.open(QIODevice::ReadOnly);
            QFileInfo filenamen(filename);
            setWindowTitle(filenamen.fileName());// название окна

            QByteArray ba; // массив для передачи
            long long size;
            ba.clear();
            size=file.size(); // размер
            ba=file.read(size); // чтение в массив
            ui->textEdit->append(QString(ba)); // помещаем в редактор

            file.close();
            izm = false;
        }

    }

}

void MainWindow::on_action_Saveas_triggered() // сохранить как
{

    QString filename;
    filename= QFileDialog::getSaveFileName(this,tr("Сохранить файл"), "C:/Users/student/Documents/177", tr("Text files(*.txt)")); // двойной слеш или обратный
    if(filename.isEmpty())
    {
        //Flag = false;
        //QMessageBox::information(this,"Error","Файл не выбран");
    }
    else
    {
        QFile file;
        file.setFileName(filename); // связываем с файлом
        file.open(QIODevice::WriteOnly);

        file.write((ui->textEdit->toPlainText().toLocal8Bit()));//запись

        file.close();
        izm = false;
    }

}
void MainWindow::closeEvent(QCloseEvent *event) // изменение  евента закрытия
{
    if(izm){
        bool flag = true;
        QMessageBox msg; // 3 ной мессаджбокс
        msg.setText("Вы хотите сохранить изменения?");
        msg.setWindowTitle("Блокнот");
        msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard|QMessageBox::Cancel);
        switch(msg.exec())
        {
        case QMessageBox::Save:  // кнопка сохранить и выйти
        {
            // сохраниение
            QString filename;

            if(currentFile.isEmpty())
            {
                filename = QFileDialog::getSaveFileName(this, "Сохранить файл","C:/Users/student/Documents/177", tr("Text files(*.txt)"));
                if (filename.isEmpty())
                {
                    event->ignore();
                    // QMessageBox::information(this,"Error","Файл не выбран");
                    flag = false;
                }
                else
                {
                    currentFile = filename;
                }
            }
            else
            {
                filename = currentFile;
            }
            if(flag)
            {
            QFile file(filename);
            QFileInfo filenamen(filename);
            setWindowTitle(filenamen.fileName()); // название окна

            file.setFileName(filename); // связываем с файлом
            file.open(QIODevice::WriteOnly);

            file.write((ui->textEdit->toPlainText().toLocal8Bit()));//запись

            file.close();
            izm = false;
            }
        }
            break;
        case QMessageBox::Discard: // выйти без сохранения изменений
        {
            event->accept();

        }
            break;
       case QMessageBox::Cancel: // отмена
        {
            event->ignore();
        }
            break;

        default:

            break;

        }
    }

}
void MainWindow::on_action_create_triggered() // создание файла
{
    bool Flag = true; // отслеживание отсутствия файла
    if(izm )// проверка на сохранение изменений
    {
        QMessageBox msg; // 3 ной мессаджбокс
        msg.setText("Вы хотите сохранить изменения?");
        msg.setWindowTitle("Блокнот");
        msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard|QMessageBox::Cancel);
        switch(msg.exec())
        {
        case QMessageBox::Save:
        { // кнопка сохранить и продолжить
            QString filename;

            if(currentFile.isEmpty())
            {
                filename = QFileDialog::getSaveFileName(this, "Сохранить файл","C:/Users/student/Documents/177", tr("Text files(*.txt)"));
                if(filename.isEmpty())
                {
                    Flag = false;
                    //QMessageBox::information(this,"Error","Файл не выбран");
                }
                else
                {
                    currentFile = filename;
                }
            }
            else
            {
                filename = currentFile;
            }
            if(Flag )
            {
                QFile file(filename);
                QFileInfo filenamen(filename);
                setWindowTitle(filenamen.fileName()); // название окна

                file.setFileName(filename); // связываем с файлом
                file.open(QIODevice::WriteOnly);

                file.write((ui->textEdit->toPlainText().toLocal8Bit()));//запись

                file.close();
                izm = false;

                setWindowTitle("Блокнот");
                currentFile.clear();
                ui->textEdit->setText(QString());
                izm = false;


            }
        }
            break;
        case QMessageBox::Discard: // продолжить без сохранения
        {
            setWindowTitle("Блокнот");

            currentFile.clear();
            ui->textEdit->setText(QString());

            izm = false;


        }
            break;


        default:

            break;
        }
    }
    else
    {
        setWindowTitle("Блокнот");
        currentFile.clear();
        ui->textEdit->setText(QString());
        izm = false;
    }
}
void MainWindow::on_action_Save_triggered() // сохранение
{
    bool Flag = true;
    QString filename;

    if(currentFile.isEmpty())
    {
        filename = QFileDialog::getSaveFileName(this, "Сохранить файл","C:/Users/student/Documents/177", tr("Text files(*.txt)"));
        if(filename.isEmpty())
        {
            Flag = false;
        }


    }
    else
    {
        filename = currentFile;
    }
    if(Flag)
    {
        currentFile = filename;
        QFile file(filename);
        QFileInfo filenamen(filename);
        setWindowTitle(filenamen.fileName()); // название окна

        file.setFileName(filename); // связываем с файлом
        file.open(QIODevice::WriteOnly);

        file.write((ui->textEdit->toPlainText().toLocal8Bit()));//запись

        file.close();
        izm = false;
    }
}
void MainWindow::on_action_exit_triggered() // кнопка выхода
{
    QWidget::close();
}

void MainWindow::on_textEdit_textChanged()// отслеживание изменени текста
{
    izm = true;
}



