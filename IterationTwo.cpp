#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <ctime>

// add timer, multiplayer functionality, track high scores, difficulty levels
// most questions answered in 1 minute
// show record between 2 users

using namespace std;

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

    cout << "You got " << correct << " right";

    return correct;
}






// The main function that is executed when the program runs
int main() {

    srand(time(nullptr));

    int mode;
    cout << "Press 1 to play single player or 2 to play multiplayer: ";
    cin >> mode;

    if (mode == 1){
        string name;
        cout << "What is your name: ";
        cin >> name;
        int length;
        cout << "How many questions do you want on the quiz?: ";
        cin >> length;
        int difficulty;
        cout << "Choose your desired difficulty level..." << endl;
        cout << "Type 1 for level 1 difficulty" << endl;
        cout << "Type 2 for level 2 difficulty" << endl;
        cout << "Type 3 for level 3 difficulty" << endl;
        cout << "Make your choice...: ";
        cin >> difficulty;
        quiz_player(name, length, difficulty);
    }
    else if (mode == 2){

        int length;
        cout << "How many questions do you want on the quiz?: ";
        cin >> length;

        int difficulty;
        cout << "Choose your desired difficulty level" << endl;
        cout << "Type 1 for level 1 difficulty" << endl;
        cout << "Type 2 for level 2 difficulty" << endl;
        cout << "Type 3 for level 3 difficulty" << endl;
        cout << "Make your choice...: ";
        cin >> difficulty;

        string winner = "";

        string player_one_name = "";
        cout << "Enter player 1's name: ";
        cin >> player_one_name;

        string player_two_name = "";
        cout << "Enter player 2's name: ";
        cin >> player_two_name;  

        int player_one_score = quiz_player("one", length, difficulty);
        cout << "..." << endl;
        cout << "Congrats " << player_one_name << ", you got a " << player_one_score << endl;
        cout << "Let's see what player 2 can do..." << endl;
        cout << "..." << endl;
        int player_two_score = quiz_player("two", length, difficulty);
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
