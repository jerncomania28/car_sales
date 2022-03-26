// import all important Libraries

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>

extern int berrno;

// General constants

#define MAX_SALES 10
#define CSV_FILE "./data.txt"
#define DISCOUNT_MIN_AGE 18
#define DISCOUNT_MAX_AGE 25
#define DISCOUNT_PERCENTAGE 0.1f
#define TRUE 1
#define FALSE 0

// MENU constants

#define BUY_CAR 'a'
#define VIEW_CARS 'b'
#define VIEW_SALES 'c'
#define SAVE 's'
#define MENU_OPTION_EXIT 'x'

// GLOBAL variables

float carPrices[MAX_SALES];

char carModels[MAX_SALES][201];

float discounts[MAX_SALES];

char customerNames[MAX_SALES][201];

unsigned short quantityOrdered[MAX_SALES];

char carModelsAvailable[10][50] = {
    "Jeep Gladiator", "Dodge Stealth", "McLaren Senna", "Acura Legend", "Lancia Stratos"};
unsigned short carModelsQuantityAvailable[5] = {1, 3, 2, 3, 1};

float carModelPricesPerSale[5] = {152.9f, 1595.5f, 1640.0f, 1530.3f, 2613.5f};

int numberOfSales = 0;

unsigned short totalNumberOfCarsAvailable;

char *_message = "Please enter a Choice : ";

bool data_changed = false;



// FILE codes

#define FILE_OPENED 0
#define FILE_CLOSED 1
#define FILE_ERROR 2

FILE *file;
unsigned char fileStatus = FILE_CLOSED;

// clear the screen function
void clearScreen()
{

    system("cls");
}

// pause the program Function

void pauseProgram(char userChoice)
{
    if (userChoice == MENU_OPTION_EXIT)
    {
        printf("\n\n Press Enter to Exit ....");
    }
    else
    {
        printf("\n\n Press Enter to return to the Menu ...");
    }

    if (userChoice != '_')
    {
        getchar();
    }

    getchar();
}

// get Character from console 
char getCharFromConsole(char message[201], char *altMessage)
{
 
 	char userInput;
 		bool b = false;

     // print altMessage everytime as far as UserInput != Alphabet
	while(true){


    printf((b) ? altMessage : message);

    scanf("\n %c", &userInput);
    if(isalpha(userInput)){

        // break out of loop if UserInput == Alphabet.
    	break;
	}
	else{
		b = true;
	}
    
	}

    // return lowercase of Input
    return tolower(userInput);
}

/* A function to check if a string is fully a number
*/

bool checker(char* str){
	int length = sizeof(str) / sizeof(char);
		
		for(int i = 0; i<length; i++){
			if(isdigit(str[i])){
				return false;
			}
		}
	return true;
	}


unsigned short getUnsignedShortFromConsole(char message[301])
{
    unsigned short userInput;
    printf(message);
    scanf("%hd", &userInput);
    return userInput;
}

void getStringFromConsole(char message[201], char *str, char *altMessage)
{
	bool b = false;
	while(true){


    char *f_message = ((b) ? altMessage : message);
    printf("%s",f_message);
	
    scanf("\n%[^\n]s", str);
    if(!checker(str)){
    	b = true;
	}
    else{
    	break;
	}
}
}

// FILE FUNCTIONS
FILE *createFile(char fileName[201])
{

    file = fopen(fileName, "w");

    if (file != NULL)
    {
        fclose(file);
    }

    return file;
}

// opening a file

void openFile(char fileName[201], char mode[4])
{

    file = fopen(fileName, mode); // this generally opens a file.

    // now if the file we have passed in is empty == NULL ;
    if (file == NULL)
    {

        // we attempt to then create One

        if (createFile(fileName) == NULL)
        {
            // if the  just created file is still equals to NULL

            fileStatus = FILE_ERROR;
        }
        else
        {
            // the newly created file is not equal to NULL
            openFile(fileName, mode);
        }
    }
    else
    {

        // if file opened sucessfully at the beginning
        fileStatus = FILE_OPENED;
    }
}

void closeFile()
{

    if (fileStatus == FILE_OPENED)
    {
        fclose(file);
        fileStatus = FILE_CLOSED;
    }
}

int find(char* str){
	if((sizeof(str) / sizeof(char)) <1)
	return -1;
//	printf("finder method called with %s",str);
	for(int i=0; i<(sizeof(carModelsAvailable) / sizeof(char*)); i++){
		if(strcmp(carModelsAvailable[i],str) == 0){
			return i;
		}
	}
	return -1;
}

