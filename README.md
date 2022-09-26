# **STM USB keyboard** 
In this Project, The STM32 USB feature is used to create a virtual keyboard. 


## Software Used 
- [CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)

## Key Concept
This Project main idea is to develop a virtual keyboard inside microcontroller. 

## Track:





in initial state when you setup the stm32 usb its mode is by default **Mouse**.




Enter below code in between ``/* USER CODE BEGIN PV */``
```c:
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
```

The main USB Function 

```c:
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
				Fun();
			}
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

```




