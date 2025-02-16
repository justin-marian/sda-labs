#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *Key;
typedef int Value;
typedef long (*HashFunction)(Key, long);

typedef struct Element {
  Key K;
  Value V;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element **elements;
  long size;
  HashFunction hashFunction;
} HashTable;

// Initialize the hash table
void initHashTable(HashTable **h, long size, HashFunction f) {
  *h = (HashTable *)malloc(sizeof(HashTable));
  if (!*h) {
    fprintf(stderr, "Error: Memory allocation failed for HashTable.\n");
    exit(1);
  }

  (*h)->elements = (Element **)calloc(size, sizeof(Element *));
  if (!(*h)->elements) {
    fprintf(stderr, "Error: Memory allocation failed for elements array.\n");
    free(*h);
    exit(1);
  }

  (*h)->size = size;
  (*h)->hashFunction = f;
}

// Check if a K exists in the hash table
int exists(HashTable *hashTable, Key K) {
  long idx = hashTable->hashFunction(K, hashTable->size);
  Element *it = hashTable->elements[idx];

  while (it) {
    if (strcmp(it->K, K) == 0)
      return 1;
    it = it->next;
  }
  return 0;
}

// Get the V of a K in the hash table
Value get(HashTable *hashTable, Key K) {
  long idx = hashTable->hashFunction(K, hashTable->size);
  Element *it = hashTable->elements[idx];

  while (it) {
    if (strcmp(it->K, K) == 0)
      return it->V;
    it = it->next;
  }
  return 0;
}

// Insert or update a K-V pair in the hash table
void put(HashTable *hashTable, Key K, Value V) {
  long idx = hashTable->hashFunction(K, hashTable->size);
  Element *it = hashTable->elements[idx];

  while (it) {
    if (strcmp(it->K, K) == 0) {
      it->V = V;
      return;
    }
    it = it->next;
  }

  Element *e = (Element *)malloc(sizeof(Element));
  if (!e) {
    fprintf(stderr, "Error: Memory allocation failed for new element.\n");
    return;
  }

  e->K = strdup(K);
  e->V = V;
  e->next = hashTable->elements[idx];
  hashTable->elements[idx] = e;
}

// Delete a K from the hash table
void deleteKey(HashTable *hashTable, Key K) {
  long idx = hashTable->hashFunction(K, hashTable->size);
  Element *e = hashTable->elements[idx];
  Element *prev = NULL;

  while (e) {
    if (strcmp(e->K, K) == 0) {
      if (prev)
        prev->next = e->next; // Remove element from chain
      else
        hashTable->elements[idx] = e->next; // Update head

      free(e->K);
      free(e);
      return;
    }
    // Move to next element
    prev = e;
    e = e->next;
  }
}

void print(HashTable *hashTable) {
  printf("\n--- Hash Table ---\n");
  for (long idx = 0; idx < hashTable->size; idx++) {
    Element *e = hashTable->elements[idx];
    if (e) {
      printf("%ld: ", idx);
      while (e) {
        printf("(%s: %d) -> ", e->K, e->V);
        e = e->next;
      }
      printf("NULL\n");
    }
  }
  printf("--- End ---\n");
}

void freeHashTable(HashTable *hashTable) {
  for (long idx = 0; idx < hashTable->size; idx++) {
    Element *e = hashTable->elements[idx];
    while (e) {
      Element *temp = e;
      e = e->next;
      free(temp->K);
      free(temp);
    }
  }
  free(hashTable->elements);
  free(hashTable);
}

long hash1(Key word, long size) {
  long h = 0;
  for (size_t i = 0, len = strlen(word); i < len; i++) {
    h = h * 17 + word[i];
  }
  return h % size;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    fprintf(stderr, "Usage: %s <hash size> <file1> <file2>\n", argv[0]);
    return 1;
  }

  long hashSize = atol(argv[1]);
  FILE *f1 = fopen(argv[2], "r");
  FILE *f2 = fopen(argv[3], "r");

  if (!f1 || !f2) {
    fprintf(stderr, "Error: Unable to open input files.\n");
    if (f1)
      fclose(f1);
    if (f2)
      fclose(f2);
    return 1;
  }

  HashTable *hashTable;
  initHashTable(&hashTable, hashSize, &hash1);

  // Read first file and populate the hash table
  char word[256];
  while (fscanf(f1, "%255s", word) == 1) {
    put(hashTable, word, get(hashTable, word) + 1);
  }
  print(hashTable);
  fclose(f1);

  // Read second file and count common words
  long common = 0;
  while (fscanf(f2, "%255s", word) == 1) {
    if (exists(hashTable, word)) {
      common++;
      long cnt = get(hashTable, word);
      if (cnt == 1)
        deleteKey(hashTable, word);
      else
        put(hashTable, word, cnt - 1);
    }
  }
  fclose(f2);

  printf("Common words: %ld\n", common);

  freeHashTable(hashTable);
  return 0;
}
