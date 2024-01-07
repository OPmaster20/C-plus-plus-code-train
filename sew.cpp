#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <cmath>
#define random(x) (rand()%x)

#define state_code_s 200;
#define state_code_o 300;
#define chance_number 3;

#define ability 4;

// <Increase chance>
// <Random location transfer>
// <Increase score>
// <Change occupation> -- <Warrior； Wizard； ninja；>

using namespace std;

class ground{
    private:
        int point_w;
        int point_h;
        int end_w;
        int end_h;
        void set_point(){
            point_h = (random(10));
            point_w = (random(10));
            end_h = (random(10));
            end_w = (random(10));
        }
       
    public:
        int w;
        int h;
        char gb[10][10];
        void init_ground(){
            this -> set_point();
            //cout << this ->  point_w << " and " << this ->  point_h << endl;
            //cout << this ->  end_w << " and " << this ->  end_h << endl;
            //comfirm_location();
            for(int i = 0; i < h; i++){
                for(int j  = 0; j < w; j++){
                    gb[i][j] = ' ';
                }
            }
            gb[this -> point_w][this -> point_h] = 'S';
            gb[this -> end_w][this -> end_h] = 'D';
            
        }
        
        void set_wall(int wall){
            int i = 0;
            while(1){
                int x = random(10);
                int y = random(10);
                if(gb[x][y] == ' '){
                    gb[x][y] = '#';
                    i++;
                }
                if(i == wall){
                    break;
                }
                
            }
            
            set_Rewards();
        }
        
        void set_Rewards(){
            int i = 0;
            int k = ability;
            while(i < k){
                int x = random(10);
                int y = random(10);
                if(gb[x][y] == ' '){
                    gb[x][y] = 'R';
                    i++;
                }else{
                    continue;
                }
            }
        }
        
        char get_gb_location(int x, int y){
            return gb[x][y];
        }

        void comfirm_location(){
            for(int i = 0; i < h; i++){
                for(int j = 0; j < w; j++){
                    if(gb[i][j] == 'S'){
                         this -> point_w = i;
                         this -> point_h = j;
                         cout << this -> point_w << " " << this -> point_h << endl;
                         break;
                    }
                }
            }
            
        
        }
        
        int move_check(char act){
            char act_unit[4] = {'w','a','s','d'};
            for(int i = 0; i < 4; i++){
                if(act == act_unit[i]){
                    return 1;
                }  
            }
            return 0;
        }
        
        int steps_check(int n){
            if(n <= 10){
                return 1;
            }
            return 0;
            
        }
        
        void print_ground(){
            for(int i = 0; i < w; i++){
                for(int j = 0; j < h; j++){
                    cout << gb[i][j] << " ";
                }
                cout << endl;
            }
            create();
        }
        
        void print_ground_process(){
            //cout << gb[this -> point_w][this -> point_h] << endl;
            for(int i = 0; i < w; i++){
                for(int j = 0; j < h; j++){
                    cout << gb[i][j] << " ";
                }
                cout << endl;
            }
        }
        
        int get_init_point_x(){
            //cout << this -> point_w << "<-" << endl;
            return this -> point_w;
        }
        
        int get_init_point_y(){
            //cout << this -> point_h << "<-" << endl;
            return this -> point_h;
        }
        
        void reset_init_point(int x,int y){
            this -> point_w = x;
            this -> point_h = y;
            //print_ground_process();
        }
        
        void reset_gb(int x, int y){
            cout << x << " " << y << endl;
            gb[x][y] = 'S';
            
            cout << gb[x][y] << "It is already seted" << endl;
            reset_init_point(x,y);
            
        }
        
        void transfer_location(){
            while(1){
                int x = random(10);
                int y = random(10);
                if(gb[x][y] == ' '){
                   reset_gb(x,y);
                }else{
                    continue;
                }
            }
        }
        
        static void create(){
            cout << " <create sccuess> " << endl;
        }
    
};

class obj{
    private:
        string obj_name;
    public:
        char move;
        int step;
        int chance;
        int state_code;
        int score;
        
        void check_chance(int n,string player){
            if(n == 0){
                this -> game_out();
            }else{
                this -> obj_name = player;
            }
            
        }
        
        int get_score(){
            return score;
        }
        
        void set_score(int n){
            score = score + n;
        }
        
        void set_chance(int k){
            chance = chance + k;
        }
        void set_name(string name){
            this -> obj_name = name;
        }
        
        string return_name(){
            return this -> obj_name;
        }
        
        static void game_out(){
            cout << " <game over> " << endl;
            cout << " <You have failed! > " << endl;
        }
        
        void game_win(){
            cout << " <game win> " << endl;
            cout << " <Next! >> > " << endl;
            score = score + 1;
        }
        
        static void game_start(){
            cout << " <game start> " << endl;
        }
        
        void welcome(){
            cout << " <welcome! player - " << this -> obj_name << ">" << endl;
        }
    
};

class occupation{
    public:
        string occ_name;
        
