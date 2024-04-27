# Jogo de corrida em Tempo Real

Jogo interativo simples desenvolvido para dois jogadores, utilizando componentes de hardware mínimos para criar uma experiência de corrida divertida e competitiva. Os jogadores controlam carros virtuais exibidos em um LCD digital, manipulando seu movimento com o pressionamento de botões. Um segundo display mantém o placar enquanto LEDs indicam o vencedor da corrida.

## Componentes

- **2x Displays**: um display é usado para a visualização da corrida, onde o progresso de cada jogador é mostrado. O segundo display é usado para manter o placar, atualizando em tempo real durante o jogo.
- **2x LEDs**: cada LED corresponde a um jogador. O LED acende para indicar o vencedor no final de cada corrida.
- **2x Botões**: cada jogador usa um botão para controlar seu carro. Cada pressão do botão avança o carro ao longo da pista no display.

## Estrutura do Jogo

- **Mecânica da corrida**: os jogadores usam seus botões para avançar seus carros no display da corrida. Cada pressão do botão move seu carro uma posição para frente.
- **Condição de vitória**: a corrida é vencida pelo primeiro jogador cujo carro alcança o final da pista no display.
- **Sistema de pontuação**: cada corrida vencida por um jogador incrementa sua pontuação no display de placar.
- **Indicação do vencedor**: no final de cada corrida, o LED do jogador vencedor acende para indicar claramente o ganhador.