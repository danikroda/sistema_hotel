#include "gerenciadorreservas.h"
#include <QDebug> // Para depuração, se necessário

// Não precisamos mais de <QTextCodec> ou <QTextStream>

GerenciadorReservas* GerenciadorReservas::getInstance()
{
    static GerenciadorReservas instancia;
    return &instancia;
}

GerenciadorReservas::GerenciadorReservas()
{
}

void GerenciadorReservas::adicionarReserva(const Reserva &reserva)
{
    listaReservas.append(reserva);
}

const QList<Reserva>& GerenciadorReservas::getListaReservas() const
{
    return listaReservas;
}

// ===================================================================
// MÉTODO DE SALVAMENTO CORRIGIDO E SIMPLIFICADO
// ===================================================================
void GerenciadorReservas::salvarReservasEmArquivo(const QString &nomeArquivo)
{
    if (listaReservas.isEmpty()) {
        return;
    }

    // Ordena a lista de reservas pela data de check-in
    std::sort(listaReservas.begin(), listaReservas.end(), [](const Reserva &a, const Reserva &b) {
        return a.dataCheckin < b.dataCheckin;
    });

    // 1. Monta todo o conteúdo do arquivo em uma única string
    QString conteudoCompleto;
    for (const Reserva &reserva : listaReservas) {
        conteudoCompleto += "====== RESUMO DA RESERVA ======\n";
        conteudoCompleto += "Atendente: " + reserva.atendente + "\n";
        conteudoCompleto += "Cliente: " + reserva.nomeCliente + "\n";
        conteudoCompleto += "CPF: " + reserva.cpfCliente + "\n";
        conteudoCompleto += "Localidade: " + reserva.localidade + "\n";
        conteudoCompleto += "Check-in: " + reserva.dataCheckin.toString("dd/MM/yyyy") + "\n";
        conteudoCompleto += "Check-out: " + reserva.dataCheckin.addDays(reserva.diarias).toString("dd/MM/yyyy") + "\n";
        conteudoCompleto += "Tipo de Quarto: " + reserva.tipoQuarto + "\n";
        conteudoCompleto += "Valor Final: R$ " + QString::number(reserva.valorFinal, 'f', 2) + "\n";
        conteudoCompleto += "===================================\n\n";
    }

    QFile arquivo(nomeArquivo);
    // Abre o arquivo em modo de escrita
    if (arquivo.open(QIODevice::WriteOnly))
    {
        // 2. Converte a string para o formato de bytes UTF-8
        QByteArray dadosEmUtf8 = conteudoCompleto.toUtf8();

        // 3. Escreve os bytes diretamente no arquivo
        arquivo.write(dadosEmUtf8);

        // 4. Fecha o arquivo
        arquivo.close();
    }
    else
    {
        // Opcional: Adiciona uma mensagem de erro se não conseguir abrir o arquivo
        qWarning() << "Não foi possível abrir o arquivo para escrita:" << nomeArquivo;
    }
}
