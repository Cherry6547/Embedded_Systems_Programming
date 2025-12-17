#include"stm32f446re.h"
#include"Ringbuffer.h"
#include"Uart.h"
#include<string.h>

int main(){
	uart2_init(115200U, 16000000U);
	printf("UART driver is working\n");//logs data to terminal via uart as we modified the _write in syscalls to call the uart_write
	while(1){
		uint8_t data;
		if(uart2_read(&data)){  //reads data from uart rx port , in our case the port reads data from keyboard
			uart2_write(&data, 1U);  //write back to the terminal simple echo function for checking the output
		}
	}
	return 0;
}
