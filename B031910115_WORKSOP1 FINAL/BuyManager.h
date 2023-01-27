#ifndef BUYMANAGER_H
#define BUYMANAGER_H

class BuyManager
{
public:
	int orderItem(Buy* buy);
	Buy* showOrderItem();
	//Purchase* displayOrderItem();

	int deleteOrderItem(int buyGoodsID);
	Buy* clearOrderItem();

	Buy* updateAllGoodsStock();

	//Purchase* saleRecord();
	//Purchase* displaySaleRecord();
};

#endif 
