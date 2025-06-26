#ifndef DIALOGRESERVA_H
#define DIALOGRESERVA_H

#include <QDialog>
#include <memory> // Para usar std::unique_ptr
#include "reserva.h"
#include "idescontostrategy.h" // Inclui o cabeçalho da Strategy

namespace Ui {
class DialogReserva;
}

class DialogReserva : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReserva(QWidget *parent = nullptr);
    ~DialogReserva();
    void setAtendente(const QString &nome);
    Reserva getReserva() const;

private slots:
    void on_btnReservar_clicked();
    void on_btnConfirmar_clicked();

private:
    Ui::DialogReserva *ui;
    QString nomeAtendente;
    Reserva reservaAtual;
    // Ponteiro inteligente para a estratégia de desconto
    std::unique_ptr<IDescontoStrategy> descontoStrategy;
};

#endif // DIALOGRESERVA_H
