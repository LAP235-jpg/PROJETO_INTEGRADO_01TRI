/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7735\st7735.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{
	AULA, 
	LOGIN,
    DEFINIR,
	BEGINE,
	RELATORIO,
	ERRO,
	ERRO2
}estado;
/* USER CODE END PTD */ 

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define left  HAL_GPIO_ReadPin(left_GPIO_Port, left_Pin)
#define down HAL_GPIO_ReadPin(down_GPIO_Port, down_Pin)
#define right HAL_GPIO_ReadPin(right_GPIO_Port, right_Pin)
#define up HAL_GPIO_ReadPin(up_GPIO_Port, up_Pin)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
int x = 0;
int alunosquant = 0;
int alunos = 0;
int saida = 0;
int senha = 0;
int banheiro = 0;
int banheiro2 = 0;
estado estadoAtual = BEGINE;
estado ultimoEstado = -1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*TELAS*/
void telalogin()
{
 DrawLines(x);
 senha = (rand()%10) + 1;

    if(right == 0)
    {
        x++;

    }

    if(left == 0)
    {
        x--;

    }
    if(x < 0){
    	x = 0;
    }
    if(x > 10){
    	x = 10;
    }

    if(up == 0)
    {
        if(x == senha)
        {
           estadoAtual = DEFINIR;
        }
        else {
          estadoAtual = ERRO2;
          x = 0;
        }



    }


}
void telainicial()

{

  ST7735_WriteString(0,0, "   BEM VINDO   " , Font_11x18, WHITE, GREEN);
  ST7735_WriteString(0,25, "    AO SISTEMA DE CONTROLE DE ACESSO  " , Font_7x10, WHITE, BLACK);
  ST7735_WriteString(0,50, "    PRESSIONE QUALQUER BOTAO PARA INICIAR  " , Font_7x10, WHITE, BLACK);

 if(right == 0 || left == 0 || up == 0 || down == 0)
 {
     estadoAtual = LOGIN;

 }
}
void teladefinir()
{

  Drawalunos(alunosquant);
    if(right == 0)
    {
        alunosquant++;
        HAL_Delay(150);
    }

    if(left == 0)
    {
        alunosquant--;
        HAL_Delay(150);
    }
    if(alunosquant > 99){
    	alunosquant = 99;
    }
    if(alunosquant < 0){
    	alunosquant = 0;
    }

    if(up == 0)
    {
        estadoAtual = AULA;
        HAL_Delay(150);
    }
}
void telaaula()
{
  DrawAula();


    if(right == 0)
    {
        alunos++;
        HAL_Delay(150);
    }

    if(left == 0)
    {
        alunos--;
        HAL_Delay(150);
    }
    if(up == 0){
      banheiro ++;
      saida ++;
      HAL_Delay(150);
    }
    if(down == 0){
          banheiro --;
        HAL_Delay(150);
        }




    if(alunos > alunosquant){
    	estadoAtual = ERRO;
    }
    if(alunos < 0){
    alunos = 0;
    }
    if(banheiro > 3){
    	estadoAtual = ERRO;
    }
    if(banheiro < 0){
    	banheiro = 0;
    }



    if(up == 0 && right == 0)
    {
    	saida --;
    	alunos --;
        estadoAtual = RELATORIO;
        HAL_Delay(150);
    }

}
void telarelatorio()

