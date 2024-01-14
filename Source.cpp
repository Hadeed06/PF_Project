#include <iostream>
#include<fstream>
#include <ctime>
#include <iomanip>
using namespace std;

void result(string T1[11], int T1_batting_scorecard[11][5], int T1_bowling_scorecard[5][4], string T2[11], int T2_batting_scorecard[11][5], int T2_bowling_scorecard[5][4])
{
	int T1_total_runs = 0, T2_total_runs = 0;

	//----Calculating the winning team---------
	for (int i = 0; i < 11; i++)
	{
		T1_total_runs += T1_batting_scorecard[i][0];
		T2_total_runs += T2_batting_scorecard[i][0];
	}
	cout << "Team1 runs: " << T1_total_runs << endl;
	cout << "Team2 runs: " << T2_total_runs << endl;

	if (T1_total_runs > T2_total_runs)
	{
		cout << "Team 1 won the match!" << endl;
	}
	else if (T1_total_runs < T2_total_runs)
	{
		cout << "Team 2 won the match" << endl;
	}
	else if (T1_total_runs == T2_total_runs)
	{
		cout << "Tie Match" << endl;
	}
	//------------------------------------------

	//----Calculating bats of the match---------
	int highest_runs = T1_batting_scorecard[0][0];
	string bats_of_the_match = T1[0];
	for (int i = 1; i < 11; i++)
	{
		if (highest_runs < T1_batting_scorecard[i][0])
		{
			highest_runs = T1_batting_scorecard[i][0];
			bats_of_the_match = T1[i];
		}
	}
	for (int i = 0; i < 11; i++)
	{
		if (highest_runs < T2_batting_scorecard[i][0])
		{
			highest_runs = T2_batting_scorecard[i][0];
			bats_of_the_match = T2[i];
		}
	}
	cout << "Batsman of the match is " << bats_of_the_match << ". He scored " << highest_runs << " runs." << endl;
	//-------------------------------------------

	//----Calculating bowler of the match-------
	int highest_wickets = T1_bowling_scorecard[0][2];
	int loweset_runs = T1_bowling_scorecard[0][0];
	string bowler_of_the_match = T1[10];
	for (int i = 1; i < 5; i++)
	{
		if (highest_wickets <= T1_bowling_scorecard[i][2] && loweset_runs >= T1_bowling_scorecard[i][0])
		{
			highest_wickets = T1_bowling_scorecard[i][2];
			loweset_runs = T1_bowling_scorecard[i][0];
			bowler_of_the_match = T1[10 - i];
		}
	}
	for (int i = 1; i < 5; i++)
	{
		if (highest_wickets <= T2_bowling_scorecard[i][2] && loweset_runs >= T2_bowling_scorecard[i][0])
		{
			highest_wickets = T2_bowling_scorecard[i][2];
			loweset_runs = T2_bowling_scorecard[i][0];
			bowler_of_the_match = T2[10 - i];
		}
	}
	cout << "Bowler of the match is " << bowler_of_the_match << endl;
	//------------------------------------------
}

void displayBatting(string T_name[11], int batting_scores[11][5])
{
	cout << "==========================Batting============================" << endl;
	cout << "    Players             Runs     Balls   4's     6's      SR" << endl;
	for (int i = 0; i < 11; i++)
	{
		cout << right << setw(2) << i + 1 << ". " << left << setw(16) << T_name[i] << "\t" << batting_scores[i][0] << "\t " << batting_scores[i][1] << "\t " << batting_scores[i][2] << "\t " << batting_scores[i][3] << "\t " << batting_scores[i][4] << endl;
	}
}

void displayBowling(string T_name[11], int bowling_scores[5][4])
{
	cout << "==========================Bowling============================" << endl;
	cout << "    Players             Runs    Balls   Wickets" << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << right << setw(2) << i + 1 << ". " << left << setw(16) << T_name[10 - i] << "\t" << bowling_scores[i][0] << "\t" << bowling_scores[i][1] << "\t" << bowling_scores[i][2] << endl;
	}

}

