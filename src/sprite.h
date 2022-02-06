#include "main.h"
#include "maze.h"

#ifndef SPRITE_H
#define SPRITE_H

// just creating the functions

class Sprite {
public:
    glm::vec3 position;
    float rotation;
    float width;
    float height;
    Sprite() {}
    Sprite(float x, float y, color_t color);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_position(float x, float y);
    glm::vec3 give_position();
    void chase_Crewmate(Maze *maze, glm::vec3 destination);
    void kill_Crewmate();
    bool hasMurdered = false;

    bool Exit();

    void tick();
    double speed;
private:
    VAO *body; 
    VAO *glasses; 
    VAO *head; 
    VAO *rleg; 
    VAO *lleg; 
    VAO *backpack; 

};

#endif // SPRITE_H
