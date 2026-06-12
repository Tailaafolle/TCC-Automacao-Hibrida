# Desenvolvimento de Sistema de Automação Residencial Híbrido

Repositório contendo os códigos-fonte do projeto de Trabalho de Conclusão de Curso (TCC) em Ciência da Computação (Atitus Educação).

# Tecnologias Utilizadas
* **Arduino Uno:** Controle lógico central, display LCD, motor de passo e decodificação infravermelha.
* **ESP-01 (ESP8266):** Coprocessador de rede Wi-Fi e integração WebSockets.
* **SinricPro & Amazon Alexa:** Middleware IoT e interface de comando por voz.
* **C++:** Linguagem utilizada no firmware.

# Estrutura do Projeto
* `/Codigo_Arduino` -> Contém a lógica de controle da porta, debounce do sensor de som e validação da senha IR.
* `/Codigo_ESP01` -> Contém a conexão Wi-Fi e a ponte serial com o SinricPro.

# Autores
* Taila Folle
* Thaísa Leal da Silva (Orientadora)
