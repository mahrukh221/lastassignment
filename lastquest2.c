#include <stdio.h>
#include <math.h>

double F_calc(double R, double C, double G, int P) {
    if (P == 0) {
        return R;
    } else {
        double Prev = F_calc(R, C, G, P - 1);
        double Cons = C;
        double Gain = G;
        double Curr = Prev - Cons + Gain;
        return Curr;
    }
}

int main() {
    double Initial_R = 100.0;
    double Cons_C = 5.0;
    double Gain_G = 2.0;
    int Num_P = 10;

    double Final_F = F_calc(Initial_R, Cons_C, Gain_G, Num_P);

    printf("%.2lf\n", Final_F);

    return 0;
}
