#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <limits> 
using namespace std;


void user_menu(const string& username);
void admin_menu();
void adminlogin();
void admin_update_game();
void menu();



struct GameDetails {
    int quantity;
    int cost;
};

struct UserDetails{
    string password;
    float user_bal;
    int user_points;
    map<string, int> games_rented;
};

// helper function to initialize gameLibrary
map<string, GameDetails> createGameLibrary() {
    return {
        {"Donkey Kong", {3, 2}},
        {"Super Mario Bros", {5, 3}},
        {"Tetris", {2, 1}},
        {"GTA Vice City", {4, 4}},
        {"NFS Most Wanted", {4, 5}}
    };
}

// Global game library initialization
map<string, GameDetails> gameLibrary = createGameLibrary();
// declare map para sa user accounts, value as userdetails struct
map <string, UserDetails> user_accounts; 
string admin_username = "admin";
string admin_password = "adminpass";

void clearInputBuffer() {
    cin.clear(); // Clear the error flag
    while (cin.get() != '\n'); // Ignore remaining input
}

void display_games(){
    cout << "---------------------------------------------------\n";
    cout << "Available Games:\n\n";
    int index = 1;

    for (const auto& game : gameLibrary){
        cout << index << ". " << game.first << " - Copies available: " << game.second.quantity 
        << " - Cost: $" << game.second.cost << "\n";
        index++;
    }
    cout << "---------------------------------------------------\n";
}

void registeruser() {
    while (true) {
        cout << "\n-----------REGISTER NEW USER-----------" << endl;
        cout << "Please input your username and password: \n" << endl;
        string username;
        string password;

        cout << "Enter a username: ";
        cin >> username;
        cout << "Password (must be 8 characters long): ";
        cin >> password;

        if (username.length() < 4){
            cout << "\n*******************************************" << endl;
            cout << "Username must be at least 4 characters long." << endl;
            cout << "********************************************" << endl;
            break;
        }

        while (password.length() < 8) {
            cout << "\n*******************************************" << endl;
            cout << "Password must be at least 8 characters long." << endl;
            cout << "********************************************" << endl;
            cout << "Password (must be 8 characters long): ";
            cin >> password;
            break;
        } 

        if (user_accounts.find(username) != user_accounts.end()){
            cout << "\n******************************************************\n";
            cout << "Username already exists. Please choose a different one.\n";
            cout << "******************************************************\n";
            break;
        } else {
            cout << "\n-------------------------------" << endl;
            cout << "Account registered successfully"   << endl;    
            cout << "-------------------------------\n" << endl;

            UserDetails newUser = {password, 0.0, 0, {}};
            user_accounts[username] = newUser;
            break;
        }
    }
}

void userlogin() {
    while (true) {
        cout << "----------LOGIN PAGE----------\n";
        string username;
        string password;

        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        auto it = user_accounts.find(username);
        if (it != user_accounts.end() && it->second.password == password) {
            cout << "\n----------------";
            cout << "Login Successful";    
            cout << "----------------\n";
            user_menu(username);
            cout << "\n****************************";
            cout << "Invalid username or password";           
            cout << "****************************\n";
            break;
        }
    }
}


void user_menu(const string& username) {
    while (true) {
        try {
            cout << "Logged in as " << username << " ---- Balance: $" << user_accounts[username].user_bal << endl;
            cout << "1. Rent a game" << endl;
            cout << "2. Return a game" << endl;
            cout << "3. Top-up Account" << endl;
            cout << "4. Display inventory" << endl;
            cout << "5. Redeem free game rental" << endl;
            cout << "6. Check Credentials" << endl;
            cout << "7. Log out" << endl << endl;

            int choice;
            cin >> choice;

            if (cin.fail()) {
                clearInputBuffer();
                throw invalid_argument("Invalid input");
            }

            switch (choice) {
                case 1:
                    //rent_game(username);
                    break;
                case 2:
                   // return_game(username);
                    break;
                case 3:
                    //top_up(username);
                    break;
                case 4:
                    //inventory(username);
                    break;
                case 5:
                    //redeem(username);
                    break;
                case 6:
                   // check_credentials(username);
                    break;
                case 7:
                    cout << "\n----------------------------------" << endl;
                    cout << "  User: '" << username << "' has logged out!" << endl;
                    cout << "----------------------------------\n" << endl;
                    //menu();
                    return;
                default:
                    cout << "\n***************************" << endl;
                    cout << "Please input a valid choice" << endl;
                    cout << "***************************\n" << endl;
            }
        } catch (const invalid_argument& e) {
            cout << "\n***************************" << endl;
            cout << e.what() << endl;
            cout << "***************************\n" << endl;
        }
    }
}

