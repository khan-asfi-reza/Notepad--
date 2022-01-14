#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    this->setWindowTitle("Notepad--");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    // Create a new file
    currentFile.clear();
    ui->textEdit->setText(QString());
}




void MainWindow::on_actionOpen_triggered()
{
    // Open a new text file
    QString filename = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot Open File: " + file.errorString());
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

}


void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as", "Text Files (*.txt)");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save File: " + file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    isSaved = true;
    QString title = "Notepad--";
    if(currentFile != ""){
        title = currentFile;
    }
    setWindowTitle(title);
}

void MainWindow::on_actionSave_triggered()
{
    if(currentFile != ""){
        QFile file(currentFile);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "Warning", "Cannot save File: " + file.errorString());
            return;
        }
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
        isSaved = true;
        QString title = "Notepad--";
        if(currentFile != ""){
            title = currentFile;
        }
        setWindowTitle(title);
    }else{
        MainWindow::on_actionSave_As_triggered();
    }
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer");
    QPrintDialog printerDialog(&printer, this);
    if(printerDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot access printer");
        return;
    }
    ui->textEdit->print(&printer);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}



void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_textEdit_textChanged()
{
    isSaved = false;
    QString title = "Notepad-- *";
    if(currentFile != ""){
        title = currentFile + "*";
    }
    setWindowTitle(title);
}

