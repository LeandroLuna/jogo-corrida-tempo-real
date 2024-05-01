# Jogo de corrida em tempo real (RTOS)

Este é um jogo interativo simples desenvolvido para dois jogadores, utilizando componentes de hardware como displays e LEDs para criar uma experiência de corrida divertida e competitiva. Os jogadores controlam carros virtuais, que são exibidos em um display OLED, avançando seus carros ao longo da pista com o pressionamento de botões. LEDs indicam o vencedor de cada corrida, e o resultado das corridas é apresentado no rodapé do display.

![Protótipo](https://github.com/LeandroLuna/jogo-corrida-tempo-real/assets/29809108/5b1ca472-e98e-4071-8174-84ab65fa41f5)

## Componentes

- **1x Displays OLED (128x32)**: um único display é usado para exibir ambos os carros e o progresso na corrida. A posição dos carros é atualizada em tempo real com cada pressão de botão dos jogadores.
- **2x LEDs**: um LED vermelho para o jogador dois e um LED verde para o jogador um. O LED correspondente acende para indicar o vencedor no final de cada corrida.
- **2x Botões**: cada jogador usa um botão para controlar seu carro. Cada pressão do botão avança o carro ao longo da pista no display.

## Esquemático (Wokwi)

![Esquemático](https://github.com/LeandroLuna/jogo-corrida-tempo-real/assets/29809108/2db57452-44d2-4b90-8073-012194e61727)

## Estrutura do Jogo

- **Mecânica da corrida**: os jogadores usam seus botões para avançar seus carros no display da corrida. Cada pressão do botão move seu carro uma posição para frente, sendo controlado através de tarefas separadas no FreeRTOS que monitoram os estados dos botões.
- **Condição de vitória**: a corrida é vencida pelo primeiro jogador cujo carro alcança o final da pista no display, definido pela constante `WIN_CONDITION`.
- **Sistema de pontuação**: cada corrida vencida por um jogador incrementa sua pontuação, que é exibida no mesmo display OLED. As pontuações são atualizadas em tempo real durante o jogo.
- **Indicação do vencedor**: no final de cada corrida, o LED do jogador vencedor acende. O jogo é então resetado automaticamente após um breve delay, permitindo uma nova partida.
