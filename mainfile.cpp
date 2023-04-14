#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <ctime>

// add timer, multiplayer functionality, track high scores, difficulty levels
// most questions answered in 1 minute

using namespace std;

int ops;

int generate_integer(){
    int randomInt = rand() % 30 + 1;
    return randomInt;
}

int generate_operator(){
    int op = rand() % 3 + 1;
    return op;
}

string generate_problem(int x, int y){

    string ex = to_string(x);
    string why = to_string(y);

    ops = generate_operator();



    string ans;
    ans += "What is ";
    ans += ex;
    switch (ops){
        case 1:
        ans += " + ";
        break;
        case 2:
        ans += " - ";
        break;
        case 3:
        ans += " * ";
        break;
    }
    ans += why;
    ans += "?: ";
    return ans;
}





int quiz_player(string player_number){
    int checker[10] = {};

    int correct = 0;


    // set questions answered to zero
    int answers = 0;

    // loop while less than 10 questions are answered, as this is a 10 question quiz
    while (answers < 10){
        int num1 = generate_integer();
        int num2 = generate_integer();
        
        string prob = generate_problem(num1, num2);
        cout << prob << endl;
        
        int correctanswer;

        switch (ops){
        case 1:
        correctanswer = num1 + num2;
        break;
        case 2:
        correctanswer = num1 - num2;
        break;
        case 3:
        correctanswer = num1 * num2;
        break;

    }

        checker[answers] = correctanswer;

        int user_guess;

        cout << "Player " << player_number << ", what is the answer?: ";
        cin >> user_guess;

        if (user_guess == checker[answers]){
            correct += 1;
        }

        answers += 1;

    }

    cout << "You got " << correct << " right";

    return correct;
}





int main() {

    srand(time(nullptr));

    int mode;
    cout << "Press 1 to play single player or 2 to play multiplayer: ";
    cin >> mode;

    if (mode == 1){
        quiz_player("one");
    }
    else if (mode == 2){

        string winner = "";

        string player_one_name = "";
        cout << "Enter player 1's name: ";
        cin >> player_one_name;

        string player_two_name = "";
        cout << "Enter player 2's name: ";
        cin >> player_two_name;  

        int player_one_score = quiz_player("one");
        cout << "..." << endl;
        cout << "Congrats " << player_one_name << ", you got a " << player_one_score << endl;
        cout << "Let's see what player 2 can do..." << endl;
        cout << "..." << endl;
        int player_two_score = quiz_player("two");
        cout << "..." << endl;
        cout << "Congrats " << player_two_name << ", you got a " << player_two_score << endl;
        cout << "..." << endl;
        if (player_one_score > player_two_score){
            winner = player_one_name;
            cout << "Congratulations to " << winner << " for winning!";
        }
        else if (player_one_score < player_two_score){
            winner = player_two_name;
            cout << "Congratulations to " << winner << " for winning!";
        }
        else{
            cout << "It was a draw!";
        }

        
    }



    
    return 0;
}