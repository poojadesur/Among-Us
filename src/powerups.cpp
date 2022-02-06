#include "powerups.h"
#include "main.h"
#include "gameplay.h"
#include <stdlib.h>

// defining all the functions in class Powerup

Powerup::Powerup(int type,float x, float y, color_t color) {
    
    this->type = type;
    this->position = glm::vec3(x, y, 0);

    this->width = 0.30;
    this->height = 0.30;

    // only buttons rendered at first
    if(type == 0 || type == -1)
    { 
        Activate(true);
        ActivateTask(false);
    }
    else
    { 
        Activate(false);
        ActivateTask(false);
    }

    static const GLfloat vertex_buffer_data[] = { 
        -0.10f,0.19f,0.0f, 
        -0.10f, 0.3f, 0.0f,
        0.10f, 0.19f, 0.0f, 

        -0.10f, 0.3f, 0.0f,
        0.10f, 0.19f, 0.0f,
        0.10f, 0.3f , 0.0f
    };

    static const GLfloat fuse_buffer_data[] = { 
        -0.03f,0.3f,0.0f, 
        -0.03f, 0.4f, 0.0f,
        0.03f, 0.3f, 0.0f, 

        -0.03f, 0.4f, 0.0f,
        0.03f, 0.3f, 0.0f,
        0.03f, 0.4f , 0.0f
    };

    int triangleAmount = 360; //# of triangles used to draw circle
	GLfloat radius = 0.2f; //radius
	GLfloat twicePi = 2.0f * M_PI;

    std::vector <float> button_buffer_data_vector;

    GLfloat xcenter = 0;
    GLfloat ycenter = 0.0f;
    
    GLfloat xx = 0;
    GLfloat yy = 0;

    GLfloat xprev = xcenter + (radius * cos(0 *  twicePi / 360));
    GLfloat yprev = ycenter + (radius * sin(0 * twicePi / 360));

    for(int i = 1; i < triangleAmount+1;i++) { 
        
        button_buffer_data_vector.push_back(xcenter);
        button_buffer_data_vector.push_back(ycenter);
        button_buffer_data_vector.push_back(0);

        button_buffer_data_vector.push_back(xprev);
        button_buffer_data_vector.push_back(yprev);
        button_buffer_data_vector.push_back(0);

        xx = xcenter + (radius * cos(i *  twicePi / 360));
        yy = ycenter + (radius * sin(i * twicePi / 360));

        button_buffer_data_vector.push_back(xx);
        button_buffer_data_vector.push_back(yy);
        button_buffer_data_vector.push_back(0);

        xprev = xx;
        yprev = yy;
    }

    int num_vertices = (int)button_buffer_data_vector.size();

    // static const creates issue here????? static const GLfloat vertex_buffer_data - og
    float button_buffer_data[num_vertices];
    for(int i=0;i<num_vertices;i++)
    {
        button_buffer_data[i] = button_buffer_data_vector[i];
    }

	radius = 0.15f; //radius
    std::vector <float> inner_coin_buffer_data_vector;
    
    xx = 0;
    yy = 0;

    xprev = xcenter + (radius * cos(0 *  twicePi / 360));
    yprev = ycenter + (radius * sin(0 * twicePi / 360));

    for(int i = 1; i < triangleAmount+1;i++) { 
        
        inner_coin_buffer_data_vector.push_back(xcenter);
        inner_coin_buffer_data_vector.push_back(ycenter);
        inner_coin_buffer_data_vector.push_back(0);

        inner_coin_buffer_data_vector.push_back(xprev);
        inner_coin_buffer_data_vector.push_back(yprev);
        inner_coin_buffer_data_vector.push_back(0);

        xx = xcenter + (radius * cos(i *  twicePi / 360));
        yy = ycenter + (radius * sin(i * twicePi / 360));

        inner_coin_buffer_data_vector.push_back(xx);
        inner_coin_buffer_data_vector.push_back(yy);
        inner_coin_buffer_data_vector.push_back(0);

        xprev = xx;
        yprev = yy;
    }

    int num_vertices2 = (int)inner_coin_buffer_data_vector.size();

    // static const creates issue here????? static const GLfloat vertex_buffer_data - og
    float inner_coin_buffer_data[num_vertices];
    for(int i=0;i<num_vertices2;i++)
    {
        inner_coin_buffer_data[i] = inner_coin_buffer_data_vector[i];
    }

    this->button = create3DObject(GL_TRIANGLES, num_vertices, button_buffer_data, color, GL_FILL);
    this->coin_outer = create3DObject(GL_TRIANGLES, num_vertices, button_buffer_data,COLOR_DARKYELLOW ,GL_FILL);
    this->coin_inner = create3DObject(GL_TRIANGLES, num_vertices2, inner_coin_buffer_data,COLOR_YELLOW ,GL_FILL);

    this->bomb_circle = create3DObject(GL_TRIANGLES, num_vertices, button_buffer_data,COLOR_RED ,GL_FILL);
    this->bomb_rectangle = create3DObject(GL_TRIANGLES, 2*3*3, vertex_buffer_data,COLOR_GREY,GL_FILL);
    this->bomb_fuse = create3DObject(GL_TRIANGLES, 2*3*3, fuse_buffer_data,COLOR_RED,GL_FILL);



}

