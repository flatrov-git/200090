#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;


// ANSI ESCAPE CODES FOR COLORS

#define WHITE "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define GRAY "\033[90m"

// LENGTH RULES

#define MIN_LENGTH 3
#define MAX_LENGTH 15


// STRACTURES //


// DECLARATION FUNCTIONS //

void init();
void login();
void registerUser();
bool isUsernameTaken(string username);
bool isLogin(string username, string password);

template <typename T> T read(string prompt);
string margin();
void logo();
void menu(vector<string> options);
void print(auto text, vector<string> options);
void lineSpacing(int number);
void inValidInput(string errorMassage);
void minMaxRule(int minLength, int maxLength, string &variable);

int main() {

    init();

    return 0;
}

// DEFINITION FUNCTIONS //

void init() {
    system("cls");
    logo();
    menu({"Login", "Register"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Please Choose An Option: ")) {
            case 1:
                login();
                return;
            case 2:
                registerUser();
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }

}

void login() {
    system("cls");
    logo();
    print("LOGIN", {"text", CYAN});
    lineSpacing(2);

    string username = read<string>("Please Enter Your Username: ");
    minMaxRule(MIN_LENGTH, MAX_LENGTH, username);
    lineSpacing(1);
    string password = read<string>("Please Enter Your Password: ");
    minMaxRule(MIN_LENGTH, MAX_LENGTH, password);

    if(isLogin(username, password)) {
        print("login", {"text", GREEN});
    }else {
        system("cls");
        print("The Username Or Password Is Incorrect", {"text", RED});
        lineSpacing(2);
        menu({"Try Again", "Register"});

        while(true) {
            switch(read<int>("Please Choose An Option: ")) {
                case 1:
                    login();
                    return;
                case 2:
                    registerUser();
                    return;
                default:
                inValidInput("Invalid Input. Please Try Again.");
            }
        }
    }
}

void registerUser() {
    system("cls");
    logo();
    print("REGISTER", {"text", CYAN});
    lineSpacing(2);

    string username, password, type = "USER";
    username = read<string>("Please Create Your Username: ");
    minMaxRule(MIN_LENGTH, MAX_LENGTH, username);

    while(isUsernameTaken(username)) {
        lineSpacing(1);
        print("Username Is Already Taken", {"text", RED});
        lineSpacing(2);
        username = read<string>("Please Create Your Username: ");
    }

    lineSpacing(1);
    password = read<string>("Please Create Your Password: ");
    minMaxRule(MIN_LENGTH, MAX_LENGTH, password);

    ofstream usersFile("users.txt", ios::app);
    usersFile << username << " " << password << " " << type << '\n';

}

bool isUsernameTaken(string username) {
    ifstream usersFile("users.txt");
    string fileUsername, filePassword, fileType;

    while(usersFile >> fileUsername >> filePassword >> fileType) {
        if(fileUsername == username)
            return true;
    }

    return false;
}

bool isLogin(string username, string password) {
    ifstream usersFile("users.txt");
    string fileUsername, filePassword, fileType;

    while(usersFile >> fileUsername >> filePassword >> fileType) {
        if(fileUsername == username && filePassword == password)
            return true;
    }

    return false;
}

template <typename T>
T read(string prompt) {
    T value;
    while(true) {
        print(prompt, {"text", YELLOW});
        cin >> value;

        // INPUT VALIDATION
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            inValidInput("Invalid Input. Please Try Again.");
        } else {
            return value;
        }
    }
}

string margin() {
    return "   ";
}

void logo() {
    lineSpacing(1);
    print("  _______  ________  ________  ________  ________  ________", {"text", MAGENTA});
    lineSpacing(1);
    print(" /  ___  \\|\\   __  \\|\\   __  \\|\\   __  \\|\\  ___  \\|\\   __  \\", {"text", MAGENTA});
    lineSpacing(1);
    print("/__/|_/  /\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\____   \\ \\  \\|\\  \\", {"text", MAGENTA});
    lineSpacing(1);
    print("|__|//  / /\\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\\\\\  \\|____|\\  \\ \\  \\\\\\  \\ ", {"text", MAGENTA});
    lineSpacing(1);
    print("    /  /_/__\\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\\\\\  \\  __\\_\\  \\ \\  \\\\\\  \\", {"text", MAGENTA});
    lineSpacing(1);
    print("   |\\________\\ \\_______\\ \\_______\\ \\_______\\|\\_______\\ \\_______\\", {"text", MAGENTA});
    lineSpacing(1);
    print("    \\|_______|\\|_______|\\|_______|\\|_______|\\|_______|\\|_______|", {"text", MAGENTA});
    lineSpacing(5);
}

void menu(vector<string> options) {
    int counter = 1;

    for(string option : options) {
        print((to_string(counter) + ". " + option), {"text", CYAN});
        lineSpacing(2);
        counter++;
    }
}

void print(auto text, vector<string> options) {
    if(options[0] == "text")
        cout << margin() << options[1] << text << WHITE;
    else if(options[0] == "error")
        cout << margin() << options[1] << "ERROR: " << "[ " << text << " ]" << WHITE;
}

void lineSpacing(int number) {
    for(int i = 0; number > i; i++) {
        cout << '\n';
    }
}

void inValidInput(string errorMassage){
    lineSpacing(1);
    print(errorMassage, {"text", RED});
    lineSpacing(2);
}

void minMaxRule(int minLength, int maxLength, string &variable) {
    int lengthVar = variable.length();

    while(minLength > lengthVar || maxLength < lengthVar) {
        lineSpacing(1);

        if(minLength > lengthVar) {
            print("Input Length must Be Greater Than " + to_string(minLength), {"text", RED});
        }else {
            print("Input Length must Be Less Than " + to_string(maxLength), {"text", RED});
        }

        lineSpacing(2);
        variable = read<string>("Please Try Again: ");
        lengthVar = variable.length();
    }
}
