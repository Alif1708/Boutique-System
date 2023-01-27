#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "AuthorizedStaff.h"
#include "AuthorizedStaffManager.h"
#include "Goods.h"
#include "GoodsManager.h"
#include "Buy.h"
#include "BuyManager.h"
#include "SaleRecord.h"
#include "SaleRecordManager.h"

#pragma warning(disable : 4996)


void AuthenticationMenu();
void Register();
void Login();

void StaffMenu(string staffID);
void StaffInformation(string staffID);
void StaffUpdatePassword(string staffID);
void StaffUpdatePhone(string staffID);

void ManageStockMenu();
void ViewStock();
void AddStock();
void DeleteStock();
void UpdateStock();

void CustomerMenu();
void CustomerOrder();
void CustomerSearchReceiptNo();

void SaleReportMenu();
void ViewSaleRecord();
void ViewSaleRecordByGoodsID();
void ViewSaleRecordByGoodsName();
void ViewSaleRecordByHighestSold();
void ViewSaleRecordByDate();

string staffID;


int main()
{
    system("cls");
    cout << "\n\n";
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t*                                         *" << endl;
    cout << "\t\t\t\t*       Welcome To Alyph Collection       *" << endl;
    cout << "\t\t\t\t*                                         *" << endl;
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\n\n";

    system("pause");

    AuthenticationMenu();

    return 0;
}

void AuthenticationMenu()
{
    int chooseOneFromMenu = 0;
    char exitConfirmation;

    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t*      Welcome To  Alyph Collection       *" << endl;
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t1. Register" << endl;
    cout << "\t\t\t\t2. Login" << endl;
    cout << "\t\t\t\t3. Exit " << endl;
    cout << "\t\t\t\t*******************************************" << endl;

    cout << "\t\t\t\tChoose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        Register();
        break;
    case 2:
        Login();
        break;
    case 3:
    ExitProgram:
        cout << "\t\t\t\tProgram terminating. Are you sure? (y/N): ";
        cin >> exitConfirmation;
        if (exitConfirmation == 'y' || exitConfirmation == 'Y') {

        }
        else if (exitConfirmation == 'n' || exitConfirmation == 'N') {
            system("cls");
            main();
        }
        else {
            cout << "\t\t\t\tWrong Input" << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "\t\t\t\tPlease choose between 1 - 3. Press Enter To Continue...";

        system("cls");
        main();
        break;
    }

}

void Register()
{

    AuthorizedStaff* authorizedStaff = new AuthorizedStaff();
    AuthorizedStaffManager authorizedStaffManager;

    int choose;

    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t****           Register Staff          ****" << endl;
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\n\n\t\t\t\tPlease enter the Staff ID details" << endl;

    cout << "\t\t\t\tID: ";
    cin >> authorizedStaff->staffID;

    cout << "\t\t\t\tPassword: ";
    cin.ignore(1, '\n');
    getline(cin, authorizedStaff->staffPassword);

    cout << "\t\t\t\tName: ";
    getline(cin, authorizedStaff->staffName);

    cout << "\t\t\t\tPhone: ";
    getline(cin, authorizedStaff->staffPhone);


    int status = authorizedStaffManager.registerStaff(authorizedStaff);

    if (status != 0)
        cout << "\t\t\t\tSuccessfully register." << endl;
    else
        cout << "\t\t\t\tUnable to register." << endl;


    cout << "\n\t\t\t\tPress '1' to Authentication Menu";
    cout << "\n\t\t\t\tpress any other key to Exit:";

    cin >> choose;
    if (choose == 1)
    {
        AuthenticationMenu();
    }
    else
    {
        exit(0);
    }

}


