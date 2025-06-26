#include "dialogconsulta.h"
#include "ui_dialogconsulta.h"
#include <QMessageBox>

DialogConsulta::DialogConsulta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConsulta)
{
    ui->setupUi(this);

    ui->comboLocalidade->addItems({"Jericoacoara", "Canoa Quebrada", "Cumbuco"});
    ui->comboTipoQuarto->addItems({"Solteiro", "Duplo", "Casal", "Triplo", "Quádruplo"});
    ui->spinDiarias->setMinimum(1);
    ui->textResumo->setReadOnly(true);
}

DialogConsulta::~DialogConsulta()
{
    delete ui;
}

void DialogConsulta::setAtendente(const QString &nome)
{
    nomeAtendente = nome;
}

// NOME CORRIGIDO
void DialogConsulta::setListaReservas(const QList<Reserva> &reservas)
{
    // NOME CORRIGIDO
    this->listaReservas = reservas;
}

void DialogConsulta::on_btnConsultarDisponibilidade_clicked()
{
    QString localidadeConsulta = ui->comboLocalidade->currentText();
    QString tipoQuartoConsulta = ui->comboTipoQuarto->currentText();
    QDate dataCheckinConsulta = ui->dateCheckin->date();
    int diariasConsulta = ui->spinDiarias->value();
    QDate dataCheckoutConsulta = dataCheckinConsulta.addDays(diariasConsulta);

    bool disponivel = true;
    QString motivoIndisponibilidade;

    // NOME CORRIGIDO
    for (const Reserva &reservaExistente : listaReservas) {
        if (reservaExistente.localidade == localidadeConsulta &&
            reservaExistente.tipoQuarto == tipoQuartoConsulta)
        {
            QDate dataCheckoutExistente = reservaExistente.dataCheckin.addDays(reservaExistente.diarias);

            if (dataCheckinConsulta < dataCheckoutExistente && dataCheckoutConsulta > reservaExistente.dataCheckin) {
                disponivel = false;
                motivoIndisponibilidade = "O quarto já está reservado neste período por " + reservaExistente.nomeCliente + ".";
                break;
            }
        }
    }

    QString mensagem;
    if (disponivel) {
        mensagem =  "✅ Quarto disponível!\n\n";
        mensagem += "Atendente: " + nomeAtendente + "\n\n";
        mensagem += "📍 Localidade: " + localidadeConsulta + "\n";
        mensagem += "🛏️ Tipo de Quarto: " + tipoQuartoConsulta + "\n";
        mensagem += "📅 Check-in: " + dataCheckinConsulta.toString("dd/MM/yyyy") + "\n";
        mensagem += "🕒 Número de diárias: " + QString::number(diariasConsulta);
    } else {
        mensagem =  "❌ Quarto Indisponível!\n\n";
        mensagem += "Atendente: " + nomeAtendente + "\n\n";
        mensagem += motivoIndisponibilidade + "\n";
    }

    ui->textResumo->setPlainText(mensagem);
}
