#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

struct Doc {
    char **Data;
    int Count;
    int Max;
};

void init(struct Doc *d, int m) {
    d->Data = (char **)malloc(m * sizeof(char *));
    d->Count = 0;
    d->Max = m;
}

void grow(struct Doc *d) {
    int new_max = d->Max * 2;
    char **p = (char **)realloc(d->Data, new_max * sizeof(char *));
    if (p == NULL) return;
    d->Data = p;
    d->Max = new_max;
}

void shrink(struct Doc *d) {
    if (d->Count < d->Max) {
        char **p = (char **)realloc(d->Data, d->Count * sizeof(char *));
        if (p == NULL) return;
        d->Data = p;
        d->Max = d->Count;
    }
}

void clean(struct Doc *d) {
	int i;
    for (i = 0; i < d->Count; i++) {
        free(d->Data[i]);
    }
    free(d->Data);
    d->Data = NULL;
    d->Count = 0;
    d->Max = 0;
}

void insert(struct Doc *d, int i, char *t) {
    if (i < 0 || i > d->Count) return;

    if (d->Count == d->Max) {
        grow(d);
    }
    int j;

    for (j = d->Count; j > i; j--) {
        d->Data[j] = d->Data[j - 1];
    }

    int len = strlen(t);
    d->Data[i] = (char *)malloc((len + 1) * sizeof(char));
    if (d->Data[i] == NULL) return;

    strcpy(d->Data[i], t);
    d->Count++;
}

void delete(struct Doc *d, int i) {
    if (i < 0 || i >= d->Count) return;

    free(d->Data[i]);
    int j;

    for (j = i; j < d->Count - 1; j++) {
        d->Data[j] = d->Data[j + 1];
    }
    d->Count--;

    if (d->Count > 0 && d->Count < d->Max / 4) {
        shrink(d);
    }
}

void print(struct Doc *d) {
	int i;
    for ( i = 0; i < d->Count; i++) {
        printf("%d: %s\n", i, d->Data[i]);
    }
}

int main() {
    struct Doc doc;
    init(&doc, 2); 

    insert(&doc, 0, "First line.");
    insert(&doc, 1, "Second line.");
    insert(&doc, 2, "Third line.");
    insert(&doc, 1, "Inserted line.");
    
    print(&doc);

    delete(&doc, 2); 
    
    printf("\n");
    print(&doc);
    
    clean(&doc);
    
    return 0;
}
