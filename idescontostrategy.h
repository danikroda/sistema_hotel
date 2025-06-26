#ifndef IDESCONTOSTRATEGY_H
#define IDESCONTOSTRATEGY_H

#include <QString>
#include <memory>

// Interface Strategy
class IDescontoStrategy {
public:
    virtual ~IDescontoStrategy() {}
    virtual double calcularDesconto(double valorSemDesconto) const = 0;
    virtual QString getNomeDesconto() const = 0;
};

// --- Estratégias Concretas ---

class SemDescontoStrategy : public IDescontoStrategy {
public:
    // CORREÇÃO: Comentamos o nome do parâmetro para indicar que ele não é usado.
    double calcularDesconto(double /*valorSemDesconto*/) const override { // <<< ESTA LINHA FOI CORRIGIDA
        return 0.0;
    }
    QString getNomeDesconto() const override {
        return "Sem desconto – tarifa padrão";
    }
};

class VipStrategy : public IDescontoStrategy {
public:
    double calcularDesconto(double valorSemDesconto) const override {
        return valorSemDesconto * 0.10; // 10%
    }
    QString getNomeDesconto() const override {
        return "Clientes VIP – 10% de desconto";
    }
};

class BaixaTemporadaStrategy : public IDescontoStrategy {
public:
    double calcularDesconto(double valorSemDesconto) const override {
        return valorSemDesconto * 0.20; // 20%
    }
    QString getNomeDesconto() const override {
        return "Baixa temporada – 20% de desconto";
    }
};

class FeriadoStrategy : public IDescontoStrategy {
public:
    double calcularDesconto(double valorSemDesconto) const override {
        return valorSemDesconto * 0.15; // 15%
    }
    QString getNomeDesconto() const override {
        return "Promoção de feriados específicos – 15% de desconto";
    }
};

#endif // IDESCONTOSTRATEGY_H
