#include<iostream>
#include <fstream>
#include<vector>
using namespace std;


// class customer

class customer
{
    
   vector<string> history;
  string name;
  long long account_numer;
  string pin;
  long long balance;
  public:
  
  //default constructor

  customer()
   {
    name="";
    account_numer=0;
    pin="";
    balance=0;
   }
 
  customer(string name,long long account_number,string pin,long long balance)
  {
    this->name=name;
    this->account_numer=account_number;
    this->pin=pin;
    this->balance=balance;
  }

  //method to add history in data base

  void addHistory(string msg)
  {
    history.push_back(msg);
  }

  //method to show history 

  void showHistory()
 {
    cout << "\n--- Transaction History ---\n";

    if(history.empty())
    {
        cout << "No transactions yet\n";
        return;
    }

    for(int i = 0; i < history.size(); i++)
    {
        cout << i + 1 << ". " << history[i] << endl;
    }
  }

  //method to deposite the amount in acocunt 

  void deposit(int amount)
  {
    if(amount>0)
    {
        balance+=amount;
        cout<<amount<<"  Rupees is deposited into your account"<<endl;
         addHistory("Deposited " + to_string(amount));
    }
    else
        {
            cout << "Invalid deposit amount\n";
        }
  }

  //method for withdrawing money

  void withdraw(int amount)
  {
     if(amount <= 0)
        {
            cout << "Invalid withdrawal amount\n";
        }
    else if(amount > balance)
        {
            cout << "Insufficient balance\n";
        }
    else
        {
            balance -= amount;
            cout << amount << " Rupees withdrawn successfully\n";
            addHistory("Withdrawn " + to_string(amount));
        }
   
  }

 //method for checking balance 

  void checkbalance()
  {
    cout << "Remaining Balance = " << balance << endl;
  }


  void changepin(string newpin)
  {
    pin=newpin;
    addHistory("PIN changed");
    cout << "PIN changed successfully\n";

  }

  //method for verifying pin 

  bool verifypin(string enteredPin)
  {
     if(enteredPin == pin)
        {
            return true;
        }
        else
        {
           return false;
        }
   }

   // accessing the information of the customer 
   //wherever the requiremnet occured


   long long getaccountnumber() const
  {
    return account_numer;
  }
  string getName()const
  {
    return name;
  }

  string getPin()const
  {
    return pin;
  }
  long long getBalance()const
  {
    return balance;
  }
    vector<string> getHistory() const
   {
    return history;
    }


};

//atm class main m functioninh class 
// handling al;l the acitivity that is made by the    customer

class atm 
{
    int max_attempt = 3;
    static vector<customer> database;
    public:
       static void addCustomer(customer c)
    {
        database.push_back(c);
    }

    /* atm( vector<customer>customers)
     {
        database=customers;
     }*/

     // finding the person in database if the enetred account number tha number and the person exits or not

     customer *findcustomer(long long int account_number)
    {
        for(int i=0;i<database.size();i++)
        {
            if(database[i].getaccountnumber()==account_number)
            {
                return &database[i];
            }
        }
        return nullptr;
    }

    //authenticating the person 

    bool authenticate(customer &c)
    {
        
        
          string enteredPin;
          int attempt = 0;

          while (attempt < max_attempt)
          {
            cout << "Enter PIN: ";
            cin >> enteredPin;

            if (c.verifypin(enteredPin))
            {
                cout << "Login Successful.\n";
                return true;
            }

            attempt++;

            cout << "Wrong PIN. Attempts Left: "
                 << max_attempt - attempt
                 << endl;
          }
        

        cout << "Access Denied.\n";
          return false;
        
    }

    //atm menu 

    void showmenu()
    {
      cout<<"\n============ATM MENU===================\n";
      cout<<"1. Check Balance\n";
      cout<<"2. Deposite\n";
      cout<<"3. Withdraw\n";
      cout<<"4. Changepin\n";
      cout<<"5. Transaction History\n";
      cout<<"6. Exit\n";
    }

    //atm perform operation  

    void performoperation(customer&c)
    {
      
       int choice;

        do
        {
            showmenu();
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                c.checkbalance();
                break;

            case 2:
            {
                int amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                c.deposit(amount);
                saveToFile();
                break;
            }

            case 3:
            {
                int amount;
                cout << "Enter withdraw amount: ";
                cin >> amount;
                c.withdraw(amount);
                saveToFile();
                break;
            }

            case 4:
            {
                string newpin;

                cout << "Enter new PIN: ";
                cin >> newpin;

                if(newpin.length() != 4)
               {
                 cout << "PIN must be exactly 4 digits\n";
                break;
               }

                bool valid = true;

                for(int i = 0; i < newpin.length(); i++)
                 {
                     if(newpin[i] < '0' || newpin[i] > '9')
                    {
                       valid = false;
                       break;
                     }
                 }

                if(!valid)
              {
               cout << "PIN must contain only digits\n";
                break;
                }

                   c.changepin(newpin);
                   saveToFile();
                    break; 
            }
            case 5:
            {
               c.showHistory();
               break;
            }

            case 6:
                cout << "Thank you for using ATM\n";
                break;

            default:
                cout << "Invalid choice\n";
            }

        } while (choice != 6);
    }

