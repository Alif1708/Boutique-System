#include <iostream>
#include <string>
#include <iomanip>
#include<ctime>

using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "SaleRecord.h"
#include "SaleRecordManager.h"

SaleRecord* SaleRecordManager::saleRecord()
{
	SaleRecord* saleRecord = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps;
	ps = dbConn.prepareStatement("INSERT INTO SALERECORD (BUY_ID, GOODS_ID, BUY_QUANTITY, BUY_TOTALPRICE, RECEIPT_NO) SELECT BUY_ID, GOODS_ID, BUY_QUANTITY, BUY_TOTALPRICE, RECEIPT_NO FROM BUY");

	ResultSet* rs = ps->executeQuery();

	delete rs;
	delete ps;

	return saleRecord;
}




SaleRecord* SaleRecordManager::showSaleRecord()
{
	SaleRecord* saleRecord = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT goods.GOODS_ID, goods.GOODS_NAME, goods.GOODS_PRICE,salerecord.BUY_QUANTITY, salerecord.BUY_TOTALPRICE, salerecord.DATESOLD FROM goods goods, salerecord salerecord WHERE goods.GOODS_ID = salerecord.GOODS_ID");

	ResultSet* rs = ps->executeQuery();

	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "| Goods ID |          Goods Name            | Goods Price |    Quantity      | Total Price |      Date Sold      |" << endl;
	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------------" << endl;

	int i = 0;
	double total = 0;

	while (rs->next())
	{
		saleRecord = new SaleRecord();
		saleRecord->goodsID = rs->getInt(1);
		saleRecord->goodsName = rs->getString(2);
		saleRecord->goodsPrice = rs->getDouble(3);
		saleRecord->buyQuantity = rs->getInt(4);
		saleRecord->buyTotalPrice = rs->getDouble(5);
		saleRecord->dateSold = rs->getString(6);

		cout << "\t\t\t\t" << "|   " << saleRecord->goodsID << "   |";
		cout << "     " << saleRecord->goodsName << "           ";
		cout << "\t   |      " << saleRecord->goodsPrice << "\t|";
		cout << "\t  " << saleRecord->buyQuantity << "        |";
		cout << "     " << saleRecord->buyTotalPrice << "\t |";
		cout << " " << saleRecord->dateSold << " |";
		cout << endl;

		total = total + saleRecord->buyTotalPrice;
		i++;
	}
	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "\t\t\t\t\t\t      " << "Total Sale: RM" << total << endl;
	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------------" << endl;

	delete rs;
	delete ps;

	return saleRecord;
}

SaleRecord* SaleRecordManager::searchByGoodsID(int goodsID)
{
	SaleRecord* saleRecord = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement(" SELECT p.Goods_ID, p.Goods_Name, p.Goods_Price, SUM(s.Buy_Quantity) AS TotalQuantitySold, SUM(s.Buy_Quantity * p.Goods_Price) AS OverallTotalPrice FROM SaleRecord AS s INNER JOIN Goods AS p ON s.Goods_ID = p.Goods_ID WHERE p.Goods_ID = ? GROUP BY s.Goods_ID");

	ps->setInt(1, goodsID);

	ResultSet* rs = ps->executeQuery();

	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "| Goods ID |         Goods Name            | Goods Price |    Total Quantity Sold      | Total Price (RM) |" << endl;
	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------" << endl;

	int i = 0;
	

	while (rs->next())
	{
		saleRecord = new SaleRecord();
		saleRecord->goodsID = rs->getInt(1);
		saleRecord->goodsName = rs->getString(2);
		saleRecord->goodsPrice = rs->getDouble(3);
		saleRecord->buyQuantity = rs->getInt(4);
		saleRecord->buyTotalPrice = rs->getDouble(5);


		cout << "\t\t\t\t" << "|   " << saleRecord->goodsID << "   |";
		cout << "     " << saleRecord->goodsName << "";
		cout << "\t           |      " << saleRecord->goodsPrice << "\t |";
		cout << "\t\t" << saleRecord->buyQuantity << "\t       |";
		cout << "   " << saleRecord->buyTotalPrice << "\            |";
		cout << endl;

		i++;
	}
	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------" << endl;
	//cout << "\t\t\t\t\t\t      " << "Total Sale: RM" << total << endl;
	//cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

	delete rs;
	delete ps;

	return saleRecord;
}

