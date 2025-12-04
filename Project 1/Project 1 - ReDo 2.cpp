#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
enum enWinner {Player = 1, Computer, Draw};
enum enChoise {Rock = 1, Paper, Scissor};
struct stRoundInfo
{
    short RoundNumber = 0;         
    enChoise Player1Choice;    
    enChoise ComputerChoice;   
    enWinner Winner;               
    string WinnerName;
};
struct stGameResults
{
    short RoundPlayer = 0;
    short PlayerWins = 0;
    short ComputerWins = 0;
    short DrawTimes = 0;
    enWinner Winner;
    string WinnerName;
};
int ReadNumberInRange(string massege, int From, int To)
{
    int pc = 0;
    do
    {
        cout << massege << endl;
        cin >> pc;
    } while (pc < 1 || pc>10);
    return pc;
}
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}
enChoise ReadPlayerChoise()
{
    int pc = 0;
    do
    {
        cout << "Please Choose A Number [1 = Rock, 2 = Paper, 3 = Scissor]\n";
        cin >> pc;
    } while (pc < 1 || pc>3);
    return (enChoise)pc;
}
enChoise GetComputerChoise()
{
    return (enChoise)RandomNumber(1, 3);
}
string Choise(enChoise Choise)
{
    string arrChoise[3]={ "Rock","Paper","Scissor" };
    return arrChoise[Choise - 1];
}
string WinnerName(enWinner Winner)
{
    if (Winner == enWinner::Player)
        return "Player";
    else if (Winner == enWinner::Computer)
        return "Computer";
    else
        return "Draw, No Winner";
}
void ClearScreen()
{
    system("cls");
    system("color F");
}
enWinner RoundsResults(stRoundInfo RoundInfo)
{
    if (RoundInfo.ComputerChoice == RoundInfo.Player1Choice)
        return enWinner::Draw;
    switch (RoundInfo.Player1Choice)
    {
    case enChoise::Rock:
        if (RoundInfo.ComputerChoice == enChoise::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enChoise::Paper:
        if (RoundInfo.ComputerChoice == enChoise::Scissor)
        {
            return enWinner::Computer;
        }
        break;
    case enChoise::Scissor:
        if (RoundInfo.ComputerChoice == enChoise::Rock)
        {
            return enWinner::Computer;
        }
        break;
    }
    
    return enWinner::Player;
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n___________Round " << RoundInfo.RoundNumber << " Results______________________\n";
    cout << "Player Choise         : " << Choise(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choise       : " << Choise(RoundInfo.ComputerChoice) << endl;
    cout << "Winner is             : " << RoundInfo.WinnerName << endl;
    cout << "________________________________________________\n\n";
}
enWinner WhoWonTheGame(int Player, int Computer)
{
    if (Player == Computer)
        return enWinner::Draw;
    else if (Player > Computer)
        return enWinner::Player;
    else
        return enWinner::Computer;
}
stGameResults FillGameResults(int PlayerWins, int Computer, int DrawTimes, int Rounds)
{
    stGameResults GameResult;
    GameResult.PlayerWins = PlayerWins;
    GameResult.ComputerWins = Computer;
    GameResult.DrawTimes = DrawTimes;
    GameResult.RoundPlayer = Rounds;
    GameResult.Winner = WhoWonTheGame(GameResult.PlayerWins, GameResult.ComputerWins);
    GameResult.WinnerName = WinnerName(GameResult.Winner);
    return GameResult;
}
void PrintFinalResult(stGameResults Game)
{
    cout << "                           Rounds Played           : " << Game.RoundPlayer << endl;
    cout << "                           Player Win Times        : " << Game.PlayerWins << endl;
    cout << "                           Computer Win Times      : " << Game.ComputerWins << endl;
    cout << "                           Draw Times              : " << Game.DrawTimes << endl;
    cout << "                           Winner is               : " << Game.WinnerName << endl;
}
stGameResults PlayGame(int Rounds)
{
    stRoundInfo RoundInfo;
    short PlayerWins = 0, Computer = 0, DrawTimes = 0;
    for (int i = 1; i <= Rounds; i++)
    {
        cout << "Round [" << i << "] Begins\n";
        RoundInfo.Player1Choice = ReadPlayerChoise();
        RoundInfo.ComputerChoice = GetComputerChoise();
        RoundInfo.RoundNumber = i;
        RoundInfo.Winner = RoundsResults(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Computer)
        {
            system("color 4F");
            cout << "\a";
            Computer++;
        }
        else if (RoundInfo.Winner == enWinner::Player)
        {
            system("color 2F");
            PlayerWins++;
        }
        else
        {
            system("color 6F");
            DrawTimes++;
        }
        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(PlayerWins, Computer, DrawTimes, Rounds);

}
string Tabs(short tab)
{
    string t = "";
    for (int i = 0; i <= tab; i++)
    {
        t += "\t";
    }
    return t;
}
void PrintGameOverScreen()
{
    cout << Tabs(2) << "____________________________________________________________\n\n";
    cout << Tabs(2) << "                     G A M E  O V E R\n\n";
    cout << Tabs(2) << "____________________________________________________________\n\n";
}
void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ClearScreen();
        stGameResults GameResult = PlayGame(ReadNumberInRange("How Many Round You Wnat To Play From 1 To 10", 1, 10));
        PrintGameOverScreen();
        PrintFinalResult(GameResult);
        cout << "\n\n Do You Wnat To Play Again?";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}