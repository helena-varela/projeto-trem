# Simulação de Trens Multithreaded em C++/Qt5

Este projeto consiste em uma aplicação gráfica interativa desenvolvida em C++ utilizando o framework Qt5 no Ubuntu Linux. O objetivo é simular a movimentação concorrente e síncrona de 6 trens operando sobre uma malha ferroviária composta por 9 regiões críticas compartilhadas, aplicando conceitos fundamentais de sistemas operacionais como Threads, Exclusão Mútua (Mutexes) e Prevenção de Deadlocks.

## 🛠️ Funcionalidades
- Execução Paralela (Threads): Cada um dos 6 trens é executado em uma thread independente (QThread), garantindo sincronização e movimentação contínua em tempo real.
- Controle Dinâmico de Velocidade:
  - 6 Sliders Individuais: Permitem ajustar a velocidade de cada trem de forma independente em uma escala de $0$ (trem totalmente parado) até $200$ (velocidade máxima).
  - 1 Slider Mestre: Ajusta simultaneamente a velocidade e a posição gráfica de todos os sliders da interface.
- Movimentação Anti-Horária: Todos os trens realizam trajetórias retangulares pré-definidas no sentido anti-horário.
- Exclusão Mútua e Prevenção de Deadlocks: Utilização de QMutex para impedir colisões e garantir que nenhum impasse (deadlock) ocorra na malha.

## 🛡️ Prevenção de Deadlocks
Para evitar a ocorrência de espera circular nas zonas de interseção entre os trilhos, o projeto adota a estratégia de Hierarquia de Recursos (Ordem Global de Lock):
1. As 9 regiões críticas são associadas a 9 mutexes globais (mutex1 a mutex9).
2. Sempre que um trem precisa transitar por um trecho compartilhado que envolve múltiplas regiões, ele deve obrigatoriamente solicitar os mutexes em ordem numérica estritamente crescente ($1 \rightarrow 2 \rightarrow \dots \rightarrow 9$).
3. Mesmo que a trajetória do trem passe por uma região de número maior antes de uma menor, a thread realiza a reserva antecedente na ordem crescente de IDs. Isso quebra a condição de espera circular, garantindo a execução contínua da simulação sem travamentos eternos.

## ⚙️ Como Compilar e Executar
Pré-requisitosCertifique-se de ter as ferramentas de compilação do C++ e as bibliotecas do Qt5 instaladas no Ubuntu:
```bash
sudo apt update
sudo apt install build-essential qtbase5-dev qttools5-dev-tools qtcreator
```

### Compilação via Terminal
1. Navegue até a pasta do projeto:
```bash
cd ~/projeto-trem
```

2. Gere o Makefile e compile a aplicação:
```bash
qmake Trem.pro
make clean
make
```

3. Execute o programa:
```bash
./Trem
```

Nota para ambiente GNOME/Wayland: 
Caso haja inconformidade com temas GTK ao executar diretamente pelo terminal, utilize o estilo Fusion:
```bash
QT_STYLE_OVERRIDE=fusion QT_QPA_PLATFORMTHEME=generic ./Trem
```

### Execução via Qt CreatorAbra o Qt Creator.
1. Clique em Open Project e selecione o arquivo Trem.pro.
2. Selecione o kit Desktop Qt 5 e clique em Configure Project.
3. Pressione Ctrl + R (ou clique no ícone do Play verde) para compilar e rodar a simulação.