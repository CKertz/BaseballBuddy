#include "player.h"
#include "Team.h"
#include <fstream>
#include <iomanip>


void retreiveDailyStats(Player atBat)
{// this will be painful, maybe there's a better way in the future? individually accessing any stat counts > 0, displaying them.
	if (atBat.getHitNum() >= 1)
	{
		if (atBat.getSingleCount() >= 1)
			cout << atBat.getPlayerLastName() << " has had " << atBat.getSingleCount() << " single(s) on the day." << endl;
		if (atBat.getDoubleCount() >= 1)
			cout << atBat.getPlayerLastName() << " has had " << atBat.getDoubleCount() << " double(s) on the day." << endl;
		if (atBat.getTripleCount() >= 1)
			cout << atBat.getPlayerLastName() << " has had " << atBat.getTripleCount() << " triple(s) on the day." << endl;
		if (atBat.getHomeRunCount() >= 1)
			cout << atBat.getPlayerLastName() << " has had " << atBat.getHomeRunCount() << " home run(s) on the day." << endl;
		if (atBat.getGrandSlamCount() >= 1)
			cout << atBat.getPlayerLastName() << " has had " << atBat.getGrandSlamCount() << " grand slam(s) on the day." << endl;
	}

	if (atBat.getSacFlyCount() >=1)
		cout << atBat.getPlayerLastName() << " has had " << atBat.getSacFlyCount() << " sac fly(s) on the day." << endl;
	if (atBat.getRBICount() >=1)
		cout << atBat.getPlayerLastName() << " has had " << atBat.getRBICount() << " RBI(s) on the day." << endl;
	if (atBat.getWalkCount() >= 1)
		cout << atBat.getPlayerLastName() << " has had " << atBat.getWalkCount() << " walk(s) on the day." << endl;
	if (atBat.getStolenBaseCount() >= 1)
		cout << atBat.getPlayerLastName() << " has had " << atBat.getStolenBaseCount() << " stolen bases on the day." << endl;
}
void callFrontBatter(vector<Player> playerList)
{
	vector<Player>::iterator itr = playerList.begin();
	while (itr->getBattingStatus() == true)
		itr++;
	cout << "Now up to bat: " << endl << itr->getPlayerFirstName() << " " << itr->getPlayerLastName() << endl;
	cout << "On the day: " << itr->getHitNum() << "/" << itr->getAttemptNum() << endl << endl;
	
	retreiveDailyStats(*itr);
	// can later implement what sort of actions have occurred. a single, homerun, stolen base etc
	// maybe a switch case function called here where certain output if singlecount, doublecount w/e
}
void advanceBatter(vector<Player> &playerList, int outCount)
{
	vector<Player>::iterator itr = playerList.begin();
	vector<Player>::iterator resettingItr = playerList.begin();// used to reflag bool hasBatted, making itr catch them again
																   //list<royalsPlayer> holder = playerList;
	while (itr->getBattingStatus() == true)
		itr++;

	itr->setBattingStatusTrue();
	itr->setisCurrentlyBattingTrue();
	itr++;
	if (itr == playerList.end())
	{
		for (int i = 0; i < playerList.size(); i++)
		{// loop goes through batting order, resets status that they have batted

			if (resettingItr->getBattingStatus() == true)
			{
				resettingItr->setBattingStatusFalse();
				resettingItr++;
			}
		}
	}

	if (outCount < 3)
		callFrontBatter(playerList);
}
void updateStats(vector <Player>&playerList, vector<Player>onBase,Player Hitter)// This is currently only used for baserunners who steal a base. since playerList is what is credited, and we before were crediting onbase which doesnt hold/change player stats. 
{
	if (onBase.size() > 0)
	{
		for (size_t i = 0; i < playerList.size(); i++)
		{
			if (onBase.empty())
				return;
			if (playerList[i].getPlayerNumber() == onBase.back().getPlayerNumber())
			{
				playerList[i].incrementStolenBaseCount();
				onBase.pop_back();
				i = 0;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < playerList.size(); i++)
			if (playerList[i].getPlayerNumber() == Hitter.getPlayerNumber())
				playerList[i].incrementStolenBaseCount();
	}

}
void initialize(int& pitchCount, int& strikeCount, int& ballCount, bool &batterUp)
{
	if (batterUp = true)
		batterUp = false;
	pitchCount = 0;
	strikeCount = 0;
	ballCount = 0;
}
void scoreKeeper(Team &atBat, int runsHit,int currentInning, Team otherTeam, Player &hitter)
{
	int totalScore = 0;
	if (atBat.getLocationStatus() == true)
	{
		for (size_t i = 0; i < runsHit; i++)
		{
			atBat.incrementScore(currentInning-1); // div by 2 because parameter passed will be the inning half number, ie inning*2
			hitter.incrementRBIcount();
		}
	}
	else
	{
		for (size_t i = 0; i < runsHit; i++)
		{
			atBat.incrementScore(currentInning); // div by 2 because parameter passed will be the inning half number, ie inning*2
			hitter.incrementRBIcount();
		}
	}

	if (atBat.getScore() > otherTeam.getScore())
		cout << atBat.getName() << " are leading " << atBat.getScore() << "-" << otherTeam.getScore() << endl;
	else if (atBat.getScore() < otherTeam.getScore())
		cout << otherTeam.getName() << " are leading " << otherTeam.getScore() << "-" << atBat.getScore() << endl;
	else
		cout << "The score is tied at " << atBat.getScore() << endl;
}
void modifyPlayersOnBase(Player &hitter, vector<Player>&onBase, Team &atBat, Team otherTeam, int inningNumber,vector<Player>::iterator &itr, bool &stealOccuring,vector<Player>&playerList,int outCount)
{
	
	int runnerBase;
	//vector<Player>::iterator itr = onBase.begin();
	itr = onBase.begin();
	if (onBase.size() >= 1)
	{
		if (stealOccuring == false)
			cout << "Below is a list of players currently on base. Where did they go?" << endl;
		else
			cout << "Below is a list of players on base. If the player stole a base, indicate where he is now." << endl;
		while (itr->getVisitedStatus() == true)// first, check if the baserunner has been visited before prompting user to edit their location
			itr++;
		while (itr != onBase.end())
		{
			if (hitter.getPlayerNumber() != itr->getPlayerNumber())
			{
				string nameHold = itr->getPlayerLastName();
				int baseHold = itr->getBaseOnBoard();
				cout << nameHold << ",  originally at base "
					<< baseHold << endl;
				cin >> runnerBase;
				if (runnerBase < 4)
					cout << nameHold << " is now on base " << runnerBase << endl << endl;
				itr->setBaseOnBoard(runnerBase);

				if (runnerBase == 4)
				{
					cout << nameHold << " has scored!" << endl;
					scoreKeeper(atBat, 1, inningNumber, otherTeam, hitter);
					hitter.incrementRBIcount();
					itr->incrementRunCount();
					itr = onBase.erase(itr);
				}

				else
				{
					if (stealOccuring == true && baseHold != runnerBase)
						updateStats(playerList, onBase,hitter);
					itr->setVisitedStatusTrue(true);

				}
			}		
					itr++;		
		}
		if (stealOccuring == true)
		{
			cout << "Did " << hitter.getPlayerLastName() << " steal a base? If yes, enter the base number below. Otherwise, enter 0." << endl;
			cin >> runnerBase;
			if (runnerBase != 0)
			{
				cout << "The hitter stole base " << runnerBase << endl;
				hitter.setHitterStealStatus(true);
				hitter.setBaseOnBoard(runnerBase);
				hitter.incrementStolenBaseCount();
				onBase.push_back(hitter);
				advanceBatter(playerList, outCount);
			}
			itr = onBase.begin();
			for (size_t i = 0; i < onBase.size(); i++)
			{
				itr->setVisitedStatusTrue(false);
				itr++;
			}

		}

	}
	stealOccuring = false;
}
void classifyRunning(Player &hitter, vector<Player>&onBase, int hitType,Team &atBat, Team otherTeam, int inningNumber,vector<Player>::iterator &onBaseItr, bool &stealOccuring,vector<Player>&playerList,int outCount)
{
	//int runnerBase;
	//vector<Player>::iterator itr = onBase.begin();
	//if (hitType < 4 && hitType != 0)
	//	cout << hitter.getPlayerLastName() << " is now on base " << hitter.getBaseOnBoard() << endl << endl;
	//if (onBase.size() >= 1)
	//{
	//	cout << "Below is a list of players currently on base. Where did they go?" << endl;
	//	while (itr->getVisitedStatus() == true)// first, check if the baserunner has been visited before prompting user to edit their location
	//		itr++;
	//	while (itr != onBase.end())
	//		/*for (size_t i = 0; i < onBase.size(); i++)*/
	//	{
	//		if (hitter.getPlayerNumber() != itr->getPlayerNumber())
	//		{
	//			string nameHold = itr->getPlayerLastName();
	//			int baseHold = itr->getBaseOnBoard();
	//			cout << nameHold << ",  originally at base "
	//				<< baseHold << endl;
	//			cin >> runnerBase;
	//			if (runnerBase < 4)
	//				cout << nameHold << " is now on base " << runnerBase << endl << endl;
	//			itr->setBaseOnBoard(runnerBase);

	//			if (runnerBase == 4)
	//			{
	//				//runsThisInning++;
	//				cout << nameHold << " has scored!" << endl;
	//				scoreKeeper(atBat, 1, inningNumber, otherTeam, hitter);
	//				//atBat.incrementScore(inningNumber);
	//				hitter.incrementRBIcount();
	//				itr->incrementRunCount();
	//				itr = onBase.erase(itr);
	//				//itr++;

	//			}

	//			else
	//			{
	//				itr->setVisitedStatusTrue(true);
	//				itr++;
	//			}
	//		}

	//	}
	//}
	modifyPlayersOnBase(hitter, onBase, atBat, otherTeam, inningNumber,onBaseItr,stealOccuring,playerList,outCount);
	if (hitType != 4 && hitType != 0)
		onBase.push_back(hitter);
	onBaseItr = onBase.begin();
	for (size_t i = 0; i < onBase.size(); i++)
	{
		onBaseItr->setVisitedStatusTrue(false);
		onBaseItr++;
	}
}
void classifyHit(Player &hitter,vector<Player>&onBase, Team &atBat, int inningNumber, Team otherTeam,vector<Player>::iterator &onBaseItr,bool &stealOccuring,vector<Player>&playerList,int outcount)
{
	
	int hitType;
	//int runnerBase;
	int runsThisInning=0;
	cout << "What kind of hit was made? \n 1. Single \n 2. Double \n 3. Triple \n 4. Home Run" << endl;
	cin >> hitType;

	hitter.setBaseOnBoard(hitType);
	//onBase.push_back(hitter); im going to push this back at the END of function, avoiding it below
	hitter.setVisitedStatusTrue(true);
	atBat.incrementTotalHits();
	switch (hitType)
	{
		case 1:
			hitter.incrementSingleCount();
			break;
		case 2:
			hitter.incrementDoubleCount();
			break;
		case 3:
			hitter.incrementTripleCount();
			break;
		case 4:
			hitter.incrementHomeRunCount();
			if (onBase.size() == 3)
				cout << "Grand Slam! All runners have scored." << endl;
			else
				cout << "Home Run! The following players have scored: " << endl;
				cout << hitter.getPlayerLastName() << endl; // this gives correct output if theres a solo home run, since the hitter is never technically on base.
			for (size_t i = 0; i < onBase.size(); i++)
				cout << onBase[i].getPlayerLastName() << endl;
			scoreKeeper(atBat, onBase.size()+1, inningNumber,otherTeam,hitter);//since the hitter isn't in onBase, we add+1 to compensate
			onBase.clear();
			break;
		default:
			break;

	}
	hitter.incrementAttemptCount();
	hitter.incrementHitCount();
	classifyRunning(hitter, onBase, hitType, atBat, otherTeam, inningNumber,onBaseItr,stealOccuring,playerList,outcount);
	//put the below code into a function, so we can call it for sac-flies. above code isnt needed for them. also this function is huge
	//vector<Player>::iterator itr = onBase.begin();
	//if (hitType < 4)
	//	cout << hitter.getPlayerLastName() << " is now on base " << hitter.getBaseOnBoard() << endl << endl;
	//if (onBase.size() >= 1)
	//{
	//	cout << "Below is a list of players currently on base. Where did they go?" << endl;
	//	while (itr->getVisitedStatus() == true)// first, check if the baserunner has been visited before prompting user to edit their location
	//		itr++;
	//	while (itr != onBase.end())
	//	/*for (size_t i = 0; i < onBase.size(); i++)*/
	//	{
	//		if (hitter.getPlayerNumber() != itr->getPlayerNumber())
	//		{
	//			string nameHold = itr->getPlayerLastName();
	//			int baseHold = itr->getBaseOnBoard();
	//			cout << nameHold << ",  originally at base "
	//				<< baseHold << endl;
	//			cin >> runnerBase;
	//			if (runnerBase < 4)
	//				cout << nameHold << " is now on base " << runnerBase << endl << endl;
	//			itr->setBaseOnBoard(runnerBase);

	//			if (runnerBase == 4)
	//			{
	//				runsThisInning++;
	//				cout << nameHold << " has scored!" << endl;
	//				scoreKeeper(atBat, 1, inningNumber, otherTeam, hitter);
	//				//atBat.incrementScore(inningNumber);
	//				hitter.incrementRBIcount();
	//				itr->incrementRunCount();
	//				itr = onBase.erase(itr);
	//				//itr++;
	//		
	//			}

	//			else
	//			{
	//				itr->setVisitedStatusTrue(true);
	//				itr++;
	//			}
	//		}
	//		//else

	//		
	//		

	//	}
	//}
	//onBase.push_back(hitter);
	//itr = onBase.begin();
	//for (size_t i = 0; i < onBase.size(); i++)
	//{
	//	itr->setVisitedStatusTrue(false);
	//	itr++;
	//}
	//if (onBase.size() > 1)//second, iterate through vector 
	//{
	//	cout << "Below is a list of players on base, where did they go?" << endl;
	//	
	////	for (size_t i = onBase.size()-1; i >= 1; --i)// make this loop go from back to front, and pop back as you go 
	//	for ( size_t i = 0; i < onBase.size()-1; i++)// the bounds on this dont let it work for if onbase.size ==2. try it again with bases loaded. may need to implement separate function for special cases of baselist sizes

	//	{
	//		string nameHold = onBase[i].getPlayerLastName();
	//		int baseHold = onBase[i].getBaseOnBoard();
	//		cout << nameHold << ",  originally at base "
	//			<< baseHold << endl;
	//		cin >> runnerBase;
	//		if (runnerBase < 4)
	//			cout << nameHold << " is now on base " << runnerBase << endl;
	//		onBase[i].setBaseOnBoard(runnerBase);

	//		if (runnerBase == 4)
	//		{
	//			runsThisInning++;
	//			cout << nameHold << " has scored!" << endl;
	//			scoreKeeper(atBat, 1, inningNumber, otherTeam, hitter);
	//			atBat.incrementScore(inningNumber);
	//			hitter.incrementRBIcount();
	//			onBase[i].incrementRunCount();
	//			onBase.erase(onBase.begin()+i);//removes the runner from the onBase vector if they have scored, meaning no longer on a base
	//			//when i erase an element and then the forloop is called, it messes with bounds and creates skips. maybe introduce a boolean, if visited == true... etc
	//			
	//		}
	//		else
	//			cout << hitter.getPlayerLastName() << " is now on base " << hitter.getBaseOnBoard() << endl;
	//		
	//	}
	//}

}
void displayBoxScore(Team Royals, Team otherTeam)
{	

	cout.width(15);	
	cout << left << "Teams";

	for (size_t i = 0; i < Royals.getTotalInnings(); i++)//this is outputting the inning numbers on top
	{
		cout << setw(3) << i+1;
	}
	cout << setw(3) << "R" << setw(3) << "H";
	cout << endl;
	if (Royals.getLocationStatus() == false)
	{

		cout.width(15);
		cout << left << Royals.getName();
		for (size_t i = 0; i < Royals.getTotalInnings(); i++)//outputting the score of the royals inning
		{
				cout << right << Royals.getScoreForInning(i) << setw(3);
		}
		cout << Royals.getScore() << setw(3) << Royals.getTotalHits();  // put in total hits here
		cout << endl;
		cout.width(15);
		cout << left << otherTeam.getName();

		for (size_t i = 0; i < otherTeam.getTotalInnings(); i++)
		{
			cout << right << otherTeam.getScoreForInning(i) << setw(3);
		}
		cout << otherTeam.getScore() << setw(3) << otherTeam.getTotalHits();
		cout << endl << endl;
	}
	else
	{
		cout.width(15);
		cout << left << otherTeam.getName();

		for (size_t i = 0; i < otherTeam.getTotalInnings(); i++)
		{
			cout << right << otherTeam.getScoreForInning(i) << setw(3);
		}
		cout << otherTeam.getScore() << setw(3) << otherTeam.getTotalHits();
		cout << endl;

		cout.width(15);
		cout << left << Royals.getName();
		for (size_t i = 0; i < Royals.getTotalInnings(); i++)//outputting the score of the royals inning
		{
			cout << right << Royals.getScoreForInning(i) << setw(3);
		}
		cout << Royals.getScore() << setw(3) << Royals.getTotalHits();// put in total hits here too
		cout << endl << endl;
	}

}
void halfInningSimulation(vector<Player>&playerList, Team &onOffense, int inningNumber,Team &otherTeam)
{
	bool stealOccuring = false;
	int auxillaryIndicator=0; // used in double play scenarios, 
	int strikeCount = 0;
	int pitchCount = 0;
	int ballCount = 0;
	int pitchChoice = 0;
	int outCount = 0;
	bool isOut = false;
	bool batterUp = false;
	bool needAdvanced = false;
	vector<Player>onBase;
	vector<Player>::iterator itr = playerList.begin();
	vector<Player>::iterator onBaseItr = onBase.begin();
	//onOffense.initializeScoreForInning(inningNumber);
	callFrontBatter(playerList);
	for (outCount; outCount < 3; outCount)
	{
		while (itr->getBattingStatus() == true)
			itr++;
		//if (itr->getPlayerNumber != playerList.front().getPlayerNumber())

		initialize(pitchCount, strikeCount, ballCount, batterUp);
		while (batterUp == false)
		{
			cout << "Press 1 if the pitch is a ball, 2 if a strike, 3 if foul, 4 if fielded out, 5 if double play, 6 if hit, 7 if HBP,8 if a stolen base occured,9 if an error is committed. " << endl; 
			cin >> pitchChoice;
			switch (pitchChoice)
			{
			case 1:
				ballCount++;
				if (ballCount < 4)
				{
					cout << "Ball number " << ballCount << " has been added." << endl;
					cout << "The pitch count is: " << ballCount << "-" << strikeCount << endl;
				}
				else
				{
					cout << "Ball 4. Batter has been walked." << endl;
					itr->incrementWalkCount();
					itr->incrementAttemptCount();
					itr->setBaseOnBoard(1);
					classifyRunning(*itr, onBase, 1, onOffense, otherTeam, inningNumber,onBaseItr,stealOccuring,playerList,outCount);
					advanceBatter(playerList,outCount);
					batterUp = true;
				}
				break;
			case 2:
				if (strikeCount < 2)
				{
					strikeCount++;
					cout << "Strike number " << strikeCount << " has been added." << endl;
					cout << "The pitch count is: " << ballCount << "-" << strikeCount << endl;
				}
				else
				{

					itr->incrementOutNum();
					itr->incrementAttemptCount();
					advanceBatter(playerList,outCount);
					outCount++;
					cout << "Strike 3. He's out." << endl << "The inning now has " << outCount << " outs." << endl << endl << endl;
					isOut = true;
					batterUp = true;
				}
				break;
			case 3:
				if (strikeCount < 2)
				{
					strikeCount++;
					cout << "Strike number " << strikeCount << " has been added." << endl;
					cout << "The pitch count is: " << ballCount << "-" << strikeCount << endl;
				}
				else
				{
					cout << "Another foul. The pitch count is: " << ballCount << "-" << strikeCount << endl;
				}
				break;
			case 4:
				outCount++;
				if (outCount == 1)
					cout << "Out has been recorded, there has been " << outCount << " out this inning." << endl;
				else
					cout << "Out has been recorded, there has been " << outCount << " outs this inning." << endl;
				if (outCount <= 2 && onBase.size() > 0)
				{
					cout << "Out has been recorded, there has been " << outCount 
						 <<" out(s) this inning. Was this a sacrifice-fly out? Enter 1 to confirm, 0 to deny." << endl;
					cin >> auxillaryIndicator;
					if (auxillaryIndicator == 1)
						classifyRunning(*itr, onBase, 0, onOffense, otherTeam, inningNumber,onBaseItr,stealOccuring,playerList,outCount);
				}

				cout << endl << endl;
				itr->incrementOutNum();
				itr->incrementAttemptCount();
				advanceBatter(playerList, outCount);
				isOut = true;
				batterUp = true;
				break;
			case 5:
				outCount += 2;
				if (onBase.size() == 0)
				{
					cout << "A double play cannot be had, as there are no other runners on base. Please select a different option." << endl;
					break;
				}
				else
				{
					cout << "Here are a list of players currently on base. Which one of them got out during the double play? Enter the number below." << endl; 
					for (size_t i = 1; i <= onBase.size(); i++)
						cout << i << ". " << onBase[i-1].getPlayerLastName() << endl;
						
					cin >> auxillaryIndicator;
					onBase.erase(onBase.begin() + auxillaryIndicator-1);
					cout << "Double play has been recorded, there has been " << outCount << " outs this inning." << endl << endl << endl;

					itr->incrementOutNum();
					itr->incrementAttemptCount();
					advanceBatter(playerList,outCount);
					isOut = true;
					batterUp = true;
				}

				break;
			case 6:
				classifyHit(*itr,onBase,onOffense,inningNumber,otherTeam,onBaseItr,stealOccuring,playerList,outCount); 
				advanceBatter(playerList, outCount); 
				batterUp = true;
				break;
			case 7:
				cout << "Hit by pitch recorded, batter is now on base 1." << endl;
				itr->incrementWalkCount();
				itr->incrementHitByPitchCount();//when displaying stats for day, walk and hbp may interfere and cause 2 instances
				itr->incrementAttemptCount();
				itr->setBaseOnBoard(1);
				classifyRunning(*itr, onBase, 1, onOffense, otherTeam, inningNumber,onBaseItr,stealOccuring,playerList,outCount);
				advanceBatter(playerList, outCount);
				batterUp = true;
				break;
			case 8:
				//cout << "Who stole a base?" << endl;
				//classifyRunning(*itr, onBase, 5, onOffense, otherTeam, inningNumber);
				stealOccuring = true;
				modifyPlayersOnBase(*itr, onBase, onOffense, otherTeam, inningNumber, onBaseItr,stealOccuring,playerList,outCount);
				
			default:
				break;
			}
		}
	}
	displayBoxScore(onOffense, otherTeam);
}
void gameTracker(Team &Royals, Team &otherTeam, vector<Player>&royalsRoster, vector<Player>&otherRoster)
{

	int totalHalfInnings = 18; // set it at 18 by default, increment into extra innings when needed later on
	for (size_t  halfInning = 1;  halfInning < totalHalfInnings; halfInning++)
	{
		if (halfInning % 2 == 0)
		{
			cout << endl << "Bottom half of inning " << halfInning / 2 << endl;
			if (Royals.getLocationStatus() == true)
				halfInningSimulation(royalsRoster,Royals,halfInning/2, otherTeam);
			else
				halfInningSimulation(otherRoster,otherTeam,halfInning/2,Royals);
		}
		else
		{
			if (halfInning / 2 == 0)
				cout << endl << "Top half of inning 1" << endl;
			else
				cout << endl << "Top half of inning " << halfInning / 2 +1 << endl;
			if (Royals.getLocationStatus() == true)
				halfInningSimulation(otherRoster, otherTeam,halfInning/2,Royals);
			else
				halfInningSimulation(royalsRoster,Royals,halfInning/2,otherTeam);
		}
		if (Royals.getScore() == otherTeam.getScore() && halfInning == 18)// give 2 more extra innings if its tied after a regular game
			totalHalfInnings += 2;
		
		//this additionally wouldn't account for a team winning the game in the bottom of extra innings, somebody would still need "out"
	}
}

void determineSides(Team &team, Team &otherTeam)
{
	char name[256];
	string otherTeamName;
	string choice = "x";
	while (choice == "x")
	{
		cout << "Are the Royals home or away? Enter H or A below." << endl;
		getline(cin,choice);
		if (choice == "A")
		{
			otherTeam.setLocationStatus(true);
			cout << "Royals are now set as being the Away team." << endl;
		}
		else if (choice == "H")
		{
			team.setLocationStatus(true);
			cout << "Royals are now set as being the Home team." << endl;
		}
		else 
			choice = 'x';
		cout << "What is the name of the other team? ie Cardinals, Pirates, Blue Jays.." << endl;
		
		cin.clear();
		cin.sync();
		cin.getline(name,256);
		team.setName("Royals");
		otherTeam.setName(name);
	}
}
void readNewRoster(ifstream&infile, vector<Player>&list)
{

	string playerFirstName;
	string lastName;
	int playerNum;
	string position;
	Player temp;

	while (infile >> playerFirstName >> lastName >> position >> playerNum)
	{
		temp.setPlayerFirstName(playerFirstName);
		temp.setPlayerLastName(lastName);
		temp.setPlayerNumber(playerNum);
		temp.setPosition(position);
		list.push_back(temp);
	}

}

int main()
{
	Team Royals;
	Team otherTeam;
	//displayBoxScore(Royals, otherTeam);
	vector<Player>PlayerList;
	vector<Player>otherPlayerList;
	ifstream infile;
	ifstream infileAwayRoster;
	infileAwayRoster.open("otherRoster.txt");
	infile.open("roster.txt");
	//Reading in the 2 rosters batting orders
	readNewRoster(infile, PlayerList);
	readNewRoster(infileAwayRoster, otherPlayerList);

	determineSides(Royals, otherTeam);
	gameTracker(Royals, otherTeam,PlayerList,otherPlayerList);


	system("pause");
	return 0;
}