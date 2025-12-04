#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 50

struct Data {
    int ID;
    char Name[MAX_LEN];
    char Dept[MAX_LEN];
    double Pay;
};

void show_data(struct Data records[], int count) {
    if (count == 0) {
        printf("No staff records found.\n");
        return;
    }
    printf("ID Name Designation Pay\n");
    int i;
    for ( i = 0; i < count; i++) {
        printf("%d %s %s %.2lf\n", records[i].ID, records[i].Name, records[i].Dept, records[i].Pay);
    }
}

int find_top_pay(struct Data records[], int count) {
    if (count == 0) return -1;

    int top_index = 0;
    double max_pay = records[0].Pay;
    int i;

    for ( i = 1; i < count; i++) {
        if (records[i].Pay > max_pay) {
            max_pay = records[i].Pay;
            top_index = i;
        }
    }
    return top_index;
}

int query(struct Data records[], int count, char input[], int query_type) {
    if (count == 0) return -1;

    if (query_type == 1) { 
        int target_ID = atoi(input);
        int i;
        for ( i = 0; i < count; i++) {
            if (records[i].ID == target_ID) {
                return i;
            }
        }
    } else if (query_type == 2) { 
    int i;
        for ( i = 0; i < count; i++) {
            if (strcasecmp(records[i].Name, input) == 0) {
                return i;
            }
        }
    }
    return -1;
}

void apply_raise(struct Data records[], int count) {
	int i;
    for (i = 0; i < count; i++) {
        if (records[i].Pay < 50000.0) {
            records[i].Pay *= 1.10; 
        }
    }
}

int main() {
    struct Data staff[3];
    int current_count = 0;
    int max_pay_idx;
    int found_idx;

    staff[current_count++] = (struct Data){101, "SARA", "Manager", 60000.0};
    staff[current_count++] = (struct Data){102, "ALI", "Analyst", 45000.0};
    staff[current_count++] = (struct Data){103, "MANO", "Clerk", 30000.0};

    show_data(staff, current_count);
    printf("\n");

    max_pay_idx = find_top_pay(staff, current_count);
    if (max_pay_idx != -1) {
        printf("Top Paid Staff: %s (%.2lf)\n", staff[max_pay_idx].Name, staff[max_pay_idx].Pay);
    }
    printf("\n");

    found_idx = query(staff, current_count, "102", 1);
    if (found_idx != -1) {
        printf("Query by ID 102 Found: %s\n", staff[found_idx].Name);
    } else {
        printf("Query by ID 102 Not Found.\n");
    }

    found_idx = query(staff, current_count, "alex", 2);
    if (found_idx != -1) {
        printf("Query by Name 'SARA' Found: %s\n", staff[found_idx].Name);
    } else {
        printf("Query by Name 'SARA' Not Found.\n");
    }
    printf("\n");

    apply_raise(staff, current_count);

    printf("Updated Pay:\n");
    show_data(staff, current_count);

    return 0;
}
