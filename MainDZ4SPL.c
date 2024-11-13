#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"//отдельно подключил SPL
#include "stm32f4xx_gpio.h"//отдельно подключил SPL

// LED2 PA6 31pin соотв. GPIO port mode register (GPIOx_MODER) 12-13 битам
// LED3 PA7 32pin соотв. GPIO port mode register (GPIOx_MODER) 14-15 битам

//ищем структуру GPIO Init structure definition	в stm32f4xx_gpio
//и созаем экземляр
	GPIO_InitTypeDef LED2;
	GPIO_InitTypeDef LED3;
	
void initClk(void);
void initGPIO(void);

int main(void)
{
initClk();
initGPIO();	

	while(1)
	{
//в stm32f4xx_gpio поищем функцию управляющ.данными или уровнем(GPIO), укажем с каким портом работаем и укажем конкретный бит
	GPIO_SetBits(GPIOA, LED2.GPIO_Pin);
	GPIO_ResetBits(GPIOA, LED3.GPIO_Pin);
	for (int i = 0; i < 900000; i++) {};
	GPIO_SetBits(GPIOA, LED3.GPIO_Pin);
	GPIO_ResetBits(GPIOA, LED2.GPIO_Pin);
	for (int i = 0; i < 900000; i++) {};
	}
}

void initClk()
{
//Требуется запустить клок на регистре AHB1
// В описании RCC register map - находим GPIOAEN который
// принадлежит регистру RCC_AHB1ENR
//ищем в stm32f4xx_rcc.h RCC_AHB1Periph, находим RCC_AHB1Periph_GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}

void initGPIO()
{
//заполняем структуру, по сути 4 региста (GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR and GPIOx_PUPDR)
	LED2.GPIO_Pin=GPIO_Pin_6;//в stm32f4xx_gpio находим ссылку на пин
	LED2.GPIO_Mode=GPIO_Mode_OUT;//в stm32f4xx_gpio находим ссылку enum с вариантом
	LED2.GPIO_Speed=GPIO_Speed_2MHz;//в stm32f4xx_gpio находим ссылку enum с вариантом
	LED2.GPIO_OType=GPIO_OType_PP;//в stm32f4xx_gpio находим ссылку enum с вариантом
	LED2.GPIO_PuPd=GPIO_PuPd_UP;//в stm32f4xx_gpio находим ссылку enum с вариантом
	
	LED3.GPIO_Pin=GPIO_Pin_7;//в stm32f4xx_gpio находим ссылку на пин
	LED3.GPIO_Mode=GPIO_Mode_OUT;//в stm32f4xx_gpio находим ссылку enum с вариантом
	LED3.GPIO_Speed=GPIO_Speed_2MHz;//в stm32f4xx_gpio находим ссылку enum с вариантом
	LED3.GPIO_OType=GPIO_OType_PP;//в stm32f4xx_gpio находим ссылку enum с вариантом
	LED3.GPIO_PuPd=GPIO_PuPd_UP;//в stm32f4xx_gpio находим ссылку enum с вариантом

//в stm32f4xx_gpio находим функцию инициализации GPIO, укажем с каким портом работаем и укажем на структуру настроек
	GPIO_Init(GPIOA, &LED2);
	GPIO_Init(GPIOA, &LED3);
}
