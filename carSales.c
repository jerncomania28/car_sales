#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int errno;

#define MAX_SALES 10
#define CSV_FILE "./data.txt"

// MENU constants

#define BUY_CAR 'a'
#define VIEW_CARS 'b'
#define VIEW_SALES 'c'
#define MENU_OPTION_EXIT 'x'

unsigned short carPrices[MAX_SALES];

char carModels[MAX_SALES][201];

char customerNames[MAX_SALES][201];

char carModelsAvailable[5][50] = {
    "Jeep Gladiator", "Dodge Stealth ", "McLaren Senna ", "Acura Legend  ", "Lancia Stratos"};
unsigned short carModelsQuantityAvailable[5] = {1, 3, 2, 3, 1};

float carModelPricesPerSale[5] = {152.9f, 1595.5f, 1640.0f, 1530.3f, 2613.5f};

unsigned short numberOfSales = 0;

//  file codes

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

char getCharFromConsole(char message[201])
{

    char userInput;

    printf(message);

    scanf("\n %c", &userInput);

    return userInput;
}

unsigned short getUnsignedShortFromConsole(char message[201])
{
    unsigned short userInput;

    printf(message);
    scanf("%hd", &userInput);

    return userInput;
}

void getStringFromConsole(char message[201], char *str)
{
    printf(message);

    scanf("\n%[^\n]s", str);
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

void readDataFromFile()
{
    int counter = 0;

    while (1)
    {
        unsigned short carPrice;
        char nameOfCar[201] = "", customerName[201] = "";

        int fileData = fscanf(file, "%s,%hd,%s", &nameOfCar, &carPrice, &customerName);

        // break if EOF(end of file ) reached.
        if (fileData == EOF)
        {
            break;
        }

        carPrices[counter] = carPrice;

        strcpy(carModels[counter], nameOfCar);
        strcpy(customerNames[counter], customerName);

        // printf("%d counter number \n", counter);

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

char *my_itoa(int num, char *str)
{
    if (str == NULL)
    {
        return NULL;
    }
    sprintf(str, "%d", 10);
    return str;
}

void writeDataToFile()
{

    for (int i = 0; i < numberOfSales; i++)
    {
        char line[201];

        char data[50];

        strcpy(line, carModels[i]);

        strcat(line, ",");

        // _itoa(
        // (int)carPrices[i], data, 10);

        my_itoa((int)carPrices[i], data);

        strcat(line, data);

        strcat(line, ",");

        strcat(line, customerNames[i]);

        fprintf(file, line);

        if (i < numberOfSales - 1)
        {
            fprintf(file, "\n");
        }
    }
}

void saveDataToFile()
{
    openFile(CSV_FILE, 'w');

    if (fileStatus == FILE_OPENED)
    {
        writeDataToFile();
    }
    else if (fileStatus == FILE_ERROR)
    {
        printf("There was an error trying to write the file %s.", CSV_FILE);

        pauseProgram('_');
    }

    closeFile();
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

void menu_showAllCars()
{

    int totalNumberOfCarsAvailable = sizeof(carModelPricesPerSale) / sizeof(float);

    sortArraysByQuantityAvailable(totalNumberOfCarsAvailable);

    printf("%d\n", totalNumberOfCarsAvailable);

    printf("\n CARS AVAILABLE IN STORE :\n");

    printf("====================================================\n\n");

    printf("S/N\tNAME OF CARS\t QUANTITY AVAILABLE \t UNIT PRICE \n\n");

    for (int i = 0; i < totalNumberOfCarsAvailable; i++)
    {
        printf("%d\t%s \t\t%hd \t\t %f \n", i, carModelsAvailable[i], carModelsQuantityAvailable[i], carModelPricesPerSale[i]);
    }

    printf("\n\n");

    printf("=====================================================\n\n");
}
void main()
{

    getDataFromFile();

    // printf("main main");
    menu_showAllCars();
}