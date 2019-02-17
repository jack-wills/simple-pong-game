//
//  main.cpp
//  Pong
//
//  Created by Jack Williams on 05/12/2017.
//  Copyright © 2017 Jack Williams. All rights reserved.
//

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool paddle1_up_flag, paddle1_down_flag, pause_flag, exit_flag = 0;

static void glfwError(int id, const char* description){
    std::cout << description << std::endl;
}
class scoreboard{
    
};

class game{
public:
    game(GLFWwindow* win, paddle& paddle1, paddle& paddle2, ai& pl2, ball& b):
    window(win), p1(paddle1), p2(paddle2), player2(pl2), ball(b)
    {
        glfwMakeContextCurrent(window);
        glfwSwapInterval( 1 );
        // set up view
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        ratio = width / (float) height;
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    void update_board(){
        if(paddle1_up_flag){
            p1.move_up();
        }
        if(paddle1_down_flag){
            p1.move_down();
        }
        player2.move();
        p1.draw_paddle();
        p2.draw_paddle();
        ball.update_pos();
        ball.update_vel();
        ball.draw_ball();
    }
    void check_game_over(){
        if((ball.get_x_pos()>1.6f) || (ball.get_x_pos()<-1.6f)){
            p1.reset();
            p2.reset();
            ball.reset();
        }
    }
private:
    GLFWwindow* window;
    paddle& p1;
    paddle& p2;
    ai& player2;
    ball& ball;
};


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS){
        paddle1_up_flag = 1;
    }else if(key == GLFW_KEY_UP && action == GLFW_RELEASE){
        paddle1_up_flag = 0;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        paddle1_down_flag = 1;
    }else if(key == GLFW_KEY_DOWN && action == GLFW_RELEASE){
        paddle1_down_flag = 0;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        if(pause_flag){
            pause_flag = 0;
        }else{
            pause_flag = 1;
        }
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        exit_flag = 1;
    }
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glfwSetErrorCallback(&glfwError);
    if (!glfwInit()) {
        cout << "glfw did not initialize!" << endl;
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(700, 400, "Pong", NULL, NULL);
    if (!window) {
        cout << "window == null" << endl;
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);
    paddle p1(-1.5f, 0.f, 0.02f);
    paddle p2(1.5f, 0.f, 0.02f);
    ball ball(ref(p1), ref(p2));
    ai player2(ref(p2), ref(ball));
    game game1(ref(window), ref(p1), ref(p2), ref(player2), ref(ball));
    long long frames = 0;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (!glfwWindowShouldClose(window) && !exit_flag) {
        glClear(GL_COLOR_BUFFER_BIT);
        while(pause_flag){
            glfwPollEvents();
        }
        game1.check_game_over();
        game1.update_board();
        glfwSwapBuffers(window);
        glfwPollEvents();
        frames++;
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>( t2 - t1 ).count()/1000000;
        if(duration > 0){
            cout << "FPS = " << frames/duration << endl;
        }
    }
    glfwTerminate();
}
