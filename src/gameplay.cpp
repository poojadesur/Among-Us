#include "gameplay.h"
#include "main.h"

// defining all the functions in class Ball

HUD::HUD(color_t color,int num_powerups) {
    
    this->health = 100;
    this->timer = 120;
    this->task = 0;
    this->num_powerups = num_powerups;
    this->num_powerups_collected = 0;
    this->imposterAlive = true;

    this->position = glm::vec3 (4,9,0);
   
    static const GLfloat vertex_buffer_data[] = { 
        -1.0f,-1.0f,0.0f, // triangle 0 4 begin
        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, // triangle 0 4 end

        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, // triangle 0 4 end
        1.0f, 1.0f , 0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, sizeof(vertex_buffer_data), vertex_buffer_data, color, GL_FILL);
}

void HUD::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void HUD::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void HUD::affectHealth(int change){
    this->health += change;
    // std::cout << "health " << this->health << std::endl;
}

int HUD::getHealth(){
    // std::cout << "returning health " << this->health << std::endl;
    return this->health;
}

void HUD::TaskComplete()
{
    this->task += 1;
}

void HUD::collectPowerUP()
{
    this->num_powerups_collected += 1;
    if(this->num_powerups_collected == this->num_powerups) TaskComplete();
}

void HUD::killImposter()
{
    this->imposterAlive = false;
    TaskComplete();
}



