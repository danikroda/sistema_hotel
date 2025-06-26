#include "dialogreserva.h"
#include "ui_dialogreserva.h"
#include <QMessageBox>
#include <QMap>
#include <QDate>

DialogReserva::DialogReserva(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReserva)
{
    ui->setupUi(this);
    ui->comboLocalidadeReserva->addItems({"Jericoacoara", "Canoa Quebrada", "Cumbuco"});
    ui->comboTipoQuartoReserva->addItems({"Solteiro", "Duplo", "Casal", "Triplo", "Quádruplo"});
    ui->comboDescontoReserva->addItems({
        "Sem desconto – tarifa padrão", "Clientes VIP – 10% de desconto",
        "Baixa temporada – 20% de desconto", "Promoção de feriados específicos – 15% de desconto"
    });
    ui->spinDiariasReserva->setMinimum(1);
    ui->textResumoReserva->setReadOnly(true);
}

DialogReserva::~DialogReserva()
{
    delete ui;
}

void DialogReserva::setAtendente(const QString &nome)
{
    nomeAtendente = nome;
}

Reserva DialogReserva::getReserva() const
{
    return this->reservaAtual;
}

void DialogReserva::on_btnReservar_clicked()
{
    if (ui->lineNomeReserva->text().isEmpty() || ui->lineCPFReserva->text().isEmpty()) {
        ui->textResumoReserva->setText("Por favor, preencha nome e CPF do cliente.");
        return;
    }

    // Seleciona a estratégia de desconto com base na escolha do usuário
    int index = ui->comboDescontoReserva->currentIndex();
    switch(index) {
    case 0: descontoStrategy = std::make_unique<SemDescontoStrategy>(); break;
    case 1: descontoStrategy = std::make_unique<VipStrategy>(); break;
    case 2: descontoStrategy = std::make_unique<BaixaTemporadaStrategy>(); break;
    case 3: descontoStrategy = std::make_unique<FeriadoStrategy>(); break;
    default: descontoStrategy = std::make_unique<SemDescontoStrategy>(); break;
    }

    QMap<QString, double> precos = {
        {"Solteiro", 100.0}, {"Duplo", 150.0}, {"Casal", 350.0},
        {"Triplo", 220.0}, {"Quádruplo", 300.0}
    };
    double valorDiaria = precos.value(ui->comboTipoQuartoReserva->currentText(), 0.0);
    double valorSemDesconto = valorDiaria * ui->spinDiariasReserva->value();

    // Usa a estratégia para calcular o valor final
    double valorFinal = valorSemDesconto - descontoStrategy->calcularDesconto(valorSemDesconto);

    // PREENCHE O OBJETO RESERVA
    reservaAtual.atendente = nomeAtendente;
    reservaAtual.nomeCliente = ui->lineNomeReserva->text();
    reservaAtual.cpfCliente = ui->lineCPFReserva->text();
    reservaAtual.localidade = ui->comboLocalidadeReserva->currentText();
    reservaAtual.dataCheckin = ui->dateCheckinReserva->date();
    reservaAtual.diarias = ui->spinDiariasReserva->value();
    reservaAtual.tipoQuarto = ui->comboTipoQuartoReserva->currentText();
    reservaAtual.valorFinal = valorFinal;
    reservaAtual.descontoAplicado = descontoStrategy->getNomeDesconto();

    // MONTA O RESUMO A PARTIR DO OBJETO
    QString resumo;
    resumo += "====== RESUMO DA RESERVA ======\n\n";
    resumo += "Atendente: " + reservaAtual.atendente + "\n\n";
    resumo += "Cliente: " + reservaAtual.nomeCliente + "\n";
    resumo += "CPF: " + reservaAtual.cpfCliente + "\n";
    resumo += "Localidade: " + reservaAtual.localidade + "\n";
    resumo += "Check-in: " + reservaAtual.dataCheckin.toString("dd/MM/yyyy") + "\n";
    resumo += "Tipo de Quarto: " + reservaAtual.tipoQuarto + "\n";
    resumo += "Número de diárias: " + QString::number(reservaAtual.diarias) + "\n\n";
    resumo += "Desconto aplicado: " + reservaAtual.descontoAplicado + "\n";
    resumo += "Valor com desconto: R$ " + QString::number(reservaAtual.valorFinal, 'f', 2) + "\n\n";
    resumo += "Status da reserva: Disponível\n";

    ui->textResumoReserva->setText(resumo);
}

void DialogReserva::on_btnConfirmar_clicked()
{
    if (this->reservaAtual.nomeCliente.isEmpty()) {
        QMessageBox::warning(this, "Atenção", "Gere um resumo clicando em 'Reservar' antes de confirmar.");
        return;
    }
    accept();
}