void Powerup::draw(glm::mat4 VP) {

    //before drawing check if powerup has already been activated

    if (this->isActive == true)
    {
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        if(type == 0 || type == -1 ) draw3DObject(this->button);
        if(type == 1)
        {
            draw3DObject(this->coin_outer);
            draw3DObject(this->coin_inner);

        }
        if(type == 2)
        {
            draw3DObject(this->bomb_circle);
            draw3DObject(this->bomb_rectangle);
            draw3DObject(this->bomb_fuse);

        }

    }
}

void Powerup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Powerup::Activate(bool activate){
    this->isActive = activate;
}

void Powerup::ActivateTask(bool canActivateTask){
    this->canActivateTask = canActivateTask;
}

bool Powerup::checkCollision(glm::vec3 crewmate_position, float cm_width, float cm_height)
{
    float x = this->position.x;
    float y = this->position.y;

    float cmx = crewmate_position.x;
    float cmy = crewmate_position.y;


    // dont check collisions for non active powerups
    if (this->isActive == false) return false;

    // LEFT
    if( abs( (cmx-cm_width) - (x + width) ) < 0.01 && (int(y) == int(cmy)) )
    { 
        return true;
    }
    // RIGHT
    if ( abs((x - width) - (cmx+cm_width) ) < 0.01 && (int(y) == int(cmy)))
    {
        
        return true;
    }
    
    // TOP
    if ( abs((y - height) - (cmy+cm_height) ) < 0.01 && (int(x) == int(cmx))) return true;
    
    // BOTTOM
    if( abs( (cmy-cm_height) - (y + height) ) < 0.01 && (int(x) == int(cmx))  ) return true;

    return false;
}

void Powerup::checkActivation(HUD* hud, glm::vec3 crewmate_position, float crewmate_width, float crewmate_height)
{
    // check collision only if active (collision with powerups doesnt matter when button hasnt been pressed yet) and update hud according to type
    if(type == -1)
    {
        if(checkCollision(crewmate_position, crewmate_width, crewmate_height) == true)
        {
            // std::cout << "it collided " << std::endl;
            Activate(false);
            hud->killImposter();
        }
    }
    if(type == 0)
    {
        if(checkCollision(crewmate_position, crewmate_width, crewmate_height) == true)
        {
            // std::cout << "it collided " << std::endl;
            Activate(false);
            ActivateTask(true);
        }

    }
    if(type == 1)
    {
        if(checkCollision(crewmate_position, crewmate_width, crewmate_height) == true)
        {
            Activate(false);
            hud->affectHealth(5);
            int healthh = hud->getHealth();
            // std::cout << "in check coll health " << healthh << std::endl;
            hud->collectPowerUP();
        }
    }
    if(type == 2)
    {
        if(checkCollision(crewmate_position, crewmate_width, crewmate_height) == true)
        {
            Activate(false);

            hud->affectHealth(-5);
            int healthh = hud->getHealth();
            // std::cout << "in check coll health " << healthh << std::endl;
        }
    }

}






