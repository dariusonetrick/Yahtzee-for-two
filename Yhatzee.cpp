
/****************************
 * 2 Player Yhatzee
 * Alan Michalek
 * ***************************/


#include <string>
#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <iomanip>
#include <vector>

using namespace std;

//#################################################################################################

class Dice{
	private:
		int value;
	
	public:

		//Randomly assigns a value between from 1 to 6 to the dice.
		void roll();
		int reveal() {return value;}
		bool selected;
		//The autograder will set the values directly instead of calling roll() to avoid randomness!
		void setValue(int value) {this->value = value;}

};

void Dice::roll() {
	if (!selected)
		setValue(1+rand() % 6);
	selected = false;
	}

//#################################################################################################

const int HAND_SIZE = 5;

class Hand {
	public:

		//Display the value of the five dice
		void show();
		void play();
		Dice* getDice(int diceNum);

		//selection is the string of dice numbers that the player wants to keep.
		//For example, "125" means that player wants to keep the first, second, and fifth dice, and roll the rest.
		void setSelection(string selection);	
		Hand();	

	private:
		Dice* Dices[HAND_SIZE]; 
};

void Hand::play(){
	for (int i = 0; i < HAND_SIZE; i++) {
			Dices[i]->roll();
	}
}

Dice* Hand::getDice(int diceNum){return Dices[diceNum];}

void Hand::setSelection(string selection) {
	for (int i = 0; i < selection.size(); i++){
		if (selection.at(i)-'0' > 0 && selection.at(i)-'0' < 6 )
			getDice(selection.at(i)-'0'-1)->selected = true;
	}
}

void Hand::show(){
	cout << "Hand: ";
	for (int i = 0; i < HAND_SIZE; i++){
		cout << getDice(i)->reveal() << " ";
	}
	cout << endl;
}

Hand::Hand(){
	for (int i = 0; i < HAND_SIZE; i++) {
		Dices[i] = new Dice;
	}
}

//######################################################################

//List of rows in the board
const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;

const int BOARD_SIZE=13; 

class Game {

	public:
		//calcScore returns a score of a hand (5 dice) for given row in the board. 
		//Note the rows are indexed from zero. 
		//For example if the hand is 2 1 1 5 1 then calcScore(hand, ONES) returns 3 and  calcScore(hand, TWOS) returns 2.
		int calcScore(Hand* hand, int row); 
				
		//Display the board
		void show();
		
		//Returns the score of the upper part of the board
		int getUpperScore();
		
		//Returns the score of the lower part of the board
		int getLowerScore();
	
		//Returns the bonus points
		int getBonusScore();

		//Returns the total score
		int getTotalScore();

		//Play a hand based on the selected row
		void play(Hand* hand, int row);
		
		//Check to see if a row has been played or not (returns true if a row has been played)
		bool isPlayed(int row);
		
