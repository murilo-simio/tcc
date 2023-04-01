# TCC

### [Link Overleaf](https://pt.overleaf.com/project/63dbd9dfc1673d779766c71e)

Características do dispositivo usado:
* MCU: STM32G070CBT6 or STM32G070RBT6 Arm® Cortex®-M0+ 32-bit MCU, 128 KB Flash, 36 KB RAM
* Interface de comunicação: modulo de rádio Si24R1 2.4GHz - usa interface SPI com o MCU
* Alimentação: pilha CR2032

Consumo de energia do controle:
![Alt text](imgs/consumo_keyfob.png)

---

## Conteúdos Relacionados
### ZigBee
  * O ZigBee é um padrão de comunição baseado em *Wireless Local Area Networks* (WLAN) baseado no protocolo IEEE 802.15.4, dentro da rede são definidos três tipos de nós: Coordenador, Roteador e Dispostivos de Borda. Ele é amplamente usado em aplicações de IoT por conta de seu baixo custo e complexidade além de ser bastante estável. Sua arquitetura utiliza a camada MAC e a camada física definidas pelo protocolo da IEEE enquanto as camadas de rede e de aplicação são próprias do ZigBee. 
  
    Para garantir a segurança de suas camadas o ZigBee utiliza algoritmo de criptografia simétrica AES-128. Esse algortimo faz operações em matrizes 4 x 4 com blocos de 128 bits durante 10 rodadas e dentro do ZigBee é responsável por criptografar os pacotes de entrada e criar textos de saída cifrados.

    Além disso, o protocolo conta com três tipos de chave: mestre, de rede e de enlace. As chave mestre são utlizadas para garantir a que a troca de chaves de Enlace permaneça confidencial, vem configurada de fábrica e geralmente é compartilhada entre todos os nós. A chave de enlace é usada para criptografar a troca de informação entre dois nós, é unica para cada par de nós e é gerenciada pela camada de aplicação. Já a chave de rede é utilizada para acrescentar novos nós na rede e é criada por um módulo chamado Trust Center.

    ![Arquitetura Zigbee](imgs/zigbee_arch.png)

    O protocolo ZigBee apresenta algumas fragilidades em sua segurança dependendo do nível de segurança selecionado. Entre elas está a distribuição das chaves, como todos os nós têm a chave mestre se um deles for comprometido toda a comunicação da rede não pode ser mais confiada. Outro problema de segurança está no algoritmo de criptografia utilizado, antes de iniciar a comunicação entre duas partes é preciso que elas compartilhem a chave para criptografar a conversa, com isso, um terceiro malicioso pode ter acesso a essa chave também.

    Além disso o ZigBee não garante a integridade do esquema de segurança, dependendo apenas do CRC para checar os dados de um quadro, e com isso, as mensagens podem ser facilmente adulteradas.

---

## Reunião 28/03/2023

### Pontos Discutidos

* Definido rumo do trabalho: Implementar comunicação segura entre Keyfob e Moto
* Sugestões de pesquisa: IoT Low Consumption IEEE, Bluetooth Lowpower, Zigbee
* Pesquisar os protocolos que essas soluções utilizam para manter sua comunicação segura
* Escrever ~4 parágrafos para cada uma, 2-3 explicando a solução empregada e 2 fazendo uma crítica a ela
* Texto pode ser usado como Estudos Relacionados

### Data de Entrega

- [ ] 04/04/2023

### Pesquisas

* IEEE Low Consumption
* Bluetooth Low Energy - BLE
* 6LoWPAN
* ZigBee


---