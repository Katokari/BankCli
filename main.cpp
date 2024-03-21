#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "MyInputsOutputs.h"

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string Name;
    string PhoneNumber;
    double AccountBalance;
    bool MarkForDeletion = false;
};
string CLIENTS_PATH = "Clients.txt";

string ConvertRecordToLine(stClientData& ClientData, string Delim)
{
    string S1 = ClientData.AccountNumber + Delim
              + ClientData.PinCode + Delim
              + ClientData.Name + Delim
              + ClientData.PhoneNumber + Delim
              + to_string(ClientData.AccountBalance);
    return S1;
}

stClientData ConvertLineToRecord(string S1, string Delim)
{
    stClientData ClientData;
    vector<string> LineRecord = MyInput::SplitString(S1, Delim);

    ClientData.AccountNumber = LineRecord.at(0);
    ClientData.PinCode = LineRecord.at(1);
    ClientData.Name = LineRecord.at(2);
    ClientData.PhoneNumber = LineRecord.at(3);
    ClientData.AccountBalance = stod(LineRecord.at(4));

    return ClientData;
}

vector<stClientData> ReadClientsFromFile(string FilePath)
{
    vector<stClientData> vClients;
    fstream File;
    File.open(FilePath, ios::in);

    if (File.is_open())
    {
        string Line;
        while (getline(File, Line))
        {
            vClients.push_back(ConvertLineToRecord(Line, "#//#"));
        }

        File.close();
    }

    return vClients;
}

void SaveClientsToFile(vector<stClientData>& vClients, string FilePath)
{
    fstream File;
    File.open(FilePath, ios::out);
    string Line;

    if (File.is_open())
    {
        for (stClientData& Client : vClients)
        {
            if (Client.MarkForDeletion == false)
            {
                Line = ConvertRecordToLine(Client, "#//#");
                File << Line << endl;
            }
        }

        File.close();
    }
}

void ShowClientListScreen(vector<stClientData>& vClients)
{
    system("CLS");

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
    cout << "___________________________________________________________________________________________________\n\n";
    cout << setw(18) << left << "| Account Number" << setw(14) << left << "| Pin Code" << setw(40) << left << "| Client Name" << setw(16) << left << "| Phone" << setw(11) << left << "| Balance\n";
    cout << "___________________________________________________________________________________________________\n\n";
    
    for (stClientData& Client : vClients)
    {
        cout << "| " << setw(16) << left << Client.AccountNumber << "| " << setw(12) << left << Client.PinCode << "| " << setw(38) << left << Client.Name << "| " << setw(14) << left << Client.PhoneNumber << "| " << setw(9) << left << Client.AccountBalance << "\n";
    }

    cout << "\n___________________________________________________________________________________________________\n\n";
    cout << "\n\n\nPress any key to go back to Main Menu...";

    system("pause");
}

bool SearchClientByAccountNumber(vector<stClientData> vClients, string AccountNumber, stClientData& Client)
{
    for (stClientData& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
        
    }
    return false;
}

stClientData ReadNewClient(string AccountNumber)
{
    stClientData ClientData;

    ClientData.AccountNumber = AccountNumber;
    ClientData.PinCode       = MyInput::ReadString("Enter PinCode? ");
    ClientData.Name          = MyInput::ReadString("Enter Name? ");
    ClientData.PhoneNumber   = MyInput::ReadString("Enter Phone Number? ");
    ClientData.AccountBalance = MyInput::ReadPositiveNumber("Enter AccountBalance? ", "Wrong Input, Please try Again? ");

    return ClientData;
}

void AddNewClient(vector<stClientData>& vClients)
{
    string AccountNumber;
    stClientData Client;
    char Answer;

    cout << "Adding New Client:\n\n";
    AccountNumber = MyInput::ReadString("Enter Account Number? ");

    while (SearchClientByAccountNumber(vClients, AccountNumber, Client))
    {
        AccountNumber = MyInput::ReadString("\nClient with [" + AccountNumber + "] already exists, Enter another Account Number? ");
    }

    Client = ReadNewClient(AccountNumber);
    vClients.push_back(Client);
}

void AddNewClientScreen(vector<stClientData>& vClients)
{
    system("CLS");
    char Answer = 'Y';

    cout << endl;
    cout << "--------------------------------------\n";
    cout << "\tAdd New Clients Screen\n";
    cout << "--------------------------------------\n";

    do
    {
        AddNewClient(vClients);
        Answer = MyInput::ReadChar("Client Added Successfully, do you want to add more clients? Y/N? ");
        cout << endl;

    } while (Answer == 'Y' || Answer == 'y');
    
    SaveClientsToFile(vClients, CLIENTS_PATH);
    
    cout << "\n\n\nPress any key to go back to Main Menu...";

    system("pause");
}

