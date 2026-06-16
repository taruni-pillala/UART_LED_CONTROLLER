#include<stdint.h>
//RCC
#define RCC_APB2ENR (*((volatile uint32_t *)0x40021018))

//GPIOA
#define GPIOA_CRH (*((volatile uint32_t *)0x40010804))

//GPIOC
#define GPIOC_CRH (*((volatile uint32_t *)0x40011004))
#define GPIOC_ODR (*((volatile uint32_t *)0x4001100c))

//UART1
#define USART1_SR (*((volatile uint32_t *)0x40013800))
#define USART1_DR (*((volatile uint32_t *)0x40013804))
#define USART1_BRR (*((volatile uint32_t *)0x40013808))
#define USART1_CR1 (*((volatile uint32_t *)0x4001380C))

void uart_send_string(char *str) {
	while(*str){
		while(!(USART1_SR & (1<<7)));
		USART1_DR = *str++;
	}
}

char uart_receive(void){
	//wait until data is received
	while(!(USART1_SR & (1<<5)));
	return(char)USART1_DR;
}

int main(void){
	//enable clocks-gpioa,gpioc,uart1
	RCC_APB2ENR |=(1<<2); //GPIOA
	RCC_APB2ENR |=(1<<4);//GPIOC
	RCC_APB2ENR |=(1<<14);//UART1

	//CONFIGURE PC13 AS O/P (LED)
	GPIOC_CRH &= ~(0xF<<20);
	GPIOC_CRH |= (0X2<<20);
	// Configure PA9 as UART TX
	GPIOA_CRH &= ~(0xF << 4);
	GPIOA_CRH |=  (0xB << 4);
	// Configure PA10 as UART RX (input floating)
    GPIOA_CRH &= ~(0xF << 8);
    GPIOA_CRH |=  (0x4 << 8);


    //UART settings -9600 band
    USART1_BRR = 0X341;
    USART1_CR1 |= (1<<2); //RECIEVER ENABLE
    USART1_CR1 |= (1<<3); //TRANSMITTER ENABLE
    USART1_CR1 |= (1<<13); //UART ENABLE

    //LED OFF initially (active low)
    GPIOC_ODR |= (1<<13);

    uart_send_string("UART LED CONTROLLER READY!\r\n");
    uart_send_string("Type 1 to turn LED ON, 0 to turn LED OFF\r\n");

    while(1){
    	char cmd = uart_receive();

    	if(cmd == '1'){
    		GPIOC_ODR &= ~(1<<13); //LED ON
    		uart_send_string("LED ON\r\n");
    	}
    	else if (cmd == '0'){
    	GPIOC_ODR |= (1 << 13);   // LED OFF
  	    uart_send_string("LED OFF\r\n");
    	}
    	else {
    		uart_send_string("INVALID COMMAND! USE 1 OR 0 \r\n");
    	}
    }
}
