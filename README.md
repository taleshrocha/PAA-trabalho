# Trabalho - 3ª Unidade

Repositório contendo as especificações do Trabalho da 3ª unidade da disciplina de Grafos.

# Pastas e especificações

- ``src`` - Contém todos os arquivos ``.cpp``;
- ``include`` - Contém todos os arquivos ``.hpp``;
- ``data/in`` - Contém os arquivos com as chaves a serem inseridas, removidas ou buscadas em ordem;
- ``build`` - Contém o ``Makefile``, o binário ``calc`` e todos os outros arquivos que o ``cmake`` cria.

# Como compilar o projeto

  ```
  cmake -B build
  cmake --build build
  ```

# Como executar o projeto
  ```
  ./build/???
  ```
## Especificação
  O projeto é compilado usando as seguintes "flags" de compilação
  -g
  -Wall
  -Werror
  -Wextra
  -Wpedantic
  -ansi
  -Ofast
  -fsanitize=address,undefined
  -lm

