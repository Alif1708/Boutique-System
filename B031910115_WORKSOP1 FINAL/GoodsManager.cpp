#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Goods.h"
#include "GoodsManager.h"

int GoodsManager::insertGoods(Goods* goods)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO GOODS (GOODS_NAME, GOODS_PRICE, GOODS_STOCK) VALUES(?, ?, ?)");

	ps->setString(1, goods->goodsName);
	ps->setDouble(2, goods->goodsPrice);
	ps->setInt(3, goods->goodsStock);


	int status = ps->executeUpdate();
	delete ps;

	return status;
}


int GoodsManager::updateGoods(Goods* goods)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE GOODS SET GOODS_STOCK = ? where GOODS_ID = ?");

	ps->setInt(1, goods->goodsStock);
	ps->setInt(2, goods->goodsID);

	int statusUpdate = ps->executeUpdate();

	if (statusUpdate != 0)
	{
		cout << "\n\t\t\t\tSuccessful Update Stock" << endl;
	}
	else
	{
		cout << "\n\t\t\t\tUnable to Update Stock" << endl;
	}

	delete ps;
	return statusUpdate;

}

Goods* GoodsManager::selectGoods(int goodsID)
{
	Goods* goods = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select * From GOODS WHERE GOODS_ID = ?");

	ps->setInt(1, goodsID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		goods = new Goods();
		goods->goodsID = rs->getInt(1);
		goods->goodsName = rs->getString(2);
		goods->goodsPrice = rs->getDouble(3);
		goods->goodsStock = rs->getInt(4);
	}

	delete rs;
	delete ps;

	return goods;
}


Goods* GoodsManager::displayGoods()
{
	Goods* goods = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement(" Select * From GOODS");

	ResultSet* rs = ps->executeQuery();

	int i = 1;
	cout << "\t\t\t\t" << "-----------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "|" << "No" << "|" << " ID " << "|" << "\t\tName" << "    | Price |" << " Stock |" << endl;
	cout << "\t\t\t\t" << "-----------------------------------------------------------------" << endl;
	while (rs->next())
	{
		goods = new Goods();

		goods->goodsID = rs->getInt(1);
		goods->goodsName = rs->getString(2);
		goods->goodsPrice = rs->getDouble(3);
		goods->goodsStock = rs->getInt(4);

		cout << "\t\t\t\t" << "|" << i << ".";
		cout << "|" << goods->goodsID << "|";
		cout << "\t" << goods->goodsName;
		cout << "\t" << "|  " << goods->goodsPrice << "\t|";
		cout << "   " << goods->goodsStock << "\t|";
		cout << endl;
		i++;
	}

	cout << "\t\t\t\t" << "-----------------------------------------------------------------";

	delete rs;
	delete ps;

	return goods;
}

int GoodsManager::deleteGoods(Goods* goods)
{

	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM GOODS WHERE GOODS_ID = ?");

	ps->setInt(1, goods->goodsID);

	int status = ps->executeUpdate();
	delete ps;

	return status;

}


void GoodsManager::updateQuantity(int buyGoodsID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM BUY WHERE WHERE_ID = ?");
	int buyQuantity = 0;
	int goodsID;
	ps->setInt(1, buyGoodsID);
	ResultSet* rs = ps->executeQuery();

	if ((rs->next()))
	{
		goodsID = rs->getInt(2);
		buyQuantity = rs->getInt(3);
	}

	int goodsQuantity = 0;
	ps = dbConn.prepareStatement("SELECT GOODS_STOCK FROM GOODS WHERE GOODS_ID = ?");
	ps->setInt(1, goodsID);

	rs = ps->executeQuery();
	if ((rs->next()))
	{
		buyQuantity = rs->getInt(1);
	}

	ps = dbConn.prepareStatement("UPDATE GOODS SET GOODS_STOCK = ? WHERE GOODS_ID = ?");
	ps->setInt(1, buyQuantity + goodsQuantity);
	ps->setInt(2, goodsID);
	ps->executeUpdate();
}

Goods* GoodsManager::searchGoodsName(string goodsName)
{
	Goods* goods = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT* FROM goods WHERE Goods_Name LIKE ?");

	ps->setString(1, "%" + goodsName + "%");

	ResultSet* rs = ps->executeQuery();


	int i = 1;
	cout << "\t\t\t\t" << "-----------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "|" << "No" << "|" << " ID " << "|" << "\t\tName" << "    | Price |" << " Stock |" << endl;
	cout << "\t\t\t\t" << "-----------------------------------------------------------------" << endl;
	while (rs->next())
	{
		goods = new Goods();

		goods->goodsID = rs->getInt(1);
		goods->goodsName = rs->getString(2);
		goods->goodsPrice = rs->getDouble(3);
		goods->goodsStock = rs->getInt(4);

		cout << "\t\t\t\t" << "|" << i << ".";
		cout << "|" << goods->goodsID << "|";
		cout << "\t" << goods->goodsName;
		cout << "\t" << "|  " << goods->goodsPrice << "\t|";
		cout << "   " << goods->goodsStock << "\t|";
		cout << endl;
		i++;
	}

	cout << "\t\t\t\t" << "-----------------------------------------------------------------";

	delete rs;
	delete ps;

	return goods;
}
