#include <stdio.h>

void main()
{

  //constants

#define DISCOUNT_MIN_AGE 18
#define DISCOUNT_MAX_AGE 25
#define MENU_BUY_CAR 'a'
#define MENU_VIEW__CAR_SALES 'b'
#define MENU_OPTION_EXIT 'x'
#define TRUE 1
#define FALSE 0

  // varaibles
  unsigned short totalNumberOfCarAvailable = 0,
                 userAge, giveDiscount = FALSE, numberOfCarsNeeded,
                 selectedCar, totalNumberOfCarsSold, numberOfSales = 0;

  unsigned short typeOfCarChoosen[totalNumberOfCarAvailable];
  float totalPrice, discountPercentage = 0;
  char *customerNames[][201] = {};
  char *discountGiven[] = {};
  char *nameOfCarPurchased[] = {};
  int quantityLeft[] = {};
  char userChoice;
  char *nameOfCars[] = {"Aston", "Audis", "BMWes", "Cardi", "Ferar"};
  int quantityAvailable[] = {4, 5, 3, 2, 4};
  float unitPrice[] = {20.0f, 30.0f, 50.0f, 70.0f, 40.0f};
  float totalSales[] = {};

  do
  {
    //official start of program

    printf("Welcome to reaingard car sale store !\n");

    printf("================================= \n\n");

    //prints menu options

    printf("Menu : \n");
    printf("a. Buy a Car\n");
    printf("b. View Sales Statistics\n");
    printf("x. Exit \n\n");

    //select a menu option

    printf("Please Choose One : ");

    userChoice = getchar();

    printf("\n\n");

    //outputs total number of available cars

    int length = sizeof(quantityAvailable) / sizeof(int);

    for (int i = 0; i < length; i++)
    {

      totalNumberOfCarAvailable += quantityAvailable[i];
    }

    // start of the switch function

    switch (userChoice)
    {

      // first case
    case MENU_BUY_CAR:
      if (totalNumberOfCarAvailable > 0)
      {

        printf("================================================================\n\n");

        // Displays the List heading format

        printf("S/N \t | Name of cars \t | Quantity Available \t | Unit Price \t\n");

        // list the collection of cars available
        for (int i = 0; i < 5; i++)
        {
          printf("%d \t | %s \t\t | %d \t\t\t | %f \t \n", i, nameOfCars[i], quantityAvailable[i], unitPrice[i]);
        };

        printf("===============================================================\n\n");

        //prints out information on the total number of cars available

        printf("We Have  a sum of %hu Cars Available \n", totalNumberOfCarAvailable);

        printf("\n\n");
      }

      //  else block
      else
      {
        printf("Sorry , there are no more cars available.");
        return;
      }

      printf("Enter your name : ");

      scanf("%s", customerNames[numberOfSales]);

      //choose the car you wish to purchase

      printf("select the one you desire to Purchase : ");

      scanf("%hu", &selectedCar);

      // check if the number choosen is contained in the displayed list.

      if (selectedCar > 4)
      {
        printf("inputed number is invalid \n");

        return;
      }

      // executed if the number choosen is in the Display list
      else
      {

        printf("You selected %s we have just %d in stocked and it's unit cost is %f \n\n", nameOfCars[selectedCar], quantityAvailable[selectedCar], unitPrice[selectedCar]);

        printf("Enter the number of %s needed :", nameOfCars[selectedCar]);

        scanf("%hu", &numberOfCarsNeeded);

        if (quantityAvailable[selectedCar] < numberOfCarsNeeded)
        {
          printf("Sorry , there are fewer cars remaining than you require");
          return;
        }

        totalPrice = numberOfCarsNeeded * unitPrice[selectedCar];

        quantityAvailable[selectedCar] = quantityAvailable[selectedCar] - numberOfCarsNeeded;

        quantityLeft[numberOfSales] = quantityAvailable[selectedCar];

        printf("How old are you ? Age : ");

        scanf("%hu", &userAge);

        giveDiscount = FALSE;

        if (userAge >= DISCOUNT_MIN_AGE && userAge <= DISCOUNT_MAX_AGE)
        {

          char affiliateResponse;
          printf("Are you an affiliate to the compaany ? Answer 'y' or 'n' \n\n");
          scanf("\n %c", &affiliateResponse);

          if (affiliateResponse == 'y')
          {
            giveDiscount = TRUE;

            discountPercentage = 0.10f;
          }
        }

        switch (giveDiscount)
        {
        case TRUE:

          totalPrice *= (1 - discountPercentage);

          printf("\n\nYou get a discount!");

          discountGiven[numberOfSales] = "yes";

          break;

        case FALSE:

          printf("\n\nNo discount given.");

          discountGiven[numberOfSales] = "No";

          break;
        }

        totalNumberOfCarAvailable = 0;

        for (int i = 0; i < length; i++)
        {

          totalNumberOfCarAvailable += quantityAvailable[i];
        }

        printf("\n\nThank you.\n");
        printf("You have bought %hu %s Cars.\n", numberOfCarsNeeded, nameOfCars[selectedCar]);
        printf("Total cost is %f GBP. \n\n", totalPrice);
        printf("we have a total of %hu available now \n\n", totalNumberOfCarAvailable);
      }

      totalSales[numberOfSales] = totalPrice;
      nameOfCarPurchased[numberOfSales] = nameOfCars[selectedCar];

      totalNumberOfCarsSold += numberOfCarsNeeded;

      numberOfSales++;

      break;

    case MENU_VIEW__CAR_SALES:

      for (int i = 0; i < numberOfSales; i++)
      {

        printf(" Sale Index : %d| Name of Car : %S | price : %f | Discount Given : %S | Customer Name : %S", i, *(nameOfCarPurchased), *(totalSales), *(discountGiven), *(customerNames));
      }

      break;

    case MENU_OPTION_EXIT:

      printf("Thank you for using this Car Sakes Program . Bye-bye !");

      break;
    }

    if (userChoice == MENU_OPTION_EXIT)
    {
      printf("\n\n Press Enter to Exit ...\n\n");
    }
    else
    {
      printf("\n\n Press Enter to return to the Menu ....\n\n");
    }

    getchar();

    getchar();
  } while (userChoice != MENU_OPTION_EXIT);

  system("cls");

  printf("\n\n Have a good day !\n\n");
}