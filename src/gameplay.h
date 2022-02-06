#include "main.h"

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

// just creating the functions

class HUD {
public:

    glm::vec3 position;
    int timer;
    int health;
    
    HUD() {}
    HUD(color_t color,int num_powerups);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    
    void affectHealth(int prevhealth);
    int getHealth();

    int task;
    int num_powerups;
    int num_powerups_collected;
    bool imposterAlive;
    void collectPowerUP();
    void killImposter();
    void TaskComplete();


private:
    VAO *object; 
};

#endif // GAMEPLAY_H
