#ifndef GERENCIADORRESERVAS_H
#define GERENCIADORRESERVAS_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include <algorithm>
#include "reserva.h"

class GerenciadorReservas
{
public:
    // Método estático para obter a única instância da classe
    static GerenciadorReservas* getInstance();

    // Funções para gerenciar as reservas
    void adicionarReserva(const Reserva &reserva);
    const QList<Reserva>& getListaReservas() const;
    void salvarReservasEmArquivo(const QString &nomeArquivo = "reservas.txt");

private:
    // Construtor, operador de cópia e de atribuição privados para garantir o padrão Singleton
    GerenciadorReservas();
    GerenciadorReservas(const GerenciadorReservas&) = delete;
    void operator=(const GerenciadorReservas&) = delete;

    QList<Reserva> listaReservas;
};

#endif // GERENCIADORRESERVAS_H
