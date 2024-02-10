#include <iostream>
#include <cstdlib>
#include <ctime>

#include "team.h"

int Sim(const int s1, const int s2){

    // Skill Difference
    double chance = static_cast<double>(50 + (s1-s2)) / 100.0;

    // Generate random variable between 0 and 1
    double r = static_cast<double>(rand()) / RAND_MAX;

    // If r less then defined chance, player 1 wins
    return r < chance ? 0 : 1;
}

int Process(){

    // Set seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Define Teams
    Team t1(10);
    Team t2(90); //Better skilled

    // Define counts
    int t1_wins = 0;
    int t2_wins = 0;
    int n_games = 100;

    //Simulation loop
    for (int i = 0; i < n_games; ++i){
        int winner = Sim(t1.getSkillStat(), t2.getSkillStat());
        if (winner == 0)
            t1_wins++;

        else 
            t2_wins++;
    }

    std::cout << "Results after " << n_games << " games:\n";
    std::cout << "Agent 1 wins: " << t1_wins << "\n";
    std::cout << "Agent 2 wins: " << t2_wins << "\n";

    // std::cout << t1.getSkillStat() << std::endl;
    // std::cout << t2.getSkillStat() << std::endl;

    system("pause");

    return 0;
}