void Login()
{
    AuthorizedStaff* authorizedStaff = new AuthorizedStaff();
    AuthorizedStaffManager authorizedStaffManager;

    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t****            Login Staff            ****" << endl;
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\n\t\t\t\tPlease enter Staff ID and Password" << endl;

    cout << "\t\t\t\tUser ID: ";
    cin.ignore(1, '\n');
    getline(cin, authorizedStaff->staffID);

    cout << "\t\t\t\tUser PW: ";
    getline(cin, authorizedStaff->staffPassword);


    if (authorizedStaffManager.loginStaff(authorizedStaff))
    {
        cout << "\n\t\t\t\tSuccessful Login" << endl;

        system("pause");

    }
    else
    {
        AuthenticationMenu();
    }
    StaffMenu(authorizedStaff->staffID);

}

void StaffMenu(string staffID)
{
    int chooseOneFromMenu = 0;
    char exitConfirmation;

    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t*     Welcome to Alyph Collection *" << endl;
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t1. Authorized Staff Information" << endl;
    cout << "\t\t\t\t2. Manage Stock" << endl;
    cout << "\t\t\t\t3. Customer Order" << endl;
    cout << "\t\t\t\t4. Sale Report" << endl;
    cout << "\t\t\t\t5. Exit " << endl;
    cout << "\t\t\t\t*******************************************" << endl;

    cout << "\t\t\t\tChoose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        StaffInformation(staffID);
        break;
    case 2:
        ManageStockMenu();
        break;
    case 3:
        CustomerMenu();
        break;
    case 4:
        SaleReportMenu();
        break;
    case 5:
    ExitProgram:
        cout << "\t\t\t\tProgram terminating. Are you sure? (y/N): ";
        cin >> exitConfirmation;
        if (exitConfirmation == 'y' || exitConfirmation == 'Y') {
        }
        else if (exitConfirmation == 'n' || exitConfirmation == 'N') {
            system("cls");
            main();
        }
        else {
            cout << "\t\t\t\tWrong Input" << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 5. Press Enter To Continue...";
        system("cls");
        main();
        break;
    }

}


void StaffInformation(string staffID)
{
    AuthorizedStaff* authorizedStaff = new AuthorizedStaff();
    AuthorizedStaffManager authorizedStaffManager;

    int choose;

    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t*       Authorized Staff Information        *" << endl;
    cout << "\t\t\t\t*******************************************" << endl;

    authorizedStaffManager.staffInformation(staffID);

    cout << "\n\n\t\t\t\tUpdate Information?" << endl;
    cout << "\t\t\t\t1) Password" << endl;
    cout << "\t\t\t\t2) Phone" << endl;
    cout << "\t\t\t\t3) Main Menu" << endl;
    cout << "\t\t\t\tChoose One: ";
    cin >> choose;
    if (choose == 1)
    {
        StaffUpdatePassword(staffID);
    }
    else if (choose == 2)
    {
        StaffUpdatePhone(staffID);
    }
    else if (choose == 3)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 1 || choose == 2 || choose == 3))
    {
        cout << "\t\t\t\tInvalid Input";
        StaffInformation(staffID);
    }
}

void StaffUpdatePassword(string staffID)
{
    int choose;
    AuthorizedStaff* updateStaffInfo = new  AuthorizedStaff();
    AuthorizedStaffManager authorizedStaffManager;



    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t*             Update Password             *" << endl;
    cout << "\t\t\t\t*******************************************" << endl;

    cout << "\t\t\t\tEnter New Password: ";
    updateStaffInfo->staffID = staffID;
    cin.ignore(1, '\n');
    getline(cin, updateStaffInfo->staffPassword);

    int status = authorizedStaffManager.updatePassword(updateStaffInfo);

    if (status != 0)
        cout << "\t\t\t\tSuccessfully Update Password." << endl;
    else
        cout << "\t\t\t\tUnable Update Password." << endl;


GO6:
    cout << "\n\n\n\t\t\t\tPress '1' to Staff Information Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        StaffInformation(staffID);
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto GO6;
    }
}

