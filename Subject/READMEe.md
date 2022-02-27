# 42-LabsNEWS

![Cpia de NEWS LOWER THIRDS - Feito com PosterMyWall](https://user-images.githubusercontent.com/87132928/155868696-7dd870d3-6d6f-41d4-a067-4a0ba9f51c2c.jpg)


## Descrição
<br>
Neste projeto desenvolvi em C uma API que segue o modelo de arquitetura REST, ele é um portal de noticias que retorna informações sobre alguns tópicos (covid, finanças, tech, clima). Além disso contrui uma aplicação(CLI) que consome e organiza os logs da API, nos mostrando a quantidade de requisições para cada rota e o metódo utilizado.

---

## Instalação
<br>

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
É Preciso criar os executaveis da API e também do CLI, você pode fazer isso realizando os seguintes comandos:

```
$ make server
$ make cli
```

---

## Como utilizar:
<br>

### API

Para executar a API basta usar o seguinte comando: 

```
$ ./API
```
Após isso ela vai estar pronta para receber requisições.

![2022-02-26-22-08-57](https://user-images.githubusercontent.com/87132928/155864552-726b1f98-6ac3-44bc-9b55-26e00528862a.gif)
<br>
<br>
### CLI

Para executar o CLI basta usar o seguinte comando: 
```
$ ./CLI_
```
O resultado te trará uma tabela com as informações dos LOGS referentes as requisições da API.
<br>
<br>
![image](https://user-images.githubusercontent.com/87132928/155869476-d3654c0c-f9d1-4457-8ec4-e0df34a36918.png)
<br>
<br>
### Requisições

Está API trabalha com cinco rotas diferentes sendo elas:
* / = retorna uma string informando os tópicos abordados na API
* /weather = retorna dados sobre o clima em SP
* /tech = retorna notícias sobre o universo tech
* /covid = retorna dados sobre o covid em SP
* /finance = retorna dados sobre as ações da B3 

Voce pode testa-las usando o seu browser ou softwares dedicados como o Postman ou o Insomnia.
<br>
É importante afirmar que o formato de retorno sempre vão ser em .JSON
  
![2022-02-27-01-07-23](https://user-images.githubusercontent.com/87132928/155867981-ec21c21d-9627-4710-9404-576aaa6dcbc8.gif)

<br>

---

<br>

## Como o projeto foi feito?
<br>
Bom o primeiro passo deste projeto e de alguma forma estabelecer uma conexão HTTP para assim conseguir receber as requisições, existem diversas maneiras de isso ser feito no meu caso eu optei em usar a biblioteca "Mongoose", a maior vantagem e desvatagem do Mongoose é ser simples por um lado o uso dele e extremamente intuitivo e tem uma documentação robusta no outro falta algumas ferramentas, usei o modelo "minimo servidor HTTP" como base para o meu projeto.
<br>
<br>

![image](https://user-images.githubusercontent.com/87132928/155896050-eff80eaf-932f-475c-9e8f-26cf15ee5bb3.png)

A partir disso comecei a explorar algumas funcionalidades do Mongoose, dentro do fn (manipulador de eventos) disse que toda vez que for recebido uma mensagem a função compara a mesma a alguma rota ja estabelecida e a partir disso retorna a mensagem em formato .JSON dependendo da rota escolhida. Apos isso ele ainda escreve uma mensagem de log em um arquivo, o resultado ficou assim :