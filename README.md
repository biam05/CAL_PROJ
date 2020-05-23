# WasteApp: recolha seletiva de lixo

## Lista de Dependências

### Ficheiros de Input

A informação é lida da pasta ```data```, sendo que esta contém duas subpastas - ```Porto``` e ```GridGraphs``` - onde estão presentes os documentos necessários para a produção do grafo no *GraphViewer*, sendo estes:

+ ```edges.txt``` - ficheiro com informação sobre as arestas;
+ ```nodes.txt``` - ficheiro com informação sobre os vértices;
+ ```tags.txt``` - ficheiro com informação sobre o que cada vértice representa;
+ ```userlogins.txt``` - ficheiro com informação sobre cada utilizador da aplicação (*username*, *password*, vértice onde tem a sua casa e tipo de utilizador (cliente ou trabalhador)).

### Bibliotecas Utilizadas

+ ```#include <winsock2.h>``` - necessário uma vez que projeto foi desenvolvido em Windows.

### APIs Utilizadas

+ *Graphviewer*
  
## Instruções de Compilação

+ Compilar o projeto (normalmente compilamos no *Clion*);
+ Correr o executável.

## Autores

+ Beatriz Costa Silva Mendes - up201806551@fe.up.pt
+ Daniel Garcia Lima Sarmento da Silva - up201806524@fe.up.pt
+ Henrique Manuel Ruivo Pereira - up201806538@fe.up.pt