        static void prompt(){
            cout << " Warning : your occupation is change" << endl;
        }
};

class operation_ground : public ground, public obj, public occupation {
    public:
        int locat_x;
        int locat_y;
        int real_x;
        int real_y;

        int check_board_gross(int x0, int y0, char act){
            if(act == 'w'){
                if(check_board_w(x0,y0)){
                    return 1;
                }
            }
            else if(act == 'a'){
                if(check_board_a(x0,y0)){
                    return 1;
                }
            }
            else if(act == 's'){
                if(check_board_s(x0,y0)){
                    return 1;
                }
            }
            else{
                if(check_board_d(x0,y0)){
                    return 1;
                }
            }

            return 0;
        }

        int check_board_w(int x, int y){
            int x0 = real_x;
            if(x0 > x){
                while(x0 >= x){
                    if(ground::get_gb_location(x0,y) == '#'){
                        return 0;
                    }
                    x0--;
                }
            }else{
                while(x0 <= x){
                    if(ground::get_gb_location(x0,y) == '#'){
                        return 0;
                    }
                    x++;
                }
            }
            return 1;
        }

        int check_board_a(int x, int y){
            int y0 = real_y;
            if(y0 > y){
                while(y0 >= y){
                    if(ground::get_gb_location(x,y0) == '#'){
                        return 0;
                    }
                    y0--;
                }
            }else{
                while(y0 <= y){
                    if(ground::get_gb_location(x,y0) == '#'){
                        return 0;
                    }
                    y0++;
                }
            }
            
            return 1;
        }

        int check_board_s(int x, int y){
            int x0 = real_x;
            if(x0 > x){
                while(x0 >= x){
                    if(ground::get_gb_location(x0,y) == '#'){
                        return 0;
                    }
                    x0--;
                }
            }else{
                while(x0 <= x){
                    if(ground::get_gb_location(x0,y) == '#'){
                        return 0;
                    }
                    x0++;
                }
            }
            
            return 1;
        }

        
        int check_board_d(int x, int y){
            int y0 = real_y;
            if(y0 > y){
                while(y0 >= y){
                    if(ground::get_gb_location(x,y0) == '#'){
                        return 0;
                    }
                    y0--;
                }
            }else{
                while(y0 <= y){
                    if(ground::get_gb_location(x,y0) == '#'){
                        return 0;
                    }
                    y0++;
                }
            }
            return 1;
        }

        char check_ifend(char location){
            if(location == 'D'){
                return 'y';
            }
            return 'n';
        }
        
        char check_ifwall(char location){
            cout << location << endl;
            if(location == '#'){
                return 'y';
            }
            return 'n';
            
        }
        
        char random_reward(){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0,4);
            
            const int a = ability;
            char reward[a] = {'c','r','s','o'};
            return reward[dist(gen)];
            
        }
        
        
        void check_reward(char location){
            if(location == 'R'){
                char fin = random_reward();
                if(fin == 'c'){
                    int k = obj::chance;
                    obj::set_chance(k);
                }
                else if(fin == 's'){
                    obj::set_score(1);
                }
                else if(fin == 'r'){
                    ground::transfer_location();
                }else{
                    occupation::prompt();
                }
            }
            
        }
        
        
        char verify(int x, int y, char act,int step){
            locat_x = x;
            locat_y = y;
            if(act == 'w'){
                check_reward(ground::get_gb_location(locat_x - step,locat_y));
                if(check_ifwall(ground::get_gb_location(locat_x - step,locat_y)) == 'n'){
                    return 'y';
                }
                if(check_ifend(ground::get_gb_location(locat_x - step,locat_y)) == 'y'){
                    return 'x';
                }
            }
            
            if(act == 'a'){
                check_reward(ground::get_gb_location(locat_x,locat_y  - step));
                if(check_ifwall(ground::get_gb_location(locat_x,locat_y  - step)) == 'n'){
                    return 'y';
                }
                if(check_ifend(ground::get_gb_location(locat_x,locat_y  - step)) == 'y'){
                    return 'x';
                }
            }
            
            if(act == 's'){
                check_reward(ground::get_gb_location(locat_x + step,locat_y));
                if(check_ifwall(ground::get_gb_location(locat_x + step,locat_y)) == 'n'){
                    return 'y';
                }
                if(check_ifend(ground::get_gb_location(locat_x + step,locat_y)) == 'y'){
                    return 'x';
                }
            }
            
            if(act == 'd'){
                check_reward(ground::get_gb_location(locat_x,locat_y + step));
                if(check_ifwall(ground::get_gb_location(locat_x,locat_y + step)) == 'n'){
                    return 'y';
                }
                if(check_ifend(ground::get_gb_location(locat_x,locat_y + step)) == 'n'){
                    return 'x';
                }
            }
            
            return 'n';
        }

        void real_local_x(int x){
            real_x = x;

        }

        void real_local_y(int y){
            real_y = y;
        }

        int get_real_local_x(){
            return real_x;
        }

        int get_real_local_y(){
            return real_y;
        }

        int operate_gb(int x,int y,char act,int step){
            if(verify(x,y,act,step) == 'y'){
                //cout << locat_x << "+ and +" << locat_y << endl;
                if(act == 'w'){
                   
                   // if(check_board_w(locat_x - step,locat_y)){
                        real_local_x(locat_x - step);
                        real_local_y(locat_y);
                        return 1;
                   // }
                   // return 4;
                    
                }else if(act == 'a'){
                  
                    //if(check_board_a(locat_x,locat_y - step)){
                        real_local_x(locat_x);
                        real_local_y(locat_y - step);
                        return 1;
                    //}
                    //return 4;
                }else if(act == 's'){
             
                   // if(check_board_s(locat_x + step,locat_y)){
                        real_local_x(locat_x + step);
                        real_local_y(locat_y);
                        return 1;
                   // }
                   // return 4;
                    
                }else{
                   
                   // if(check_board_d(locat_x,locat_y + step)){
                        real_local_x(locat_x);
                        real_local_y(locat_y + step);
                        return 1;
                    //}
                    //return 4;
                    
                }
                return 1;
            }
            if(verify(x,y,act,step) == 'x'){
                return 3;
            }
            return 0;
            
        }
    
};

