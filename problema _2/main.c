#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int id;
  int colaboracoes;
  int *relacoes;
  int quantidadeRelacoes;
} Pessoa;

void adicionarRelacao(Pessoa *pessoas, int indexPessoa1, int indexPessoa2)
{
  Pessoa *pessoa = &pessoas[indexPessoa1 - 1];
  int *novo = realloc(pessoa->relacoes, (pessoa->quantidadeRelacoes + 1) * sizeof(int));

  pessoa->relacoes = novo;
  pessoa->relacoes[pessoa->quantidadeRelacoes++] = indexPessoa2;
  pessoa->colaboracoes++;
}

int calcularTamanhoGrupo(Pessoa *pessoas, int colaboracoesMinimas, int numPessoas)
{
  char *removida = calloc(numPessoas, sizeof(char));
  int *fila = malloc(numPessoas * sizeof(int));

  int inicio = 0, fim = 0;

  for (int i = 0; i < numPessoas; i++)
  {
    if (pessoas[i].colaboracoes < colaboracoesMinimas)
    {
      removida[i] = 1;
      fila[fim++];
    }
  }

  while (inicio < fim)
  {
    Pessoa *pessoa = &pessoas[fila[inicio++]];

    for (int i = 0; i < pessoa->quantidadeRelacoes; i++)
    {
      int v = pessoa->relacoes[i] - 1;
      if (removida[v])
        continue;
      if (--pessoas[v].colaboracoes < colaboracoesMinimas)
      {
        removida[v] = 1;
        fila[fim++] = v;
      }
    }
  }

  free(removida);
  free(fila);

  return numPessoas - fim;
}

int main(void)
{
  int numPessoas, relacoes, colaboracoesMinimas;

  scanf("%d %d %d", &numPessoas, &relacoes, &colaboracoesMinimas);

  Pessoa *pessoas = (Pessoa *)malloc(numPessoas * sizeof(Pessoa));

  for (int i = 0; i < numPessoas; i++)
  {
    Pessoa pessoa = {i + 1, 0, NULL, 0};
    pessoas[i] = pessoa;
  }

  for (int i = 0; i < relacoes; i++)
  {
    int indexPessoa1, indexPessoa2;
    scanf("%d %d", &indexPessoa1, &indexPessoa2);

    adicionarRelacao(pessoas, indexPessoa1, indexPessoa2);
    adicionarRelacao(pessoas, indexPessoa2, indexPessoa1);
  }

  int tamanhoGrupo = calcularTamanhoGrupo(pessoas, colaboracoesMinimas, numPessoas);
  printf("%d", tamanhoGrupo);

  for (int i = 0; i < numPessoas; i++)
    free(pessoas[i].relacoes);
  free(pessoas);

  return 0;
}