		//Check to see if all rows haven been played or not (returns true if all rows have been played)
		bool isFinished();
		bool isThreeKind(Hand* hand);
		bool isTwoKind(Hand* hand);
		bool isFiveKind(Hand* hand);
		bool isLargeStraight(Hand* hand);
		bool isSmallStraight(Hand* hand);
		void sort(Hand* hand);
	private:
		int scores[BOARD_SIZE] {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
		string dash[BOARD_SIZE] {"-","-","-","-","-","-","-","-","-","-","-","-","-"};
};



void Game::play(Hand* hand, int row){
	if (isFinished())
		return;
	if (isPlayed(row))
		return;
	calcScore(hand, row);
}

void Game::sort(Hand* hand){
	int temp;
	int swaps;
	do{
		swaps = 0;
		for (int i = 0; i < 4; i++){
			if (hand->getDice(i)->reveal() > hand->getDice(i+1)->reveal()){
				temp = hand->getDice(i)->reveal();
				hand->getDice(i)->setValue(hand->getDice(i+1)->reveal());
				hand->getDice(i+1)->setValue(temp);
				swaps+=1;
			}
		
		}
	}while(swaps != 0);
}

bool Game::isLargeStraight(Hand* hand){
int straight = 0; 
	for (int i = 0; i < 4; i++){
		if (hand->getDice(i)->reveal() + 1 == hand->getDice(i+1)->reveal())
			straight += 1;
	}
	return (straight == 4);		
	
}
bool Game::isSmallStraight(Hand* hand){ 	
	int straight = 0;	
	for (int i = 0; i < 4; i++){
		if (hand->getDice(i)->reveal() == hand->getDice(i+1)->reveal())
			continue;
		if (hand->getDice(i)->reveal() + 1 == hand->getDice(i+1)->reveal())
			straight += 1;
	}
	return (straight >= 3);		
}


bool Game::isThreeKind(Hand* hand){
	int kind = 0;
	for (int i = 0; i < HAND_SIZE; i++){
		for (int n = 0; n < HAND_SIZE; n++){
			if (hand->getDice(i)->reveal() == hand->getDice(n)->reveal())
				kind += 1;
		}
		if (kind == 3){
			return true;
		}
		kind = 0;
	}
	return false;	
}

bool Game::isFiveKind(Hand* hand){
	int kind = 0;
	for (int i = 0; i < HAND_SIZE; i++){
		for (int n = 0; n < HAND_SIZE; n++){
			if (hand->getDice(i)->reveal() == hand->getDice(n)->reveal())
				kind += 1;
		}
		if (kind == 5){
			return true;
		}
		kind = 0;
	}
	return false;	
}

bool Game::isTwoKind(Hand* hand){
	int kind = 0;
	for (int i = 0; i < HAND_SIZE; i++){
		for (int n = 0; n < HAND_SIZE; n++){
			if (hand->getDice(i)->reveal() == hand->getDice(n)->reveal())
				kind += 1;
		}
		if (kind == 2)
			return true;
		kind = 0;
	}
	return false;	
}

int Game::calcScore(Hand* hand, int row) {
	int kind = 0;
	row[scores] = 0;
	if (row <= SIXES){
		for (int i = 0; i < HAND_SIZE; i++){
			if (hand->getDice(i)->reveal() == (row+1))
				scores[row] += (row+1);
		}
	}
	if (row == THREE_OF_KIND){
		for (int i = 0; i < HAND_SIZE; i++){
			for (int n = 0; n < HAND_SIZE; n++){
				if (hand->getDice(i)->reveal() == hand->getDice(n)->reveal())
					kind += 1;
			}
			if (kind >= 3){
				for (int i = 0; i < HAND_SIZE; i++){
					scores[row] += (hand->getDice(i)->reveal());
				} 
				break;
			}
			kind = 0;
		}
	}
	if (row == FOUR_OF_KIND){
		for (int i = 0; i < HAND_SIZE; i++){
			for (int n = 0; n < HAND_SIZE; n++){
				if (hand->getDice(i)->reveal() == hand->getDice(n)->reveal())
					kind += 1;
			}
			if (kind >= 4){
				for (int i = 0; i < HAND_SIZE; i++){
					scores[row] += (hand->getDice(i)->reveal());
				} 
				break;
			}
			kind = 0;
		}
	}	
	if (row == YAHTZEE){
		for (int i = 0; i < HAND_SIZE; i++){
			for (int n = 0; n < HAND_SIZE; n++){
				if (hand->getDice(i)->reveal() == hand->getDice(n)->reveal())
					kind += 1;
			}
			if (kind == 5){
				scores[row] = 50;
				break;
			}
			kind = 0;
		}

	}
	if (row == CHANCE){
		for (int i = 0; i < HAND_SIZE; i++){
			scores[row] += (hand->getDice(i)->reveal());
		} 
	}	
	if (row == FULL_HOUSE) {
		if ((isTwoKind(hand) && isThreeKind(hand)) || isFiveKind(hand))
			scores[row] = 25;
	}
	if (row == SMALL_STRAIGHT) {
		sort(hand);
		if (isSmallStraight(hand))
			scores[row] = 30;
	}
	if (row == LARGE_STRAIGHT) {
		sort(hand);
		if (isLargeStraight(hand))
			scores[row] = 40;
	}
	return scores[row];
}

void Game::show(){
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (scores[i] > -1) {
			dash[i] = to_string(scores[i]);
		}
	}
	cout << "1.  Ones: " << setw(12) << dash[ONES] << endl;
	cout << "2.  Twos: " << setw(12) << dash[TWOS] << endl;
	cout << "3.  Threes: " << setw(10) << dash[THREES] << endl;
	cout << "4.  Fours: " << setw(11) << dash[FOURS] << endl;
	cout << "5.  Fives: " << setw(11) << dash[FIVES] << endl;
	cout << "6.  Sixes: " << setw(11) << dash[SIXES] << endl;
	cout << "    Sum: " << setw(13) << getUpperScore() << endl;
	cout << "    Bonus: " << setw(11) << getBonusScore() << endl;
	cout << "7. Three of a kind: " << setw(2) << dash[THREE_OF_KIND] << endl;
	cout << "8. Four of a kind: "  << setw(3) << dash[FOUR_OF_KIND] << endl;
	cout << "9. Full House: " << setw(7) << dash[FULL_HOUSE] << endl;
	cout << "10. Small straight: " << setw(2) << dash[SMALL_STRAIGHT] << endl;
	cout << "11. Large straight: " << setw(2) << dash[LARGE_STRAIGHT] << endl;
	cout << "12. Chance: " << setw(10) << dash[CHANCE] << endl;
	cout << "13. Yhatzee: " << setw(9) << dash[YAHTZEE] << endl;  
	cout << "Total: " << setw(15) << getTotalScore() << endl; 
	
}

