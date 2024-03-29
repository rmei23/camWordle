#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Game{
    private:
        vector<string> wordBank;
        vector<string> guessBank;

    public:
        string masterWord;
        string board;
        Game();
        void checkWord(string word);
        void displayBoard();
        void fillWordBank(string fileName);
        void fillGuessBank(string fileName);
        void setWord();
        void makeGame();
        bool win(string str);
        bool validWord(string word);
};

Game::Game(){
    masterWord = "";
    board = "";
}

void Game::checkWord(string word){
    for(int i = 0; i < 5; i++){
        bool wrongPlace = false;
        bool rightPlace = false;
        if(masterWord[i] == word[i]){
            board[i] = 'o';
            rightPlace = true;
        }
        else{
            for(int x = 0; x < 5; x++){
                if(word[i] == masterWord[x]){
                    wrongPlace = true;
                }
            }
            if(wrongPlace == true){
                board[i] = '?';;
            }
        }
        if(wrongPlace == false && rightPlace == false){
            board[i] = 'x';
        }
    }
    return;
}

void Game::displayBoard(){
    cout << "| ";
    for(int i = 0; i < 5; i++){
        cout << board[i] << " | ";
    }
    return;
}

bool Game::win(string str){
    int compare = str.compare(masterWord);
    if(compare == 0){
        return true;
    }
    return false;
}

void Game::fillWordBank(string fileName){
    string line;
    ifstream file(fileName);
    if(file.is_open()){
        while(getline(file, line)){
            wordBank.push_back(line);
        }
    }
    file.close();
    return;
}

void Game::fillGuessBank(string fileName){
    string line;
    ifstream file(fileName);
    if(file.is_open()){
        while(getline(file, line)){
            guessBank.push_back(line);
        }
    }
    file.close();
    return;
}

void Game::setWord(){
    srand(time(NULL));
    int size = wordBank.size();
    int index = rand() % size;
    masterWord = wordBank.at(index);
    return;
}

bool Game::validWord(string word){
    if(word.length() != 5){
        return false;
    }
    for(int i = 0; i < guessBank.size(); i++){
        if(guessBank[i] == word){
            return true;
        }
    }
    return false;
}

void Game::makeGame(){
    fillWordBank("possibleWords.txt");
    fillGuessBank("allWords.txt");
    setWord();
    cout << "Correct letters will show up as a <o> on the board, Correct letters in the wrong place will show up as <?>, and Incorrect letters will show up as <x>. "
    "You will have 6 attempts to guess the word." << endl;
    return;
}

int main(){
    Game newGame;
    newGame.makeGame();
    newGame.displayBoard();
    string input;
    int turns = 0;
    while(!(newGame.win(input)) && turns < 6){
        cout << "This is attempt #" << turns + 1 << "." << endl << "Enter your 5 letter word:" << endl;
        cin >> input;
        while(newGame.validWord(input) == false){
            cout << "Invalid word. Please enter a valid word" << endl;
            cin >> input;
        }
        if(newGame.win(input)){
            cout << "|o|o|o|o|o|" << endl << "Congradulations! You win! You guessed the word in " << turns + 1 << " tries!" << endl;
            break;
        }
        else{
            newGame.checkWord(input);
            newGame.displayBoard();
        }
        turns++;
    }
    if(turns == 6){
        cout << "Nice try but you are out of attempts. The word was: " << newGame.masterWord << endl;
    }
    return 0;
}
