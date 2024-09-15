#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

enum enMode
{
	EmptyMode = 0,
	UpdateMode,
	AddNewMode
};

class clsBankClient : public clsPerson
{
private:
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float  _AccountBalance;
	bool _MarkedForDeletion = false;

	static clsBankClient _convert_line_to_client_object(string line, string separator = "#//#") {
		vector<string>vClientData;
		vClientData = clsString::Split(line, separator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	};

	static clsBankClient _get_empty_client_object() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0.0);
	};

	struct stTrnsferLogRecord;

	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTrnsferLogRecord TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;
	}


	static string _convert_client_object_to_line(clsBankClient client, string separator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += client.FirstName + separator;
		stClientRecord += client.LastName + separator;
		stClientRecord += client.Email + separator;
		stClientRecord += client.Phone + separator;
		stClientRecord += client.getAccountNumber() + separator;
		stClientRecord += client.PinCode + separator;
		stClientRecord += to_string(client.AccountBalance);

		return stClientRecord;
	};

	static void _save_clients_data_to_file(vector <clsBankClient> vClients) 
	{
		fstream file1;
		file1.open("Clients.txt", ios::out);	//	overwrite mode

		string data_line;

		if (file1.is_open())
		{
			for (clsBankClient client : vClients)
			{
				if (client._MarkedForDeletion == false) {
					data_line = _convert_client_object_to_line(client);
					file1 << data_line << endl;
				}
			}
			file1.close();
		}
	};

	static vector<clsBankClient> _load_clients_data_from_file()
	{
		vector<clsBankClient> vClients;

		fstream file1;
		file1.open("Clients.txt", ios::in);	//	read mode

		if (file1.is_open())
		{
			string line;
			while (getline(file1, line))
			{
				clsBankClient client = _convert_line_to_client_object(line);
				vClients.push_back(client);
			}
			file1.close();
		}
		return vClients;
	}

	void _Update() 
	{
		vector<clsBankClient>_vClients;
		_vClients = _load_clients_data_from_file();

		for (clsBankClient& client : _vClients) 
		{
			if (client.getAccountNumber() == getAccountNumber()) 
			{
				client = *this;
				break;
			}
		}
		_save_clients_data_to_file(_vClients);
	};

	void _add_data_line_to_file(string data_line) 
	{
		fstream file1;
		file1.open("Clients.txt", ios::out | ios::app);

		if (file1.is_open())
		{
			file1 << data_line << endl;

			file1.close();
		}
	}

	void _AddNew() {
		_add_data_line_to_file(_convert_client_object_to_line(*this));
	};

public:

	struct stTrnsferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;

	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool isEmpty() { return _Mode == enMode::EmptyMode; }

	string getAccountNumber() { return _AccountNumber; };
	string getPinCode() { return _PinCode; };
	float getAccountBalance() { return _AccountBalance; };

	void setPinCode(string PinCode) { _PinCode = PinCode; };
	void setAccountBalance(float AccountBalance) { _AccountBalance = AccountBalance; };

	__declspec(property(get = getPinCode, put = setPinCode))string PinCode;
	__declspec(property(get = getAccountBalance, put = setAccountBalance))float AccountBalance;

	string getFullName() { return FirstName + " " + LastName; };

	//void Print()
	//{
	//	cout << "\nClient Info:";
	//	cout << "\n____________________________";
	//	cout << "\nFirstName   : " << FirstName;
	//	cout << "\nLastName    : " << LastName;
	//	cout << "\nFull Name   : " << getFullName();
	//	cout << "\nEmail       : " << Email;
	//	cout << "\nPhone       : " << Phone;
	//	cout << "\nAcc. Number : " << _AccountNumber;
	//	cout << "\nPassword    : " << _PinCode;
	//	cout << "\nBalance     : " << _AccountBalance;
	//	cout << "\n____________________________\n";

	//}

	static bool clientExists(string AccountNumber) { return !(Find(AccountNumber).isEmpty()); }

	static clsBankClient Find(string AccountNumber) {
		fstream file1;
		file1.open("Clients.txt", ios::in);	//	read mode

		if (file1.is_open()) 
		{
			string line;
			while (getline(file1, line)) 
			{
				clsBankClient client = _convert_line_to_client_object(line);
				if (client.getAccountNumber() == AccountNumber)
				{
					file1.close();
					return client;
				}
			}
			file1.close();
		}
		return _get_empty_client_object();
	};

	static clsBankClient Find(string AccountNumber, string PinCode) {
		fstream file1;
		file1.open("Clients.txt", ios::in);	//	read mode

		if (file1.is_open())
		{
			string line;
			while (getline(file1, line))
			{
				clsBankClient client = _convert_line_to_client_object(line);
				if (client.getAccountNumber() == AccountNumber && client.PinCode == PinCode)
				{
					file1.close();
					return client;
				}
			}
			file1.close();
		}
		return _get_empty_client_object();
	};

	bool Delete()
	{
		vector<clsBankClient> _vClients;
		_vClients = _load_clients_data_from_file();

		for (auto& client : _vClients)
		{
			if (client.getAccountNumber() == _AccountNumber)
			{
				client._MarkedForDeletion = true;
				break;
			}
		}
		_save_clients_data_to_file(_vClients);
		*this = _get_empty_client_object();

		return true;
	}

	enum enSaveStatus
	{
		svFailed_empty_object = 0,
		svSucceeded,
		svFailed_account_number_exists
	};

	enSaveStatus Save()
	{
		switch (_Mode)
		{
		case EmptyMode:
			return enSaveStatus::svFailed_empty_object;

		case UpdateMode:
			_Update();
			return enSaveStatus::svSucceeded;

		case AddNewMode:

			if (clsBankClient::clientExists(_AccountNumber)) {
				return enSaveStatus::svFailed_account_number_exists;
			}
			else {
				_AddNew();

				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveStatus::svSucceeded;
			}
		}
	}

	static clsBankClient add_new_client_object(string AccontNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccontNumber, "", 0.0);
	}

	static vector<clsBankClient> getClientsList()
	{
		return _load_clients_data_from_file();
	}

	static double getTotalBalances()
	{
		vector <clsBankClient> vClients = getClientsList();
		double TotalBalances = 0;

		for (clsBankClient clinet : vClients)
		{
			TotalBalances += clinet.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	void Withdraw(double Amount) {
		_AccountBalance -= Amount;
		Save();
	}

	static  vector <stTrnsferLogRecord> GetTransfersLogList()
	{
		vector <stTrnsferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);	//	read Mode

		if (MyFile.is_open())
		{
			string Line;
			stTrnsferLogRecord TransferRecord;

			while (getline(MyFile, Line))
			{
				TransferRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogRecord.push_back(TransferRecord);
			}
			MyFile.close();
		}
		return vTransferLogRecord;
	}
};