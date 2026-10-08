#include <stdio.h>

void printCelsius(float fahrenheit) {
    float celsius = (fahrenheit - 32.0f) * 5.0f / 9.0f;
    printf("%.1f^F is %.1f^C\n", fahrenheit, celsius);
}

int main() {
    
    printCelsius(32.0f);
    printCelsius(98.6f);
    printCelsius(212.0f);
    
    return 0;
}
