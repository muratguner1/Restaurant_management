#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
int main()
{
    int selection, amount, foodId;
    char tableId[250];
    float fee;
    do{
        printf("Display food menu (1)\n");
        printf("Create table (2)\n");
        printf("Delete table (3)\n");
        printf("Check new order (4)\n");
        printf("Show order list of table (5)\n");
        printf("Show all invoices (6)\n");
        printf("Update food (7)\n");
        printf("Exit (8)\n");
        printf("Enter your selection : ");
        scanf("%d",&selection);
        switch(selection){
        case 1 :
            displayFood();
            break;
        case 2 :
            printf("Enter table ID: ");
            scanf("%s",&tableId);
            CreateNewTable(tableId);
            break;
        case 3 :
            printf("Enter table ID: ");
            scanf("%s",&tableId);
            DeleteTable(tableId);
            break;
        case 4 :
            CheckNewOrder();
            break;
        case 5 :
			printf("Enter table id to show orders: ");
			scanf("%s", &tableId);
			ShowOrderList(tableId);
            break;
        case 6 :
            ShowAllInvoices();
            break;
        case 7 :
            printf("Enter food ID to update: ");
            scanf("%d",&foodId);
            printf("Enter new fee: ");
            scanf("%f",&fee);
            UpdateFee(foodId,fee);
            break;
        }
    }while(selection !=8);
    return 0;
}
