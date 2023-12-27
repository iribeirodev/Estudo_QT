#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_triggered()
{
    QString filtro = "Todos Arquivos (*.*) ;; Arquivos de text (*.txt)";
    QString nome_arquivo = QFileDialog::getOpenFileName(this, "Abrir", QDir::homePath(), filtro);
    QFile arquivo(nome_arquivo);
    local_arquivo = nome_arquivo;

    if (!arquivo.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "", "Arquivo não pode ser aberto.");
        return;
    }

    QTextStream entrada(&arquivo);
    QString texto = entrada.readAll();
    ui->textEdit->setText(texto);
    arquivo.close();
}


void MainWindow::on_actionNovo_triggered()
{
    local_arquivo = "";
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}


void MainWindow::on_actionSalvar_Como_triggered()
{
    QString filtro = "Todos Arquivos (*.*) ;; Arquivos de text (*.txt)";
    QString nome_arquivo = QFileDialog::getSaveFileName(this, "Salvar Como", QDir::homePath(), filtro);
    QFile arquivo(nome_arquivo);
    local_arquivo = nome_arquivo;

    if (!arquivo.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "", "Arquivo não pode ser gravado.");
        return;
    }

    QTextStream saida(&arquivo);
    QString texto = ui->textEdit->toPlainText();
    saida << texto;

    arquivo.flush();
    arquivo.close();
}


void MainWindow::on_actionSalvar_triggered()
{
    QFile arquivo(local_arquivo);

    if (!arquivo.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "", "Arquivo não pode ser gravado.");
        return;
    }

    QTextStream saida(&arquivo);
    QString texto = ui->textEdit->toPlainText();
    saida << texto;

    arquivo.flush();
    arquivo.close();
}


void MainWindow::on_actionFechar_triggered()
{
    close();
}


void MainWindow::on_actionCopiar_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionRecortar_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionColar_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionDesfazer_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRefazer_triggered()
{
    ui->textEdit->redo();
}

