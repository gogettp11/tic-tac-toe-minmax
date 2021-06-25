#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string>
#include<stack>
#include<queue>
#include <time.h>
using namespace std;

class Game{
    vector<string> board;
    stack<pair<int,int>> move_history;
    char player_1, player_2;
    char current_player;
    private:
        void nextPlayer(){
            if(current_player==player_1)
                current_player = player_2;
            else
                current_player = player_1;
        }
        bool isDraw(){
            if(board[0].find('-') == std::string::npos&&board[1].find('-') == std::string::npos&&board[2].find('-') == std::string::npos)
                return true;
            else
                return false;
        }
    public:
        Game(char &&player_1, char &&player_2){
            for(int i = 0;i < 3; i++)
                board.push_back("---");
            this->player_1 = player_1;
            this->player_2 = player_2;
            srand(time(NULL));
            current_player = rand()%2 ? player_1 : player_2;
        }
        bool isEnd(){
            if(board[0].find('-') == std::string::npos&&board[1].find('-') == std::string::npos&&board[2].find('-') == std::string::npos)
                return true;
            else if (board[0][0] !='-'&&board[0][0] == board[0][1] && board[0][1] == board[0][2])
                return true;
            else if (board[1][0] !='-'&&board[1][0] == board[1][1] && board[1][1] == board[1][2])
                return true;
            else if (board[2][0] !='-'&&board[2][0] == board[2][1] && board[2][1] == board[2][2])
                return true;
            else if (board[0][0] !='-'&&board[0][0] == board[1][0] && board[1][0] == board[2][0])
                return true;
            else if (board[0][1] !='-'&&board[0][1] == board[1][1] && board[1][1] == board[2][1])
                return true;
            else if (board[0][2] !='-'&&board[0][2] == board[1][2] && board[1][2] == board[2][2])
                return true;
            else if (board[0][0] !='-'&&board[0][0] == board[1][1] && board[1][1] == board[2][2])
                return true;
            else if (board[0][2] !='-'&&board[0][2] == board[1][1] && board[1][1] == board[2][0])
                return true;
            else
                return false;
        }
        bool makeMove(int x,int y){
            if(board[y][x]=='-'){
                board[y][x]=this->current_player;
                move_history.push(make_pair(x,y));
                this->nextPlayer();
                return true;
            }else
                return false;
        }
        pair<int,int> undo(){
            pair<int,int> &last_move = move_history.top();
            move_history.pop();
            board[last_move.second][last_move.first] = '-';
            nextPlayer();
            return last_move;
        }
        pair<int,int> getLastMove(){
            return move_history.top();
        }
        string toString(){
            string str;
            for(int i = 0; i < board.size(); i++){
                str.append(board[i]+'\n');
            }
            return str;
        }
        vector<pair<int,int>> getPossibleMoves(){
            vector<pair<int,int>> possible_moves;
            for(int x = 0; x < 3; x++){
                for(int y = 0; y < 3; y++){
                    if(board[y][x])
                        possible_moves.push_back(make_pair(x,y));
                }
            }
            return possible_moves;
        }
        char getScore(){
            if(this->isEnd())
        }
};
enum value : int8_t{
    win1 = -1,
    draw = 0,
    win0 = 1
};
// x , y , score
tuple<int,int,value> minimax(bool is_maximizing, Game &game){
    if(game.isEnd()){
        pair<int,int> move = game.getLastMove();
        return make_tuple(move.first,move.second,);
    }
    vector<pair<int,int>> possible_moves = game.getPossibleMoves();
    if(is_maximizing){
        tuple<int,int,value> val = make_tuple(0,0,value::win1);
        for(int i = 0; i < possible_moves.size();i++){
            tuple<int,int,value> temp_val = minimax(!is_maximizing,game);
            val = get<2>(val)>get<2>(temp_val) ? val : temp_val;
            game.undo();
        }
    }else{
        tuple<int,int,value> val = make_tuple(0,0,value::win0);
        for(int i = 0; i < possible_moves.size();i++){
            tuple<int,int,value> temp_val = minimax(!is_maximizing,game);
            val = get<2>(val)<get<2>(temp_val) ? val : temp_val;
            game.undo();
        }
    }
}

int main(){
    
    Game game('x','o');
    bool maximizing = true;
    cout << game.toString();
    while(game.isEnd()){
        Game copy_game = game;  //copying game
        tuple<int,int,int> move = minimax(maximizing, copy_game);
        game.makeMove(get<1>(move),get<0>(move));
        maximizing = !maximizing;
        cout << game.toString();
    }
    cout << "game ends here" << endl;
}