SaleRecord* SaleRecordManager::searchByGoodsName(string goodsName)
{
	SaleRecord* saleRecord = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT p.Goods_ID, p.Goods_Name, p.Goods_Price, SUM(s.Buy_Quantity) AS TotalQuantitySold, SUM(s.Buy_Quantity * p.Goods_Price) AS OverallTotalPrice FROM SaleRecord AS s INNER JOIN Goods AS p ON s.Goods_ID = p.Goods_ID WHERE p.Goods_Name LIKE ? GROUP BY s.Goods_ID");

	ps->setString(1, "%" + goodsName + "%");

	ResultSet* rs = ps->executeQuery();

	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "| Goods ID |          Goods Name            | Goods Price |    Total Quantity Sold      | Total Price (RM) |" << endl;
	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------" << endl;

	int i = 0;
	//double total = 0;

	while (rs->next())
	{
		saleRecord = new SaleRecord();
		saleRecord->goodsID = rs->getInt(1);
		saleRecord->goodsName = rs->getString(2);
		saleRecord->goodsPrice = rs->getDouble(3);
		saleRecord->buyQuantity = rs->getInt(4);
		saleRecord->buyTotalPrice = rs->getDouble(5);


		cout << "\t\t\t\t" << "|   " << saleRecord->goodsID << "   |";
		cout << "     " << saleRecord->goodsName << "";
		cout << "\t           |      " << saleRecord->goodsPrice << "\t |";
		cout << "\t\t" << saleRecord->buyQuantity << "\t       |";
		cout << "   " << saleRecord->buyTotalPrice << "\            |";
		cout << endl;

		
		i++;
	}
	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------" << endl;
	//cout << "\t\t\t\t\t\t      " << "Total Sale: RM" << total << endl;
	//cout << "------------------------------------------------------------------------------------------------------------------------" << endl;


	if (saleRecord != 0)
	{
		cout << "\n\t\t\t\tSuccessful Search" << endl;
	}
	else
	{
		cout << "\n\t\t\t\tUnable to Search" << endl;
	}

	delete rs;
	delete ps;

	return saleRecord;
}


SaleRecord* SaleRecordManager::searchByHighestSold()
{
	SaleRecord* saleRecord = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT p.Goods_ID, p.Goods_Name, p.Goods_Price, SUM(s.Buy_Quantity) AS TotalQuantitySold, SUM(s.Buy_Quantity*p.Goods_Price) AS OverallTotalPrice FROM SaleRecord AS s INNER JOIN Goods AS p ON s.Goods_ID = p.Goods_ID GROUP BY s.Goods_ID ORDER BY OverallTotalPrice DESC");

	ResultSet* rs = ps->executeQuery();

	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "| Goods ID |          Goods Name            | Goods Price |    Total Quantity Sold      | Total Price (RM) |" << endl;
	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------" << endl;

	int i = 0;
	//double total = 0;

	while (rs->next())
	{
		saleRecord = new SaleRecord();
		saleRecord->goodsID = rs->getInt(1);
		saleRecord->goodsName = rs->getString(2);
		saleRecord->goodsPrice = rs->getDouble(3);
		saleRecord->buyQuantity = rs->getInt(4);
		saleRecord->buyTotalPrice = rs->getDouble(5);


		cout << "\t\t\t\t" << "|   " << saleRecord->goodsID << "   |";
		cout << "     " << saleRecord->goodsName << "";
		cout << "\t           |      " << saleRecord->goodsPrice << "\t |";
		cout << "\t\t" << saleRecord->buyQuantity << "\t       |";
		cout << "   " << saleRecord->buyTotalPrice << "\            |";
		cout << endl;

		i++;
	}
	cout << "\t\t\t\t" << "------------------------------------------------------------------------------------------------------------------" << endl;
	//cout << "\t\t\t\t\t\t      " << "Total Sale: RM" << total << endl;
	//cout << "------------------------------------------------------------------------------------------------------------------------" << endl;


	if (saleRecord != 0)
	{
		cout << "\n\t\t\t\tSuccessful Search" << endl;
	}
	else
	{
		cout << "\n\t\t\t\tUnable to Search" << endl;
	}

	delete rs;
	delete ps;

	return saleRecord;
}