void readDataFromFile()
{
    int counter = -1;
    
    //counts the quantity
    int quantity=0;

    while (true)
    {
        unsigned short carPrice, quantityOrder,discount;
        char nameOfCar[201] = "", customerName[201] = "";

       int fileData = fscanf(file, "%[^,],%hu,%[^,],%hu,%hu\n", &nameOfCar, &carPrice, &customerName, &quantityOrder,&discount);
    
	
        // break if EOF(end of file ) reached.
        if (fileData == EOF)
        {
            break;
        }
		printf("%s %d %s %d %d\n",nameOfCar,carPrice,customerName,quantityOrder,discount);
        carPrices[counter] = carPrice;
        quantityOrdered[counter] = quantityOrder;
        discounts[counter] = discount;
        strcpy(carModels[counter], nameOfCar);
        strcpy(customerNames[counter], customerName);

        // printf("%d counter number \n", counter);
        
        //update the quantity of cars available with the 
        //data gotten from the file
        int position = find(nameOfCar);
       // printf(" position%d", position);
        carModelsQuantityAvailable[position] -= quantityOrder;
     
        

        counter++;
    }

    numberOfSales = counter;
}

void getDataFromFile()
{
    openFile(CSV_FILE, "r");

    if (fileStatus == FILE_OPENED)
    {
        readDataFromFile();
    }
    else if (fileStatus == FILE_ERROR)
    {
        printf("There was an error trying to read from the file %s.", CSV_FILE);

        pauseProgram('_');
    }

    closeFile();
}

// char *my_itoa(int value, char *str, int base)
// {
//     if (str == NULL)
//     {
//         return NULL;
//     }
//     sprintf(str, "%d", value);
//     return str;
// }

void writeDataToFile()

{
	
    for (int i = 0; i < numberOfSales; i++)
    { 
	if((sizeof(carModels[i]) / sizeof(char*)) <1 || carPrices[i] == 0){
		break;
	}
	 char line[201];

        char data[50];

        strcpy(line, carModels[i]);

        strcat(line, ",");

        sprintf(data, "%d", (int)carPrices[i]);

        // itoa((int)carPrices[i],data,10);

        strcat(line, data);

        strcat(line, ",");

        strcat(line, customerNames[i]);
        strcat(line, ",");

        sprintf(data, "%d", (int)quantityOrdered[i]);

        // itoa( (int)quantityOrdered[i],data,10);

        strcat(line, data);
        //   strcat(line, ",");

        // sprintf(data, "%f", discounts[i]);

        // itoa( (int)quantityOrdered[i],data,10);
        strcat(line, ",");
        
 		sprintf(data, "%d", discounts[i] * 100);
        strcat(line, ",");
        
 		sprintf(data, "%d", discounts[i] * 100);

        strcat(line, data);
        
       // strcpy(line, "\n\n testing written files");

        fprintf(file, line);

        if (i < numberOfSales - 1)
        {
            fprintf(file, "\n");
        }
    }

}

void saveDataToFile()
{
	if(data_changed){
    openFile(CSV_FILE, "w");

    if (fileStatus == FILE_OPENED)
    {
        writeDataToFile();
        data_changed = false;
    }
    else if (fileStatus == FILE_ERROR)
    {
        printf("There was an error trying to write the file %s.", CSV_FILE);

        pauseProgram('_');
    }

    closeFile();
    	}

}

// end of file functions.

void menu_greetCustomer()
{

    printf("Welcome to REINGEARD CAR STORE ! \n\n");
}

void menu_showMenu()
{

    printf("Menu :\n");
    printf("%c. Buy A Car\n", BUY_CAR);
    printf("%c. View Cars\n", VIEW_CARS);
    printf("%c. View sales\n", VIEW_SALES);
    printf("%c. Save\n", SAVE);
    printf("%c. Exit\n\n", MENU_OPTION_EXIT);
}

