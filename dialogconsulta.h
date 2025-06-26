#ifndef DIALOGCONSULTA_H
#define DIALOGCONSULTA_H

#include <QDialog>
#include <QList>
#include "reserva.h"

namespace Ui {
class DialogConsulta;
}

class DialogConsulta : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConsulta(QWidget *parent = nullptr);
    ~DialogConsulta();

    void setAtendente(const QString &nome);
    void setListaReservas(const QList<Reserva> &reservas); // NOME CORRIGIDO

private slots:
    void on_btnConsultarDisponibilidade_clicked();

private:
    Ui::DialogConsulta *ui;
    QString nomeAtendente;
    QList<Reserva> listaReservas; // NOME CORRIGIDO
};

#endif // DIALOGCONSULTA_H