void game(string T1[11], int batting_scorecard[11][5], string T2[11], int bowling_scorecard[5][4], int overs)
{
	int index = 1; // this index is used to help in swtiching and moving to next batsmen
	int index2 = 0; // this index is used to help in swtiching and moving to next bowler
	int* temp; // for switching players scores after over is complete or scoring odd numbers

	int* batting = &batting_scorecard[0][0]; //stores the address of first batsman scores of the team that won the toss
	int* runner_up = &batting_scorecard[1][0]; //stores the address of second batsman scores
	
	string* batting_ = &T1[0]; // stores the address of first batsman name of the team that won the toss
	string* runner_up_ = &T1[1]; // stores the address of second batsman name
	string* temp_; // for switching players name after over is complete or scoring odd numbers

	string* bowling = &T2[10];  // giving the 10th adrees of bowling team to the first bowler
	
	srand(time(0));

	//---To jump overs---
	int jump;
	cout << "Enter number the overs you want to jump: " << endl;
	cin >> jump;

	int wickets = 0;
	int total_runs = 0;
	int runs = NULL;
	for (int i = 1; i <= overs * 6; i++)
	{
		
		system("cls");
		if (wickets < 5) // 10% chance out for first five players
		{
			runs = (rand() % 10) - 1;
		}
		else // 50% chance out for last five players
		{
			runs = (rand() % 14) - 7;
		}

		if (runs == 1 || runs == 3 || runs == 5)
		{
			cout << *batting_ << " scored : " << runs << " runs" << endl << endl;
			*batting += runs; // calculates batsman's runs
			*(batting + 1) += 1; // ball counter
			*(batting + 4) = ((*batting) / (*(batting + 1))) * 100; // SRR 

			//switching addresses between batsman and the runner up
			temp = batting;
			batting = runner_up;
			runner_up = temp;

			//switching names between batsman and runnerup for display
			temp_ = batting_;
			batting_ = runner_up_;
			runner_up_ = temp_;

			//bowling update
			bowling_scorecard[index2][0] += runs;  
			bowling_scorecard[index2][1] += 1;

			total_runs += runs;
		}
		else if (runs == 0 || runs == 2 || runs == 4 || runs == 6 || runs == 7 || runs == 8)
		{
			if (runs == 8)
			{
				runs = 6;
			}
			if (runs == 7)
			{
				runs = 4;
			}
			cout << *batting_ << " scored: " << runs << " runs" << endl << endl;
			*batting += runs; //calculates runs
			*(batting + 1) += 1; // ball counter
			*(batting + 4) = ((*batting) / (*(batting + 1))) * 100; // SRR 

			if (runs == 4)
			{
				*(batting + 2) += 1; // 4s counter
			}
			else if (runs == 6)
			{
				*(batting + 3) += 1; // 6s counter
			}

			//bowling update
			bowling_scorecard[index2][0] += runs;
			bowling_scorecard[index2][1] += 1;

			total_runs += runs;
		}
		else if (runs <= -1) // condition for out
		{
			wickets++;
			cout << *batting_ << " is out!" << endl << endl;
			*(batting + 1) += 1; // ball counter
			*(batting + 4) = ((*batting) / (*(batting + 1))) * 100; // SRR 

			if (wickets == 10)
			{
				break;
			}

			index++;
			batting = &batting_scorecard[index][0];
			batting_ = &T1[index];

			//bowling update
			bowling_scorecard[index2][1] += 1;
			bowling_scorecard[index2][2] += 1;
		}

		if (i % 6 == 0) // condition for over complete
		{
			//switching addresses between batsman and the runner up
			temp = batting;
			batting = runner_up;
			runner_up = temp;

			temp_ = batting_;
			batting_ = runner_up_;
			runner_up_ = temp_;

			index2++; // new bowler
			if (index2 == 5)
			{
				index2 = 0;
			}
		}


		

		displayBatting(T1, batting_scorecard);
		cout << endl << endl;
		displayBowling(T2, bowling_scorecard);
		cout << endl << "Batting: " << *batting_ << "\truns: " << *batting << endl;
		cout << "Runner Up: " << *runner_up_ << "\truns: " << *runner_up << endl;
		cout << "Scores:" << endl;
		cout << total_runs << "/" << wickets << endl;
		cout << "Balls: " << i << endl;

		if (i >= (jump * 6) - 1) // condition for jumping
		{
			cout << endl << "Press Enter to continue..." << endl;
			cin.get();
		}
		
	}
}

