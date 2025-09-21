# ex-2.1 – Projeto Multi-Click SDL2  

## Descrição  
Este projeto implementa, usando SDL2, um sistema simples para detectar múltiplos cliques do mouse em sequência.  
O programa monitora a posição e o tempo dos cliques: cada clique consecutivo na mesma área, feito dentro de um intervalo de 250 ms, aumenta um contador interno.  
Quando há uma pausa de 250 ms sem novos cliques, considera-se que a sequência terminou e é desenhado na tela um quadrado cujo tamanho é proporcional ao número de cliques acumulados.  

## Como funciona o código  

O programa é estruturado em algumas partes principais:

- **Definições iniciais**  
  São definidos o tempo máximo entre cliques (`CLICK_TIMEOUT = 250 ms`) e o limite de quadrados que podem ser desenhados (`MAX_QUADRADOS`).

- **Estruturas de dados**  
  - `MultiClick`: guarda a quantidade de cliques, o tempo do último clique e a posição onde ele ocorreu, além de um flag para saber se estamos contando cliques.  
  - `Quadrado`: guarda as informações necessárias para desenhar cada quadrado (posição x, y e tamanho).  

- **Inicialização SDL**  
  Cria a janela e o renderer para desenhar na tela.  

- **Loop principal**  
  - Usa `SDL_WaitEventTimeout` para esperar eventos, respeitando o tempo restante do intervalo de 250 ms.  
  - Se o evento é clique do mouse, verifica se é o primeiro clique ou se está dentro do intervalo de 250 ms.  
    - Se for o primeiro clique (ou intervalo maior que 250 ms), reinicia a contagem.  
    - Se estiver dentro do tempo, incrementa a contagem de cliques.  
  - Se o tempo de 250 ms passa sem novo clique, calcula o tamanho do quadrado (número de cliques × 20), armazena-o no vetor `quadrados` e reinicia o contador.  

- **Desenho na tela**  
  - Limpa o fundo com cor branca.  
  - Percorre o vetor de quadrados e desenha todos com `SDL_RenderFillRect` usando cor roxa.  
  - Atualiza a tela com `SDL_RenderPresent`.  

- **Finalização**  
  Destroi renderer, janela e finaliza SDL quando o usuário fecha a janela.