void StaffUpdatePhone(string staffID)
{
    int choose;
    AuthorizedStaff* updateStaffInfo = new AuthorizedStaff();
    AuthorizedStaffManager authorizedStaffManager;


    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t*              Update Phone               *" << endl;
    cout << "\t\t\t\t*******************************************" << endl;

    cout << "\t\t\t\tEnter New Phone: ";
    updateStaffInfo->staffID = staffID;
    cin.ignore(1, '\n');
    getline(cin, updateStaffInfo->staffPhone);

    int status = authorizedStaffManager.updatePhone(updateStaffInfo);

    if (status != 0)
        cout << "\t\t\t\tSuccessfully Update Phone." << endl;
    else
        cout << "\t\t\t\tUnable Update Phone." << endl;


GO7:
    cout << "\n\n\n\t\t\t\tPress '1' to Staff Information Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        StaffInformation(staffID);
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto GO7;
    }
}


void ManageStockMenu()
{
    int chooseOneFromMenu = 0;

    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t****          Manage Goods          ****" << endl;
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t1. View Stock" << endl;
    cout << "\t\t\t\t2. Add Goods" << endl;
    cout << "\t\t\t\t3. Delete Goods" << endl;
    cout << "\t\t\t\t4. Update Stock" << endl;
    cout << "\t\t\t\t5. Main Menu " << endl;
    cout << "\t\t\t\t*******************************************" << endl;

    cout << "\t\t\t\tChoose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        ViewStock();
        break;
    case 2:
        AddStock();
        break;
    case 3:
        DeleteStock();
        break;
    case 4:
        UpdateStock();
        break;
    case 5:
        StaffMenu(staffID);
        break;
    default:
        cout << "\t\t\t\tPlease choose between 1 - 5. Press Enter To Continue...";
        system("cls");
        ManageStockMenu();
        break;
    }
}

void ViewStock()
{
    Goods* goods = new Goods();
    GoodsManager goodsManager;

    int choose;

    system("cls");
    cout << "\t\t\t\t*****************************************************************" << endl;
    cout << "\t\t\t\t****                       View Stock                        ****" << endl;
    cout << "\t\t\t\t*****************************************************************" << endl;

    goodsManager.displayGoods();

    cout << endl;

invalidInputViewStock:
    cout << "\n\n\n\t\t\t\tPress '1' to Manage Stock Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        ManageStockMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputViewStock;
    }

}

void AddStock()
{
    Goods* goods = new Goods();
    GoodsManager goodsManager;

    int choose;

    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t****            Add Goods            ****" << endl;
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\tPlease enter the Stock details" << endl;

    cout << "\t\t\t\tGoods Name: ";
    cin.ignore(1, '\n');
    getline(cin, goods->goodsName);

    cout << "\t\t\t\tGoods Price: ";
    cin >> goods->goodsPrice;

    cout << "\t\t\t\tGoods Stock: ";
    cin >> goods->goodsStock;

    int status = goodsManager.insertGoods(goods);

    if (status != 0)
        cout << "\t\t\t\tSuccessfully added a new goods." << endl;
    else
        cout << "\t\t\t\tUnable to add a new goods." << endl;

invalidInputAddStock:
    cout << "\n\t\t\t\tPress '1' to Manage Stock Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        ManageStockMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputAddStock;
    }
}

void DeleteStock()
{
    Goods* goods = new Goods();
    GoodsManager goodsManager;

    int choose;
    system("cls");
    cout << "\t\t\t\t*****************************************************************" << endl;
    cout << "\t\t\t\t****                     Remove Goods                      ****" << endl;
    cout << "\t\t\t\t*****************************************************************" << endl;

    goodsManager.displayGoods();

    cout << "\n\n\t\t\t\tPlease Enter Goods ID to be remove: ";
    cin >> goods->goodsID;

    int status = goodsManager.deleteGoods(goods);

    if (status != 0)
        cout << "\t\t\t\tSuccessfully remove goods." << endl;
    else
        cout << "\t\t\t\tUnable to remove goods." << endl;

invalidInputDeleteStock:
    cout << "\n\t\t\t\tPress '1' to Manage Stock Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        ManageStockMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputDeleteStock;
    }
}