void swapUnsignedShort(unsigned short *a, unsigned short *b)
{
    unsigned short temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swapFloat(float *a, float *b)
{
    float temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void sortArraysByQuantityAvailable(int length)
{

    for (int i = 0; i < length - 1; i++)
    {

        for (int j = i + 1; j < length; j++)
        {

            if (carModelsQuantityAvailable[j] > carModelsQuantityAvailable[i])
            {

                swapUnsignedShort(&carModelsQuantityAvailable[j], &carModelsQuantityAvailable[i]);

                swapFloat(&carModelPricesPerSale[j], &carModelPricesPerSale[i]);

                // and in the discountGivenPerSale array
                // swapBool(&discountGivenPerSale[i], &discountGivenPerSale[j]);

                char temp[201];
                strcpy(temp, carModelsAvailable[i]);
                strcpy(carModelsAvailable[i], carModelsAvailable[j]);
                strcpy(carModelsAvailable[j], temp);

            } // end of "if" statement

        } // end of second "for" loop

    } // end of first "for" loop
}

// show all cars available in store .
void menu_showAllCars()
{

    int length = sizeof(carModelPricesPerSale) / sizeof(float);

    sortArraysByQuantityAvailable(length);

    // printf("%d\n", totalNumberOfCarsAvailable);

    printf("\n CARS AVAILABLE IN STORE :\n");

    printf("====================================================\n\n");

    printf("S/N\tNAME OF CARS\t QUANTITY AVAILABLE \t UNIT PRICE \n\n");

    for (int i = 0; i < length; i++)
    {
        printf("%d\t%s \t\t%hd \t\t %f \n", i, carModelsAvailable[i], carModelsQuantityAvailable[i], carModelPricesPerSale[i]);

       // totalNumberOfCarsAvailable += carModelsQuantityAvailable[i];
    }

    printf("\n\n");

    printf("=====================================================\n\n");
}

// End of  show all cars available in store.

bool checkIfDiscountIsNeeded(unsigned short userAge)
{

    if (userAge >= DISCOUNT_MIN_AGE)
    {

        printf("You are eligible to Drive\n");

        return TRUE;
    }
    else
    {
        printf("You are below Driving Age \n");

        return FALSE;
    }
}

float applyDiscount(float currentPrice)
{
    return currentPrice * (1 - DISCOUNT_PERCENTAGE);
}

void printDiscountOutcome(bool giveDiscount)
{

    switch (giveDiscount)
    {

    case TRUE:
        printf("\n You got a discount!\n\n");
        
        break;

    case FALSE:
        printf("\n No discount given.\n\n");
        break;
    }
}

void menu_buyCar()
{



    unsigned short numberOfCarsNeeded = 0, userAge = 0, carChoosen;
    bool giveDiscount = FALSE;
    float totalPrice = 0;

    getStringFromConsole("What is your name ? Name :", &customerNames[numberOfSales],"Please enter a valid name without NUMBER : ");
    // getStringFromConsole("What is your name ? Name :", customerNames[numberOfSales]);
    // getStringFromConsole("What is your name ? Name :", customerNames[numberOfSales]);
	menu_showAllCars();
    carChoosen = getUnsignedShortFromConsole("select the type of Car you want from the Displayed Table Above ? ");

    int totalNumberOfCarsAvailable = sizeof(carModelPricesPerSale) / sizeof(float);
    if (carChoosen < totalNumberOfCarsAvailable)
    {

        printf("You have selected %s we Have just %hd available and it cost %f Each. \n\n", carModelsAvailable[carChoosen], carModelsQuantityAvailable[carChoosen], carModelPricesPerSale[carChoosen]);

        numberOfCarsNeeded = getUnsignedShortFromConsole("Enter the Number Needed : ");

        if (numberOfCarsNeeded <= carModelsQuantityAvailable[carChoosen])
        {

            printf("We can satisfy the Quantity of %s requested \n\n", carModelsAvailable[carChoosen]);

            totalPrice = numberOfCarsNeeded * carModelPricesPerSale[carChoosen];

            userAge = getUnsignedShortFromConsole("How old are you? Age : ");

            giveDiscount = checkIfDiscountIsNeeded(userAge);

            if (giveDiscount == TRUE)
            
            {
            	discounts[numberOfSales] = 1- DISCOUNT_PERCENTAGE;
                totalPrice = applyDiscount(totalPrice);
            }
			else{
					discounts[numberOfSales] = 1.0;
			}
			
            printDiscountOutcome(giveDiscount);
            carPrices[numberOfSales] = carModelPricesPerSale[carChoosen];

            carModelsQuantityAvailable[carChoosen] = carModelsQuantityAvailable[carChoosen] - numberOfCarsNeeded;

            // printf("we have a total of %hd %s Remaining in store ", carModelsQuantityAvailable[carChoosen], carModelsAvailable[carChoosen]);

            quantityOrdered[numberOfSales] = numberOfCarsNeeded;

            strcpy(carModels[numberOfSales], carModelsAvailable[carChoosen]);

            // present the outcome
            printf("\n\nThank you.\n");
            printf("You have bought %hd %s.\n", numberOfCarsNeeded, carModelsAvailable[carChoosen]);
            printf("Total cost is %f GBP.\n", totalPrice);
            printf("\nThere are %hd  %s remaining.", carModelsQuantityAvailable[carChoosen], carModelsAvailable[carChoosen]);
			numberOfSales++;
        }
    }
    else
    {
        printf("Sorry ,The selected Number isn't listed in The Display. \n\n");
    }
    // numberOfSales++;
    // data_changed = true;
   
   
}

void menu_exit()
{
    printf("Thank you for using Our car Sales Management Program . Bye-bye!");

    saveDataToFile();
}

void printSalesDataAtPosition(int position)
{

    float price = carPrices[position] * quantityOrdered[position];

    printf("Sale Index: %d | Sale Amount: %f | Car Model: %s | "
           "Car Price: %f | Number of Tickets: %hd | "
           "Customer Name: %s\n",
           // please note that the above are three separate strings that will be glued together by the program
           position, price, carModels[position],
           carPrices[position], quantityOrdered[position],
           customerNames[position]);
}
//Counts the number of cars available for sale

void countAvailableCars(){
	 int length = sizeof(carModelPricesPerSale) / sizeof(float);
	 totalNumberOfCarsAvailable = 0;
	 for(int i=0; i<length; i++){
	 	totalNumberOfCarsAvailable += carModelsQuantityAvailable[i];
	 }
}
void view_sales()
{

    sortArraysByQuantityAvailable(numberOfSales);

    float totalSalesValue = 0;
    unsigned int numberOfcarSold = 0;

    printf("\nAll sales Data : \n\n");

    // printf("%d number of cars sold" , numberOfSales);

    for (int i = 0; i < numberOfSales; i++)
    {

        float price = carPrices[i] * quantityOrdered[i];
//        if(price == 0.0){
//        	continue;
//		}   
		
	
		//char *formatted_discount = (discounts[i] == 0.0) ? "No" : "";
		
        // printSalesDataAtPosition(i);
		// printf("\n%s car model, sold for %f GBP at %f GBP per one for %hd quantity with %.2f Discount \n to %s ",carModels[i], price,carPrices[i],  quantityOrdered[i],discounts[i],customerNames[i]);
		printf("\n\n%s car model, sold for %f GBP at %f GBP per one for %hd quantity with %.2f discount to %s ",carModels[i], price,carPrices[i],  quantityOrdered[i],discounts[i],customerNames[i]);
		printf("\n\n%s car model, sold for %f GBP at %f GBP per one for %hd quantity with %.2f discount to %s ",carModels[i], price,carPrices[i],  quantityOrdered[i],discounts[i],customerNames[i]);
        totalSalesValue += price;
        numberOfcarSold += quantityOrdered[i];
    }

    totalNumberOfCarsAvailable -= numberOfcarSold;
   countAvailableCars();
    printf("\nThere are %d number of cars available",totalNumberOfCarsAvailable);

   // printf("\n %hd Cars have been sold with a total value of %f GBP , there are %hd Cars remamining", numberOfcarSold, totalSalesValue, totalNumberOfCarsAvailable);
}



void programLoop(){
	
	
	char userChoice;

	  do
    {

       // clearScreen();

        menu_greetCustomer();
        menu_showMenu();
		
        userChoice = getCharFromConsole(_message,"Please Enter a valid alphabet input :");
        _message = "Please enter a choice : ";
        
        // clearScreen();
        // userChoice = getCharFromConsole("Please Choose one : ");
        if(!isalpha(userChoice)){
	
        // userChoice = getCharFromConsole("Please Enter a valid alphabet input");
        continue;
    }
       clearScreen();
        switch (userChoice)
        {
        case BUY_CAR:
            menu_buyCar();
            break;
        case VIEW_CARS:
            menu_showAllCars();
            break;

        case VIEW_SALES:

            view_sales();

            break;
            
            case SAVE:
            	saveDataToFile();
            	break;

        case MENU_OPTION_EXIT:

            menu_exit();
            break;
        
        default : 
       		_message = "Ensure the option is mapped to a menu\nEnter choice again : ";
        	programLoop();
			break;
		}

        pauseProgram(userChoice);
  

    }
	 while (userChoice != MENU_OPTION_EXIT);

}

//The main method 
//Entry to the app
void main()
{
	
	countAvailableCars();
    getDataFromFile();

    programLoop();
    clearScreen();

    printf("\n\nHave a  good day!\n\n");
}