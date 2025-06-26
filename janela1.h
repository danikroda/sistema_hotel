#ifndef JANELA1_H
#define JANELA1_H

#include <QDialog>
#include <QCloseEvent> // Incluído para o evento de fechar a janela

// Não precisa mais de <QList> ou "reserva.h" aqui

namespace Ui {
class Janela1;
}

class Janela1 : public QDialog
{
    Q_OBJECT

public:
    explicit Janela1(QWidget *parent = nullptr);
    ~Janela1();

    void setAtendente(const QString &nome);

protected:
    // Sobrescreve o evento de fechamento para salvar as reservas
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_btnConsultar_clicked();
    void on_btnListar_clicked();
    void on_btnSair_clicked();
    void on_btnEncaminhaReservar_clicked();

private:
    Ui::Janela1 *ui;
    QString nomeAtendente;
    // A lista de reservas foi removida daqui para ser centralizada no Singleton
};

#endif // JANELA1_H
