void delay(int ms) {
    for (int i = 0; i < 3000 * ms; i++) {}
}

int main(void) {
    int *GPIOx_CRL;
    int *GPIOx_CRH;
    int *GPIOx_ODR;
    int *apb2enr;
    int i;
    GPIOx_CRL = (int *) (0x40010800); 
    GPIOx_ODR = (int *) (0x4001080C); 
    apb2enr = (int *) 0x40021018;
    *apb2enr |= 0x0004;    
    *GPIOx_CRL = 0x00300000; 
    char kharchevka[] = {'-', ' ', '*', ' ', '-', '-', '-', '-', '*', '-', '-', ' ', '-',
                      '*', '-', ' ', '-', '-', '-', ' ', '*', '*', '*', '-'};
    int length = sizeof(kharchevka) / sizeof(char);
    int j = 0;
    for (;; j++) {
        *GPIOx_ODR = 0x00000000;
        char element = kharchevka[j % length];
        if (element == '*') {
            *GPIOx_ODR = 0x00000020;
            delay(150);
        } else if (element == '-') {
            *GPIOx_ODR = 0x00000020;
            delay(300);
        } else if (element == ' ') {
            *GPIOx_ODR = 0x0000000;
            delay(600);
        }
        if (j % length == length - 1) {
            delay(3000);
        };
    }
}
