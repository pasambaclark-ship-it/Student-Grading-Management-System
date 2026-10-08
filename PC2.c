#include <stdio.h>

int main() {
    float hoursWorked, hourlyRate, grossPay, taxRate, netPay;

    
    printf("Enter hours worked this week: ");
    scanf("%f", &hoursWorked);
    printf("Enter hourly rate: $");
    scanf("%f", &hourlyRate);

    
    if (hoursWorked <= 40) {
        grossPay = hoursWorked * hourlyRate;
    } else {
        float overtimeHours = hoursWorked - 40;
        grossPay = (40 * hourlyRate) + (overtimeHours * hourlyRate * 1.5);
    }


    if (grossPay < 600) {
        taxRate = 0.0;
    } else if (grossPay <= 1200) {
        taxRate = 0.12;
    } else {
        taxRate = 0.22;
    }

    
    netPay = grossPay - (grossPay * taxRate);

    
    printf("\n--- Weekly Pay Stub ---\n");

    printf("Hours Worked: %.2f\n", hoursWorked);

    printf("Hourly Rate: $%.2f\n", hourlyRate);

    printf("Gross Pay: $%.2f\n", grossPay);

    printf("Tax Rate: %.0f%%\n", taxRate * 100);
    
    printf("Net Pay: $%.2f\n", netPay);

    return 0;
}
