# Snake Game

## INSTITUIÇÃO:

* CESAR School

## DISCIPLINA:

* Programação Imperativa e Funcional - 2024.2.

## GRUPO

* JOÃO ANTÔNIO SAMPAIO FERREIRA [@JoaoAntonioSampaioFerreira](https://github.com/JoaoAntonioSampaioFerreira)
* JOSE JORGE DA SILVA DIAS [@JJorgeD](https://github.com/JJorgeD)
* ANDRÉ BURLE COSENTINO [@burle777](https://github.com/burle777)


Este é um jogo clássico da cobrinha desenvolvido em C, para ser jogado no terminal.

## Como Compilar e Executar

1. **Navegue até o diretório do seu projeto**:
    ```bash
    cd ~/snakegame
    ```

2. **Compile todos os arquivos `.c` na pasta `src`**:
    ```bash
    gcc ./src/*.c -I./include -o cli-lib-example
    ```

3. **Execute o jogo compilado**:
    ```bash
    ./cli-lib-example
    ```

## Descrição do Jogo

O objetivo do jogo é controlar a cobra para comer a comida (`*`) que aparece em posições aleatórias no campo. Toda vez que a cobra come a comida, ela cresce em tamanho. O jogo termina quando a cobra bate nas bordas do campo ou em si mesma.

### Controles

- **W**: Mover para cima
- **A**: Mover para a esquerda
- **S**: Mover para baixo
- **D**: Mover para a direita
- **Q**: Sair do jogo

## Como Jogar

1. Compile e execute o jogo seguindo as instruções acima.
2. Use as teclas de controle para mover a cobra e comer a comida.
3. Evite bater nas paredes ou em si mesmo para não acabar o jogo.
4. Pressione `Q` a qualquer momento para sair do jogo.
