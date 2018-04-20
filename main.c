#include "Libraries.h";

#define inputs GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7

/*Pin Connections:
 * PE4 [pin 5]  -> RS
 * PE5 [pin 6]  -> EN
 * PD0 [pin 23] -> D4
 * PD1 [pin 24] -> D5
 * PD2 [pin 25] -> D6
 * PD3 [pin 26] -> D7
*/

/* Input pins:
Keypad       Tiva
 2            PC4
 7            PC5
 6            PC6
 4            PC7

 Output pins:
Keypad       Tiva
 3            PB4
 1            PB0
 5            PB1
 */

// Function Declarations
int CheckRow();
int CheckColumn();
void initKeypad();
int BaseMenu();
void MainMenuChoice();
int GetKeyPress();

static int keys[4][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9},
    {10,0,12}
};
uint32_t prevNum = 20;

//global variables
int maintPass;
int cleanPass;
int adminPass;

//start of main program
void main(void)
{
    maintPass = 2;  //declaring passwords
    cleanPass = 5;
    adminPass = 7;


    //80Mhz, 16Mhz crystal
  //  SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
 SysCtlClockSet(SYSCTL_SYSDIV_8|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  initLCD();
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);  // enable ports
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4); //Set output pins



  GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7); //Set input pins

  GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPD);
   GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_5,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPD);
   GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPD);
   GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_7,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPD);//Turn on pull up resistor of PB4
   GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4); // Write outputs high PartB



  SysCtlDelay(10000000);



  while(1) //to keep menu running
  {
      GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4);

      BaseMenu();
  }

}

/****************************   Functions *******************************/

