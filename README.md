# Parser_Spice
O Parser_Spice é um programa em C++ projetado para analisar e processar arquivos de netlist SPICE (Simulation Program with Integrated Circuit Emphasis). Este programa é capaz de interpretar arquivos de entrada SPICE e extrair informações relevantes do circuito, tornando-o uma ferramenta útil para simular circuitos eletrônicos.

## Introdução
O SPICE é uma ferramenta amplamente utilizada na simulação de circuitos eletrônicos, e este parser tem como objetivo simplificar o processo de leitura e interpretação de arquivos de netlist SPICE. Ele pode ser usado para diversas finalidades, como análise, simulação e teste de circuitos.

## Como Usar
Para usar o programa Parser_Spice, siga estas etapas:

Clone ou baixe o repositório para a sua máquina local.

Compile o programa usando o compilador C++ de sua preferência.

Execute o programa e forneça o arquivo de netlist SPICE como argumento:

bash
Copy code
./Parser_Spice seu_circuito.ckt
O programa irá analisar o netlist SPICE, processar os elementos do circuito e exibir os resultados.

## Elementos Suportados
O parser suporta uma ampla variedade de elementos de circuitos SPICE, incluindo:

Resistores (R)
Capacitores (C)
Indutores (L)
Fontes de tensão (V)
Fontes de corrente (I)
Fontes de corrente controladas por tensão (G, E)
Fontes de corrente controladas por corrente (F, H)
Diodos (D)
Transistores bipolares de junção (BJT - Q)
Transistores de efeito de campo de junção (JFET - J)
Transistores de efeito de campo metal-óxido-semicondutor (MOSFET - M)
Subcircuitos (.SUBCKT)
Fim de subcircuitos (.ENDS)
Chamadas de subcircuitos (X)
Configurações de opções (.OPTIONS)
Comandos de definição de nós (.NODESET)
Condições iniciais (.IC)
Análise AC (.AC)
Análise DC (.DC)
Análise de polos e zeros (.PZ)
Análise de sensibilidade (.SENS)
Análise de função de transferência (.TF)
Análise transitória (.TRAN)
Declarações de impressão (.PRINT)

## Tratamento de Erros
O parser inclui tratamento de erros para detectar e relatar vários erros de sintaxe e lógica no netlist SPICE. Ele fornece mensagens de erro informativas, incluindo números de linha e coluna, para ajudar os usuários a identificar e corrigir problemas em suas descrições de circuito.

## Contribuições
Contribuições para este projeto são bem-vindas! Se você deseja contribuir, siga estas etapas:

Faça um fork do repositório.

Crie um novo branch para sua funcionalidade ou correção de bug.

Faça suas alterações e faça commit delas com mensagens de commit claras e concisas.

Faça push das suas alterações para o seu fork.

Crie uma solicitação pull para o branch develop do repositório principal.

## Licença
Este projeto está licenciado sob a Licença MIT, o que significa que você tem a liberdade de usar e modificar o código para seus próprios fins. No entanto, revise a licença para obter detalhes completos e responsabilidades.

Obrigado por usar o Parser_Spice! Se você tiver alguma dúvida ou encontrar problemas, sinta-se à vontade para abrir uma issue no GitHub.
