# Jogo da Forca em C 🎮 
Um jogo da Forca executado no terminal, desenvolvido em linguagem C como exercício de aprendizagem e posteriormente revisado para praticar validação de entradas, manipulação de arquivos e organização de código.

## Sobre o projeto
Este projeto começou como um exercício realizado durante um curso da Alura, com o objetivo de praticar conceitos fundamentais da linguagem C. A partir da proposta inicial, o código foi revisado para melhorar a experiência de jogo, tratar entradas inválidas e simplificar a manutenção do banco de palavras. O projeto também serve como registro do meu processo de aprendizagem em programação e da evolução de um exercício introdutório para uma aplicação com validações adicionais.

## Funcionalidades:
- Sorteio de uma palavra a partir de um arquivo externo.
- Registro de letras tentadas.
- Identificação de letras corretas e incorretas.
- Exibição gráfica da forca no terminal.
- Verificação das condições de vitória e derrota.
- Inclusão de novas palavras no banco de dados.
- Validação das entradas e prevenção de tentativas repetidas.

## Tecnologias e conceitos:
- Linguagem C.
- Entrada e saída de dados com `stdio.h`.
- Manipulação de strings.
- Arrays e funções.
- Leitura e escrita de arquivos.
- Geração de números pseudoaleatórios.
- Validação de entradas e tratamento de erros.

## Estrutura dos arquivos:
- `forca.c`: implementação do jogo.
- `palavras.txt`: banco de palavras, com uma palavra por linha.
O projeto foi mantido em um único arquivo de código-fonte para preservar sua simplicidade e facilitar o estudo de suas funções.

## Melhorias em relação à versão inicial:
- Prevenção de chutes repetidos.
- Normalização de letras para maiúsculas.
- Validação do comprimento e dos caracteres das palavras.
- Verificação de falhas na abertura e leitura de arquivos.
- Simplificação do banco de palavras, eliminando o contador manual.
- Organização das funções e inclusão de comentários explicativos.

## Limitações conhecidas:
Nesta versão, o jogo aceita apenas letras de A a Z, sem acentos, espaços ou caracteres especiais. O tratamento de palavras acentuadas e de entradas internacionais poderá ser implementado em uma versão futura.

## Origem e créditos:
O projeto tem como ponto de partida um exercício de curso da Alura. As modificações e melhorias serão documentadas neste repositório, preservando a transparência sobre a origem do código e o processo de aprendizagem.
