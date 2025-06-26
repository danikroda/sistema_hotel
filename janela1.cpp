#include "janela1.h"
#include "ui_janela1.h"
#include <QMessageBox>
#include "dialogconsulta.h"
#include "dialogreserva.h"
#include "dialoglistagem.h"
#include "gerenciadorreservas.h" // Inclui o nosso Singleton

Janela1::Janela1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Janela1)
{
    ui->setupUi(this);
}

Janela1::~Janela1()
{
    delete ui;
}

void Janela1::setAtendente(const QString &nome)
{
    nomeAtendente = nome;
    ui->labelAtendente->setText("Atendente: " + nome);
}

// Este método é chamado automaticamente quando a janela é fechada
void Janela1::closeEvent(QCloseEvent *event)
{
    // Chama o método para salvar as reservas antes de fechar
    GerenciadorReservas::getInstance()->salvarReservasEmArquivo();
    QDialog::closeEvent(event); // Continua o processo normal de fechamento
}

void Janela1::on_btnConsultar_clicked()
{
    DialogConsulta dialog(this);
    dialog.setAtendente(nomeAtendente);
    // Busca a lista de reservas do Gerenciador central
    dialog.setListaReservas(GerenciadorReservas::getInstance()->getListaReservas());
    dialog.exec();
}

void Janela1::on_btnEncaminhaReservar_clicked()
{
    DialogReserva reservaDialog(this);
    reservaDialog.setAtendente(nomeAtendente);

    if (reservaDialog.exec() == QDialog::Accepted) {
        Reserva novaReserva = reservaDialog.getReserva();
        // Adiciona a nova reserva através do Gerenciador central
        GerenciadorReservas::getInstance()->adicionarReserva(novaReserva);
        QMessageBox::information(this, "Sucesso", "Reserva adicionada à lista central!");
    }
}

void Janela1::on_btnListar_clicked()
{
    Dialoglistagem dialogDeListagem(this);
    // Busca a lista de reservas do Gerenciador central
    dialogDeListagem.setReservas(GerenciadorReservas::getInstance()->getListaReservas());
    dialogDeListagem.exec();
}

void Janela1::on_btnSair_clicked()
{
    close(); // O método close() irá disparar o closeEvent, salvando os dados.
}
