#include <iostream>
#include <string>
#include <iomanip>
#include<ctime>

using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Buy.h"
#include "BuyManager.h"

int BuyManager::orderItem(Buy* buy)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO `buy` ( `GOODS_ID`, `BUY_QUANTITY`, `BUY_TOTALPRICE`, `RECEIPT_NO`) VALUES (?,?,?,?);");

	ps->setInt(1, buy->goodsID);
	ps->setInt(2, buy->buyQuantity);
	ps->setDouble(3, buy->totalPrice);
	ps->setInt(4, buy->receiptNo);

	int statusBuy = ps->executeUpdate();

	if (statusBuy != 0)
	{
		cout << "\n\t\t\t\tSuccessful Add Order" << endl;
	}
	else
	{
		cout << "\n\t\t\t\tUnable to Add Order" << endl;
	}

	delete ps;
	return statusBuy;

	
}



Buy* BuyManager::showOrderItem()
{
	Buy* buy = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT buy.GOODS_ID ,goods.GOODS_NAME ,buy.BUY_QUANTITY,buy.BUY_TOTALPRICE FROM GOODS goods, BUY buy WHERE buy.GOODS_ID = goods.GOODS_ID");

	ResultSet* rs = ps->executeQuery();

	int i = 1;
	double total = 0;

	cout << "\t\t\t\t" << "-------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "| Goods ID |            Goods Name          | Quantity | Total Price|" << endl;
	cout << "\t\t\t\t" << "-------------------------------------------------------------------------" << endl;

	while (rs->next())
	{
		buy = new Buy();

		buy->goodsID = rs->getInt(1);
		buy->goodsName = rs->getString(2);
		buy->buyQuantity = rs->getInt(3);
		buy->totalPrice = rs->getDouble(4);


		cout << "\t\t\t\t" << "|   " << buy->goodsID << "     |";
		cout << "   " << buy->goodsName;
		cout << "\t|     " << buy->buyQuantity << "\t   |";
		cout << "     " << buy->totalPrice << "     |";
		cout << endl;

		total = total + buy->totalPrice;
		i++;
	}
	cout << "\t\t\t\t" << "-------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "\t\t\t\t\t\t      " << "Total:   RM" << total << endl;
	cout << "\t\t\t\t" << "-------------------------------------------------------------------------" << endl;

	delete rs;
	delete ps;

	return buy;

}


int BuyManager::deleteOrderItem(int buyGoodsID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM BUY WHERE GOODS_ID =?");

	ps->setInt(1, buyGoodsID);

	int statusOrderDelete = ps->executeUpdate();
	delete ps;
	return statusOrderDelete;
}

Buy* BuyManager::clearOrderItem()
{
	Buy* buy = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM BUY");

	ResultSet* rs = ps->executeQuery();

	delete rs;
	delete ps;

	return buy;
}

Buy* BuyManager::updateAllGoodsStock()
{
	Buy* buy = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE GOODS goods1 INNER JOIN (SELECT buy.GOODS_ID, SUM(goods2.GOODS_STOCK + buy.BUY_QUANTITY) AS GOODS_STOCK FROM GOODS goods2 INNER JOIN BUY buy ON goods2.GOODS_ID = buy.GOODS_ID GROUP BY goods2.GOODS_ID) AS p ON goods1.GOODS_ID = p.GOODS_ID SET goods1.GOODS_STOCK = p.GOODS_STOCK");

	ResultSet* rs = ps->executeQuery();

	delete rs;
	delete ps;

	return buy;
}