int Game::getLowerScore() {
	int score = 0;
	for (int i = 6; i < 13; i++){
		if (scores[i] > -1)
			score += scores[i];
	}
	return score;
}

int Game::getUpperScore() {
	int score = 0;
	for (int i = 0; i < 6; i++){
		if (scores[i] > -1)
			score += scores[i];
	}
	return score;
}

int Game::getBonusScore() {
	if (getUpperScore() >= 63)
		return 35;
	return 0;
}

int Game::getTotalScore() {
	return (getUpperScore() + getLowerScore() + getBonusScore()); 
}

bool Game::isPlayed(int row) {
	if (scores[row] > -1)
		return true;
	return false;
}

bool Game::isFinished() {
	for (int i = 0; i < BOARD_SIZE; i++){
		if (scores[i] == -1)
			return false;
	}
	return true;
}

class player {
	public:
		bool draw;
		bool won;
		Game game;
		Hand* hand = new Hand();
		player(){
				cout << "Enter name: ";
				cin >> name;
				}
		string name; 
};


void multiplayer(){
	bool finish;
	player players[2];
	int inputRow;
	string input;
	while(!finish){
		for (int i = 0; i < 2; i++){
			cout << "----------- " << players[i].name << " -----------" << endl;
			players[i].game.show();
			players[i].hand->play();
			for (int n = 0; n < 2; n++){
				players[i].hand->show();
				cout << "Keep Dice (s to stop rolling): ";
				cin >> input;
				if (input == "s")
					break;
				players[i].hand->setSelection(input);
				players[i].hand->play();
			}
			players[i].hand->show();
			cout << "Select a combination to play: ";
			while (true){
				cin >> inputRow;
				if (inputRow > 0 && inputRow < 14)
					break;
				cout << "Sorry, you need to enter correct row number. Also this game is buggy :)\n";
			}
			players[i].game.play(players[i].hand, inputRow - 1);
			players[i].game.show();		
			if (players[0].game.isFinished() && players[1].game.isFinished())
				finish = true;
		}
	}
	if (players[0].game.getTotalScore() == players[1].game.getTotalScore()){
		cout << "\nDRAW";
		return;
	}
	if (players[0].game.getTotalScore() > players[1].game.getTotalScore()){
		players[0].won = true;
		players[1].won = false;	}
	else{
		players[0].won = false;
		players[1].won = true; }

	for (int i = 0; i < 2; i++){
		if (players[i].won){
			cout << "--------------" << players[i].name << " won --------------";
			return;
		}
		}
	}


//#######################################################################################


void win();

void run() {
	multiplayer();
}

void win () {
	player players[2];
	
	if (players[0].game.getTotalScore() == players[1].game.getTotalScore()){
		cout << "\nDRAW";
		return;
	}
	if (players[0].game.getTotalScore() > players[1].game.getTotalScore()){
		players[0].won = true;
		players[1].won = false;	}
	else{
		players[0].won = false;
		players[1].won = true; }

	for (int i = 0; i < 2; i++){
		if (players[i].won){
			cout << "--------------" << players[i].name << " won --------------";
			return;
		}
		}
	}


int main() {
	srand(time(0));
	run();
	return 0;
}
