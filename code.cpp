#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
#include <cstdlib>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

class Games {
    public:
        Games(): player_index(0), reg_0(0), reg_1(0), reg_2(0), reg_3(0), reg_4(0), reg_5(0), reg_6(0) {}
        string gpu;
        int player_index;
        int reg_0;
        int reg_1;
        int reg_2;
        int reg_3;
        int reg_4;
        int reg_5;
        int reg_6;
        int my_dis;
        int dis1;
        int dis2;
};


void removeUnecessaryActions(vector<int> vec){
    
    auto it = find(vec.begin(), vec.end(), -1);
    while (it != vec.end())
    {
        vec.erase(it);
        it = find(vec.begin(), vec.end(), -1);
    }

}

int countOccurrences(const std::vector<int>& vec, const int target) {
    int count = 0;
    for(const auto& elem : vec) {
        if(elem == target) {
            count++;
        }
    }
    return count;
}

bool valueExists(const std::map<int, int>& myMap, const int value) {
    for (const auto& pair : myMap) {
        if (pair.second == value) {
            return true;
        }
    }
    return false;
}

int game1(Games game) {
    int my_pos;
    vector<int> possible_pos;
    int free_space = 0;

    possible_pos.push_back(game.reg_0);
    possible_pos.push_back(game.reg_1);
    possible_pos.push_back(game.reg_2);

    // lookig for the exact player.
    my_pos = possible_pos.at(game.player_index);
    cerr << "my pos: " << my_pos << endl;
    for (int i = my_pos + 1; i < game.gpu.length(); i++)
    {
        if (game.gpu.at(i) == '#')
            break;
        if (game.gpu.at(i) == '.')
            free_space++;
        // else
        //     break;
    }
    cerr << "the path: " << game.gpu << endl;
    cerr << "free space: " << free_space << endl;
    if (free_space == 0)
        return 1; // TOP
    else if (free_space == 1)
        return 4; // LEFT
    else if (free_space == 2 || free_space == 3)
        return 3; // DOWN
    else
        return 2; // RIGHT
}


int game2(Games &game, int turn, int len) {
    int wind_speed;
    int my_pos = game.player_index;
    int x,y;
    vector<int> players_cords;
    vector<vector<int>> cords;

    cerr << "game2 state: " << turn << " len: " << len << endl;
    // if (turn < (len / 3))
    //     return -1;

    players_cords.push_back(game.reg_0);
    players_cords.push_back(game.reg_1);
    players_cords.push_back(game.reg_2);
    players_cords.push_back(game.reg_3);
    players_cords.push_back(game.reg_4);
    players_cords.push_back(game.reg_5);

    for (int i = 0; i < 3; i++)
    {
        vector<int> cord;
        for (int j = 0; j < 2; j++)
        {
            if (players_cords.size() > 1)
                cord.push_back(players_cords.at(j));
            else
                cord.push_back(players_cords.at(0));
            // cerr << "--> " << players_cords.at(j) << endl;
            players_cords.erase(players_cords.begin());
        }
        cords.push_back(cord);
        cord.clear();
    }
    // cords: cords of other player exclude mine.
    if (my_pos == 0)
    {
        cords.erase(cords.begin());
        x = game.reg_0; y = game.reg_1;
        game.my_dis = sqrt(pow(x, 2) + pow(y, 2));
        game.dis1 = sqrt(pow(game.reg_2, 2) + pow(game.reg_3, 2));
        game.dis2 = sqrt(pow(game.reg_4, 2) + pow(game.reg_5, 2));
    }
    else if (my_pos == 1)
    {
        cords.erase(cords.begin() + 1);
        x = game.reg_2; y = game.reg_3;
        game.my_dis = sqrt(pow(x, 2) + pow(y, 2));
        game.dis1 = sqrt(pow(game.reg_0, 2) + pow(game.reg_1, 2));
        game.dis2 = sqrt(pow(game.reg_4, 2) + pow(game.reg_5, 2));
    }
    else
    {
        cords.erase(cords.begin() + 2);
        x = game.reg_4; y = game.reg_5;
        game.my_dis = sqrt(pow(x, 2) + pow(y, 2));
        game.dis1 = sqrt(pow(game.reg_2, 2) + pow(game.reg_3, 2));
        game.dis2 = sqrt(pow(game.reg_0, 2) + pow(game.reg_1, 2));
    }

    int res;
    int absX;
    int absY;
    if (x > 0 &&  y > 0)
        res = (x > y) ? 4 : 3;
    else if (x < 0 && y < 0)
    {
        absX = abs(x);
        absY = abs(y);

        res = (absX > absY) ? 2 : 1;
    }
    else if (x > 0 && y < 0)
    {
        absY = abs(y);
        res = (x > absY) ? 4 : 1;
    }
    else if (x < 0 && y > 0)
    {
        absX = abs(x);
        res = (absX > y) ? 2 : 3;
    }
    else 
        res = -1;
    return res; 
}

