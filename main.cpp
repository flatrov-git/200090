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

struct userDataType {
  string username;
  string type;
};


// -------- GLOBAL VARIABLE -------- //

vector<userDataType> userData;
vector<vector<string>> games;

// DECLARATION FUNCTIONS //

void init();
void login();
void registerUser();
bool isUsernameTaken(string username);
bool isLogin(string username, string password);
string typeClient(string username);
void setUserData(string username, string type);
void home();
void dashboardAdmin();
void tournamentHandler();
void getGames();
void addNewGame();
string organizingTournament();
void activeTournament();
void disableTournament();
void deleteAllGames();
void dashboardUser();
void clearTextfile(string nameFile);

template <typename T> T read(string prompt);
string margin();
void logo();
void menu(vector<string> options);
void print(auto text, vector<string> options);
void lineSpacing(int number);
void inValidInput(string errorMassage);
void minMaxRule(int minLength, int maxLength, string &variable);
void minMaxRule(int minLength, int maxLength, int &variable);
string capitalizeText(string text);
int intLength(int number);
bool isPowerTwo(int number);
string dynamicTable(vector<vector<string>> data, vector<string> rows, vector<int> columns, bool (*filter) (const vector<string>&) = nullptr, bool addNumbers = true, string indent = "   ") {
    string content = "\n";
    string betweenSpace = "  ";
    vector<int> rowsLength;
    vector<int> biggestColName;

    for (int i = 0; i < rows.size(); i++) {
        rowsLength.push_back(rows[i].length());
    }

    for (int i = 0; i < columns.size(); i++) {
        int currentBiggestLength = 0;
        for (int j = 0; j < data.size(); j++) {
            currentBiggestLength = max(currentBiggestLength, (int) data[j][columns[i]].length());
        }
        biggestColName.push_back(currentBiggestLength);
    }

    content += indent;
    for (int i = 0; i < rows.size(); i++) {
        content += rows[i];
        for (int j = 0; j < biggestColName[i] - rowsLength[i]; j++) {
            content += " ";
        }
        content += betweenSpace;
    }
    content += "\n";

    content += indent;
    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < max(rowsLength[i], biggestColName[i]) + betweenSpace.length() - (i == rows.size() - 1 ? 2 : 0); j++) {
            content += "_";
        }
    }
    content += "\n\n";
    int number = 1;
    for (int i = 0; i < data.size(); i++) {

        auto appendRow = [&](int i){
                    if (addNumbers) {
           for(int l = 0; l < (indent.length() - to_string(number).length()) - 1; l++){
                content += " ";
            }
            content += to_string(number) + " ";

        }else{
            content += indent;
        }
            for (int j = 0; j < columns.size(); j++) {
                content += data[i][columns[j]];
                for (int k = 0; k < (max(rowsLength[j], biggestColName[j]) - data[i][columns[j]].length()) + betweenSpace.length(); k++) {
                    content += " ";
                }
            }
            content += "\n\n";
            number++;
        };
        if(filter == nullptr){
            appendRow(i);
        }else{
            if(filter(data[i])){
                appendRow(i);
            }
        }
    }

    return content;
}

int main() {

    init();

    return 0;
}

// DEFINITION FUNCTIONS //

