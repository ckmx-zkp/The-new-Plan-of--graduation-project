
//  ����LED1�����������
#define LED1ON()      GPIOB->ODR |=  GPIO_Pin_7;
#define LED1OFF()     GPIOB->ODR &= ~GPIO_Pin_7;
#define LED1B()       GPIOB->ODR ^=  GPIO_Pin_7;

//  ����LED2�����������
#define LED2ON()      GPIOB->ODR |=  GPIO_Pin_6;
#define LED2OFF()     GPIOB->ODR &= ~GPIO_Pin_6;
#define LED2B()       GPIOB->ODR ^=  GPIO_Pin_6;

//  ����LED3�����������
#define LED3ON()      GPIOB->ODR |=  GPIO_Pin_5;
#define LED3OFF()     GPIOB->ODR &= ~GPIO_Pin_5;
#define LED3B()       GPIOB->ODR ^=  GPIO_Pin_5;

//  ����LED4�����������
#define LED4ON()      GPIOB->ODR |=  GPIO_Pin_4;
#define LED4OFF()     GPIOB->ODR &= ~GPIO_Pin_4;
#define LED4B()       GPIOB->ODR ^=  GPIO_Pin_4;

//  ����LED5�����������
#define LED5ON()      GPIOB->ODR |=  GPIO_Pin_3;
#define LED5OFF()     GPIOB->ODR &= ~GPIO_Pin_3;
#define LED5B()       GPIOB->ODR ^=  GPIO_Pin_3;

//  ���尴����ӦIO��
#define KEY1      GPIO_Pin_0;
#define KEY2      GPIO_Pin_1;
#define KEY3      GPIO_Pin_2;
#define KEY4      GPIO_Pin_3;

extern unsigned char key_bit;

void gpio_conf(void);
void key_work(void);










