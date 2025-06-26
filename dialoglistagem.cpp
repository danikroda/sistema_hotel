#include "dialoglistagem.h"
#include "ui_dialoglistagem.h"

Dialoglistagem::Dialoglistagem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoglistagem)
{
    ui->setupUi(this);
    ui->textBrowserListagem->setReadOnly(true);
}

Dialoglistagem::~Dialoglistagem()
{
    delete ui;
}

void Dialoglistagem::setReservas(const QList<Reserva> &reservas)
{
    if (reservas.isEmpty()) {
        ui->textBrowserListagem->setText("Nenhuma reserva foi feita ainda.");
        return;
    }

    QString textoCompleto;
    for (const Reserva &reserva : reservas) {
        // Para cada objeto Reserva na lista, cria um resumo em texto
        textoCompleto += "====== RESUMO DA RESERVA ======\n";
        textoCompleto += "Atendente: " + reserva.atendente + "\n";
        textoCompleto += "Cliente: " + reserva.nomeCliente + "\n";
        textoCompleto += "CPF: " + reserva.cpfCliente + "\n";
        textoCompleto += "Localidade: " + reserva.localidade + "\n";
        textoCompleto += "Check-in: " + reserva.dataCheckin.toString("dd/MM/yyyy") + "\n";
        textoCompleto += "Check-out: " + reserva.dataCheckin.addDays(reserva.diarias).toString("dd/MM/yyyy") + "\n";
        textoCompleto += "Tipo de Quarto: " + reserva.tipoQuarto + "\n";
        textoCompleto += "Valor Final: R$ " + QString::number(reserva.valorFinal, 'f', 2) + "\n";
        textoCompleto += "===================================\n\n";
    }
    ui->textBrowserListagem->setText(textoCompleto);
}
