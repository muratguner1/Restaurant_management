#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED
#include "common.h"

void CheckNewOrder();
void CreateNewTable(char tableID[]);
void DeleteTable(char tableID[]);
void ShowAllInvoices();
void UpdateFee(int foodID, float newFee);

#endif // ADMIN_H_INCLUDED