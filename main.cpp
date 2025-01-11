#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;


// ANSI ESCAPE CODES FOR COLORS

#define WHITE "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define GRAY "\033[90m"


// STRACTURES //


// DECLARATION FUNCTIONS //

void init();
void login();

template <typename T> T read(string prompt);
string margin();
void logo();
void ioFunc(auto &variable, auto question);
void menu(vector<string> options);
void print(auto text, vector<string> options);
void lineSpacing(int number);
void inValidInput(string errorMassage);

int main() {

    init();

    return 0;
}

// DEFINITION FUNCTIONS //

void init() {
    logo();
    menu({"Login", "Sign-Up"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Please Choose An Option: ")) {
            case 1:
                print("login", {"text", WHITE});
                return;
            case 2:
                print("sign-up", {"text", WHITE});
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }

}

void login() {
    logo();
    print("LOGIN", {"text", CYAN});
    lineSpacing(2);
    string username, password;

    ioFunc(username, "Please Enter Your Username: ");
    lineSpacing(1);
    ioFunc(password, "Please Enter Your Password: ");
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

void ioFunc(auto &variable, auto question) {
    print(question, {"text", YELLOW});
    cin >> variable;
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
