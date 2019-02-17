//
//  paddle.cpp
//  Pong
//
//  Created by Jack Williams on 17/02/2019.
//  Copyright © 2019 Jack Williams. All rights reserved.
//

#include "paddle.hpp"


void draw_rectangle(float x, float y, float width, float height){
    glBegin(GL_POLYGON);
    glVertex2f(x-width, y+height);
    glVertex2f(x-width, y-height);
    glVertex2f(x+width, y-height);
    glVertex2f(x+width, y+height);
    glEnd();
}


class paddle{
public:
    paddle(float x, float y, float s):
    paddle_x(x), paddle_y(y), speed(s)
    {
        paddle_width = 0.05f;
        paddle_height = 0.15f;
    }
    void reset(){
        paddle_y = 0;
    }
    void draw_paddle(){
        draw_rectangle(paddle_x, paddle_y, paddle_width, paddle_height);
    }
    void move_up(){
        if(paddle_y+paddle_height < 1.f){
            paddle_y += speed;
        }
    }
    void move_down(){
        if(paddle_y-paddle_height > -1.f){
            paddle_y -= speed;
        }
    }
    float get_pos(){
        return paddle_y;
    }
private:
    float speed;
    float paddle_width;
    float paddle_height;
    float paddle_x;
    float paddle_y;
    
};
