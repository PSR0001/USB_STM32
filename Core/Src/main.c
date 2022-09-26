/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * @author         : Partha Singha Roy
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern USBD_HandleTypeDef hUsbDeviceFS;

char msg_buff[100];

typedef struct {
	uint8_t MODIFIER;
	uint8_t RESERVED;
	uint8_t KEYCODE1;
	uint8_t KEYCODE2;
	uint8_t KEYCODE3;
	uint8_t KEYCODE4;
	uint8_t KEYCODE5;
	uint8_t KEYCODE6;
}subKeyBoard;

subKeyBoard keyBoardHIDsub= {0,0,0,0,0,0,0,0};

void Fun();
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void KeyBoardPrint(char *data,uint16_t length)
	  {
	  	for(uint16_t count=0;count<length;count++)
	  	{
	  		if(data[count]>=0x41 && data[count]<=0x5A)
	  		{
	  			keyBoardHIDsub.MODIFIER=0x02;
	  			keyBoardHIDsub.KEYCODE1=data[count]-0x3D; //04 to 1D all the alphabet
	  			USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
	  			Fun();
	  		}
	  		else if(data[count]>=0x61 && data[count]<=0x7A)
	  		{
	  			keyBoardHIDsub.KEYCODE1=data[count]-0x5D;  //04 to 1D all the alphabet
	  			USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
	  			Fun();
	  		}
//	  		else if(data[count]==0x21)
//			{
//	  			keyBoardHIDsub.MODIFIER=0x02;
//	  			keyBoardHIDsub.KEYCODE1=0x1E; //for !
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//				HAL_Delay(15);
//				keyBoardHIDsub.KEYCODE1=0x00;
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//			}
//	  		else if(data[count]==0x22)
//			{
//	  			keyBoardHIDsub.MODIFIER=0x02;
//				keyBoardHIDsub.KEYCODE1=0x34; //for "
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//				HAL_Delay(15);
//				keyBoardHIDsub.KEYCODE1=0x00;
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//			}

//	  		else if(data[count]>=0x23 && data[count] <= 0x25 )
//			{
//				keyBoardHIDsub.MODIFIER=0x02;
//				keyBoardHIDsub.KEYCODE1= data[count]-0x03; //for # $ %
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//				HAL_Delay(15);
//				keyBoardHIDsub.KEYCODE1=0x00;
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//			}
	  		else if(data[count]==0x27)
			{
				keyBoardHIDsub.KEYCODE1=0x34; //for '
				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
				Fun();
			}
	  		else if(data[count]>=0x28 && data[count] <= 0x29 )
			{
				keyBoardHIDsub.MODIFIER=0x02;
				keyBoardHIDsub.KEYCODE1= data[count]-0x02; //for ( )
				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//				HAL_Delay(15);
//				keyBoardHIDsub.KEYCODE1=0x00;
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
				Fun();
			}
//	  		else if(data[count]>=0x2A )
//			{
//				keyBoardHIDsub.MODIFIER=0x02;
//				keyBoardHIDsub.KEYCODE1= 0x25; //for *
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//				HAL_Delay(15);
//				keyBoardHIDsub.KEYCODE1=0x00;
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//			}
//	  		else if(data[count]>=0x23 && data[count] <= 0x25 )
//			{
//				keyBoardHIDsub.MODIFIER=0x02;
//				keyBoardHIDsub.KEYCODE1= data[count]-0x03; //for # $ %
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//				HAL_Delay(15);
//				keyBoardHIDsub.KEYCODE1=0x00;
//				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
//			}
	  		else if(data[count]==0x3D)
			{
				keyBoardHIDsub.KEYCODE1=0x2E; // for =
				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
				Fun();
			}
	  		else if(data[count]==0x2E)
			{
				keyBoardHIDsub.KEYCODE1=0x37; // for .
				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
				Fun();
			}
	  		else if(data[count]==0x7B)
			{
	  			keyBoardHIDsub.MODIFIER=0x02;
				keyBoardHIDsub.KEYCODE1=0x2F; //for {
				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
				Fun();
			}
	  		else if(data[count]==0x7D)
			{
	  			keyBoardHIDsub.MODIFIER=0x02;
				keyBoardHIDsub.KEYCODE1=0x30; //for }
				USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
				Fun();
			}
	  		else if(data[count]==0x20)
	  		{
	  			keyBoardHIDsub.KEYCODE1=0x2C;
	  			USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
	  			Fun();
	  		}

	  		else if(data[count]==0x2B)
	  		{
	  			keyBoardHIDsub.KEYCODE1=0x28;
	  			USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
	  			Fun();
	  		}
	  		HAL_Delay(25);
	  	}
	  }


void Fun(){
	HAL_Delay(15);
	keyBoardHIDsub.MODIFIER=0x00;
	keyBoardHIDsub.KEYCODE1=0x00;
	USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
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

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  //use sprintf for writing the string in msg_buff
  int buffer=sprintf(msg_buff,"function STM(){+let A = 'I can You Can'+return ()=>{+console.log(A)+}+}+STM()()++");


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  KeyBoardPrint(msg_buff, buffer);
	  HAL_Delay(5000);

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