bool MarkClientForDeletionByAccountNumber(vector<stClientData>& vClients, string AccountNumber)
{
    for (stClientData& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            Client.MarkForDeletion = true;
            return true;
        }   
    }
    return false;
}

void PrintClient(stClientData& Client)
{
    cout << "\nThe following are the client details:\n" << endl;

    cout << "-----------------------------------------------\n";
    cout << "Account Number: " << Client.AccountNumber << endl;
    cout << "Pin Code      : " << Client.PinCode << endl;
    cout << "Name          : " << Client.Name << endl;
    cout << "Phone         : " << Client.PhoneNumber << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
    cout << "-----------------------------------------------\n";
}

bool DeleteClientByAccountNumber(vector<stClientData>& vClients, string AccountNumber)
{
    stClientData Client;
    char Answer = 'n';

    if (SearchClientByAccountNumber(vClients, AccountNumber, Client))
    {
        PrintClient(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? "; 
        cin >> Answer;
        
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeletionByAccountNumber(vClients, AccountNumber);
            SaveClientsToFile(vClients, CLIENTS_PATH);

            vClients = ReadClientsFromFile(CLIENTS_PATH);

            cout << "\n\nClient Deleted Successfully.";

            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

void DeleteClientScreen(vector<stClientData>& vClients)
{
    system("CLS");
    string AccountNumber;

    cout << endl;
    cout << "--------------------------------------\n";
    cout << "\tDelete Client Screen\n";
    cout << "--------------------------------------\n";

    AccountNumber = MyInput::ReadString("\nPlease enter Account Number? ");
    if (DeleteClientByAccountNumber(vClients, AccountNumber))
    {
        cout << "\n\n\nPress any key to go back to Main Menu...";

        system("pause");
    }
}

bool UpdateClientByAccountNumber(vector<stClientData>& vClients, string AccountNumber)
{
    stClientData Client;
    char Answer = 'n';

    if (SearchClientByAccountNumber(vClients, AccountNumber, Client))
    {
        PrintClient(Client);

        cout << "\n\nAre you sure you want update this client? y/n ? "; 
        cin >> Answer;
        
        if (Answer == 'y' || Answer == 'Y')
        {
            for (stClientData& C : vClients)
            {
                if (C.AccountNumber == Client.AccountNumber)
                {
                    C = ReadNewClient(C.AccountNumber);
                    break;
                }
            }
            
            SaveClientsToFile(vClients, "Clients.txt");

            cout << "\n\nClient Updated Successfully.";

            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

void UpdateClientScreen(vector<stClientData>& vClients)
{
    system("CLS");
    string AccountNumber;

    cout << endl;
    cout << "--------------------------------------\n";
    cout << "\tUpdate Client Screen\n";
    cout << "--------------------------------------\n";

    AccountNumber = MyInput::ReadString("\nPlease enter Account Number? ");
    if (UpdateClientByAccountNumber(vClients, AccountNumber))
    {
        cout << "\n\n\nPress any key to go back to Main Menu...";

        system("pause");
    }
}

void FindClientScreen(vector<stClientData>& vClients)
{
    system("CLS");
    string AccountNumber;

    cout << endl;
    cout << "------------------------------------\n";
    cout << "\tFind Client Screen\n";
    cout << "------------------------------------\n";

    AccountNumber = MyInput::ReadString("\nPlease enter Account Number? ");

    for (stClientData& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            PrintClient(C);
        }
    }

    cout << "\n\n\nPress any key to go back to Main Menu...";

    system("pause");

}

void ShowMainMenueScreen(vector<stClientData>& vClients)
{
    while(true)
    {
        system("CLS");
        int Answer;

        cout << "==============================================\n";
        cout << "\t\tMain Menue Screen\n";
        cout << "==============================================\n";
        cout << "\t[1] Show Client List.\n";
        cout << "\t[2] Add New Client.\n";
        cout << "\t[3] Delete Client.\n";
        cout << "\t[4] Update Client Info.\n";
        cout << "\t[5] Find Client.\n";
        cout << "\t[6] Exit.\n";
        cout << "==============================================\n";
        
        Answer = MyInput::ReadNumberInRange("Choose what do you want to do? [1 to 6]? ", "Please Choose a number from [1 to 6]? ", 1, 6);

        switch (Answer)
        {
            case 1 :
                ShowClientListScreen(vClients);
                break;
            case 2 :
                AddNewClientScreen(vClients);
                break;
            case 3 :
                DeleteClientScreen(vClients);
                break;
            case 4 :
                UpdateClientScreen(vClients);
                break;
            case 5 :
                FindClientScreen(vClients);
                break;
            case 6 :
                exit(0);
                break;
        }
    }
}


int main()
{   
    vector <stClientData> vClients = ReadClientsFromFile(CLIENTS_PATH);
    ShowMainMenueScreen(vClients);

    system("pause");

    return 0;
}