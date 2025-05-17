#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include "common.h"
char *foodsTxt = "Foods.txt";
char *ordersTxt = "Orders.txt";
char *closedOrdersTxt = "ClosedOrders.txt";
char *takenOrdersTxt = "TakenOrders.txt";
char *logTtxt = "log.txt";
int numberOfFoods = 4;

void displayFood()
{
    FILE *file = fopen(foodsTxt, "rb+");
    Food current;
    printf("Foods: \n");

    while(fread(&current, sizeof(current), 1, file) == 1)
    {
        printf("Food id: %d\n", current.id);
        printf("Food name: %s\n", current.name);
        printf("Food fee: %.2f\n", current.fee);
        printf("------------------\n");
    }
    fclose(file);
}

void ShowOrderList(char tableID[])
{
    DIR *dir;
    if((dir = opendir(tableID)) != NULL)
    {
		char temp[100];
		strcpy(temp, tableID);
		strcat(temp, "//");
		strcat(temp, ordersTxt);
        FILE *file = fopen(temp,"rb+");
        takenOrder current;
        fread(&current,sizeof(current),1,file);
        printf("Orders :\n");
        while (!feof(file))
        {
            printf("Table ID: %s \n",tableID);
            printf("Food id: %d \n",current.f.id);
            printf("Food name: %s\n",current.f.name);
            printf("Food fee: %.2f\n",current.f.fee);
            printf("Amount: %d\n",current.quantity);
            printf("Is confirmed: %s\n",current.isConfirmed ? "Yes" : "No");
            printf("Is active: %s\n",current.isActive ? "Yes" : "No");
            printf("-------------------------\n");
            fread(&current,sizeof(current),1,file);
        }
		fclose(file);
    }
    else
	{
		printf("There is no table with the given id!!!\n");
		return;
	}
	close(dir);

}

void writeToLogFile(char text[])
{
	FILE *file = fopen(logTtxt,"a+");
	fprintf(file,"%s",text);
	fclose(file);
}



