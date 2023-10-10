# Trabalho - 2ª Unidade

Repositório contendo as especificações do Trabalho da 2ª unidade da disciplina de PAA.

# Pastas e especificações

- ``src`` - Contém todos os arquivos ``.cpp``;
- ``include`` - Contém todos os arquivos ``.hpp``;
- ``test-cases`` - Contém todos os casos de teste utilizados durante o trabalho;
- ``log-files`` - Contém todos os arquivos de log, ou seja, tudo que é impresso na tela também é escrito em um arquivo desta pasta;
- ``build`` - Contém o ``Makefile``, o binário ``graf`` e todos os outros arquivos que o ``cmake`` cria.

# Como compilar o projeto

  ```
  cmake -B build
  cmake --build build
  ```

# Como executar o projeto
  ```
  ./build/paa test-cases/caminho-para-o-arquivo-de-testes-desejado
  ```
## Especificação
  O projeto é compilado usando as seguintes "flags" de compilação
  -Wall
  -Werror
  -Wextra
  -Wpedantic
  -ansi
  -fsanitize=address,undefined
  -lm

