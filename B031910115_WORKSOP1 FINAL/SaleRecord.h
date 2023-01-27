#include <string>
#include<ctime>
using namespace std;

#ifndef SALERECORD_H
#define SALERECORD_H

class SaleRecord
{
public:
	string goodsName;
	int goodsStock, goodsID;
	double goodsPrice;

	int buyID, buyQuantity;
	double buyTotalPrice;

	string dateSold, dateSold1, dateSold2;

	int receiptNo;
};

#endif