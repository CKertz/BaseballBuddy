#pragma once

class Team {
private:
	string Name;
	bool isHome = false;
	vector<int>score{ 0,0,0,0,0,0,0,0,0 };
	bool onOffense = false;
	int currentInning = 1;//this is to refer to which element in score vector to place runs. a run in the 2nd inning goes in 2nd element of vector.
	int totalHits = 0;
public:
	Team() {
		Name = "unchosen";
		isHome = false;
		onOffense = false;
	}
	void initializeScoreForInning(int inning) { score.push_back(0); } // may want to delete. I just delcared 0 in all 9 innings in score instead. still testing
	void setName(string team) { Name = team; }
	bool getLocationStatus(){return isHome;}
	bool getOffenseStatus(){return onOffense;}
	void setCurrentInning(int currentInn) { currentInning = currentInn; }
	void setOffenseStatus(bool choice){onOffense = choice;}
	void setLocationStatus(bool choice){isHome = choice;}
	void incrementScore(int inning) { score[inning]+=1; }
	void incrementTotalHits() { totalHits++; }
	int getTotalHits() { return totalHits; }
	string getName() { return Name; }
	int getScoreForInning(int inningRequest) { return score[inningRequest]; }
	int getTotalInnings() { return score.size(); }
	int getScore()
	{
		int sum = 0;
		for (size_t i = 0; i<score.size(); i++ )
			sum += score[i];
		return sum;
	}
};