void adminlogin(){
    while (true){
        string admin_user;
        string admin_pass;

        cout << "------------------" << endl;
        cout << "ADMIN LOGIN PAGE" << endl;
        cout << "------------------\n" << endl;
        cout << "Admin username: ";
        cin >> admin_user;
        cout << endl;
        cout << "Admin Password: ";
        cin >> admin_pass;
        cout << endl;

        if (admin_user == admin_username && admin_pass == admin_password){
            cout << "\n-----------------" << endl;
            cout << "Login Successful!" << endl;
            cout << "-----------------\n" << endl;
            admin_menu();
        }
        else{
            cout << "\n******************************" << endl;
            cout << "Incorrect username or password" << endl;
            cout << "******************************\n" << endl;
            break;
        }
    }
}

void admin_menu(){
    while (true){
        try {
            int choice; 

            cout << "Admin Menu" << endl;
            cout << "1. Update Game Details" << endl;
            cout << "2. Log out\n" << endl;

            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                clearInputBuffer();
                throw invalid_argument("Invalid input");
            }

            if (choice == 1){
                admin_update_game();
                break;
            }
            else if (choice == 2){
                cout << "ADMIN LOGGED OUT! \n";
                menu();
            }
            else {
                cout << "\n***************************" << endl;
                cout << "Please input a valid choice" << endl;
                cout << "***************************\n" << endl;
                admin_menu();
            }
        } catch (const invalid_argument& e) {
                cout << "\n***************************" << endl;
                cout << e.what() << endl;
                cout << "***************************\n" << endl;
            }
    }
}

// void admin_update_game() {
//     int game_index = 0; // to track game index
//     cout << "Update Game" << endl;
//     cout << "1. Update Game Copies" << endl;
//     cout << "2. Update Game Copies" << endl;
//     cout << "3. Log out\n\n";

//     try {
//         int choice;
//         cout << "Enter your choice: ";
//         cin >> choice;
//         if (cin.fail()) {
//             clearInputBuffer();
//             throw invalid_argument("Invalid input");
//         }
//         switch (choice) {
//             case 1:
//             display_games();
//             int game_index;
//             cout << "Select the number of the game to be updated: ";
//             cin >> game_index;
//             for (auto& game : gameLibrary) {
//                 int idx;
//                 string game_name;
//                 idx = 1;
//                 if (game_index == idx){
//                     game_name = game;
//                     if (game_)

//                 }
//             }
            




//         }
//     }
// }


void top_up (){
    try {
        string amount;
        cout << "\n-----Top-up Account-----\n";
        cout << "Enter the amount to top up (leave blank to cancel transcation): ";
        getline(cin >> ws, amount); //allow blank input

        if (amount_str.empty()) {
            std::cout << "\n--------------------------------------------------------" << std::endl;
            std::cout << "                TRANSACTION CANCELLED" << std::endl;
            std::cout << "--------------------------------------------------------\n" << std::endl;
            return;

        }
        else {
            float amount = stof(amount);
            if (amount > 0){
               user_accounts[username].user_bal += amount; 
                cout << "\n------------------------------------------------------" << endl;
                cout << "      Top-up successful. New balance: ${user_accounts[username]['Balance']}" << endl;
                cout << "------------------------------------------------------\n"<< endl;
            } else {
                cout << " \nInvalid amount. Please enter a positive value.\n" << endl;
                return;
            }
        }
    } catch (const invalid_argument& e) {
        cout << "\n***************************" << endl;
        cout << e.what() << endl;
        cout << "***************************\n" << endl;
    } 
}
int main () {

}

