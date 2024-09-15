#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsDate.h"
#include "clsUtil.h"
#include "clsPerson.h"
#include "clsString.h"

using namespace std;
class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int    _Permissions;
    bool _MarkedForDeletion = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::EncryptText(User.Password) +Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;
    }

    static  vector <clsUser> _LoadUsersDataFromFile() {
        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLinetoUserObject(Line);
                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;
    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out); //  overwrite

        string DataLine;
        if (MyFile.is_open())
        {
            for (clsUser user : vUsers)
            {
                if (user.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(user);
                    MyFile << DataLine << endl;

                }
            }
            MyFile.close();
        }
    }

    struct stLoginRegisterRecord;

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;


        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = LoginRegisterDataLine[2];
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;

    }

    void _Update() {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& user : _vUsers)
        {
            if (user.UserName == UserName)
            {
                user = *this;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
    }

    void _AddNew() {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pShowLogs = 128
    };

    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    string getUserName() { return _UserName; }
    string getPassword() { return _Password; }
    int getPermissions() { return _Permissions; }

    void setUserName(string UserName) { _UserName = UserName; }
    void setPassword(string Password) { _Password = Password; }
    void setPermissions(int Permissions) { _Permissions = Permissions; }

    __declspec(property(get = getUserName, put = setUserName)) string UserName;
    __declspec(property(get = getPassword, put = setPassword)) string Password;
    __declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

    string getFullName() { return FirstName + " " + LastName; }

    bool MarkedForDeleted() {
        return _MarkedForDeletion;
    }

    bool isEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    static bool userExists(string UserName)
    {
        clsUser User = clsUser::Find(UserName);
        return (!User.isEmpty());
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case EmptyMode:
        {
            return enSaveResults::svFaildEmptyObject;
        }
        case UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }
        case AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::userExists(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
        }
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDeletion = true;
                break;
            }

        }
        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyUserObject();

        return true;
    }

    static clsUser GetAddNewUserObject(string UserName) {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList() {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::eAll)
            return true;

        if ((this->Permissions & Permission) == Permission)
            return true;

        else
            return false;
    }

    static void _StoreUserLog(string UserName, string Password, int Permissions, string separator = "#//#")
    {
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::app);

        string DataLine = "";
        if (MyFile.is_open())
        {
            DataLine += clsDate::clsDate().DateTimeToString();  
            // or DataLine += clsDate date; date.DateTimeToString();
            DataLine += separator;

            DataLine += UserName;
            DataLine += separator;

            DataLine += clsUtil::EncryptText(Password);
            DataLine += separator;

            DataLine += to_string(Permissions);

            MyFile << DataLine << endl;

            MyFile.close();
        }
    }

    static vector <stLoginRegisterRecord> LoadUserLogsFromFile()
    {
        vector<stLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in); //  read

        string Line;

        stLoginRegisterRecord loginRegisterRecord;

        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                loginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
                vLoginRegisterRecord.push_back(loginRegisterRecord);
            }
            MyFile.close();
        }
        return vLoginRegisterRecord;
    }

};