int game2_state(Games game) {
    
    if (game.my_dis > game.dis1 && game.my_dis > game.dis2)
        return 0;
    else
        return 1;
}

int game3(Games game) {
    int risk;
    vector<int> risks;

    vector <int> dirc;
    string gpu = game.gpu;
    for (int i = 0; i < gpu.length(); i++)
    {
        if (gpu.at(i) == 'U')
            dirc.push_back(1);
        else if (gpu.at(i) == 'R')
            dirc.push_back(2);
        else if (gpu.at(i) == 'D')
            dirc.push_back(3);
        else
            dirc.push_back(4);
    }

    risks.push_back(game.reg_3);
    risks.push_back(game.reg_4);
    risks.push_back(game.reg_5);

    risk = risks.at(game.player_index);

    if (risk >= 3)
        return dirc.at(0);
    else
        return dirc.at(1);
    // check for space travelled compare you with other players.
}


int game4(Games game, int turn) {

    string gpu = game.gpu;
    // for (int i = 0; i < gpu.length(); i++)
    // {
        if (gpu.at(turn) == 'U')
            return 1;
        else if (gpu.at(turn) == 'R')
            return 2;
        else if (gpu.at(turn) == 'D')
            return 3;
        else
            return 4;
    // }
}

// *******************************************************
//  1: TOP                                               *
//  2: RIGHT                                             *
//  3: DOWN                                              *
//  4: LEFT                                              *
// *******************************************************
int main()
{
    int player_idx; // which player from the 3 i am?
    cin >> player_idx; cin.ignore();
    int nb_games;
    cin >> nb_games; cin.ignore();
    int game2_turn = 0;

    vector<Games> our_games;
    int game1_res;
    int game2_res;
    int game3_res;
    int game4_res;
    int turn = 0;
    int game1_state,game2_state,game3_state,game4_state;


    map<int, int> freqs;
    vector<int> actions;
    bool pass_game2 = true;
    int lenOfGame2 = 0;

    while (1) {
        // ========================== score of each player. ====================================
            for (int i = 0; i < 3; i++) {
                string score_info;
                getline(cin, score_info);
            }
        // ========================== Fill the data ============================================
        for (int i = 0; i < nb_games; i++) {
            Games game;

            cin >> game.gpu >> game.reg_0 >> game.reg_1 >> game.reg_2 >> game.reg_3 >> game.reg_4 >> game.reg_5 >> game.reg_6; cin.ignore();
            game.player_index = player_idx;
            our_games.push_back(game);
            
        }
        // ================================================================================= End fill the data ================================

        if (pass_game2)
        {
            lenOfGame2 = our_games.at(1).gpu.length();
            pass_game2 = false;
        }
        if (turn >= our_games.at(3).gpu.length())
            turn = 0;
        if (our_games.at(1).gpu.length() <= 0)
            game2_turn = 0;
        actions.push_back(game1(our_games.at(0)));
        cerr << "after game 1" << endl;
        actions.push_back(game2(our_games.at(1), game2_turn, lenOfGame2));
        cerr << "after game 2" << endl;
        actions.push_back(game3(our_games.at(2)));
        cerr << "after game 3" << endl;
        actions.push_back(game4(our_games.at(3), turn));
        cerr << "after game 4" << endl;
        
        // remove unnecessary actions ( -1 )
        removeUnecessaryActions(actions);

        for (int i = 0; i < 4; i++)
        {
            cerr << "act: " << actions.at(i) << endl;
            // if (valueExists(freqs, actions.at(i)) == false)
            if (freqs.find(actions.at(i)) == freqs.end())
                freqs.insert(make_pair(actions.at(i), countOccurrences(actions, actions.at(i))));
        }

       int max_value = std::numeric_limits<int>::min();
       int toDo;

        for (const auto& pair : freqs) {
            if (pair.second > max_value) {
                max_value = pair.second;
                toDo = pair.first;
            }
        }



        // take the action ..............................................................
        if (toDo == 1)
            cout << "UP" << endl;
        else if (toDo == 2)
            cout << "RIGHT" << endl;
        else if (toDo == 3)
            cout << "DOWN" << endl;
        else
            cout << "LEFT" << endl;

        // analyse the states of the games.
        
        // increment turn.
        turn++;
        game2_turn++;
        // reset setting ...
        if (our_games.at(1).gpu.length() == 0)
            pass_game2 = true;
        our_games.clear();
        freqs.clear();
        actions.clear();
        // cout << "UP" << endl;
    }
}