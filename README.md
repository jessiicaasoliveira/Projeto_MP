# Projeto Final da disciplina Métodos de Programação

Professor: Jan Correa

Integrantes grupo:          Matrícula:

- Amanda Aline Figueiredo Carvalho    15/0115997
- Bruno Justino Garcia Praciano       13/0006912               
- Jéssica da Silva Oliveira           13/0028983

Data de Entrega do Projeto: 02/12/2018

Comandos para compilação do programa:

- Ir para diretório /src do trabalho

- Para compilar o jogo, ir para o terminal e  digitar o comando `make` ou `make main`

- Para compilação do módulo de teste CUnit, ir para o terminal, instalar o CUnit e  digitar o comando `make Tests`

- Digite `./Tests` para execução do CUnit

- Instale o Splint e digite `make splint` para a execução do Splint

- Aumente a janela do terminal para ficar do tamanho da tela do computador e digite o comando `./main` no terminal

- Ao executar o jogo você será apresentado a um menu que possuirá as funções de:

- New Game
- Load Game
- Credits
- Exit
		  
- Caso escolha `New Game`:

- Um novo jogo será inicializado, na parte superior da tela do jogo estará a barra de status onde haverá toda informação necessária para se saber quais são os recursos(Amount R1 e R2), tropas(T1, T2 e T3 Amount), construções(HP X, A, C, B) existentes. O jogo estará abaixo desta barra de status, a matriz representada por 'X' faz a geração do recurso 1, a matriz representada por 'B' faz a geração do recurso 2. Os recursos são gerados de acordo com o tempo do jogo. A matriz representada por 'C' gera tropas ao se encostar algum tipo de tropa nela e a matriz representada por 'X' será a sua base a qual vc deverá proteger contra as tropas inimigas.

- A construções inimigas são representadas por 'D', 'E', 'F' e 'Y' sendo que são respectivamente como 'A', 'B', 'C' E 'X'.
 	
- Suas tropas são representadas por '1', '2' e '3' e as tropas inimigas por '7', '8' e '9' para movimentar uma determinada tropa(1, 2 ou 3) deverá digitar o numero da tropa que se deseja mover e usar as setas para movimentação.A interação tropas versus tropas se dará quando uma tropa estiver encostada na outra. A interação tropas versus construções se dará da mesma maneira, se a tropa estiver encostada em alguma construção inimiga os pontos de vida dessa construção serão diminuidos de acordo com os pontos de dano da tropa até que esta fique com vida zero e então a construção é retirada do jogo, se a tropa estiver encostada na construção representada por 'C' esta começará a gerar mais tropas do tipo que está encostada
	
- O jogo é finalizado quando a base inimiga ou a sua base for derrotada, ou seja seus pontos de vida estiverem zerados.
		
- Caso escolha `Load Game`:

- Se não houver nenhum jogo salvo, o jogo não irá começar e irá aparecer uma mensagem de erro:
	"You do not have any game saved"

- Caso já houver algum jogo salvo, este será inicializado com os status e posições do momento em que o jogo foi salvo anteriormente e o jogo seguirá normalmente.

- Caso escolha `Exit`:

- o jogo será finalizado.

- Os movimentos do pc serão executados seguindo um algoritmo de PathFinder.
 
- Durante a execução do jogo, para entrar no menu para pausar o jogo será utilzando a tecla ESC que se precionada duas vezes seguidas aparecerá mais rapidamente.No menu de pause terá as seguintes funções:

- Continue: voltará ao jogo e seguirá normalmente.

- Save Game: salvará o jogo para o load game do menu inicial, o jogo voltará e seguirá normalmente.

- Exit Game: para finalizar o jogo.

- Caso exista algum save game existente, e se o módulo CUnit for compilado e executar o CUnit essa execução irá apagar o save Game. Os testes feitos pelo CUnit serão documentados utilizando o doxygen, que estarão na parte do CUnit.c.

- As funções de interface, ou seja, as que tinham como parâmetro, ou chamavam dentro dela uma janela, ou WINDOW* , não foram testadas, pois a janela deixa a tela desorganizada e é impossível entender os testes do CUnit.

- Para abrir o doxygen  ir na pasta Html do doxygen e abrir o arquivo index.html

- Para rodar o Gcov, basta ir na pasta OBJ e rodar gcov nome_do_arquivo.c . É necessário ter pelo menos o link dos arquivos .c ou uma cópia deles na pasta OBJ para funcionar.

- Na pasta gcov estão os relatórios do gcov de todos os .c do programa.