int main()
{
	string T1[11]{ "Hadeed Rauf" ,"Ammar" , "Ali" ,"Muneeb" ,"Kuzaima" ,"Ahmed" ,"Bhatti" ,"Farzeen" ,"mubeen" ,"Alyan" ,"Qasim" };
	string T2[11]{ "Salman " ,"Talha" ,"Hani" ,"Haider" ,"Samiullah" ,"Umair" ,"Shehryar" ,"Anas" ,"Usman" ,"Ashraf" ,"Rizwan" };

	//file to store the data of players

	fstream my_file;
	my_file.open("players_data.txt", ios::out);
	if (!my_file)
	{
		cout << "Filel is not oppened :" << endl;
	}
	else
	{
		cout << "File for players data is created :" << endl;
		for (int i = 0; i < 11; i++)
		{
			my_file << "Player [" << i + 1 << "]for team A is" << T1[i] << "\t\t\t" << "Player [" << i + 1 << "]for team B is" << T2[i] << endl;
		}
	}
	



	int T1_batting_scorecard[11][5] = { 0 };
	int T1_bowling_scorecard[5][4] = { 0 };

	int T2_batting_scorecard[11][5] = { 0 };
	int T2_bowling_scorecard[5][4] = { 0 };

	srand(time(0));
	int overs;
	int num = rand() % 2;

	cout << "Welcome!" << endl;
	cout << "Enter number of overs:" << endl;
	cin >> overs;


	// file to define the number of overs 
   
	int over;
	fstream m_file;
	if (!my_file)
	{
		cout << "Filel is not created :" << endl;
	}

	else
	{
		cout << "File for overs configration is created :" << endl;
		for (int i = 0; i < 11; i++)
		{
			my_file << " 10" << endl;
		}
	}
	m_file.close();

	

	//Tossing
	if (num == 0)
	{
		cout << "Team1 won the toss and chose to Bat first" << endl;
		cout << endl << "Press Enter to continue..." << endl;
		cin.get();
		game(T1, T1_batting_scorecard, T2, T2_bowling_scorecard, overs);

		system("cls");
		cout << "Team 2 is batting now" << endl;
		cout << endl << "Press Enter to continue..." << endl;
		cin.get();
		game(T2, T2_batting_scorecard, T1, T1_bowling_scorecard, overs);
	}
	else if (num == 1)
	{
		cout << "Team2 won the toss and chose to Bat first" << endl;
		cout << endl << "Press Enter to continue..." << endl;
		cin.get();
		game(T2, T2_batting_scorecard, T1, T1_bowling_scorecard, overs);

		system("cls");
		cout << "Team 1 is batting now" << endl;
		cout << endl << "Press Enter to continue..." << endl;
		cin.get();
		game(T1, T1_batting_scorecard, T2, T2_bowling_scorecard, overs);
	}

	system("cls");


	// batting scorecard of team no1 
	displayBatting(T1, T1_batting_scorecard);
	cout << endl << "===================================================" << endl;
	cout << endl << "===================================================" << endl;
	cout << endl << "===================================================" << endl;
	// batting scorecard of team no2 
	displayBatting(T2, T2_batting_scorecard);
	cout << endl << "===================================================" << endl;
	cout << endl << "===================================================" << endl;
	cout << endl << "===================================================" << endl;
	// bowling scorecard of team no1
	displayBowling(T1, T1_bowling_scorecard);
	cout << endl << "===================================================" << endl;
	cout << endl << "===================================================" << endl;
	cout << endl << "===================================================" << endl;
	// bowling scorecard of team no2
	displayBowling(T2, T2_bowling_scorecard);
	cout << endl << "===================================================" << endl;
	cout << endl << "===================================================" << endl;
	cout << endl << "===================================================" << endl;


	// showing the final result that which team wins and whose the batsman and bower of the match 

	result(T1, T1_batting_scorecard, T1_bowling_scorecard, T2, T2_batting_scorecard, T2_bowling_scorecard);
	return 0;
}