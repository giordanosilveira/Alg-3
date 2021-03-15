Aluno: Giordano Henrique Silveira (GRR20197154)

Como foi feito?
-> Estrutura das árvores: A árvore A contem três ponteiros para a estrutura nodo a - direita, esquerda e pai - e
uma chave que aponta para uma estruta da árvore B. A árvore B contem dois ponteiros para a estrutura nodo B -
direita, esquerda - já que o ponteiro pai era opcional. Vale ressaltar que a árvore B não é uma BST porque depende
da árvore dada pelo usuário
-> Main: primeiramente você entra com uma string que vai conter o comando e a árvore.
Logo depois ele vai separar a árvore e o comando (b,i ou r). De acordo com o comando, ele vai
entrar em um dos 4 "if's" e executar o comando. O comando i, ele vai incluir uma árvore B (BT) na árvore A (BST).
Para isso, eu monto a árvore B primeiramente e depois eu passo o ponteiro dessa árvore montada para a função
inserir na árvore A. O comando B, vai buscar na árvore A o nodo que corresponte a soma dos nodos da árvore B.
Primeiro eu somo os nodos da árvore B e passo a soma, um valor inteiro, para a função busca. Dentro da busca, eu
somo o a chave da árvore A, que é uma árvore B e faço a busca. O comando r, vai excluir um nodo da árvore A.
Eu faço isso somando primeiramente a árvore B, passo essa soma para a função busca que me retorna um nodo A,
e na função remover eu excluo esse nodo. 
-> Funcionalidades: todas as funções da árvore A, funcionam como uma BST normal, com a diferença que o nodo chave
é uma BT - árvore B. A função mais complicada da árvore B é a função "monta_arvore" pois eu tive que tratar
nela o caso de parenteses vázios (EX: (25(10(5)())()) e números compostos de mais de um digito.
-> Bibliotecas: eu separei as funções que usei em duas Bibliotecas diferente. A "libstA" que contem todas as funções
da árvore A. E a "libstB" que contem todas as funções da árvore B.

Haverá dois warnings na compilação. Mas ele ocorrem 

Para mais dúvidas, eu comentei todas minhas funções nas minhas duas bibliotecas. Acho que se eu explicasse aqui
todas elas, esse arquivo ficaria muito extenso.

That's all folks!