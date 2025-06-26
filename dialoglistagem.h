#ifndef DIALOGLISTAGEM_H
#define DIALOGLISTAGEM_H

#include <QDialog>
#include <QList>      // Usa QList
#include "reserva.h" // Inclui a estrutura

namespace Ui {
class Dialoglistagem;
}

class Dialoglistagem : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoglistagem(QWidget *parent = nullptr);
    ~Dialoglistagem();

    void setReservas(const QList<Reserva> &reservas); // Recebe uma lista de objetos Reserva

private:
    Ui::Dialoglistagem *ui;
};

#endif // DIALOGLISTAGEM_H
