#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include "customer.h"

extern char *foodsTxt;
extern char *ordersTxt;
extern char *closedOrdersTxt;
extern char *takenOrdersTxt;
extern char *logTtxt;

void newOrder(char tableId[], int foodId, int amount)
{
    DIR *dir;
    if((dir = opendir(tableId)) == NULL)
    {
        printf("There is no table with given id!!!\n") ;
    }
    else
    {
        Food f2 = checkFoodId(foodsTxt, foodId);
        if(f2.id == -1)
        {
            printf("There is no food with given id!!!\n");
        }
        else
        {
            takenOrder order;
            order.f.id = f2.id;
            order.f.fee = f2.fee;
            strcpy(order.f.name, f2.name);
            order.quantity = amount;
            strcpy(order.tableId, tableId);
            order.isConfirmed = false;
            order.isActive = true;

            FILE *file = fopen(takenOrdersTxt, "ab+");
            fseek(file, 0, SEEK_END);
            long size = ftell(file);
			fseek(file, 0, SEEK_SET);
            if(size <= 0){
                fwrite(&order, sizeof(order), 1, file);
                printf("New order is added successfully....\n");
                char text[200];
                sprintf(text, "New order for table %s is taken successfully....\n", order.tableId);
                writeToLogFile(text);
                fclose(file);

            }
            else
            {
                printf("We are so busy now!!!\n");
            }
        }

    }

}

Food checkFoodId(char *foodsTxt, int foodId)
{
    FILE *file = fopen(foodsTxt, "rb+");
    Food current;
    fread(&current, sizeof(current), 1, file);
    Food checkF;
    checkF.id = -1;
    while(!feof(file))
    {
        if(current.id == foodId)
        {
            checkF.id = current.id;
            checkF.fee = current.fee;
            strcpy(checkF.name, current.name);
            break;
        }
        fread(&current, sizeof(current), 1, file);
    }

    fclose(file);
    return checkF;
}

void updateQuantity(char tableId[], int foodId, int newAmount)
{
    DIR *dir;
    if((dir = opendir(tableId)) != NULL)
    {
        strcat(tableId, "//");
        strcat(tableId, ordersTxt);
        FILE *file = fopen(tableId, "rb+");
        takenOrder current;
        fread(&current, sizeof(current), 1, file);
        bool isUpdated = false;
        while(!feof(file))
        {
            if(current.f.id == foodId)
            {
                printf("girdi\n");
                current.quantity = newAmount;
                fseek(file, -sizeof(current), SEEK_CUR);
                fwrite(&current, sizeof(current), 1, file);
                isUpdated = true;
                break;
            }
            fread(&current, sizeof(current), 1, file);
        }
        fclose(file);
        closedir(dir);
        if(isUpdated)
		{
			printf("Amount is update...\n");
			char text[200];
			sprintf(text,"Amount of the food with id %d in table %s is updated as %d\n",foodId, tableId, newAmount);
			writeToLogFile(text);
		}
		else
        {
            printf("Order not found!!!\n");
        }
    }
    else
    {
        printf("There is no table with given id!!!!\n");
    }
}

void cancelOrder(char tableId[], int foodId)
{

    DIR *dir;
    if((dir = opendir(tableId)) != NULL)
    {
        strcat(tableId, "//");
        strcat(tableId, ordersTxt);
        FILE *file = fopen(tableId, "rb+");
        takenOrder current;
        fread(&current, sizeof(current), 1, file);
        bool isUpdated = false;
        while(!feof(file))
        {
            if(current.f.id == foodId)
            {
                if(!current.isActive)
                {
                    printf("The order is already canceled. That's why it can't be updated!!!\n");
					break;
                }
                else
                {
                    printf("girdi\n");
                    current.isActive = false;
                    fseek(file, -sizeof(current), SEEK_CUR);
                    fwrite(&current, sizeof(current), 1, file);
                    isUpdated = true;
                    break;
                }
            }
            fread(&current, sizeof(current), 1, file);
        }
        fclose(file);
        closedir(dir);
        if(isUpdated)
		{
			printf("Order is canceled...\n");
			char text[200];
			sprintf(text,"Order of the food with id %d in table %s//Orders.txt is canceled \n",foodId, tableId);
			writeToLogFile(text);
		}
		else
        {
            printf("Order not found!!!\n");
        }
    }
    else
    {
        printf("There is no table with given id!!!!\n");
    }
}

void payBill(char tableId[])
{
	float result = 0.00;
	DIR *dir;
	if((dir = opendir(tableId)) != NULL)
	{
		strcat(tableId, "//");
        strcat(tableId, ordersTxt);
        FILE *file = fopen(tableId, "rb+");
		fseek(file, 0, SEEK_END);
        long size = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		if(size == 0)
		{
			fclose(file);
			printf("%.2f\n", result);
			printf("Payment recieved successfully....\n");
			file = fopen(tableId, "wb");
			fclose(file);
			file = fopen(closedOrdersTxt, "a+");
			fprintf(file, "%f\n", result);
			char text[200];
			sprintf(text, "Payment of the table %s received successfully....\nTOTAL FEE :%.2f\n", tableId, result);
			writeToLogFile(text);
			fclose(file);
			closedir(dir);
		}
		else
		{
			takenOrder current;
			fread(&current, sizeof(current), 1, file);
			while(!feof(file))
			{
				if(current.isActive)
				{
					result += (current.f.fee) * (current.quantity);
				}
				fread(&current, sizeof(current), 1, file);
			}
			fclose(file);
			printf("%.2f\n", result);
			printf("Payment recieved successfully....\n");
			file = fopen(tableId, "wb");
			fclose(file);
			file = fopen(closedOrdersTxt, "a+");
			fprintf(file, "%f\n", result);
			char text[200];
			sprintf(text, "Payment of the table %s received successfully....\nTOTAL FEE :%.2f\n", tableId, result);
			writeToLogFile(text);
			fclose(file);
			closedir(dir);		
		}
	}
	else
	{
		printf("There is no table with given id!!!!\n");
	}
}

