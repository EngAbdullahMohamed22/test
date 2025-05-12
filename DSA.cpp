#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <Windows.h>
#include <ctime>
#include <chrono>
#include <sstream>
#include <conio.h>
/***
*@author BeBo
*/
using namespace std;
using namespace chrono;
enum Colors {
    black = 0,
    blue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    BRIGHT_BLACK = 8,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_MAGENTA = 13,
    BRIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

void setcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void reset() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void seperator() {
    setcolor(blue);
    cout << "-------------------------------\n";
    reset();
}

string Time_p() {
    auto now = time(0);
    tm local;
    localtime_s(&local, &now);
    char buffle[89];
    strftime(buffle, sizeof buffle, "%I:%M:%S %p", &local);
    string s = buffle;
    return s;
}

string TIMEPERSECOND() {
    auto TIME = system_clock::now();
    auto secondtime = system_clock::to_time_t(TIME);
    char arr[26];
    ctime_s(arr, sizeof arr, &secondtime);
    string s = arr;
    return s;
}

int login();

class person {
protected:
    string name, mobilephone, faculty;
    int age;
    string ID;

public:
    person() :name("unknown"), mobilephone("01"), faculty("unknown"),
        age(0), ID("unkown") {
    }

    person(string Name, string moblie, string fac, int Age, string id)
        :name(Name), mobilephone(moblie), faculty(fac), age(Age), ID(id) {
    }

    string NAME;
    string MOBILE;
    string FAC;

    void setname() {
        string n;
        cout << "Enter Your Name: ";
        getline(cin, n);
        NAME = n;
    }

    void setmobile() {
        string n;
        cout << "Enter Your Mobile Number: ";
        cin >> n;
        MOBILE = n;
    }

    void setfac() {
        string n;
        cout << "Enter Your Faculty Name: ";
        getline(cin, n);
        FAC = n;

    }

    int AGE = 0;

    void setage() {
        int n;
        cout << "Enter Your Age: ";
        cin >> n;
        AGE = n;
    }

    string IDNUMBER;

    void setID() {
        string n;
        cout << "Enter Your ID: ";
        getline(cin, n);
        IDNUMBER = n;
    }

    void getdetails() {
        if (NAME.empty() || MOBILE.empty() || FAC.empty() || AGE == 0 || IDNUMBER.empty()) {
            seperator();
            setcolor(4);
            cout << "Complete Your details first\n";
            reset();
            seperator();
            login();
        }
        else {
            seperator();
            cout << "Your Name is: " << NAME << endl;
            cout << "Your Phone Number is: " << MOBILE << endl;
            cout << "Your Faculty is: " << FAC << endl;
            cout << "Your Age is: " << AGE << endl;
            cout << "Your ID is: " << IDNUMBER << endl;
            seperator();
        }
    }
} p;

int cli_select_option(initializer_list<string> s, int i = 1) {
    int choice;
    for (auto& str : s) {
        if (str == "Exit") {
            setcolor(red);
            cout << i << ". " << str << endl;
            reset();
        }
        else {
            cout << i << ". " << str << endl;
        }
        i++;
    }
    seperator();
    while (true) {
        setcolor(green);
        cout << "Enter Your Choice (integer only): ";
        reset();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            setcolor(4);
            cout << "Invalid Choice, please Try Again\n";
            reset();
        }
        else if (choice == 0) {
            cout << "Please Enter another number instead of zero\n";
        }
        else if (choice < 0) {
            cout << "Enter a non-negative number\n";
        }
        else {
            cin.ignore(1000, '\n');
            return choice;
        }
    }
}

void app();

string setPassword() {
    string password = "";
    char ch;
    setcolor(green);
    cout << "Enter Your Password: ";
    reset();
    while (true) {
        ch = _getch();
        if (ch == '\r') break;
        else if (ch == ' ' || ch == -32 || ch == 72 || ch == 80 || ch == 77 || ch == 75) {
            continue;
        }
        else if (ch == 27) {
            cout << "\nYou Canceled a Password\n";
            seperator();
            setcolor(green);
            cout << "Enter Your Password: ";
            reset();
        }
        else if (ch == 8) {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            if (password.size() < 16)
                cout << '*';
            password += ch;
        }
    }
    cout << endl;
    seperator();
    if (password.size() > 16 || password.size() < 8) {
        setcolor(4);
        cout << "Invalid Password, it must be between 8 and 16 characters\n";
        reset();
        seperator();
        return setPassword();  // Properly return here
    }
    else return password;
}

string defult = " ";
string user = defult;
string password;

void cli_register() {
    seperator();
    string name;
    cout << "Enter Your Name: ";
    getline(cin, name);
    string pass = setPassword();
    user = name;
    password = pass;
    cout << "Your Account has been created\n";
    seperator();
}

void exit() {
    char c;
    setcolor(4);
    cout << "If You want to exit, press space\n";
    reset();
    cin >> c;
    if (c == ' ') return;
}

int login() {
    int number = cli_select_option({ "Name", "Mobile Phone", "Faculty", "Age", "ID", "Show Details", "Exit" });
    return number;
}

void cli_log_in() {
    seperator();
    string name;
    cout << "Enter Your Name: ";
    cin >> name;
    if (name != user) {
        cout << "User not found\n";
        seperator();
        app();
        return;
    }
    string pass = setPassword();
    if (pass != password) {
        cout << "Your password is incorrect\n";
        seperator();
        return;
    }
    string startprogram = Time_p();
    cout << "Logged in successfully\n";
    seperator();
    setcolor(14);
    cout << "The Program Started at: " << startprogram << endl;
    reset();
    seperator();

    while (true) {
        int number = cli_select_option({ "Name", "Mobile Phone", "Faculty", "Age", "ID", "Show Details", "Exit" });
        switch (number) {
        case 1:
            p.setname();
            seperator();
            break;
        case 2:
            p.setmobile();
            seperator();
            break;
        case 3:
            p.setfac();
            seperator();
            break;
        case 4:
            p.setage();
            seperator();
            break;
        case 5:
            p.setID();
            seperator();
            break;
        case 6:
            p.getdetails();
            seperator();
            break;
        case 7:
            seperator();
            return;
        default:
            seperator();
            cout << "Enter Valid Number\n";
            seperator();
            break;
        }
    }
}

void app() {
    setcolor(BRIGHT_YELLOW);
    cout << "<---Welcome--->\n";
    setcolor(blue);
    seperator();
    reset();
    int number = cli_select_option({ "Register", "Log in", "Exit" });
    switch (number) {
    case 1:
        cli_register();
        app();
        break;
    case 2:
        cli_log_in();
        app();
        break;
    case 3:
        break;
    default:
        seperator();
        cout << "Enter Valid Number\n";
        seperator();
        app();
        break;
    }
}

void begin_app() {
    string TIME = TIMEPERSECOND();
    setcolor(12);
    cout << "Date Of Day: " << TIME;
    reset();
    seperator();
    app();
    string endprogram = Time_p();
    seperator();
    setcolor(14);
    cout << "The Program Ended at: " << endprogram << endl;
    seperator();
    setcolor(3);
    cout << "Thank You for using the App\n";
    reset();
    seperator();
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    begin_app();
    return 0;
}
