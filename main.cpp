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
vector<vector<string>> gamePredictionArray;
vector<vector<string>> gamePredictionUserArray;

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
void editGames();
void changeStateGame(int index);
void changeStatusPredictionGame(int index);
bool gamesOver();
void nextStepHandler();
void newGameStep(int number);
vector<vector<string>> getLastGames(int number, vector<vector<string>> games);
void creatorGame(int numberOne, int numberTwo, vector<vector<string>> lastGames);
string gameWinnir(vector<string> game);
void dashboardUser();
void gamePrediction();
void getGamePrediction();
void getGamePredictionUser(string username);
void addGamePrediction(int index, int goalTeamOne, int goalTeamTwo);
bool isGameTaken(string username, string nameTeamOne, string nameTeamTwo);
void userPointsHandler();
void pointsHandler();
string getPoint(string nameTeamOne, string nameTeamTwo, string goalTeamOne, string goalTeamTwo);
void exit();

template <typename T> T read(string prompt);
string margin();
void logo();
void menu(vector<string> options);
void print(auto text, vector<string> options);
void lineSpacing(int number);
void inValidInput(string errorMassage);
void minMaxRule(int minLength, int maxLength, string &variable);
void minMaxRule(int minLength, int maxLength, int &variable);
void clearTextfile(string nameFile);
string capitalizeText(string text);
int intLength(int number);
bool isPowerTwo(int number);
void clearFunc();
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
    clearFunc();
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
    clearFunc();
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
        clearFunc();
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
    clearFunc();
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
    clearFunc();
    logo();
    print("Welcome back " + userData[0].username, {"text", GREEN});
    lineSpacing(3);
    menu({"Handling Tournament", "Change Information Of Tournament Games", "Exit"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Please Choose An Option: ")) {
            case 1:
                tournamentHandler();
                return;
            case 2:
                editGames();
                return;
            case 3:
                exit();
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }

}