int BaseMenu()  //menu function, runs continuously through loop, once options are finished returns to beginning, if password is incorrect returns to beginning
{
    clearLCD();  //initial menu to put in pin
    setCursorPositionLCD(0,5);
    printLCD("USER MENU");
    setCursorPositionLCD(2,0);
    printLCD("Enter PIN:");


    SysCtlDelay(1000000);

    while (GetKeyPress() == -1);
    int choice = GetKeyPress();  //get password input

    if (choice == adminPass)  //if password is correct continue into if statement
    {
            clearLCD();  //secondary menu
            printLCD("1) Maintenance");
            setCursorPositionLCD(1,0);
            printLCD("2) Cleaning");
            setCursorPositionLCD(2,0);
            printLCD("3) Administration");
            SysCtlDelay(10000000);
            while (GetKeyPress() == -1);
            int choiceTwo = GetKeyPress();  //menu choice input from keypad

            switch(choiceTwo)
            {
            case 1:  //for option 1

                    clearLCD();
                    printLCD("Enter maintenance");
                    setCursorPositionLCD(1,0);
                    printLCD("password:");
                    setCursorPositionLCD(2,0);
                    SysCtlDelay(10000000);
                    while (GetKeyPress() == -1);
                    int choiceThree = GetKeyPress();  //waiting for password input

                    if (choiceThree == maintPass)  //if password is correct
                    {
                        clearLCD(); //code for stepper motor move would go inside here
                        setCursorPositionLCD(1,0);
                        printLCD("Moving into position");
                        SysCtlDelay(100000000);
                        break;
                    }
                    else {  //if password is incorrect
                        clearLCD();
                        setCursorPositionLCD(1,0);
                        printLCD("Incorrect Password!");
                        SysCtlDelay(10000000);
                        break;
                    }

            case 2: //for option 2

                    clearLCD();
                    printLCD("Enter cleaning");
                    setCursorPositionLCD(1,0);
                    printLCD("password:");
                    setCursorPositionLCD(2,0);
                    SysCtlDelay(10000000);
                    while (GetKeyPress() == -1);
                    int choiceFour = GetKeyPress();  //waiting for password input

                    if (choiceFour == cleanPass)  //if password is correct
                    {
                         clearLCD();  //code for motor moving would go in here
                         setCursorPositionLCD(1,0);
                         printLCD("Moving into position");
                         SysCtlDelay(100000000);
                         break;
                    }
                    else {  //if password is incorrect
                         clearLCD();
                         setCursorPositionLCD(1,0);
                         printLCD("Incorrect Password!");
                         SysCtlDelay(10000000);
                         break;
                    }

            case 3:  //for option 3

                clearLCD();
                printLCD("Enter administration");
                setCursorPositionLCD(1,0);
                printLCD("password:");
                setCursorPositionLCD(2,0);
                SysCtlDelay(10000000);
                while (GetKeyPress() == -1);
                int choiceFive = GetKeyPress();  //waiting for password input

                if (choiceFive == adminPass) //if password is correct
                {
                    clearLCD();
                    setCursorPositionLCD(0,2);
                    printLCD("Change Password: ");
                    setCursorPositionLCD(1,0);
                    printLCD("1) Maintenance");
                    setCursorPositionLCD(2,0);
                    printLCD("2) Cleaning");
                    setCursorPositionLCD(3,0);
                    printLCD("3) Administrative");
                    SysCtlDelay(10000000);
                    while (GetKeyPress() == -1);
                    int choiceSix = GetKeyPress(); //waiting for choice input

                        switch (choiceSix)
                        {

                            case 1: //option 1
                                clearLCD();
                                printLCD("Enter new mainten-");
                                setCursorPositionLCD(1,0);
                                printLCD("ance password:");
                                SysCtlDelay(10000000);
                                while (GetKeyPress() == -1);
                                int newMaint = GetKeyPress(); //waiting for new password input
                                maintPass = newMaint; //input is assigned as new password value
                                break;

                             case 2:  //option 2
                                clearLCD();
                                printLCD("Enter new cleaning");
                                setCursorPositionLCD(1,0);
                                printLCD("password:");
                                SysCtlDelay(10000000);
                                while (GetKeyPress() == -1);
                                int newClean = GetKeyPress(); //waiting for new password input
                                cleanPass = newClean;  //input is assigned as new password value
                                break;

                             case 3:  //option 3
                                clearLCD();
                                printLCD("Enter new administr-");
                                setCursorPositionLCD(1,0);
                                printLCD("ation password:");
                                SysCtlDelay(10000000);
                                while (GetKeyPress() == -1);
                                int newAdmin = GetKeyPress(); //waiting for new password input
                                adminPass = newAdmin;  //input is assigned as new password value
                                choiceFive = newAdmin;  //input is also assigned as password inputed so program does not think value is now incorrect
                                choice = newAdmin; //input is also assigned to original pin so program does not think value is now incorrect
                                break;
                             }
                         }
                         if (choiceFive != adminPass) //if password is incorrect
                         {
                             clearLCD();
                             setCursorPositionLCD(1,0);
                             printLCD("Incorrect Password!");
                             SysCtlDelay(10000000);
                               }
                break;
    }
    }
    if (choice != adminPass) //if pin is incorrect
    {
        clearLCD();
        setCursorPositionLCD(1,0);
        printLCD("Incorrect Password!");
        SysCtlDelay(10000000);
    }
    return 0;
}











//********************Key Press functions****************************************

int GetKeyPress()
{
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4);

    int col = CheckColumn();
    int row = CheckRow();
    if (row != -1 && col != -1) return keys[row][col];
    else return -1;

}



//**************************************Check row and column function ****************
int CheckColumn()
{
    int check = GPIOPinRead(GPIO_PORTC_BASE, inputs);
    if (check != 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4, GPIO_PIN_4);
        SysCtlDelay(250000);

        if (GPIOPinRead(GPIO_PORTC_BASE, inputs) != 0)
        {
            return 0;
        }
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4, GPIO_PIN_0);
        SysCtlDelay(250000);

        if (GPIOPinRead(GPIO_PORTC_BASE, inputs) != 0)
        {
            return 1;
        }
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4, GPIO_PIN_1);
        SysCtlDelay(250000);

        if (GPIOPinRead(GPIO_PORTC_BASE, inputs) != 0)
        {
            return 2;
        }

    }
    return -1;
}
int CheckRow()
{
    if (GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4) != 0)
              {
                  return 0;
              }

          else if (GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_5) != 0)
              {
                  return 1;
              }

          else if (GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_6) != 0)
              {
                  return 2;
              }

          else if (GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_7) != 0)
              {
                  return 3;
              }
    return -1;
}