void init() {
    system("cls");
    logo();
    menu({"Login", "Register", "Exit"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Please Choose An Option: ")) {
            case 1:
                login();
                return;
            case 2:
                registerUser();
                return;
            case 3:
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
        setUserData(username, typeClient(username));
        home();
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
        minMaxRule(MIN_LENGTH, MAX_LENGTH, username);
    }

    lineSpacing(1);
    password = read<string>("Please Create Your Password: ");
    minMaxRule(MIN_LENGTH, MAX_LENGTH, password);

    ofstream usersFile("users.txt", ios::app);
    usersFile << username << " " << password << " " << type << '\n';
    usersFile.close();

    setUserData(username, type);
    home();
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

string typeClient(string username) {
    ifstream usersFile("users.txt");
    string fileUsername, filePassword, fileType;

    while(usersFile >> fileUsername >> filePassword >> fileType) {
        if(fileUsername == username)
            return fileType;
    }
}

void setUserData(string username, string type) {
    userDataType newUser;
    newUser.username = username;
    newUser.type = type;

    userData.push_back(newUser);
}

void home() {
    if(userData[0].type == "ADMIN")
        dashboardAdmin();
    else
        dashboardUser();
}

void dashboardAdmin() {
    system("cls");
    logo();
    print("Welcome back " + userData[0].username, {"text", GREEN});
    lineSpacing(3);
    menu({"Handling Tournament", "Edit Tournament Games", "Exit"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Please Choose An Option: ")) {
            case 1:
                tournamentHandler();
                return;
            case 2:
                cout << "dashboardUser";
                return;
            case 3:
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }

}

void tournamentHandler() {
    system("cls");
    getGames();
    print(dynamicTable(games, {"Team One", "Team Two", "Result", "Status"}, {0,1,2,3}), {"text", WHITE});
    lineSpacing(2);

    if(organizingTournament() == "DISABLE") {
        menu({"Add New Game", "Activate The Tournament", "Delete All Games", "Exit"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Please Choose An Option: ")) {
                case 1:
                    addNewGame();
                    return;
                case 2:
                    activeTournament();
                    return;
                case 3:
                    deleteAllGames();
                    return;
                case 4:
                    dashboardAdmin();
                    return;
                default:
                    inValidInput("Invalid Input. Please Try Again.");
            }
        }
    } else if(organizingTournament() == "ACTIVE") {
        menu({"Delete The Tournament", "Exit"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Please Choose An Option: ")) {
                case 1:
                    disableTournament();
                    return;
                case 2:
                    dashboardAdmin();
                    return;
                default:
                    inValidInput("Invalid Input. Please Try Again.");
            }
        }
    }

}

void getGames() {
    games.clear();
    ifstream gamesFile("games.txt");
    string teamOne, teamTwo, goalTeamOne, goalTeamTwo, status;
    int counter = 1;

    while(gamesFile >> teamOne >> teamTwo >> goalTeamOne >> goalTeamTwo >> status) {
        games.push_back({teamOne, teamTwo, goalTeamOne + " : " + goalTeamTwo, status});
        counter++;
    }

    gamesFile.close();
}

void addNewGame() {
    system("cls");
    lineSpacing(1);
    string teamOne = read<string>("Please Enter Team One Name: ");
    minMaxRule(MIN_LENGTH, MAX_LENGTH, teamOne);
    lineSpacing(1);
    string teamTwo = read<string>("Please Enter Team Two Name: ");
    minMaxRule(MIN_LENGTH, MAX_LENGTH, teamTwo);
    lineSpacing(1);
    int goalTeamOne = read<int>("Please Enter Team One Goals: ");
    minMaxRule(0, 30, goalTeamOne);
    lineSpacing(1);
    int goalTeamTwo = read<int>("Please Enter Team Two Goals: ");
    lineSpacing(1);
    minMaxRule(0, 30, goalTeamTwo);
    print(teamOne + " " + to_string(goalTeamOne) + " : " + to_string(goalTeamTwo) + " " + teamTwo, {"text", WHITE});
    lineSpacing(2);

    menu({"Yes", "No"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Are You Sure About The Team Registration: ")) {
            case 1: {
                ofstream gamesFile("games.txt", ios::app);
                gamesFile << teamOne << " " << teamTwo << " " << goalTeamOne << " " << goalTeamTwo << " " << "OPEN" << '\n';
                gamesFile.close();
                tournamentHandler();
                return;
            } case 2:
                tournamentHandler();
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }
}

string organizingTournament() {
    ifstream organizingTournamentFile("organizingTournament.txt");
    string status;

    while(organizingTournamentFile >> status) {
        return status;
    }
}

void activeTournament() {
    system("cls");

    if(isPowerTwo(games.size())) {
        print(dynamicTable(games, {"Team One", "Team Two", "Result", "Status"}, {0,1,2,3}), {"text", WHITE});
        lineSpacing(2);

        menu({"Yes", "No"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Are You Sure To Active The Tournament: ")) {
                case 1: {
                    clearTextfile("organizingTournament.txt");
                    ofstream organizingTournamentFile("organizingTournament.txt");
                    organizingTournamentFile << "ACTIVE";
                    organizingTournamentFile.close();
                    tournamentHandler();
                    return;
                }
                case 2:
                    tournamentHandler();
                    return;
                default:
                    inValidInput("Invalid Input. Please Try Again.");
            }
        }

    }else {
        print("The Number Of Teams must Be a Power Of Two", {"error", RED});
        lineSpacing(2);

        menu({"Add New Game", "Go Back"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Are You Sure To Active The Tournament: ")) {
                case 1:
                    addNewGame();
                    return;
                case 2:
                    tournamentHandler();
                    return;
                default:
                    inValidInput("Invalid Input. Please Try Again.");
            }
        }
    }

}

void disableTournament() {
    system("cls");

    menu({"Yes", "No"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Are You Sure To Delete? All Game Data Will Be Deleted: ")) {
            case 1: {
                clearTextfile("organizingTournament.txt");
                ofstream organizingTournamentFile("organizingTournament.txt");
                organizingTournamentFile << "DISABLE";
                organizingTournamentFile.close();
                clearTextfile("games.txt");
                tournamentHandler();
                return;
            }
            case 2:
                tournamentHandler();
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }
}

void deleteAllGames() {
    system("cls");

    if(games.size()) {
        menu({"Yes", "No"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Are You Sure To Delete All Games: ")) {
                case 1: {
                    clearTextfile("games.txt");
                    tournamentHandler();
                    return;
                }
                case 2:
                    tournamentHandler();
                    return;
                default:
                    inValidInput("Invalid Input. Please Try Again.");
            }
        }
    }else {
        print("There Is No Game To Delete", {"error", RED});
        lineSpacing(2);

        menu({"Add New Game", "Go Back"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Are You Sure To Active The Tournament: ")) {
                case 1:
                    addNewGame();
                    return;
                case 2:
                    tournamentHandler();
                    return;
                default:
                    inValidInput("Invalid Input. Please Try Again.");
            }
        }
    }
}

void dashboardUser() {
    system("cls");
    logo();
    cout << "dashboardUser";
}

void clearTextfile(string nameFile) {
    ofstream file(nameFile, ios::out | ios::trunc);
    file.close();
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

void minMaxRule(int minLength, int maxLength, int &variable) {
    int lengthVar = intLength(variable);

    while(minLength > lengthVar || maxLength < lengthVar) {
        lineSpacing(1);

        if(minLength > lengthVar) {
            print("Input Length must Be Greater Than " + to_string(minLength), {"text", RED});
        }else {
            print("Input Length must Be Less Than " + to_string(maxLength), {"text", RED});
        }

        lineSpacing(2);
        variable = read<int>("Please Try Again: ");
        lengthVar = intLength(variable);
    }
}

string capitalizeText(string text) {
    string capitalizeText;

    for(char letter: text) {
        capitalizeText += toupper(letter);
    }

    return capitalizeText;
}

int intLength(int number){
    int length = 1;

    while(number /= 10){
        length++;
    }

    return length;
}


bool isPowerTwo(int number) {
    if (number <= 0)
        return false;

    while(number % 2 == 0) {
        number /= 2;
    }

    return number == 1;
}