void tournamentHandler() {
    clearFunc();
    getGames();
    print(dynamicTable(games, {"Team One", "Team Two", "Goal Team One", "Goal Team Two", "Status"}, {0,1,2,3,4}), {"text", WHITE});
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
        menu({"Delete The Tournament", "Go To Next Step", "Exit"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Please Choose An Option: ")) {
                case 1:
                    disableTournament();
                    return;
                case 2: {
                    if(gamesOver()) {
                        nextStepHandler();
                        return;
                    }else {
                        lineSpacing(1);
                        print("All Games Must Be Finished To Go To Next Step", {"error", RED});
                        lineSpacing(2);
                        break;
                    }
                }
                case 3:
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
    string teamOne, teamTwo, goalTeamOne, goalTeamTwo, mode;
    int counter = 1;

    while(gamesFile >> teamOne >> teamTwo >> goalTeamOne >> goalTeamTwo >> mode) {
        games.push_back({teamOne, teamTwo, goalTeamOne, goalTeamTwo, mode});
        counter++;
    }

    gamesFile.close();
}

void addNewGame() {
    clearFunc();
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
    clearFunc();

    if(isPowerTwo(games.size())) {
        print(dynamicTable(games, {"Team One", "Team Two", "Goal Team One", "Goal Team Two", "Status"}, {0,1,2,3,4}), {"text", WHITE});
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

                    ofstream stepHandlerFile("stepHandler.txt");
                    clearTextfile("stepHandler.txt");
                    stepHandlerFile << games.size();
                    stepHandlerFile.close();
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
        print("The Number Of Teams must Be A Power Of Two", {"error", RED});
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
    clearFunc();

    menu({"Yes", "No"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Are You Sure To Delete? All Game Data Will Be Deleted: ")) {
            case 1: {
                clearTextfile("gamePrediction.txt");
                clearTextfile("organizingTournament.txt");
                clearTextfile("stepHandler.txt");
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
    clearFunc();

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

void editGames() {
    clearFunc();

    if(organizingTournament() == "ACTIVE") {
        getGames();
        print(dynamicTable(games, {"Team One", "Team Two", "Goal Team One", "Goal Team Two", "Status"}, {0,1,2,3,4}), {"text", WHITE});
        lineSpacing(2);

        int gameId = read<int>("Select The Game You Want To Change (Between 1 To " + to_string(games.size()) + ") : ");
        minMaxRule(1, games.size(), gameId);
        int index = gameId - 1;

        if(games[index][4] == "FINISHED") {
            clearFunc();
            lineSpacing(1);
            print("The Selected Game Is Over", {"error", RED});
            lineSpacing(2);
            menu({"Try Again", "Go Back"});
            lineSpacing(1);

            while(true) {
                switch(read<int>("Please Choose An Option: ")) {
                    case 1: {
                        editGames();
                        return;
                    }
                    case 2:
                        dashboardAdmin();
                        return;
                    default:
                        inValidInput("Invalid Input. Please Try Again.");
                }
            }
        }

        clearFunc();
        int goalTeamOne = read<int>("Please Enter Team One Goals: ");
        minMaxRule(stoi(games[index][2]), 30, goalTeamOne);
        lineSpacing(1);
        int goalTeamTwo = read<int>("Please Enter Team Two Goals: ");
        minMaxRule(stoi(games[index][3]), 30, goalTeamTwo);
        lineSpacing(2);

        changeStateGame(index);
        games[index][2] = to_string(goalTeamOne);
        games[index][3] = to_string(goalTeamTwo);

        clearTextfile("games.txt");
        ofstream gamesFile("games.txt");
        for(vector<string> a: games) {
            gamesFile << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << '\n';
        }

        gamesFile.close();
        dashboardAdmin();

    }else {
        print("There Is No Active Tournament", {"error", RED});
        lineSpacing(2);

        menu({"Handling Tournament", "Go Back"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Are You Sure To Active The Tournament: ")) {
                case 1:
                    tournamentHandler();
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

void changeStateGame(int index) {
    menu({"Yes", "No"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Do You Want To Change The State Of The Game: ")) {
            case 1: {
                games[index][4] = "FINISHED";
                changeStatusPredictionGame(index);
                return;
            }
            case 2:
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }
}

void changeStatusPredictionGame(int index) {
    getGamePrediction();
    int counter = 0;

    for(vector<string> a: gamePredictionArray) {
        if(a[1] == games[index][0] && a[2] == games[index][1])
            gamePredictionArray[counter][5] = "FINISHED";

        counter++;
    }

    clearTextfile("gamePrediction.txt");
    ofstream gamePredictionFile("gamePrediction.txt");
    for(vector<string> a: gamePredictionArray) {
        gamePredictionFile << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << " " << a[5] << '\n';
    }

    gamePredictionFile.close();
}

bool gamesOver() {
    for(vector<string> a: games) {
        if(a[4] == "OPEN")
            return false;
    }
    return true;
}

void nextStepHandler() {
    clearFunc();
    ifstream stepHandlerFile("stepHandler.txt");
    int number;
    stepHandlerFile >> number;
    stepHandlerFile.close();

    if(number / 2) {
        newGameStep(number);
        clearTextfile("stepHandler.txt");
        ofstream stepHandlerFile("stepHandler.txt");
        stepHandlerFile << (number / 2);
        stepHandlerFile.close();

        tournamentHandler();
        return;

    }else {
        print("The Tournament Ended With " + gameWinnir(games.back()) + " Winning", {"text", GREEN});

        lineSpacing(2);

        menu({"Delete The Tournament", "Go Back"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Please Choose An Option: ")) {
                case 1: {
                    disableTournament();
                    return;
                } case 2:
                    tournamentHandler();
                    return;
                default:
                    inValidInput("Invalid Input. Please Try Again.");
            }
        }
    }
}

void newGameStep(int number) {
    vector<vector<string>> lastGames = getLastGames(number, games);
    creatorGame(1, number, lastGames);
}

vector<vector<string>> getLastGames(int number, vector<vector<string>> games) {
    return vector<vector<string>>(games.end() - number, games.end());
}

void creatorGame(int numberOne, int numberTwo, vector<vector<string>> lastGames) {
    ofstream gamesFile("games.txt", ios::app);
    gamesFile << gameWinnir(lastGames[numberOne - 1]) << " " << gameWinnir(lastGames[numberTwo - 1]) << " " << "0" << " " << "0" << " " << "OPEN" << '\n';
    gamesFile.close();

    if(numberTwo - numberOne == 1)
        return;
    else
        creatorGame(numberOne + 1, numberTwo - 1, lastGames);
}

string gameWinnir(vector<string> game) {
    if(game[2] > game[3])
        return game[0];
    else
        return game[1];
}

void dashboardUser() {
    clearFunc();
    logo();
    print("Welcome back " + userData[0].username, {"text", GREEN});
    lineSpacing(3);
    menu({"Game Prediction", "My Points", "Exit"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Please Choose An Option: ")) {
            case 1: {
                if(organizingTournament() == "ACTIVE") {
                    gamePrediction();
                    return;
                }else {
                    lineSpacing(1);
                    print("There Is No Active Tournament", {"error", RED});
                    lineSpacing(2);
                    break;
                }
            }
            case 2: {
                getGamePredictionUser(userData[0].username);

                if(gamePredictionUserArray.size()) {
                    userPointsHandler();
                    return;
                }else {
                    lineSpacing(1);
                    print("You Have Not Made A Prediction Yet", {"error", RED});
                    lineSpacing(2);
                    break;
                }
            }
            case 3:
                exit();
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }
}

void gamePrediction() {
    clearFunc();
    getGames();
    getGamePrediction();
    print(dynamicTable(games, {"Team One", "Team Two", "Goal Team One", "Goal Team Two", "Status"}, {0,1,2,3,4}), {"text", WHITE});
    lineSpacing(2);

    int gameId = read<int>("Select The Game You Want To Prediction (Between 1 To " + to_string(games.size()) + ") : ");
    minMaxRule(1, games.size(), gameId);
    int index = gameId - 1;

    if(games[index][4] == "FINISHED") {
        clearFunc();
        lineSpacing(1);
        print("The Selected Game Is Over", {"error", RED});
        lineSpacing(2);
        menu({"Try Again", "Go Back"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Please Choose An Option: ")) {
                case 1: {
                    gamePrediction();
                    return;
                }
                case 2:
                    dashboardUser();
                    return;
                default:
                    inValidInput("Invalid Input. Please Try Again.");
            }
        }
    }

    while(isGameTaken(userData[0].username, games[index][0], games[index][1])) {
        clearFunc();
        lineSpacing(1);
        print("You Already Predicted This Game", {"error", RED});
        lineSpacing(2);
        menu({"Try Again", "Go Back"});
        lineSpacing(1);

        while(true) {
            switch(read<int>("Please Choose An Option: ")) {
                case 1: {
                    gamePrediction();
                    return;
                }
                case 2:
                    dashboardUser();
                    return;
                default:
                    inValidInput("Invalid Input. Please Try Again.");
            }
        }
    }

    clearFunc();
    int goalTeamOne = read<int>("Please Enter Team One Goals: ");
    minMaxRule(stoi(games[index][2]), 30, goalTeamOne);
    lineSpacing(1);
    int goalTeamTwo = read<int>("Please Enter Team Two Goals: ");
    minMaxRule(stoi(games[index][3]), 30, goalTeamTwo);
    lineSpacing(2);

    print(games[index][0] + " " + to_string(goalTeamOne) + " : " + to_string(goalTeamTwo) + " " + games[index][1], {"text", WHITE});
    lineSpacing(2);

    menu({"Yes", "No"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Are You Sure About The Prediction: ")) {
            case 1: {
                addGamePrediction(index, goalTeamOne, goalTeamTwo);
                dashboardUser();
                return;
            } case 2:
                dashboardUser();
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }
}

void getGamePrediction() {
    gamePredictionArray.clear();
    ifstream gamePredictionFile("gamePrediction.txt");
    string username, teamOne, teamTwo, goalTeamOne, goalTeamTwo, mode;

    while(gamePredictionFile >> username >> teamOne >> teamTwo >> goalTeamOne >> goalTeamTwo >> mode) {
        gamePredictionArray.push_back({username, teamOne, teamTwo, goalTeamOne, goalTeamTwo, mode});
    }

    gamePredictionFile.close();
}

void getGamePredictionUser(string username) {
    getGamePrediction();
    gamePredictionUserArray.clear();

    for(vector<string> a: gamePredictionArray) {
        if(a[0] == username) {
            string teamOne = a[1], teamTwo = a[2], goalTeamOne = a[3], goalTeamTwo = a[4], mode = a[5];
            gamePredictionUserArray.push_back({teamOne, teamTwo, goalTeamOne, goalTeamTwo, mode});
        }
    }
}

void addGamePrediction(int index, int goalTeamOne, int goalTeamTwo) {
    ofstream gamePredictionFile("gamePrediction.txt", ios::app);
    gamePredictionFile << userData[0].username << " " << games[index][0] << " " << games[index][1] << " " << goalTeamOne << " " << goalTeamTwo << " " << games[index][4] << '\n';

    gamePredictionFile.close();
}

bool isGameTaken(string username, string nameTeamOne, string nameTeamTwo) {
    ifstream gamePredictionFile("gamePrediction.txt");
    string usernameFile, teamOne, teamTwo, goalTeamOne, goalTeamTwo, mode;

    while(gamePredictionFile >> usernameFile >> teamOne >> teamTwo >> goalTeamOne >> goalTeamTwo >> mode) {
        if(usernameFile == username && teamOne == nameTeamOne && teamTwo == nameTeamTwo)
            return true;
    }
    gamePredictionFile.close();

    return false;
}

void userPointsHandler() {
    clearFunc();
    getGamePredictionUser(userData[0].username);
    pointsHandler();
    print(dynamicTable(gamePredictionUserArray, {"Team One", "Team Two", "Goal Team One", "Goal Team Two", "Score"}, {0,1,2,3,4}), {"text", WHITE});
    lineSpacing(2);

    menu({"Change Sort", "Go Back"});
    lineSpacing(1);

    while(true) {
        switch(read<int>("Please Choose An Option: ")) {
            case 1: {
                userPointsHandler();
                return;
            } case 2:
                dashboardUser();
                return;
            default:
                inValidInput("Invalid Input. Please Try Again.");
        }
    }
}

void pointsHandler() {
    int counter = 0;

    for(vector<string> a: gamePredictionUserArray) {
        if(a[4] == "OPEN")
            gamePredictionUserArray[counter][4] = "-";
        else
            gamePredictionUserArray[counter][4] = getPoint(gamePredictionUserArray[counter][0], gamePredictionUserArray[counter][1], gamePredictionUserArray[counter][2], gamePredictionUserArray[counter][3]);

        counter++;
    }
}

string getPoint(string nameTeamOne, string nameTeamTwo, string goalTeamOne, string goalTeamTwo) {
    getGames();
    int miness;
    int minessPrediction;

    if(stoi(goalTeamOne) > stoi(goalTeamTwo))
        minessPrediction = stoi(goalTeamOne) - stoi(goalTeamTwo);
    else
        minessPrediction = stoi(goalTeamTwo) - stoi(goalTeamOne);

    for(vector<string> a: games) {
        if(a[0] == nameTeamOne && a[1] == nameTeamTwo) {
            if(stoi(a[2]) > stoi(a[3]))
                miness = stoi(a[2]) - stoi(a[3]);
            else
                miness = stoi(a[3]) - stoi(a[2]);

            if(a[2] == goalTeamOne && a[3] == goalTeamTwo)
                return "3";
            else if(miness == minessPrediction)
                return "2";
            else
                return "0";
        }
    }
}

void exit() {
    clearFunc();
    userData.clear();
    init();
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

        if(minLength > lengthVar)
            print("Input Length must Be Greater Than " + to_string(minLength), {"text", RED});
        else
            print("Input Length must Be Less Than " + to_string(maxLength), {"text", RED});

        lineSpacing(2);
        variable = read<string>("Please Try Again: ");
        lengthVar = variable.length();
    }
}

void minMaxRule(int minAmount, int maxAmount, int &variable) {
    while(minAmount > variable || maxAmount < variable) {
        lineSpacing(1);

        if(minAmount > variable)
            print("Input Amount must Be Greater Than " + to_string(minAmount), {"text", RED});
        else
            print("Input Amount must Be Less Than " + to_string(maxAmount), {"text", RED});

        lineSpacing(2);
        variable = read<int>("Please Try Again: ");
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
    if(number <= 0)
        return false;

    while(number % 2 == 0) {
        number /= 2;
    }

    return number == 1;
}

void clearFunc() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
