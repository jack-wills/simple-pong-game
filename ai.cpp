//
//  ai.cpp
//  Pong
//
//  Created by Jack Williams on 17/02/2019.
//  Copyright © 2019 Jack Williams. All rights reserved.
//

#include "ai.hpp"


random_device rd; //used to obtain a seed for the random number engine
mt19937 gen(rd()); //Standard 'mersenne_twister_engine' seeded with rd()
uniform_real_distribution<> ran_ai_move(-0.13f, 0.13f); //generate a random number between -0.15 - 0.15

class ai{
public:
    ai(paddle& paddle, ball& b):
    p(paddle), ball(b){
        
    }
    void move(){
        if((ball.get_vel_x()>0)&&(ball.get_x_pos()>0)){
            if(random_flag){
                random_flag = 0;
                offset = ran_ai_move(gen);
            }
        }else{
            random_flag = 1;
        }
        if ((ball.get_vel_x()>0)&&(ball.get_x_pos()>0)){
            ball_traj = (ball.get_vel_y()*((1.45f-ball.get_x_pos())/ball.get_vel_x()))+ball.get_y_pos();
            destination = floor((ball_traj+offset)*50)/50;
            position = floor((p.get_pos())*50)/50;
            if (destination>position){
                p.move_up();
            }else if(destination<position){
                p.move_down();
            }
        }
    }
private:
    float offset;
    float ball_traj;
    float destination, position;
    bool random_flag;
    paddle& p;
    ball& ball;
};
