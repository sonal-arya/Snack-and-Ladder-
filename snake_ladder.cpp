#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <map>      // for snakes and ladders positions
#include <vector>   // for storing the board
using namespace std;

class Player {
public:
    string name;
    int position;
    
    Player(string playerName) {
        name = playerName;
        position = 1; // All players start at position 1
    }

    void move(int diceRoll) {
        position += diceRoll;
        if (position > 100) {
            position = 100;  // Prevent moving beyond the last square
        }
    }
};


class SnakeAndLadder {
private:
    map<int, int> snakes; // Key: snake head, Value: snake tail
    map<int, int> ladders; // Key: ladder bottom, Value: ladder top
    int finalPosition;
    
public:
    SnakeAndLadder(int boardSize) {
        finalPosition = boardSize;
        
        // Example snakes and ladders (you can modify as per need)
        snakes[16] = 6;
        snakes[47] = 26;
        snakes[49] = 11;
        snakes[56] = 53;
        snakes[62] = 19;
        snakes[87] = 24;
        ladders[3] = 22;
        ladders[5] = 8;
        ladders[20] = 29;
        ladders[27] = 84;
        ladders[72] = 91;
        ladders[77] = 96;
    }

    void displayBoard(Player& player1, Player& player2) {
        cout << "Snake :**" <<" ," << "Ladder:##"<<endl<<"\nCurrent Board:  \n";
        for (int i = 100; i > 0; i -= 10) {
            for (int j = i; j > i - 10; --j) {
                if (j == player1.position && j == player2.position) {
                    cout << "|P1P2";  // Both players on the same square
                } else if (j == player1.position) {
                    cout << "| P1 ";
                } else if (j == player2.position) {
                    cout << "| P2 ";
                } else if (snakes.find(j) != snakes.end()) {
                    cout << "| **" <<" ";  // Represent a snake with 'S'
                } else if (ladders.find(j) != ladders.end()) {
                    cout << "| ##" <<" ";  // Represent a ladder with 'L'
                } else {
                    printf("|%3d ", j);  // Regular square number
                }
            }
            cout << "|" << endl;
        }
        cout << endl;
    }
    
    void checkForSnakesAndLadders(Player &player) {
        if (snakes.find(player.position) != snakes.end()) {
            cout << player.name << " got bitten by a snake! Sliding down from " << player.position;
            player.position = snakes[player.position];
            cout << " to " << player.position << endl;
        } else if (ladders.find(player.position) != ladders.end()) {
            cout << player.name << " climbed a ladder! Moving up from " << player.position;
            player.position = ladders[player.position];
            cout << " to " << player.position << endl;
        }
    }
    
    bool isGameOver(Player &player) {
        return player.position >= finalPosition;
    }
};

int rollDice() {
    return (rand() % 6) + 1;
}

int main() {
    srand(time(0));  // Seed for random number generation

    int boardSize = 100;
    SnakeAndLadder game(boardSize);

    Player player1("Player 1");
    Player player2("Player 2");

    Player* currentPlayer = &player1;

    while (true) {
        game.displayBoard(player1, player2);  // Display board at the start of each turn
        
        cout << currentPlayer->name << "'s turn. Press enter to roll the dice...";
        cin.ignore();

        int diceRoll = rollDice();
        cout << currentPlayer->name << " rolled a " << diceRoll << endl;
        currentPlayer->move(diceRoll);
        cout << currentPlayer->name << " moved to position " << currentPlayer->position << endl;

        game.checkForSnakesAndLadders(*currentPlayer);

        if (game.isGameOver(*currentPlayer)) {
            cout << currentPlayer->name << " has won the game!" << endl;
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }

    return 0;
}
