#include <stdio.h>
#include <stdlib.h>

int *generateCandidates(int *guaritas, int k, int n, int *numCandidates) {
  int *candidates = malloc(n * sizeof(int));
  int count = 0;

  for (int i = 0; i < n; i++) {
    int isCandidate = 1;

    for (int j = 0; j < n; j++) {
      if (guaritas[j] == i)
        isCandidate = 0;
    }

    if (isCandidate)
      candidates[count++] = i;
  }

  *numCandidates = count;
  return candidates;
}

int isSolution(int k, int n) { return k == n; }

void processSolution(int a[], int n) {
  for (int i = 0; i < n; i++)
    printf("%d ", a[i] + 1);
  printf("\n");
}

void backtrack(int k, int guaritas[], int n) {
  if (isSolution(k, n)) {
    processSolution(guaritas, n);
    return;
  }

  int numCandidates;
  int *candidates = generateCandidates(guaritas, k, n, &numCandidates);

  if (guaritas[k] == -1) {
    for (int i = 0; i < numCandidates; i++) {
      guaritas[k] = candidates[i];
      backtrack(k + 1, guaritas, n);
    }

    guaritas[k] = -1;
  } else {
    backtrack(k + 1, guaritas, n);
  }
}

int main() {
  int n, numGuaritasObrigatorias;
  int *guaritas;

  scanf("%d %d", &n, &numGuaritasObrigatorias);

  guaritas = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    guaritas[i] = -1;

  for (int i = 0; i < numGuaritasObrigatorias; i++) {
    int x, y;
    scanf("%d %d", &x, &y);

    guaritas[y - 1] = x - 1;
  }

  backtrack(0, guaritas, n);

  return 0;
}