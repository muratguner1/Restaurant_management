#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include "admin.h"
extern char *foodsTxt;
extern char *ordersTxt;
extern char *closedOrdersTxt;
extern char *takenOrdersTxt;
extern char *logTtxt;

void CreateNewTable(char tableID[])
{
    DIR *dir;
    if( (dir = opendir(tableID)) == NULL )
    {
        printf("Table %s is crated successfully....\n",tableID);
        mkdir(tableID, S_IRUSR | S_IWUSR | S_IXUSR);
        strcat(tableID,"//");
        strcat(tableID,ordersTxt);
        FILE *file = fopen(tableID, "ab+");
        fclose(file);
		char text[200];
		sprintf(text,"Table %s is crated successfully....\n",tableID);
		writeToLogFile(text);
    }
    else
    {
        closedir(dir);
        printf("This table already exist!!!\n");
    }
}

void DeleteTable(char tableID[])
{
    DIR *dir;
    if( (dir = opendir(tableID)) != NULL)
    {
        char temp[50];
        strcpy(temp,tableID);
        strcat(temp,"//");
        strcat(temp,ordersTxt);
        remove(temp);
        rmdir(tableID);
        printf("Table %s is deleted successfully....\n",tableID);
		char text[200];
		sprintf(text,"Table %s is deleted successfully....\n",tableID);
		writeToLogFile(text);
    }
    else
    {
        closedir(dir);
        printf("There is no table with given ID!!!\n");
    }
}

void CheckNewOrder()
{

    takenOrder current;
	int confirm;
    FILE *file = fopen(takenOrdersTxt,"rb+");
    fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
    if(size <= 0)
    {
        printf("size: %d \n", sizeof(current));
        printf("No new orders...\n");
    }
    else
    {
        fread(&current,sizeof(current),1,file);
        printf("size: %d \n", sizeof(current));
        printf("Table ID: %s \n",current.tableId);
        printf("Food id: %d \n",current.f.id);
        printf("Food name: %s\n",current.f.name);
        printf("Food fee: %.2f\n",current.f.fee);
        printf("Amount: %d\n",current.quantity);
        printf("Is confirmed: %s\n",current.isConfirmed ? "Yes" : "No");
        printf("Is active: %s\n",current.isActive ? "Yes" : "No");
        printf("Confirm order? \nYes: 1\nNo:0\n");
		printf("Warning: Unconfirmed orders will be canceled!!!\n");
		printf("Warning: Approved orders are assigned to the relevant table!!!\n");
        scanf("%d", &confirm);
		file = fopen(takenOrdersTxt,"wb");
        fclose(file);
        if(confirm == 1)
        {
			current.isConfirmed = true;
			char temp[100];
			strcpy(temp, current.tableId);
			strcat(temp, "//");
			strcat(temp, ordersTxt);
            file = fopen(temp,"ab+");
            fwrite(&current,sizeof(current),1,file);
            printf("New order is taken successfully...\n");
            char text[200];
            sprintf(text,"New order for table %s is added to its order list successfully....\n",current.tableId);
            writeToLogFile(text);
			fclose(file);
        }
		else
		{
			file = fopen(takenOrdersTxt,"wb");
			fclose(file);
		}
		
    }
	
}

void ShowAllInvoices()
{
    FILE *file;
    if ((file = fopen(closedOrdersTxt,"r")) == NULL)
    {
        printf("No payment information!!!\n");
    }
    else
    {
        char fee[50];
        while (fgets(&fee,sizeof(fee),file) != NULL)
        {
            printf("Total Fee: %.2f \n", strtof(fee,NULL));
        }
    }
    fclose(file);
}

void UpdateFee(int foodID, float newFee)
{
    FILE *file = fopen(foodsTxt,"rb+");
    Food current;
    fread(&current,sizeof(current),1,file);
    bool isUpdated = false;
    while ( !feof(file))
    {
        if(current.id == foodID)
        {
            current.fee = newFee;
            fseek(file, -sizeof(current), SEEK_CUR);
            fwrite(&current,sizeof(current),1,file);
            isUpdated = true;

        }
        fread(&current,sizeof(current),1,file);
    }
    fclose(file);
    if(isUpdated)
    {
        printf("Food is updated...\n");
        char text[200];
        sprintf(text,"Fee of the food %d is updated as %f...\n",foodID,newFee);
        writeToLogFile(text);
    }
    else
    {
        printf("There is no food with the given food ID!!!\n");
    }
}
