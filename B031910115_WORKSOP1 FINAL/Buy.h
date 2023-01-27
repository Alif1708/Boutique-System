#include <string>
#include<ctime>
using namespace std;

#ifndef BUY_H
#define BUY_H

class Buy
{
public:
	string goodsName;
	int goodstock, goodsID, buyID, buyQuantity, receiptNo;
	double goodsPrice, totalPrice;

	string dateSold;
};

#endif
