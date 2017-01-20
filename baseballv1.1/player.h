#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <list>
using namespace std;

class Player {
private:
	//standard player attributes declared
	string playerFirstName;
	string playerLastName;
	string position;
	bool hasBatted;
	bool onBatVisited;
	bool isStealing = false;
	bool hitterStoleBase = false;
	int playerNumber;
	int baseOnBoard;

	//now declaring statistics
	int singleCount = 0;
	int doubleCount = 0;
	int tripleCount = 0;
	int homeRunCount = 0;
	int hitNum = 0;
	int outNum = 0;
	int attemptNum = 0;
	int walkNum = 0;
	int RBIcount = 0;
	int runNum = 0;
	int stolenBaseCount = 0;
	int sacFlyCount = 0;
	int hitByPitchCount = 0;
	int grandSlamCount = 0;
public:

	Player() {
		playerFirstName = "John";
		playerLastName = "Doe";
		position = "CF";
		playerNumber = 1;
		hasBatted = false;
		onBatVisited = false;
	}
	string getPlayerFirstName() {return playerFirstName;}
	string getPlayerLastName() {return playerLastName;}
	string getPosition() {return position;}
	int getHitByPitchCount() { return hitByPitchCount; }
	int getGrandSlamCount() { return grandSlamCount; }
	int getHitNum() { return hitNum; }
	int getAttemptNum() { return attemptNum; }
	int getPlayerNumber() {return playerNumber;}
	int getStolenBaseCount() { return stolenBaseCount; }
	int getBaseOnBoard() { return baseOnBoard; }
	int getSingleCount() { return singleCount; }
	int getDoubleCount() { return doubleCount; }
	int getTripleCount() { return tripleCount; }
	int getHomeRunCount() { return homeRunCount; }
	int getWalkCount() { return walkNum; }
	int getRBICount() { return RBIcount; }
	int getSacFlyCount() { return sacFlyCount; }
	void incrementSacFlyCount() { sacFlyCount++; }
	bool getHitterStoleStatus() { return hitterStoleBase; }
	bool getBattingStatus() {return hasBatted;}
	bool getVisitedStatus() { return onBatVisited; }
	bool getStealingStatus() { return isStealing; }
	void setStealingStatus(bool choice) { isStealing = choice; }
	void incrementHitByPitchCount() { hitByPitchCount++; }
	void setVisitedStatusTrue(bool status) { onBatVisited = status; }
	void incrementStolenBaseCount() { stolenBaseCount++; }
	void incrementWalkCount(){walkNum++;}
	void incrementSingleCount(){singleCount++;}
	void incrementDoubleCount() { doubleCount++; }
	void incrementTripleCount() { tripleCount++; }
	void incrementHomeRunCount() { homeRunCount++; }
	void incrementHitCount() { hitNum++; }
	void incrementOutNum() { outNum++; }
	void incrementRBIcount() { RBIcount++; }
	void incrementRunCount() { runNum++; }
	void incrementGrandSlamCount() { grandSlamCount++; }
	void incrementAttemptCount() { attemptNum++; }
	void setBaseOnBoard(int base) { baseOnBoard = base; }
	void setBattingStatusTrue(){hasBatted = true;}
	void setBattingStatusFalse() { hasBatted = false; }
	void setisCurrentlyBattingTrue(){}
	void setPlayerFirstName(string name) {playerFirstName = name;}
	void setPlayerLastName(string name) {playerLastName = name;}
	void setPosition(string pos) {position = pos;}
	void setPlayerNumber(int num) {playerNumber = num;}
	void setHitterStealStatus(bool choice) { hitterStoleBase = choice; }

};