int UpdateAddStock(int quantity, Goods* goods)
{
    return goods->goodsStock = goods->goodsStock + quantity;
}

void UpdateStock()
{
    Goods* goods = new Goods();
    GoodsManager goodsManager;

    int choose, quantity;

    system("cls");
    cout << "\t\t\t\t*****************************************************************" << endl;
    cout << "\t\t\t\t****                      Update Stock                       ****" << endl;
    cout << "\t\t\t\t*****************************************************************" << endl;
    goodsManager.displayGoods();

    cout << "\n\n\t\t\t\tPlease enter Stock details" << endl;

    cout << "\t\t\t\tGoods ID: ";
    cin >> goods->goodsID;

    goods = goodsManager.selectGoods(goods->goodsID);

    cout << "\t\t\t\tGoods Stock: ";
    cin >> quantity;

    goods->goodsStock = UpdateAddStock(quantity, goods);


    int statusUpdate = goodsManager.updateGoods(goods);

invalidInputUpdateStock:
    cout << "\n\t\t\t\tPress '1' to Manage Stock Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        ManageStockMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputUpdateStock;
    }

}


void CustomerMenu()
{
    int chooseOneFromMenu = 0;

    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t****            Customer Menu          ****" << endl;
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t1. Order Menu" << endl;
    cout << "\t\t\t\t2. Search Receipt No" << endl;
    cout << "\t\t\t\t3. Main Menu " << endl;
    cout << "\t\t\t\t*******************************************" << endl;

    cout << "\t\t\t\tChoose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        CustomerOrder();
        break;
    case 2:
        CustomerSearchReceiptNo();
        break;
    case 3:
        StaffMenu(staffID);
        break;
    default:
        cout << "\t\t\t\tPlease choose between 1 - 3. Press Enter To Continue...";
        system("cls");
        CustomerMenu();
        break;
    }
}


int UpdateDeductStock(int quantity, Goods* goods)
{
    return goods->goodsStock = goods->goodsStock - quantity;
}


double calculateTotalPrice(double price, int quantity)
{
    double totalPrice;
    totalPrice = price * quantity;
    return totalPrice;
}

