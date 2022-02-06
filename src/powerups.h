#include "main.h"
#include "gameplay.h"

#ifndef POWERUPS_H
#define POWERUPS_H

// button, powerups and obstacles are all created with the same class PowerUps

class Powerup {
public:
    
    glm::vec3 position;
    float width;
    float height;
    
    // type -1 = imposter button, 0 = powerup button, 1 is powerup, 2 is obstacle
    int type;
    Powerup() {}
    Powerup(int type,float x, float y, color_t color);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    
    bool isActive;
    bool canActivateTask;
    void Activate(bool activate);
    void ActivateTask(bool canActivateTask);

    void checkActivation(HUD* hud, glm::vec3 crewmate_position, float crewmate_width, float crewmate_height);

    bool checkCollision(glm::vec3 crewmate_position, float crewmate_width, float crewmate_height);


private:

    VAO *object; 
    VAO *coin_outer; 
    VAO *coin_inner; 

    VAO *bomb_circle; 
    VAO *bomb_rectangle;
    VAO *bomb_fuse; 

    VAO *button; 

};

#endif // POWERUPS_H
