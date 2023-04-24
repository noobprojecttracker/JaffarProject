#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>

// add timer, multiplayer functionality, track high scores, difficulty levels
// most questions answered in 1 minute
// show record between 2 users
// endless mode

using namespace std;

namespace timer
{
    auto startTime = chrono::steady_clock::now();;
    auto endTime = chrono::steady_clock::now();;
    double totalTime;
}

int ops;


// Function to generate a random integer based on the difficulty level chosen by the user
int generate_integer(int how_hard){     
    if (how_hard == 1){
        int randomInt = rand() % 10 + 1;
        return randomInt;       
    }
    else if (how_hard == 2){
        int randomInt = rand() % 30 + 1;
        return randomInt;
    }
    else{
        int randomInt = rand() % 50 + 1;
        return randomInt;
    }

}



// Function to generate a random operator for each question based off of random integer generation
int generate_operator(){
    int op = rand() % 3 + 1;
    return op;
}




// Function to generate a problem. It takes in 2 integers and generates a random operation to perform on them by calling
// to the generate_operator function to create the problem. It returns the problem generated as a string
string generate_problem(int x, int y){

    // convert the integer inputs into strings so that they can be formed into the string expression
    string ex = to_string(x);
    string why = to_string(y);

    // generate a random operator
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





// Function to quiz a player based off player's ID, the length of quiz, and the difficulty level chosen
// It quizzes the player until the desired quiz length has been reached
int quiz_player(string player_ID, int quiz_length, int how_hard){

    // default an array of size (quiz_length) which will store the correct answer for each
    // question. As we ask get user input for a question i, we check if user answer i is equal
    // to checker[i], and track their score via this method

    timer::startTime = chrono::steady_clock::now(); // gets time at start of quiz

    int checker[quiz_length];


    // default the user's score to zero
    int correct = 0;


    // set questions answered to zero as a default
    int answers = 0;

    // loop while less than (quiz_length) questions are answered, as this is a (quiz_length) question quiz
    while (answers < quiz_length){
        int num1 = generate_integer(how_hard);
        int num2 = generate_integer(how_hard);
        
        string prob = generate_problem(num1, num2);
        cout << "\n**** Question " << answers+1 << " ****" << endl;
        cout << prob << endl;
        
        // initiate this correctanswer variable each iteration of the loop to store
        // the correct answer
        int correctanswer;

        // this block of code determines what the correct answer is for the problem
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

        // set the answer for a given problem i to the checker array at index i
        checker[answers] = correctanswer;

        // initiate this user_guess variable each iteration of the loop to store
        // the user's inputted answer
        int user_guess;

        cout << "Player " << player_ID << ", what is the answer?: ";
        cin >> user_guess;

        // check if the user's guess is what it should be. if true, increment their correct answers by 1.
        if (user_guess == checker[answers]){
            correct += 1;
        }

        answers += 1;

    }

    // cout << "You got " << correct << " right";
    timer::endTime = chrono::steady_clock::now(); // gets time at end of quiz
    timer::totalTime = double (std::chrono::duration_cast <std::chrono::seconds> (timer::endTime - timer::startTime).count()); // calculates the time the quiz took
    return correct;
}


// This function prints out a message criticizing or congratulating the user
// based on the grade received on their math quiz
void evaluate_performance(int score, int questions){
    float num;
    float denom;
    num = score;
    denom = questions;
    float final;
    final = (num/denom)*100;
    if (final > 50){
        cout << "\nLooks like you scored a " << score << " out of " << questions << ". That comes out to " << setprecision(3) << final << " percent. Not bad!" << endl;
        cout << "and it only took you " << setprecision(3) << timer::totalTime << " seconds? Very well done!" << endl;
    }
    else{
        cout << "\nLooks like you need to brush up on your math skills! You scored a " << score << " out of " << questions << ". That comes out to " << setprecision(3) << final << " percent. Yikes!" << endl;
        cout << "and it took you " << setprecision(3) << timer::totalTime << " seconds? Better luck next time!" << endl;
    }
}


void welcome_screen(){
    cout << "\n***********************************************\n";
    cout << "....Welcome to the Brain Blitz Math Quiz....";
    cout << "\n...You will be evaluated on your math skills...";
    cout << "\n..................Good Luck!.................";
    cout << "\n***********************************************\n";

}



// The main function that is executed when the program runs
int main() {

    srand(time(nullptr));

    welcome_screen();


    // Determine what mode the user wants to play in
    int mode;
    cout << "\nPress 1 to play single player or 2 to play multiplayer: ";
    cin >> mode;
    while (mode != 1 && mode != 2){
        cout << "\nPlease choose between mode 1 or 2!\n";
        cout << "\n*******************************************\n";
        cout << "\nPress 1 to play single player or 2 to play multiplayer: ";
        cin >> mode;
    }


    // Block of code for single player gameplay
    if (mode == 1){
        string name;
        cout << "\n*******************************************\n";
        cout << "\nWhat is your name: ";
        cin >> name;

        int length;
        cout << "\n*******************************************\n";
        cout << "\nHow many questions do you want on the quiz " << name << "?: ";
        cin >> length;
        cout << "\n*******************************************\n";
        while (length <= 0){
            cout << "\n*******************************************\n";
            cout << "\nWe can't ask you " << length << " questions! Choose a different number: ";
            cin >> length;
            cout << "\n*******************************************\n";            
        }

        int difficulty;
        cout << "\nChoose your desired difficulty level\n" << endl;
        cout << "\n*******************************************\n";
        cout << "\nType 1 for level 1 difficulty" << endl;
        cout << "Type 2 for level 2 difficulty" << endl;
        cout << "Type 3 for level 3 difficulty" << endl;
        cout << "\n*******************************************\n";
        cout << "\nMake your choice...: ";
        cin >> difficulty;

        // This loop ensures that the user enters a difficulty level that is offered
        while (difficulty != 1 && difficulty != 2 && difficulty != 3){
            cout << "Please choose a difficulty level from the list below" << endl;
            cout << "\nType 1 for level 1 difficulty" << endl;
            cout << "Type 2 for level 2 difficulty" << endl;
            cout << "Type 3 for level 3 difficulty" << endl;
            cout << "\nMake your choice...: ";
            cin >> difficulty;        
        }

        for (int i = 3; i >= 1; i--) {
            if (i == 3){
                cout << "\nAre you ready " << name << " ?" << endl;
            }
            cout << "\n*******************************************\n";
            cout << i << " second(s) remaining..."  << endl;
            cout << "\n*******************************************\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        cout << "\nTime's up! Good luck " << name << endl;

        int score = quiz_player(name, length, difficulty);

        cout << "\n*******************************************\n";
        evaluate_performance(score, length);

    }





    // Block of code for 1 vs 1 game mode
    else if (mode == 2){

        cout << "\nGood choice..." << endl;

        int length;
        cout << "\n*******************************************\n";
        cout << "How many questions do you want on the quiz?: ";
        cin >> length;
        cout << "\n*******************************************\n";
        while (length <= 0){
            cout << "\n*******************************************\n";
            cout << "We can't ask you " << length << " questions! Choose a different number: ";
            cin >> length;
            cout << "\n*******************************************\n";            
        }

        // Declare the difficulty variable to store the difficulty level chosen by the user
        // which will then be fed into other functions as arguments
        int difficulty;

        cout << "\nChoose your desired difficulty level\n" << endl;
        cout << "\n*******************************************\n";
        cout << "\nType 1 for level 1 difficulty" << endl;
        cout << "Type 2 for level 2 difficulty" << endl;
        cout << "Type 3 for level 3 difficulty" << endl;
        cout << "\n*******************************************\n";
        cout << "\nMake your choice...: ";
        cin >> difficulty;
        // This loop ensures that the user enters a difficulty level that is offered
        while (difficulty != 1 && difficulty != 2 && difficulty != 3){
            cout << "\nPlease choose a difficulty level from the list below" << endl;
            cout << "\n*******************************************\n";
            cout << "\nType 1 for level 1 difficulty" << endl;
            cout << "Type 2 for level 2 difficulty" << endl;
            cout << "Type 3 for level 3 difficulty" << endl;
            cout << "\n*******************************************\n";
            cout << "\nMake your choice...: ";
            cin >> difficulty;        
        }

        // This string will store the winner's name, it is initalized as empty
        string winner = "";

        // Collect the names of the users
        string player_one_name = "";
        cout << "\n*******************************************\n";
        cout << "Enter player 1's name: ";
        cin >> player_one_name;
        cout << "\n*******************************************\n";
        cout << "Welcome to the duel " << player_one_name << endl;

        string player_two_name = "";
        cout << "\n*******************************************\n";
        cout << "Enter player 2's name: ";
        cin >> player_two_name;  
        cout << "\n*******************************************\n";
        // This loop ensures that 2 users can not have the same display name
        while (player_two_name == player_one_name){
            cout << "Player 2, please choose a name different than your opponent's!: ";
            cout << "\n*******************************************\n";
            cin >> player_two_name;
        }
        cout << "Welcome to the duel " << player_two_name << endl;


        // This block of code quizzes both players by calling to other functions
        // and then prints out their respective scores and determines the winner

        for (int i = 3; i >= 1; i--) {
            if (i == 3){
                cout << "\nAre you ready " << player_one_name << " ?" << endl;
            }
            cout << "\n*******************************************\n";
            cout << i << " second(s) remaining..."  << endl;
            cout << "\n*******************************************\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        cout << "\nTime's up! Good luck " << player_one_name << endl;


        int player_one_score = quiz_player("one", length, difficulty);
        cout << "..." << endl;
        cout << "\n*******************************************\n";
        cout << "Congrats " << player_one_name << ", you got a " << player_one_score << " out of " << length << endl;
        this_thread::sleep_for(chrono::seconds(3));
        cout << "\n*******************************************\n";

        this_thread::sleep_for(chrono::seconds(2));
        cout << "Now let's see what " << player_two_name << " can do..." << endl;
        cout << "\n*******************************************\n";
        this_thread::sleep_for(chrono::seconds(2));


        for (int i = 3; i >= 1; i--) {
            if (i == 3){
                cout << "\nAre you ready " << player_two_name << " ?" << endl;
            }
            cout << "\n*******************************************\n";
            cout << i << " second(s) remaining..."  << endl;
            cout << "\n*******************************************\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        cout << "\nTime's up! Good luck " << player_two_name << endl;


        int player_two_score = quiz_player("two", length, difficulty);
        cout << "..." << endl;
        cout << "\n*******************************************\n";
        cout << "Congrats " << player_two_name << ", you got a " << player_two_score << " out of " << length << endl;
        this_thread::sleep_for(chrono::seconds(3));
        cout << "\n*******************************************\n";
        cout << "..." << endl;
        if (player_one_score > player_two_score){
            winner = player_one_name;
            cout << "\n*******************************************\n";
            cout << "Congratulations to " << winner << " for winning!";
            cout << "\n*******************************************\n";
        }
        else if (player_one_score < player_two_score){
            winner = player_two_name;
            cout << "\n*******************************************\n";
            cout << "Congratulations to " << winner << " for winning!";
            cout << "\n*******************************************\n";
        }
        else{
            cout << "\n*******************************************\n";
            cout << "It was a draw! How boring!";
            cout << "\n*******************************************\n";
        }
        
    }


    return 0;
}