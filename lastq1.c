#include <stdio.h>
#include <math.h>

double repayment_calc(double L, double R, int Y) {
    if (Y == 0) {
        return L;
    } else {
        double P = repayment_calc(L, R, Y - 1);
        double I = P * (R / 100.0);
        return P + I;
    }
}

double remaining_calc(double L, double R, int Y, double Repay) {
    if (Y == 0) {
        return L;
    } else {
        double Rem = remaining_calc(L, R, Y - 1, Repay);
        double I = Rem * (R / 100.0);
        Rem = Rem + I - Repay;
        return Rem;
    }
}

int main() {
    double loan = 100000.0;
    double rate = 5.0;
    int years = 3;
    double payment = 35000.0;

    double total_repayment = repayment_calc(loan, rate, years);
    printf("%.2lf\n", total_repayment);

    double loan_remaining = remaining_calc(loan, rate, years, payment);
    printf("%.2lf\n", loan_remaining);

    return 0;
}
