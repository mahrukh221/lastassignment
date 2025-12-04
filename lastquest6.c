#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 100
#define FIELD_MAX 50
#define DATA_FILE "data.bin"

struct Student {
    int id;
    char name[NAME_MAX];
    char batch[FIELD_MAX];
    char type[FIELD_MAX];
    char reg_date[FIELD_MAX];
    char dob[FIELD_MAX];
    char focus[FIELD_MAX];
};

struct Manager {
    struct Student *list;
    int count;
    int max;
};

void start(struct Manager *m) {
    m->count = 0;
    m->max = 5;
    m->list = (struct Student *)malloc(m->max * sizeof(struct Student));
    if (m->list == NULL) exit(1);
}

void expand(struct Manager *m) {
    m->max *= 2;
    struct Student *new_list = (struct Student *)realloc(m->list, m->max * sizeof(struct Student));
    if (new_list == NULL) exit(1);
    m->list = new_list;
}

int find(struct Manager *m, int id) {
	int i;
    for ( i = 0; i < m->count; i++) {
        if (m->list[i].id == id) {
            return i;
        }
    }
    return -1;
}

void load(struct Manager *m) {
    FILE *f = fopen(DATA_FILE, "rb");
    if (f == NULL) return; 

    while (fread(&m->list[m->count], sizeof(struct Student), 1, f) == 1) {
        m->count++;
        if (m->count == m->max) {
            expand(m);
        }
    }
    fclose(f);
}

void save(struct Manager *m) {
    FILE *f = fopen(DATA_FILE, "wb");
    if (f == NULL) return;

    fwrite(m->list, sizeof(struct Student), m->count, f);
    fclose(f);
}

void add(struct Manager *m, struct Student s) {
    if (find(m, s.id) != -1) {
        printf("Error: ID %d exists.\n", s.id);
        return;
    }

    if (m->count == m->max) {
        expand(m);
    }
    
    m->list[m->count] = s;
    m->count++;
    printf("Added ID %d.\n", s.id);
}

void display(struct Manager *m) {
    printf("--- All Records (%d) ---\n", m->count);
    if (m->count == 0) {
        printf("Empty.\n");
        return;
    }
    printf("ID | Name | Batch | Type\n");
    int i;
    for (i = 0; i < m->count; i++) {
        printf("%d | %s | %s | %s\n", 
               m->list[i].id, 
               m->list[i].name, 
               m->list[i].batch, 
               m->list[i].type);
    }
}

int main() {
    struct Manager team;
    start(&team);
    load(&team);

    struct Student p1 = {101, "Ali", "SE", "IEEE", "2025-01-01", "2000-05-15", "Both"};
    struct Student p2 = {102, "Sara", "AI", "ACM", "2025-01-02", "2001-10-20", "ACM"};
    struct Student p3 = {103, "Mano", "Cyber", "IEEE", "2025-01-03", "1999-03-03", "IEEE"};

    add(&team, p1);
    add(&team, p2);
    add(&team, p3);
    
    display(&team);

    save(&team);

    free(team.list);
    return 0;
}