void CustomerOrder()
{
    Goods* goods = new Goods();
    Goods* goodsName = new Goods();
    GoodsManager goodsManager;

    Buy* buy = new Buy();
    BuyManager buyManager;

    SaleRecord* saleRecord = new SaleRecord();
    SaleRecordManager saleRecordManager;


    int choose, buyGoodsID, option;
    char chooseDecision;
    string answer;

    time_t rawtime;
    srand(time(&rawtime));
    int receiptOrder = rand();

    system("cls");
    cout << "\t\t\t\t*****************************************************************" << endl;
    cout << "\t\t\t\t****                       Order Menu                        ****" << endl;
    cout << "\t\t\t\t*****************************************************************" << endl;


    do {

    invalidInput3:
        system("cls");
        goodsManager.displayGoods();

        cout << "\n\n\t\t\t\tWould you like to search by Goods Name?" << endl;
        cout << "\t\t\t\t1) Yes" << endl;
        cout << "\t\t\t\t2) No" << endl;
        cout << "\t\t\t\tInput: ";
        cin >> option;


        if (option == 1) {
            system("cls");
            goodsManager.displayGoods();
            cout << "\n\t\t\t\tInput Goods Name: ";
            cin >> goodsName->goodsName;
            system("cls");
            goodsManager.searchGoodsName(goodsName->goodsName);
            cout << endl;
            goto goToGoodsID;
        }
        else if (option == 2) {
            goto goToGoodsID;
        }
        else if (!(option == 1 || option == 2)) {
            cout << "\n\n\t\t\t\tInvalid input" << endl;
            system("pause");
            goto invalidInput3;
        }


    goToGoodsID:
        cout << "\n\n\t\t\t\tPlease enter ID of the Goods: ";
        cin >> buy->goodsID;

        goods = goodsManager.selectGoods(buy->goodsID);

        cout << "\t\t\t\tQuantity: ";
        cin >> buy->buyQuantity;

        cout << "\n\t\t\t\tReceipt Order: " << receiptOrder << endl;
        cout << "\n\t\t\t\tGoods ID: " << buy->goodsID << endl;
        cout << "\t\t\t\tGoods Name: " << goods->goodsName << endl;
        cout << "\t\t\t\tGoods Price: " << goods->goodsPrice << endl;
        cout << "\t\t\t\tBuy Quantity: " << buy->buyQuantity << endl;

        cout << "\t\t\t\tTotal Price: RM ";
        buy->totalPrice = calculateTotalPrice(goods->goodsPrice, buy->buyQuantity);
        cout << buy->totalPrice << endl;

        buy->receiptNo = receiptOrder;

        buyManager.orderItem(buy);

        goods->goodsStock = UpdateDeductStock(buy->buyQuantity, goods);

        goodsManager.updateGoods(goods);


    invalidInput:
        cout << "\n\t\t\t\tOrder another item?";
        cout << "\n\t\t\t\tY) = Yes";
        cout << "\n\t\t\t\tN) = No";
        cout << "\n\t\t\t\tEnter Input: ";
        cin >> chooseDecision;

        if (chooseDecision == 'N' || chooseDecision == 'n')
        {
        GO1:
            system("cls");
            cout << "\n\n";
            buyManager.showOrderItem();

            int choice1;

            cout << "\t\t\t\tWould you like to proceed payment?" << endl;
            cout << "\t\t\t\t1) Proceed Payment" << endl;
            cout << "\t\t\t\t2) Delete Order Item" << endl;
            cout << "\t\t\t\t3) Cancel Order" << endl;
            cout << "\n\t\t\t\tEnter Input: ";
            cin >> choice1;

            if (choice1 == 1)
            {

                time_t now = time(0);
                char* date_time = ctime(&now);

                system("cls");
                cout << "\n\t\t\t\t\t************************";
                cout << "\n\t\t\t\t\t*  Payment Succesfull  *";
                cout << "\n\t\t\t\t\t************************";

                cout << endl;
                system("pause");

                system("cls");
                cout << "\n\t\t\t\t-------------------------------------------------------------------------" << endl;
                cout << "\t\t\t\t Receipt Order: " << buy->receiptNo << "\t\t\t\t" << date_time;
                buyManager.showOrderItem();

                saleRecordManager.saleRecord();

                buyManager.clearOrderItem();

            GO3:
                cout << "\n\n\t\t\t\tPress '1' to  Customer Order";
                cout << "\n\t\t\t\tPress '2' to Customer Menu: ";

                cin >> choose;
                if (choose == 1)
                {
                    CustomerOrder();
                }
                else if (choose == 2)
                {
                    CustomerMenu();
                }
                else if (!(choose == 2 || choose == 1))
                {
                    system("cls");
                    cout << "\t\t\t\tInvalid Input" << endl;
                    system("pause");
                    goto GO3;
                }
            }
            else if (choice1 == 2)
            {
                cout << "\t\t\t\tEnter Goods ID: ";
                cin >> buyGoodsID;

                goodsManager.updateQuantity(buyGoodsID);

                int statusOrderDelete = buyManager.deleteOrderItem(buyGoodsID);

                if (statusOrderDelete != 0)
                {
                    cout << "\t\t\t\tSuccessfully remove goods." << endl;
                    system("pause");
                    goto GO1;
                }
                else
                {
                    cout << "\t\t\t\tUnable to remove goods." << endl;
                }
            }
            else if (choice1 == 3)
            {
                system("pause");
                system("cls");

                cout << "\n\t\t\t\t\t******************************";
                cout << "\n\t\t\t\t\t*        Order Cancel        *";
                cout << "\n\t\t\t\t\t******************************";

                buyManager.updateAllGoodsStock();
                buyManager.clearOrderItem();

            GO4:
                cout << "\n\n\t\t\t\tPress '1' to  Customer Order";
                cout << "\n\t\t\t\tPress '2' to Customer Menu: ";

                cin >> choose;
                if (choose == 1)
                {
                    CustomerOrder();
                }
                else if (choose == 2)
                {
                    CustomerMenu();
                }
                else if (!(choose == 2 || choose == 1))
                {
                    system("cls");
                    cout << "\t\t\t\tInvalid Input" << endl;
                    system("pause");
                    goto GO4;
                }
            }
            else if (!(choice1 == 1 || choice1 == 2 || choice1 == 3))
            {
                system("cls");
                cout << "\t\t\t\tInvalid Input" << endl;
                system("pause");
                goto GO1;
            }

        }

        else if (!(chooseDecision == 'N' || chooseDecision == 'n' || chooseDecision == 'Y' || chooseDecision == 'y'))
        {
            cout << "\n\t\t\t\tInvalid Input !!!" << endl;
            goto invalidInput;
        }

    } while (chooseDecision == 'Y' || chooseDecision == 'y');

}