SaleRecord* SaleRecordManager::searchByDate(string dateSold1, string dateSold2)
{
	SaleRecord* saleRecord = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT p.Goods_ID, p.Goods_Name, p.Goods_Price, s.Buy_Quantity AS TotalQuantitySold, s.Buy_TotalPrice AS OverallTotalPrice, s.DATESOLD FROM Goods p LEFT JOIN salerecord s ON s.Goods_ID = p.Goods_ID WHERE s.DateSold BETWEEN ? AND ? ");

	ps->setString(1, dateSold1);
	ps->setString(2, dateSold2);

	ResultSet* rs = ps->executeQuery();

	cout << "\t\t\t\t" << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "| Goods ID |          Goods Name            | Goods Price |    Total Quantity Sold      | Total Price (RM) |      Date Sold      |" << endl;
	cout << "\t\t\t\t" << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;

	int i = 0;
	double total = 0;

	while (rs->next())
	{
		saleRecord = new SaleRecord();
		saleRecord->goodsID = rs->getInt(1);
		saleRecord->goodsName = rs->getString(2);
		saleRecord->goodsPrice = rs->getDouble(3);
		saleRecord->buyQuantity = rs->getInt(4);
		saleRecord->buyTotalPrice = rs->getDouble(5);
		saleRecord->dateSold = rs->getString(6);


		cout << "\t\t\t\t" << "|   " << saleRecord->goodsID << "   |";
		cout << "     " << saleRecord->goodsName << "";
		cout << "\t           |      " << saleRecord->goodsPrice << "\t |";
		cout << "\t\t" << saleRecord->buyQuantity << "\t       |";
		cout << "   " << saleRecord->buyTotalPrice << "\            |";
		cout << " " << saleRecord->dateSold << " |";
		cout << endl;

		total = total + saleRecord->buyTotalPrice;
		i++;
	}
	cout << "\t\t\t\t" << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t" << "\t\t\t\t\t\t      " << "Total Sale: RM" << total << endl;
	cout << "\t\t\t\t" << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;

	delete rs;
	delete ps;

	return saleRecord;
}

SaleRecord* SaleRecordManager::searchByReceiptNo(int receiptNo)
{
	SaleRecord* saleRecord = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT s.Receipt_No, p.Goods_ID, p.Goods_Name, p.Goods_Price, s.Buy_Quantity, s.Buy_TotalPrice, s.DateSold FROM SaleRecord AS s INNER JOIN Goods AS p ON s.Goods_ID = p.Goods_ID WHERE s.Receipt_No = ?");

	ps->setInt(1, receiptNo);

	ResultSet* rs = ps->executeQuery();

	cout << "\t\t" << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t" << "|  Receipt No  | Goods ID |           Goods Name            |  Price |          Quantity           | Total Price (RM) |      Date Sold      |" << endl;
	cout << "\t\t" << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	int i = 0;
	double total = 0;

	while (rs->next())
	{
		saleRecord = new SaleRecord();
		saleRecord->receiptNo = rs->getInt(1);
		saleRecord->goodsID = rs->getInt(2);
		saleRecord->goodsName = rs->getString(3);
		saleRecord->goodsPrice = rs->getDouble(4);
		saleRecord->buyQuantity = rs->getInt(5);
		saleRecord->buyTotalPrice = rs->getDouble(6);
		saleRecord->dateSold = rs->getString(7);

		cout << "\t\t" << "|     " << saleRecord->receiptNo << "    |";
		cout << "" << "   " << saleRecord->goodsID << "    |";
		cout << "  " << saleRecord->goodsName << "";
		cout << "\t           |      " << saleRecord->goodsPrice << "\t|";
		cout << "\t\t" << saleRecord->buyQuantity << "\t       |";
		cout << "   " << saleRecord->buyTotalPrice << "\            |";
		cout << " " << saleRecord->dateSold << " |";
		cout << endl;

		total = total + saleRecord->buyTotalPrice;
		i++;
	}
	cout << "\t\t" << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t" << "\t\t\t\t\t\t\t      " << "Total Price: RM" << total << endl;
	cout << "\t\t" << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	delete rs;
	delete ps;

	return saleRecord;
}