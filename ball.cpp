//
//  ball.cpp
//  Pong
//
//  Created by Jack Williams on 17/02/2019.
//  Copyright © 2019 Jack Williams. All rights reserved.
//

#include "ball.hpp"

class ball{
public:
    ball(paddle& p1, paddle& p2):
    paddle1(p1), paddle2(p2)
    {
        radius = 0.05f;
        x = 0.f;
        y = 0.f;
        vel_x = -0.02f;
        vel_y = 0.f;
    }
    void reset(){
        radius = 0.05f;
        x = 0.f;
        y = 0.f;
        vel_x = -0.02f;
        vel_y = 0.f;
    }
    void draw_ball(){
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center of circle
        for(int i = 0; i <= tri_num;i++) {
            glVertex2f(x + (radius * cos(i *  two_pi / tri_num)),
                       y + (radius * sin(i * two_pi / tri_num))
                       );
        }
        glEnd();
    }
    void update_vel(){
        paddle1_diff = y - paddle1.get_pos();
        paddle2_diff = y - paddle2.get_pos();
        if (x+radius > 1.45f && x < 1.55f){ //Player 2 collision
            if((paddle2_diff>-0.15f)&&(paddle2_diff<0.15f)){
                vel_y += paddle2_diff/10;
                vel_x *= -1.f;
            }
        }else if(x-radius < -1.45f && x > -1.55){ //Player 1 collision
            if((paddle1_diff+radius>-0.15f)&&(paddle1_diff-radius<0.15f)){
                vel_y += paddle1_diff/10;
                vel_x *= -1.f;
            }
        }
        if((y+radius >= 1.f)||(y-radius <= -1.f)){
            vel_y *= -1.f;
        }
    }
    void update_pos(){
        time = glfwGetTime();
        dt = time - prev_time;
        x += vel_x;
        y += vel_y;
        prev_time = time;
    }
    float get_x_pos(){
        return x;
    }
    float get_y_pos(){
        return y;
    }
    float get_vel_x(){
        return vel_x;
    }
    float get_vel_y(){
        return vel_y;
    }
private:
    float radius;
    float vel_x,vel_y;
    float x,y;
    float prev_time, time, dt;
    float paddle1_diff,paddle2_diff;
    int tri_num = 20;
    const float two_pi = M_PI*2;
    paddle& paddle1;
    paddle& paddle2;
};
