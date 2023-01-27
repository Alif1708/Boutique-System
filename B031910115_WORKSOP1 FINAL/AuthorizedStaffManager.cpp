#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "AuthorizedStaff.h"
#include "AuthorizedStaffManager.h"

int AuthorizedStaffManager::registerStaff(AuthorizedStaff* AuthorizedStaff)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO AuthorizedStaff VALUES (?, ?, ?, ?)");

	ps->setString(1, AuthorizedStaff->staffID);
	ps->setString(2, AuthorizedStaff->staffPassword);
	ps->setString(3, AuthorizedStaff->staffName);
	ps->setString(4, AuthorizedStaff->staffPhone);

	int status = ps->executeUpdate();
	delete ps;

	return status;
}


bool  AuthorizedStaffManager::loginStaff(AuthorizedStaff* staff)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM AuthorizedStaff WHERE staff_ID = ? AND staff_Password = ?");

	ps->setString(1, staff->staffID);
	ps->setString(2, staff->staffPassword);

	ResultSet* rs = ps->executeQuery();

	if (!(rs->next()))
	{
		cout << "\n\t\t\t\tWrong ID or Password. Please try again." << endl;
		system("pause");
		system("cls");
		return false;
	}

	delete rs;
	delete ps;

	return true;
}

AuthorizedStaff* AuthorizedStaffManager::staffInformation(string staffID)
{
	AuthorizedStaff* authorizedStaff = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM AUTHORIZEDSTAFF WHERE STAFF_ID = ? ");
	ps->setString(1, staffID);
	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		authorizedStaff = new AuthorizedStaff();

		authorizedStaff->staffID = rs->getString(1);
		authorizedStaff->staffPassword = rs->getString(2);
		authorizedStaff->staffName = rs->getString(3);
		authorizedStaff->staffPhone = rs->getString(4);

		cout << "\t\t\t\tID: " << authorizedStaff->staffID << endl;
		cout << "\t\t\t\tPassword: " << authorizedStaff->staffPassword << endl;
		cout << "\t\t\t\tName: " << authorizedStaff->staffName << endl;
		cout << "\t\t\t\tPhone: " << authorizedStaff->staffPhone << endl;
	}

	delete rs;
	delete ps;

	return authorizedStaff;

}

int AuthorizedStaffManager::updatePhone(AuthorizedStaff* staff)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE AUTHORIZEDSTAFF SET STAFF_PHONE = ? WHERE STAFF_ID = ?");

	ps->setString(1, staff->staffPhone);
	ps->setString(2, staff->staffID);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int AuthorizedStaffManager::updatePassword(AuthorizedStaff* staff)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE AUTHORIZEDSTAFF SET STAFF_PASSWORD = ? WHERE STAFF_ID = ?");

	ps->setString(1, staff->staffPassword);
	ps->setString(2, staff->staffID);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}