{
  Drawmenu();

  if(right == 0 || left == 0 || up == 0 || down == 0){
	  estadoAtual = BEGINE;
  }

}
void telaerro2(){
	Drawerro2();
	if(right == 0 || left == 0 || up == 0 || down == 0){
		estadoAtual = LOGIN;
	}
}
void telaerro(){
 Drawerro();
		if(right == 0 || left == 0 || up == 0 || down == 0){
		alunos = 0;
		banheiro = 0;
		saida = 0;
		estadoAtual = AULA;
		}
}
/*DESENHO DAS TELAS*/
void DrawAula()
{
	char alunosq[3];

		    alunosq[0] = (alunosquant / 10) + '0';
		    alunosq[1] = (alunosquant % 10) + '0';
		    alunosq[2] = '\0';

	 char alu[3];

		    	    alu[0] = (alunos / 10) + '0';
		    	    alu[1] = (alunos % 10) + '0';
		    	    alu[2] = '\0';
     char ban[10]={0};
     ban[0]=banheiro + '0';

  ST7735_WriteString(0,0, "AULA INICIADA" , Font_11x18, WHITE, BLACK);
  ST7735_WriteString(80,25, alu, Font_7x10, WHITE, BLACK);
  ST7735_WriteString(105,25, alunosq , Font_7x10, WHITE, BLACK);
  ST7735_WriteString(95, 25,"/",Font_7x10,WHITE, BLACK);
  ST7735_WriteString(00, 25,"NUM.ALUNOS:",Font_7x10,WHITE, BLACK);
  ST7735_WriteString(00, 40,"ALU.FORA:",Font_7x10,WHITE, BLACK);

  ST7735_WriteString(75 ,40, ban , Font_7x10, WHITE, BLACK);
  ST7735_WriteString(90, 40,"/3" , Font_7x10, WHITE, BLACK);
}
void DrawLines()
{
	char c[3];

		    c[0] = (x / 10) + '0';
		    c[1] = (x % 10) + '0';
		    c[2] = '\0';


		ST7735_WriteString(0,0, "    LOGGIN   " , Font_11x18, WHITE, GREEN);
		ST7735_WriteString(55,40, c , Font_16x26, WHITE, BLACK);
		ST7735_WriteString(10,70, "pa9 + pa11 -" , Font_7x10, WHITE, BLACK);

}
void Drawmenu()
{
	int falta = alunosquant - alunos;

	char fal[3];

			    fal[0] = (falta / 10) + '0';
			    fal[1] = (falta % 10) + '0';
			    fal[2] = '\0';
    char sai[3];

			    		    sai[0] = (saida / 10) + '0';
			    		    sai[1] = (saida % 10) + '0';
			    		    sai[2] = '\0';

 	ST7735_WriteString(0,10, "RELATORIO  " , Font_11x18, WHITE, BLACK);
 	ST7735_WriteString(0,40, "FALTAS:", Font_7x10, WHITE, BLACK);
 	ST7735_WriteString(50,40, fal , Font_7x10, WHITE, BLACK);
 	ST7735_WriteString(0,55, "N DE SAIDAS:" , Font_7x10, WHITE, BLACK);
 	ST7735_WriteString(90,55, sai , Font_7x10, WHITE, BLACK);


}
void Drawerro2(){
	ST7735_WriteString(0,0, "SENHA" , Font_11x18, WHITE, RED);
	ST7735_WriteString(0,20, "INCORRETA" , Font_11x18, WHITE, RED);
}
void Drawerro(){
	ST7735_WriteString(0,0, "ERRO " , Font_16x26, WHITE, RED);
	ST7735_WriteString(0,27, "QUANTIDADE DE ALUNOS OU BANHEIRO EXEDIDA" , Font_7x10,WHITE, RED);
	ST7735_WriteString(0,50, "PRESSIONE QUALQUER TECLA PARA RETORNAR" , Font_7x10,WHITE, RED);
}
void Drawalunos()

{
	  char alunosq[3];

	    alunosq[0] = (alunosquant / 10) + '0';
	    alunosq[1] = (alunosquant % 10) + '0';
	    alunosq[2] = '\0';

	ST7735_WriteString(0,0, "DEFINA A QUANTIDADE DE ALUNOS   " , Font_7x10, WHITE, BLACK);
  ST7735_WriteString(0,30, alunosq , Font_11x18, WHITE, BLACK);
  ST7735_WriteString(20,30, "/99", Font_11x18, WHITE, BLACK);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------r   ----*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
srand(time(NULL));
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

ST7735_Init();
DrawLines(x);
Drawalunos();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

	  if(estadoAtual != ultimoEstado)
	     {
	         switch(estadoAtual)
	         {
	         case BEGINE:
	         ST7735_FillScreen(BLACK);
	         break;
	             case LOGIN:
	                 ST7735_FillScreen(BLACK);
	                 break;
	             case DEFINIR:
	            	  ST7735_FillScreen(BLACK);
	            	  break;

	             case AULA:
	                 ST7735_FillScreen(BLACK);
	                 break;

	             case RELATORIO:
	            	 ST7735_FillScreen(BLACK);
	            	 break;
	             case ERRO:
	             ST7735_FillScreen(RED);
	             break;
	             case ERRO2:
	             	 ST7735_FillScreen(RED);
	             	     break;
	         }

	         ultimoEstado = estadoAtual;
	     }

	     switch(estadoAtual)
	     {
	     case BEGINE:
	    	 telainicial();
	    	 break;
	         case LOGIN:
	        	 senha;
	             telalogin();
	             break;

	         case RELATORIO:
	        	 telarelatorio();
	             break;

	         case AULA:
	             telaaula();
	             break;

	         case DEFINIR:
	         teladefinir();
	         	 break;
	         case ERRO:
	         telaerro();
	         break;
	         case ERRO2:
	         telaerro2();
	         break;
	     }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin|led1_Pin|led2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin led1_Pin led2_Pin */
  GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin|led1_Pin|led2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : left_Pin down_Pin right_Pin up_Pin */
  GPIO_InitStruct.Pin = left_Pin|down_Pin|right_Pin|up_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
