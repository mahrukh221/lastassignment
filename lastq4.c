#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct B {
    int ID;
    int Score;
    long Time;
};

struct S {
    struct B *List;
    int Count;
    int Limit;
    long Clock;
};

void init_s(struct S *s, int C) {
    s->List = (struct B *)malloc(C * sizeof(struct B));
    s->Count = 0;
    s->Limit = C;
    s->Clock = 0;
}

int find_b(struct S *s, int ID) {
	int i;
    for ( i = 0; i < s->Count; i++) {
        if (s->List[i].ID == ID) {
            return i;
        }
    }
    return -1;
}

void put_b(struct S *s, int ID, int P) {
    int idx = find_b(s, ID);
    s->Clock++;

    if (idx != -1) {
        s->List[idx].Score = P;
        s->List[idx].Time = s->Clock;
    } else {
        if (s->Count < s->Limit) {
            s->List[s->Count].ID = ID;
            s->List[s->Count].Score = P;
            s->List[s->Count].Time = s->Clock;
            s->Count++;
        } else {
            int low_idx = 0;
            int min_score = s->List[0].Score;
            long min_time = s->List[0].Time;
            int i;

            for ( i = 1; i < s->Limit; i++) {
                if (s->List[i].Score < min_score) {
                    min_score = s->List[i].Score;
                    min_time = s->List[i].Time;
                    low_idx = i;
                } else if (s->List[i].Score == min_score && s->List[i].Time < min_time) {
                    min_time = s->List[i].Time;
                    low_idx = i;
                }
            }

            s->List[low_idx].ID = ID;
            s->List[low_idx].Score = P;
            s->List[low_idx].Time = s->Clock;
        }
    }
}

int get_p(struct S *s, int ID) {
    int idx = find_b(s, ID);
    s->Clock++;

    if (idx != -1) {
        s->List[idx].Time = s->Clock; 
        return s->List[idx].Score;
    } else {
        return -1;
    }
}

void do_ops(struct S *s) {
    char op[10];
    int ID, P, R;

    while (scanf("%s", op) == 1) {
        if (strcmp(op, "ADD") == 0) {
            if (scanf("%d %d", &ID, &P) == 2) {
                put_b(s, ID, P);
            }
        } else if (strcmp(op, "ACCESS") == 0) {
            if (scanf("%d", &ID) == 1) {
                R = get_p(s, ID);
                printf("%d\n", R);
            }
        }
    }
}

int main() {
    int C, Q;
    struct S shelf;

    if (scanf("%d %d", &C, &Q) != 2) return 1;

    init_s(&shelf, C);

    do_ops(&shelf);

    free(shelf.List);
    return 0;
}
