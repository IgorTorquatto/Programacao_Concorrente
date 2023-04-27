# Tasks 
* Aluno: Cicero Igor Alves Torquato dos Santos
* Disciplina: Programação Concorrente 

### Introdução 

Um dos problemas do OpenMP sections é que suas seções são **estáticas** , ou seja , são boas se sabemos quantas delas nós usaremos. <br>
O OpenMP Tasks surge como uma ferramenta para resolver esse problema, já que torna o número total de tarefas a ser utilizado seja **dinâmico**.<br>
Ao escrever um código com o OpenMP tasks a nova tarefa é incluída em uma **lista de tarefas** e s nova tarefa pode ser executada imediatamente ou pode ser adiada.<br>
*Importante:* Deve haver um conjunto de encadeamento de threads em paralelo existente para que isso funcione. Caso contrário, um thread acaba fazendo todas as tarefas e você não obtém nenhuma contribuição para o paralelismo.<br>

### OpenMP sections X OpenMP tasks

As tasks são muito parecidas com as sections do OpenMP, mas as sections são estáticas, ou seja, o número de seções é definido quando você escreve o código, enquanto as tasks podem ser criadas a qualquer momento e em qualquer número, sob controle da lógica do seu programa.

