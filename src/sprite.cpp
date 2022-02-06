#include "sprite.h"
#include "main.h"
#include "maze.h"
#include <vector>
#include <algorithm>
#include <math.h>

const float PI = 3.14;

// defining all the functions in class Sprite

Sprite::Sprite(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);

    //actually half the width and half the height
    this->width = 0.20;
    this->height = 0.3;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat body_vertex_buffer_data[] = { 
        -0.20f,-0.2f,0.0f, // triangle 0 4 begin
        -.20f, 0.2f, 0.0f,
        0.20f, -0.2f, 0.0f, // triangle 0 4 end

        -0.20f, 0.2f, 0.0f,
        0.20f, -0.2f, 0.0f, // triangle 0 4 end
        0.20f, 0.2f , 0.0f
    };

    static const GLfloat glasses_vertex_buffer_data[] = {
        -0.10f,0.08f,0.0f, // triangle 1 : begin
        -0.10f, 0.22f, 0.0f,
        0.10f, 0.08f, 0.0f, // triangle 1 : end

        -0.10f, 0.22f, 0.0f,
        0.10f, 0.08f, 0.0f, // triangle 1 : end
        0.10f, 0.22f , 0.0f
    };

    static const GLfloat rleg_vertex_buffer_data[] = {
        -0.2f,-0.28f,0.0f, // triangle 1 : begin
        -0.2f, -0.20f, 0.0f,
        -0.10f, -0.28f, 0.0f, // triangle 1 : end

        -0.2f, -0.20f, 0.0f,
        -0.10f, -0.28f, 0.0f, // triangle 1 : end
        -0.10f, -0.20f , 0.0f
    };

    static const GLfloat lleg_vertex_buffer_data[] = {
        0.10f,-0.28f,0.0f, // triangle 1 : begin
        0.10f, -0.20f, 0.0f,
        0.20f, -0.28f, 0.0f, // triangle 1 : end

        0.10f, -0.20f, 0.0f,
        0.20f, -0.28f, 0.0f, // triangle 1 : end
        0.20f, -0.20f , 0.0f
    };

    static const GLfloat backpack_vertex_buffer_data[] = {
        -0.10f,0.08f,0.0f, // triangle 1 : begin
        -0.10f, 0.22f, 0.0f,
        0.10f, 0.08f, 0.0f, // triangle 1 : end

        -0.10f, 0.22f, 0.0f,
        0.10f, 0.08f, 0.0f, // triangle 1 : end
        0.10f, 0.22f , 0.0f
    };


    int triangleAmount = 180; //# of triangles used to draw circle
	GLfloat radius = 0.2f; //radius
	GLfloat twicePi = 2.0f * M_PI;

    std::vector <float> head_vertex_buffer_data_vector;

    GLfloat xcenter = 0;
    GLfloat ycenter = 0.2f;
    
    GLfloat xx = 0;
    GLfloat yy = 0;

    GLfloat xprev = xcenter + (radius * cos(0 *  twicePi / 360));
    GLfloat yprev = ycenter + (radius * sin(0 * twicePi / 360));

    for(int i = 1; i < triangleAmount+1;i++) { 
        
        head_vertex_buffer_data_vector.push_back(xcenter);
        head_vertex_buffer_data_vector.push_back(ycenter);
        head_vertex_buffer_data_vector.push_back(0);

        head_vertex_buffer_data_vector.push_back(xprev);
        head_vertex_buffer_data_vector.push_back(yprev);
        head_vertex_buffer_data_vector.push_back(0);

        xx = xcenter + (radius * cos(i *  twicePi / 360));
        yy = ycenter + (radius * sin(i * twicePi / 360));

        head_vertex_buffer_data_vector.push_back(xx);
        head_vertex_buffer_data_vector.push_back(yy);
        head_vertex_buffer_data_vector.push_back(0);

        xprev = xx;
        yprev = yy;
    }

    int num_vertices = (int)head_vertex_buffer_data_vector.size();

    // static const creates issue here????? static const GLfloat vertex_buffer_data - og
    float head_vertex_buffer_data[num_vertices];
    for(int i=0;i<num_vertices;i++)
    {
        head_vertex_buffer_data[i] = head_vertex_buffer_data_vector[i];
    }
    
    this->body = create3DObject(GL_TRIANGLES, 2*3*3 , body_vertex_buffer_data, color, GL_FILL);
    this->glasses = create3DObject(GL_TRIANGLES, 2*3*3, glasses_vertex_buffer_data, COLOR_GREY, GL_FILL);
    this->head = create3DObject(GL_TRIANGLES, num_vertices, head_vertex_buffer_data, color, GL_FILL);
    this->rleg = create3DObject(GL_TRIANGLES, 2*3*3, rleg_vertex_buffer_data, color, GL_FILL);
    this->lleg = create3DObject(GL_TRIANGLES, 2*3*3, lleg_vertex_buffer_data, color, GL_FILL);

}

void Sprite::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->body);
    draw3DObject(this->glasses);
    draw3DObject(this->head);
    draw3DObject(this->rleg);
    draw3DObject(this->lleg);


}

void Sprite::chase_Crewmate(Maze *maze, glm::vec3 destination) {

    int source_idx = maze->calculateIndex((int)this->position.y,(int)this->position.x);
    int destination_idx = maze->calculateIndex((int)destination.y, (int)destination.x);

    int direction = maze->graph->shortestPath(source_idx,destination_idx);

    // imposter found crewmate
    if(direction == 5)
    {
        kill_Crewmate();
    }

    if(source_idx == -1) return;

    // TOP = 1, BOTTOM = -1 , RIGHT = -2, LEFT = 2

    if (direction == 1) set_position(this->position.x,this->position.y + 1);
    if (direction == -1) set_position(this->position.x,this->position.y - 1);
    if (direction == 2) set_position(this->position.x - 1,this->position.y);
    if (direction == -2) set_position(this->position.x + 1,this->position.y);
}

void Sprite::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Sprite::give_position() {
    return this->position;
}

void Sprite::tick() {
    this->rotation += 0;
    // this->position.x -= speed;
    // this->position.y -= speed;
    this->position.z -= 1;
}

void Sprite::kill_Crewmate()
{
    this->hasMurdered = true;
}

bool Sprite::Exit()
{
    if(this->position.x < 0 || this->position.y < 0) return true;
    
    else return false;

}