//adding real world entity to this managemnet system
  void addCustomer()
 {
    string name;
    long long account_number;
    string pin;
    long long balance;

    cout << "Enter name: ";
    cin >> name;

    cout << "Enter account number: ";
    cin >> account_number;
    if(account_number < 10000000)
    {
      cout << "Invalid account number\n";
      return;
    }

    if(findcustomer(account_number) != nullptr)
    {
        cout << "Account already exists\n";
        return;
     }

    cout << "Set PIN: ";
    cin >> pin;
    if(pin.length() != 4)
    {
      cout << "PIN must be exactly 4 digits\n";
      return;
    }

    for(int i = 0; i < pin.length(); i++)
    {
       if(pin[i] < '0' || pin[i] > '9')
        {
        cout << "PIN must contain only digits\n";
        return;
        }
    }
     cout << "Enter initial balance: ";
    cin >> balance;
    if(balance < 0)
     {
      cout << "Balance cannot be negative\n";
       return;
     }
     customer newCustomer(name, account_number, pin, balance);

       database.push_back(newCustomer);

      saveToFile();


      cout << "Account created successfully!\n";
     
 }

//removing the rel world entity from the managemnet system
 void deleteCustomer(long long account_number)
 {
    for(int i = 0; i < database.size(); i++)
    {
        if(database[i].getaccountnumber() == account_number)
        {
            database.erase(database.begin() + i);
            saveToFile();
            cout << "Account deleted successfully\n";
            return;
        }
    }

    cout << "Account not found\n";
}
      
//saving the database to the file 

void saveToFile()
 {
    ofstream fout("customers.txt");

    for(int i = 0; i < database.size(); i++)
    {
        fout << database[i].getName() << "|"
     << database[i].getaccountnumber() << "|"
     << database[i].getPin() << "|"
     << database[i].getBalance() << "|";

      vector<string> h = database[i].getHistory();

      for(int j = 0; j < h.size(); j++)
      {
         fout << h[j];

         if(j != h.size()-1)
          {
            fout << ",";
           }
       }

        fout << endl;
    }

    fout.close();
  }
//accessing the data from the database
 void loadFromFile()
 {
    
     database.clear();

    ifstream fin("customers.txt");

    string line;

    while(getline(fin, line))
    {
        vector<string> parts;
        string temp = "";

        for(char ch : line)
        {
            if(ch == '|')
            {
                parts.push_back(temp);
                temp = "";
            }
            else
            {
                temp += ch;
            }
        }

        parts.push_back(temp);

        if(parts.size() < 4)
            continue;

        customer c(
            parts[0],
            stoll(parts[1]),
            parts[2],
            stoll(parts[3])
        );

        if(parts.size() >= 5)
        {
            string historyData = parts[4];
            string historyItem = "";

            for(char ch : historyData)
            {
                if(ch == ',')
                {
                    c.addHistory(historyItem);
                    historyItem = "";
                }
                else
                {
                    historyItem += ch;
                }
            }

            if(!historyItem.empty())
            {
                c.addHistory(historyItem);
            }
        }

        database.push_back(c);
    }

    fin.close();
 }

};


vector<customer> atm::database;

int main()
{
    atm machine;

    machine.loadFromFile();

    long long acc;
    int choice;
 do
 {
   cout << "1. Create Account\n";
   cout << "2. Login\n";
   cout << "3. Delete Account\n";
   cout << "4. Exit\n";

    cin >> choice;
    if(choice == 1)
   {
    machine.addCustomer();
   }
   if(choice == 3)
   {
    long long acc;

    cout << "Enter account number: ";
    cin >> acc;

    customer* c = machine.findcustomer(acc);

        if(c != nullptr)
        {
            if(machine.authenticate(*c))
            {
              machine.deleteCustomer(acc);
            }
        }
         else
        {
             cout << "Account not found\n";
        }
    }
    if(choice==2)
    {
        cout << "Enter account number: ";
        cin >> acc;

      customer* c = machine.findcustomer(acc);

       if(c != nullptr)
       {
        if(machine.authenticate(*c))
        {
            machine.performoperation(*c);
        }
       }
       else
       {
        cout << "Account not found\n";
        }
        
    }
    if(choice == 4)
    {
          return 0;
     }
    }while(choice!=4);

    return 0;
}