void CustomerSearchReceiptNo()
{
    SaleRecord* saleRecord = new SaleRecord();
    SaleRecordManager saleRecordManager;

    int choose;

    system("cls");
    cout << "\t\t\t************************************************************************************************************************************" << endl;
    cout << "\t\t\t****                                                     Customer Receipt Order                                                 ****" << endl;
    cout << "\t\t\t************************************************************************************************************************************" << endl;

    cout << "\t\t\t\tPlease input Receipt No: ";
    cin >> saleRecord->receiptNo;

    saleRecordManager.searchByReceiptNo(saleRecord->receiptNo);

invalidInputCustomerReceipt:
    cout << "\n\n\t\t\t\tPress '1' to  Customer Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        CustomerMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputCustomerReceipt;
    }
}


void SaleReportMenu()
{
    int chooseOneFromMenu;

    system("cls");
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t****            Sale Report            ****" << endl;
    cout << "\t\t\t\t*******************************************" << endl;
    cout << "\t\t\t\t1. View Sale Record" << endl;
    cout << "\t\t\t\t2. View Sale Record By Goods ID" << endl;
    cout << "\t\t\t\t3. View Sale Record By Goods Name" << endl;
    cout << "\t\t\t\t4. View Sale Record By Highest Goods Sold" << endl;
    cout << "\t\t\t\t5. View Sale Record By Date" << endl;
    cout << "\t\t\t\t6. Main Menu " << endl;
    cout << "\t\t\t\t*******************************************" << endl;


    cout << "\t\t\t\tChoose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        ViewSaleRecord();
        break;
    case 2:
        ViewSaleRecordByGoodsID();
        break;
    case 3:
        ViewSaleRecordByGoodsName();
        break;
    case 4:
        ViewSaleRecordByHighestSold();
        break;
    case 5:
        ViewSaleRecordByDate();
        break;
    case 6:
        StaffMenu(staffID);
        break;
    default:
        cout << "\t\t\t\tPlease choose between 1 - 6. Press Enter To Continue...";
        system("cls");
        SaleReportMenu();
        break;
    }


}


void ViewSaleRecord()
{
    SaleRecord* saleRecord = new SaleRecord();
    SaleRecordManager saleRecordManager;

    int choose;

    system("cls");
    cout << "\t\t\t\t***********************************************************************************************************************" << endl;
    cout << "\t\t\t\t****                                                  Sale Record                                                  ****" << endl;
    cout << "\t\t\t\t***********************************************************************************************************************" << endl;


    saleRecordManager.showSaleRecord();

invalidInputViewStock:
    cout << "\n\n\t\t\t\tPress '1' to  Sale Report Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        SaleReportMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputViewStock;
    }
}


