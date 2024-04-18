#define WIFI_RX_PIN F7
#define WIFI_TX_PIN F6
#define UART_RX_PIN F10
#define UART_TX_PIN F11
#define BAUD_RATE_WIFI 9600
#define BAUD_RATE 9600

const char* CMD_AT = "AT\r\n";
const char* CMD_RST = "AT+RST\r\n";
const char* CMD_MODE = "AT+CWMODE=1\r\n";
const char* CMD_LIST_AP = "AT+CWLAP\r\n";


void response_wait(){
  unsigned resp;
  unsigned counter = 0;
  while(1)
  {
    if(UART1_Data_Ready() == 1)
    {
      resp = UART1_Read();
      UART2_Write(resp);
      counter = 0;
    }
    else
    {
      counter++;
      Delay_ms(1);
    }
    if(counter == 5000)
      break;
  }
}


void main()
{

  AD1PCFG = 0xFFFF;
  TRISB = 0;
  LATB = 0;

  Unlock_IOLOCK();
  PPS_Mapping_NoLock(6, _INPUT, _U2RX);     //Set UART1 Rx be pin RP0
  PPS_Mapping_NoLock(7, _OUTPUT, _U2TX);   //Set UART1 Tx be pin RP1
  Lock_IOLOCK();

  Unlock_IOLOCK();
  PPS_Mapping_NoLock(15, _INPUT, _U1RX);     //Set UART1 Rx be pin RP7
  PPS_Mapping_NoLock(10, _OUTPUT, _U1TX);   //Set UART1 Tx be pin RP6
  Lock_IOLOCK();


  UART1_Init(BAUD_RATE_WIFI);
  Delay_ms(500);
  UART2_Init(BAUD_RATE);
  Delay_ms(500);

  UART2_Write_Text("Sending reset command...\r\n");
  Delay_ms(100);
  UART1_Write_Text(CMD_RST);
  response_wait();

  Delay_ms(500);

  UART2_Write_Text("Sending AT command...\r\n");
  Delay_ms(100);
  UART1_Write_Text(CMD_AT);
  response_wait();

  Delay_ms(500);

  UART2_Write_Text("\nListing available APs...\r\n");
  Delay_ms(100);
  UART1_Write_Text(CMD_LIST_AP);
  response_wait();
  
  Delay_ms(500);

  while(1)
  {
    if(UART1_Data_Ready() == 1)
    {
      UART2_Write(UART1_Read());
      Delay_ms(5);
    }
  }
}