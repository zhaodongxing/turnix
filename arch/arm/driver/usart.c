#include <stddef.h>
#include <stdint.h>
#include <reg.h>

/* USART TXE Flag
 * This flag is cleared when data is written to USARTx_DR and
 * set when that data is transferred to the TDR
 */
#define USART_FLAG_TXE  ((uint16_t) 0x0080)
#define USART_FLAG_RXNE ((uint16_t) 0x0020)

void usart_init(void)
{
    *(RCC_APB2ENR) |= (uint32_t) (0x00004005);

    /* USART1 Configuration, Rx->PA3, Tx->PA2 */
    *(GPIOA_CRL) = 0x44444444;
    *(GPIOA_CRH) = 0x000004b0;

    pUSART1->CR1 = 0x0000000C;
    pUSART1->CR2 = 0x00000000;
    pUSART1->CR3 = 0x00000000;
    pUSART1->BRR = 0x00000271; /*115200bps*/
    pUSART1->CR1 |= 0x2000;
}

int putchar(int c)
{
    while(!((pUSART1->SR) & USART_FLAG_TXE));
    pUSART1->DR = (c & 0xFF);
    return 0;
}

int getchar(void){
    while(!((pUSART1->SR) & USART_FLAG_RXNE));
    return pUSART1->DR;
}

#if 0
void USART2_IRQHandler()  
{
    if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET) 
    {  
       USART_ClearITPendingBit(USART2,USART_IT_RXNE);
       Uart2_Buffer[Uart2_Rx] = USART_ReceiveData(USART2);  
       Uart2_Rx++;  
       Uart2_Rx &= 0x3F;
    }  

    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) == SET)
    {  
        USART_ClearFlag(USART2,USART_FLAG_ORE); 
        USART_ReceiveData(USART2); 
    }  
} 


if( Uart2_Tx != Uart2_Rx )  
{  
    USART2_SendByte(Uart2_Buffer[Uart2_Tx]); 
    Uart2_Tx++;  
    Uart2_Tx &= 0x3F; 
} 
#endif
