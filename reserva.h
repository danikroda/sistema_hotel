#ifndef RESERVA_H
#define RESERVA_H

#include <QString>
#include <QDate>

// Esta estrutura organiza todos os dados de uma única reserva
struct Reserva
{
    QString atendente;
    QString nomeCliente;
    QString cpfCliente;
    QString localidade;
    QDate dataCheckin;
    int diarias;
    QString tipoQuarto;
    double valorFinal;
    QString descontoAplicado;
};

#endif // RESERVA_H
