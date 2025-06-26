#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "janela1.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelResultado->clear();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    QString usuario = ui->lineEditCadastro->text();
    QString senha = ui->lineEditSenha->text();

    QMap<QString, QString> loginsValidos;
    loginsValidos["atendente1"] = "senha1";
    loginsValidos["atendente2"] = "senha2";
    loginsValidos["atendente3"] = "senha3";
    loginsValidos["atendente4"] = "senha4";

    if (loginsValidos.contains(usuario) && loginsValidos[usuario] == senha) {
        ui->labelResultado->setText("Login bem-sucedido!");

        Janela1 *janela = new Janela1();
        janela->setAttribute(Qt::WA_DeleteOnClose); // BOA PRÁTICA: Deleta a janela ao fechar
        janela->setAtendente(usuario);
        janela->show();

        this->close();
    } else {
        ui->labelResultado->setText("Usuário ou senha incorretos.");
    }
}