class person : public obj{
    public:
        string skills;
        string occupation;
        
        void init_player(){
            occupation = "civilian";
            skills = "NULL";
            obj::chance = chance_number;
            obj::state_code = state_code_s;
            obj::step = 0;
            obj::move = '_';
            obj::score = 0;
        }
        
        void player_infor(){
            cout << "-----------------------------------------------------------" << endl;
            cout << "|< Player: " << obj::return_name() << "                    |" << endl;
            cout << "| Chance: " << obj::chance << "                            |" << endl;
            cout << "| Score: " << obj::score << "                              |" << endl;
            cout << "| Occupation: " << occupation << "                         |" << endl;
            cout << "| Skill: " << skills << " " << ">                          |" << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
        
        int get_chance(){
            int k = obj::chance;
            return k;
        }
        
        char get_move(){
            return obj::move;
        }
        
        void set_chance(int n){
            obj::chance = n;
        }
        
        void set_move(char n){
            obj::move = n;
            
        }
        
        void get_win_fun(){
            obj::game_win();
        }
        
        static void prompt(){
            cout << "you can input direction and steps " << endl;
        }

        static void prompt_outboard(){
            cout << "Can't moving! " << endl;
        }
        
};

int check_commend(string lines){
    if(lines == "yes" || lines == "y" ){
        return 1;
    }else{
        return 0;
    }
}

string input_name(){
    string player_name;
    cout << "input player name: ";
    cin >> player_name;
    return player_name;
}

char play_acts(){
    char act;
    cout << "Direction: ";
    cin >> act;
    return act;
}

int play_steps(){
    int step;
    cout << "steps: ";
    cin >> step;
    return step;
}

int judgment(int chance){
    if(chance == 0){
        return 0;
    }
    return 1;
    
}

int main()
{
    ground gd;
    operation_ground op_gd;
    srand((int)time(0));
    gd.h = 10;
    gd.w = 10;
    int wall_number;
    string commed;
    cout << "Input wall number:";
    std::cin >> wall_number;
    gd.init_ground();
    gd.set_wall(wall_number);
    gd.print_ground();
    cout << "--------------review---------------" << endl;
    
    person player1;
    player1.set_name(input_name());
    player1.welcome();
    player1.init_player();
    player1.game_start();
    gd.print_ground();
    player1.player_infor();
    
    while(1){
        int x1 = gd.get_init_point_x();
        int y1 = gd.get_init_point_y();

        player1.prompt();
        char move_act = play_acts();
        if(gd.move_check(move_act) == 0){
            continue;
        }
        int step_number = play_steps();
        if(gd.steps_check(step_number) == 0){
            continue;
        }
        int state = op_gd.operate_gb(x1,y1,move_act,step_number);
        if(state == 0){
            //gd.print_ground();
            //op_gd.operate_gb(move_act,step_number);
            int k = player1.get_chance();
            player1.set_chance(k - 1);
            player1.player_infor();
            gd.print_ground_process();
        }
        if(state == 1){
            int x = op_gd.get_real_local_x();
            int y = op_gd.get_real_local_y();
            //gd.print_ground_process();
            if (op_gd.check_board_gross(x1,y1,move_act)){
                gd.reset_init_point(x,y);
                gd.gb[x1][y1] = ' ';
                gd.gb[x][y] = 'S';
                gd.print_ground_process();
            //op_gd.operate_gb(move_act,step_number);
                player1.set_move(move_act);
            //cout << player1.get_move() << endl;
                player1.player_infor();
            }else{
                player1.prompt_outboard();
            }
            
            
        }
        
        if(state == 3){
            player1.get_win_fun();
        }

        if(judgment(player1.get_chance()) == 0){
            player1.game_out();
            break;
        }
        
        
        
    }
    
    
    //player1.prompt();
    return 0;
}
