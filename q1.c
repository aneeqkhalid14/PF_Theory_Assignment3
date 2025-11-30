#include <stdio.h>

void calculateRepayment(double loan, double rate, int year, double installment){
    if(year == 0 || loan <= 0){
        return;
    }
    printf("Year %d: Remaining Loan = %.2f\n", year, loan);
    loan = loan + (loan * rate / 100.0);
    loan = loan - installment; 
    calculateRepayment(loan,rate,year-1,installment);
}

int main(){
    double installment, loan = 100000, rate = 5;
    int year = 3;
    printf("Enter fixed installment amount: \n");
    scanf("%lf", &installment);
    calculateRepayment(loan,rate,year,installment);
    return 0;

}