void ViewSaleRecordByGoodsID()
{
    Goods* goods = new Goods();
    GoodsManager goodsManager;

    SaleRecord* saleRecord = new SaleRecord();
    SaleRecordManager saleRecordManager;

    int choose;

    system("cls");
    cout << "\t\t\t\t***********************************************************************************************************************" << endl;
    cout << "\t\t\t\t****                                                  Sale Record                                                  ****" << endl;
    cout << "\t\t\t\t***********************************************************************************************************************" << endl;

    goodsManager.displayGoods();

    cout << "\n\t\t\t\tEnter Goods ID: ";
    cin >> saleRecord->goodsID;

    saleRecordManager.searchByGoodsID(saleRecord->goodsID);


invalidInputViewByGoodsID:
    cout << "\n\n\t\t\t\tPress '1' to  Sale Report Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        SaleReportMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputViewByGoodsID;
    }
}

void ViewSaleRecordByGoodsName()
{
    Goods* goods = new Goods();
    GoodsManager goodsManager;

    SaleRecord* saleRecord = new SaleRecord();
    SaleRecordManager saleRecordManager;

    int choose;

    system("cls");
    cout << "\t\t\t\t***********************************************************************************************************************" << endl;
    cout << "\t\t\t\t****                                                  Sale Record                                                  ****" << endl;
    cout << "\t\t\t\t***********************************************************************************************************************" << endl;

    goodsManager.displayGoods();

    cout << "\n\t\t\t\tEnter Goods Name: ";
    cin >> saleRecord->goodsName;

    saleRecordManager.searchByGoodsName(saleRecord->goodsName);

invalidInputViewByGoodsName:
    cout << "\n\n\t\t\t\tPress '1' to  Sale Report Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        SaleReportMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputViewByGoodsName;
    }
}


void ViewSaleRecordByHighestSold()
{
    SaleRecord* saleRecord = new SaleRecord();
    SaleRecordManager saleRecordManager;

    int choose;

    system("cls");
    cout << "\t\t\t\t***********************************************************************************************************************" << endl;
    cout << "\t\t\t\t****                                                  Sale Record                                                  ****" << endl;
    cout << "\t\t\t\t***********************************************************************************************************************" << endl;

    saleRecordManager.searchByHighestSold();

invalidInputViewByHighestSold:
    cout << "\n\n\t\t\t\tPress '1' to  Sale Report Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        SaleReportMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputViewByHighestSold;
    }
}

void ViewSaleRecordByDate()
{
    SaleRecord* saleRecord = new SaleRecord();
    SaleRecordManager saleRecordManager;

    int choose;

    system("cls");
    cout << "\t\t\t\t************************************************************************************************************************" << endl;
    cout << "\t\t\t\t****                                                           Sale Record                                          ****" << endl;
    cout << "\t\t\t\t************************************************************************************************************************" << endl;

    cout << "\n\t\t\t\tEnter Date Range Ex: 2021-08-01 ~ 2021-08-31" << endl;
    cout << "\n\t\t\t\tNote!!!: Second Date must +1 from the current date desire." << endl;
    cout << "\n\t\t\t\tExample to get Date in range (2021-08-01 to 2021-08-07)" << endl;
    cout << "\t\t\t\tDate 1: 2021-08-01" << endl;
    cout << "\t\t\t\tDate 2: 2021-08-08" << endl;

    cout << "\n\n\t\t\t\tEnter Date 1 (Ex:2021-08-01): ";
    cin >> saleRecord->dateSold1;

    cout << "\t\t\t\tEnter Date 2 (Ex:2021-08-31): ";
    cin >> saleRecord->dateSold2;

    saleRecordManager.searchByDate(saleRecord->dateSold1, saleRecord->dateSold2);


invalidInputViewByDate:
    cout << "\n\n\t\t\t\tPress '1' to  Sale Report Menu";
    cout << "\n\t\t\t\tPress '2' to Main Menu: ";

    cin >> choose;
    if (choose == 1)
    {
        SaleReportMenu();
    }
    else if (choose == 2)
    {
        StaffMenu(staffID);
    }
    else if (!(choose == 2 || choose == 1))
    {
        system("cls");
        cout << "\t\t\t\tInvalid Input" << endl;
        system("pause");
        goto invalidInputViewByDate;
    }
}
