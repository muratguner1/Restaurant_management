#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED
#include "common.h"

void newOrder(char tableId[], int foodId, int amount);
Food checkFoodId(char *foodsTxt, int foodId);
void updateQuantity(char tableId[], int foodId, int newAmount);
void cancelOrder(char tableId[], int foodId);
void payBill(char tableId[]);

#endif // CUSTOMER_H_INCLUDED
