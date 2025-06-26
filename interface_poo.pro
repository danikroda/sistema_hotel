#-------------------------------------------------
# Arquivo de Projeto Qt - Versão Completa e Corrigida
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++17

# Você pode mudar "seu_projeto_final" para o nome que preferir
TARGET = seu_projeto_final


# ===================================================================
# SEÇÃO MAIS IMPORTANTE: A LISTA DE ARQUIVOS
# ===================================================================

# Lista de todos os arquivos de código-fonte (.cpp) do projeto
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    janela1.cpp \
    dialogreserva.cpp \
    dialogconsulta.cpp \
    dialoglistagem.cpp \
    gerenciadorreservas.cpp

# Lista de todos os arquivos de cabeçalho (.h) do projeto
HEADERS += \
    mainwindow.h \
    janela1.h \
    reserva.h \
    dialogreserva.h \
    dialogconsulta.h \
    dialoglistagem.h \
    gerenciadorreservas.h
    idescontostrategy.h

# Lista de todos os arquivos de interface (.ui) do projeto
FORMS += \
    mainwindow.ui \
    janela1.ui \
    dialogreserva.ui \
    dialogconsulta.ui \
    dialoglistagem.ui
