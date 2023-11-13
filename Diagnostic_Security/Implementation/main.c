#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO.h"

#include "LCD_Interface.h"
#include "UART_Interface.h"

#include "UART_Services.h"
#include <string.h>


#define  F_CPU	8000000
#include <util/delay.h>
u8 service[8] = "3101AA00";
u8 subService[8];
u8 service_2[4] = "2701";
u8 subService_2[4];
u8 securityFlag=0;
u8 CodeBeforeRand[4] = "6701"; 	
u8 CodeEncrypted[] = "2702"; 	
	
u8 NRC1[] = "7F3135";
u8 NRC2[] = "7101AA00";
u8 randomBytes[8] = "84251745";	//send on uart 2702
u8 key[8] = "01010101";
u8 encryptedBytes[8] ;
u8 decryptedBytes[8];

void encryptBytes(u8* arr, u8 length,  u8 *key);
void SendSecurityAccess(void);
int main(void)
{
	DIO_Init();
	LCD_Init();
	UART_Init();
	
	
	
    while(1) 
    {	
		UART_ReceiveString(subService);
		if (memcmp(service, subService, 8) == 0)
		{
			if(securityFlag == 0)
			{
				LCD_WriteString(NRC1);
				SendSecurityAccess();
			}
			else
			{
				LCD_Clear();
				LCD_WriteString(NRC2);
				DIO_WritePin(PINC0,HIGH);
			}
		}
		
	}
}

void SendSecurityAccess(void)
{
	UART_ReceiveString(subService_2);
	if(memcmp(service,subService_2,8)==0)
	{
		LCD_Clear();
		encryptBytes(randomBytes,8,key);
		LCD_GoTo(0,0);
		LCD_WriteString(CodeBeforeRand);
		LCD_WriteString(encryptedBytes);
		LCD_GoTo(2,0);
		LCD_WriteString(randomBytes);
	}
	UART_ReceiveString(decryptedBytes);
	if(memcmp(randomBytes,decryptedBytes,8)==0)
	{
		LCD_Clear();
		LCD_WriteString(CodeEncrypted);
		securityFlag=1;
		LCD_WriteString("6702");
	}
	else
	{
		LCD_WriteString("7F2735");
	}
	
}
void encryptBytes(u8* arr, u8 length, u8 *key)
{
	// Implementing symmetric encryption algorithm here
	// Example: using XOR encryption with the secureAccessKey:
	for(u8 i=0; i<length; i++)
	{
		encryptedBytes[i] = arr[i]^key[i];
	}
	/*for (u8 i = 0; i < length; i++)
	{
		arr[i] ^= key[i % 4];
	}
	*/
}
