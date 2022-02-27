# Students API

## Descrição

    Neste projeto desenvolvi em C uma API que segue o modelo de arquitetura REST, ele é um portal de noticias que retorna informações sobre alguns tópicos (covid, finanças, tech, clima).

<h1></h1>

## Instalação

### 1º Passo: Pré-requisitos 
É necessario ter a biblioteca Libcurl, ela geralmente não vem instalada por padrão na maioria dos sistemas. No entanto, você pode obte-lá usando:
```
$ sudo apt-get install libcurl4-gnutls-dev
```

### 2º Passo: Clonar o repósitorio e entrar no diretório:

```
$ git clone https://github.com/42sp/42labs-selection-process-v2-edubona8.git 42-labs
$ cd 42-labs
```
### 3º Passo: Criar os executaveis do programa:
É Preciso criar os executaveis da API e também do CLI, voce pode fazer isso realizando os seguintes comandos:

```
$ make server
$ make cli
```

<h1></h1>

## Como utilizar:

### API

Para executar a API basta usar o seguinte comando: 

```
$ ./API
```
Após isso ela vai estar pronta para receber requisições.

https://user-images.githubusercontent.com/87132928/155864262-8c1b546b-8f31-4909-abc9-c3d8c7b777b9.gif

### CLI

Para executar a API basta usar o seguinte comando: 

```
$ ./CLI_
```
O resultado te trará uma tabela com as informações dos LOGS da API.



