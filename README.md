# Desenvolvimento de um método e sistema para compilação e simulação de redes de petri para utilização em controladores lógicos industriais

<!-- TODO RESUMO -->

# Compilação

Utilizar GNU Make para compilar. Ver arquivo [Makefile](Makefile).

## Compilação rápida
```console
$ make
```

## Compilação rápida + Synctex
```console
$ make SYNC_LINE={linha arquivo .tex} SYNC_FILE={arquivo fonte .tex}
```

Obs: synctex está configurado para usar o leitor de pdf Okular.

## Compilação completa (com bibtex)
```console
$ make build
```

## Limpar ambiente
```console
$ make clear
```

# Integração com vscode

O repositório já vem com a pasta de configuração [.vscode](./.vscode/), onde está configurada a procura direta e reversa, para já sair utilizando a configuração instale:

* Leitor de pdf [Okular](https://okular.kde.org/pt-br/).
* Vscode, [Visual studio code](https://code.visualstudio.com).
* Extensão vscode, [Code Spell Checker](https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker).
* Extensão vscode, [Brazilian Portuguese - Code Spell Checker](https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker-portuguese-brazilian).
* Extensão vscode, [TexLab](https://marketplace.visualstudio.com/items?itemName=efoerster.texlab).