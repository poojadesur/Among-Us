#include "main.h"
#include "timer.h"
#include "maze.h"
#include "sprite.h"
#include "gameplay.h"
#include "powerups.h"
#include <stdlib.h> 


#define GLT_IMPLEMENTATION
#include "gltext.h"


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

glm::vec3 CameraPosition (0,0,3);

Maze *maze1;
Sprite crewmate;
Sprite *imposter;
HUD *hud;

Timer *t60;

Powerup imposter_button;
Powerup powerup_button;
Powerup powerup1;
Powerup powerup2;
Powerup powerup3;
Powerup powerup4;
// Powerup powerup5;

Powerup obstacle1;
Powerup obstacle2;
Powerup obstacle3;
Powerup obstacle4;
// Powerup obstacle5;


float screen_zoom = 1, screen_center_x = 6.5, screen_center_y = 6.5;
float camera_rotation_angle = 0;
const int MAZE_SIZE = 12;
const float SPEED = 0.01;
const int TIMELIMIT = 300;


void render_text(HUD *hud,Timer* t60) {
    // Initialize glText
    gltInit();

    // Creating text
    GLTtext *text = gltCreateText();
    GLTtext *health = gltCreateText();
    GLTtext *timer = gltCreateText();
    GLTtext *tasks = gltCreateText();

    string nl = "\n";
    string str = "Health: ";
    string s = to_string(hud->health);
    str.append(s);
    str.append(nl);

    // char const *Health = H.c_str();  //use char const* as target type
    // gltSetText(health, Health);

    string T = "Timer: ";
    string q = to_string(t60->getTimeLeft());
    str.append(T);
    str.append(q);
    str.append(nl);

    // char const *Timer = T.c_str();  //use char const* as target type
    // gltSetText(timer, Timer);


    string Ta = "Tasks: ";
    string Ta1 = "/2";
    string p = to_string(hud->task);
    str.append(Ta);
    str.append(p);
    str.append(Ta1);
    str.append(nl);

    char const *Text = str.c_str();
    // char const *Tasks = Ta.c_str();  //use char const* as target type
    gltSetText(text, Text);

    // Begin text drawing (this for instance calls glUseProgram)
    gltBeginDraw();

    // Draw any amount of text between begin and end
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);
    gltDrawText2D(text, 6.5, 6.5, 2);


    // Finish drawing text
    gltEndDraw();

    // Deleting text
    gltDeleteText(text);

    // Destroy glText
    gltTerminate();

}


void render_winText() {
    // Initialize glText
    gltInit();

    // Creating text
    GLTtext *text = gltCreateText();

    const char* Text = "***GAME OVER***\n\nYou Win!!!";

    gltSetText(text, Text);

    // Begin text drawing (this for instance calls glUseProgram)
    gltBeginDraw();

    // Draw any amount of text between begin and end
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);
    gltDrawText2D(text, 6.5, 6.5, 5);

    // Finish drawing text
    gltEndDraw();

    // Deleting text
    gltDeleteText(text);

    // Destroy glText
    gltTerminate();

}

void render_loseText() {
    // Initialize glText
    gltInit();

    // Creating text
    GLTtext *text = gltCreateText();

    const char* Text = "***GAME OVER***\n\nYou Lost :(";

    gltSetText(text, Text);

    // Begin text drawing (this for instance calls glUseProgram)
    gltBeginDraw();

    // Draw any amount of text between begin and end
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);
    gltDrawText2D(text,6.5,6.5, 5);


    // Finish drawing text
    gltEndDraw();

    // Deleting text
    gltDeleteText(text);

    // Destroy glText
    gltTerminate();

}


/* Render the scene with openGL */
/* Edit this function according to your assignment */

void draw_winScreen()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    render_winText();

}


void draw_loseScreen()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    render_loseText();

}

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    glm::vec3 CameraFront (0, 0, -1);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(CameraPosition, CameraPosition + CameraFront, up);

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render

    // if button for powerups is pressed then draw powerups and obstacles

    // if button for vaporise imposter is pressed dont draw imposter

    maze1->draw(VP);
    crewmate.draw(VP);
    glm::vec3 crewmate_position = crewmate.give_position();
    
    if(hud->imposterAlive)
    {
        if(t60->imposterTime())imposter->chase_Crewmate(maze1,crewmate_position);

        imposter->draw(VP);
    }
    // hud->draw(VP);

    imposter_button.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    imposter_button.draw(VP);

    powerup_button.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    if(powerup_button.canActivateTask)
    {
        powerup1.Activate(true);
        powerup2.Activate(true);
        powerup3.Activate(true);
        powerup4.Activate(true);
        obstacle1.Activate(true);
        obstacle2.Activate(true);
        obstacle3.Activate(true);
        obstacle4.Activate(true);
        powerup_button.ActivateTask(false);
    }
    powerup_button.draw(VP);

    powerup1.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    powerup1.draw(VP);
    powerup2.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    powerup2.draw(VP);
    powerup3.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    powerup3.draw(VP);
    powerup4.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    powerup4.draw(VP);
    // powerup5.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    // powerup5.draw(VP);

    obstacle1.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    obstacle1.draw(VP);
    obstacle2.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    obstacle2.draw(VP);
    obstacle3.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    obstacle3.draw(VP);
    obstacle4.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    obstacle4.draw(VP);
    // obstacle5.checkActivation(hud,crewmate_position,crewmate.width, crewmate.height);
    // obstacle5.draw(VP);

    render_text(hud,t60);

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    if (left) {
        int move = detect_collision(maze1,2,crewmate.position.x,crewmate.position.y,crewmate.width,crewmate.height);
        if (move == 1) 
        { 
            crewmate.set_position(crewmate.position.x - SPEED,crewmate.position.y);
            hud->set_position(hud->position.x - SPEED,hud->position.y);
            CameraPosition += glm::vec3 (-SPEED,0,0);

        }
        // std::cout << crewmate.position.x - crewmate.width << " " << crewmate.position.y + crewmate.width  << std::endl;
    }

    if (right) {
        int move = detect_collision(maze1,-2,crewmate.position.x,crewmate.position.y,crewmate.width,crewmate.height);
        if (move == 1) 
        {
            crewmate.set_position(crewmate.position.x + SPEED,crewmate.position.y);
            hud->set_position(hud->position.x + SPEED,hud->position.y);
            CameraPosition += glm::vec3 (SPEED,0,0);

        }
        // std::cout << crewmate.position.x - crewmate.width << " " << crewmate.position.y << std::endl;
        // std::cout << crewmate.position.x - crewmate.width << " " << crewmate.position.y + crewmate.height  << std::endl;
    }

    if (up) {
        int move = detect_collision(maze1,1,crewmate.position.x,crewmate.position.y,crewmate.width,crewmate.height);
        if (move == 1) 
        {
            crewmate.set_position(crewmate.position.x,crewmate.position.y+SPEED);
            hud->set_position(hud->position.x,hud->position.y+SPEED);
            CameraPosition += glm::vec3 (0,SPEED,0);

        }
        // std::cout << crewmate.position.x << " " << crewmate.position.y + crewmate.height << std::endl;
        // std::cout << crewmate.position.x - crewmate.width << " " << crewmate.position.y + crewmate.height  << std::endl;
    }

    if (down) {
        int move = detect_collision(maze1,-1,crewmate.position.x,crewmate.position.y,crewmate.width,crewmate.height);
        if (move == 1) 
        {
            crewmate.set_position(crewmate.position.x,crewmate.position.y-SPEED);
            hud->set_position(hud->position.x,hud->position.y-SPEED);
            CameraPosition += glm::vec3 (0,-SPEED,0);

        }
        // std::cout << crewmate.position.x << " " << crewmate.position.y - crewmate.height << std::endl;
        // std::cout << crewmate.position.x - crewmate.width << " " << crewmate.position.y + crewmate.height  << std::endl;

    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    t60 = new Timer(1.0 / 60, TIMELIMIT, 1.0, 3.0);
    
    maze1 = new Maze(MAZE_SIZE,MAZE_SIZE,COLOR_PURPLE);
    maze1->generateMaze();

    crewmate = Sprite(6.5,6.5,COLOR_CYAN);

    srand (time(NULL)); 
    int randx;
    int randy;
    int idx;
    std::vector<int>::iterator it;
    int min = 0;
    int max = 11;
    
    randx = min + ( std::rand() % ( max - min + 1 ) );;
    randy = min + ( std::rand() % ( max - min + 1 ) );;
    
    imposter = new Sprite(randx+0.5,randy+0.5,COLOR_RED);

    hud = new HUD(COLOR_GREY,4);

    randx = min + ( std::rand() % ( max - min + 1 ) );;
    randy = min + ( std::rand() % ( max - min + 1 ) );;
    int ibidx = randx + randy*MAZE_SIZE;

    imposter_button = Powerup(-1,randx + 0.5,randy+0.5,COLOR_RED);

    randx = min + ( std::rand() % ( max - min + 1 ) );
    randy = min + ( std::rand() % ( max - min + 1 ) );;

    int puidx = randx + randy*MAZE_SIZE;

    while(puidx == ibidx)
    {
        randx = min + ( std::rand() % ( max - min + 1 ) );;
        randy = min + ( std::rand() % ( max - min + 1 ) );;
        puidx = randx + randy*MAZE_SIZE;
    }

    powerup_button = Powerup(0,randx + 0.5,randx + 0.5,COLOR_GREEN);

    powerup1 = Powerup (1,2.5,9.5,COLOR_YELLOW);
    powerup2 = Powerup (1,4.5,3.5,COLOR_YELLOW);
    powerup3 = Powerup (1,7.5,8.5,COLOR_YELLOW);
    powerup4 = Powerup (1,8.5,1.5,COLOR_YELLOW);
    // powerup5 = Powerup (1,10.5,10.5,COLOR_YELLOW);

    obstacle1 = Powerup (2,1.5,2.5,COLOR_BLUE);
    obstacle2 = Powerup (2,3.5,5.5,COLOR_BLUE);
    obstacle3 = Powerup (2,5.5,11.5,COLOR_BLUE);
    obstacle4 = Powerup (2,7.5,3.5,COLOR_BLUE);
    // obstacle5 = Powerup (2,10.5,6.5,COLOR_BLUE);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../src/shaders/shader.vert", "../src/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    
    srand(time(0));

    int width  =1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        // if (t60.processTick() and t60.inTimeLimit()) {
        if (t60->processTick() ) {
            // 60 fps

            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_input(window);
        }

        if(imposter->hasMurdered || !t60->inTimeLimit())
        {
            t60->startScreen();
            while(t60->ScreenTime())
            {
                draw_loseScreen();

                // Swap Frame Buffer in double buffering
                glfwSwapBuffers(window);

                tick_input(window);
            }
            break;
        }

        if(hud->task == 2 and crewmate.Exit())
        {
            t60->startScreen();
            while(t60->ScreenTime())
            {
                draw_winScreen();

                // Swap Frame Buffer in double buffering
                glfwSwapBuffers(window);

                tick_input(window);
            }

            break;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}


bool detect_collision(Maze *maze1, int direction, float x, float y, float width, float height) {

    // borders are all drawn in integer spaces

    int column = (int)x;
    int row = (int)y;

    int i = column + row*MAZE_SIZE;  

    // TOP RIGHT BOTTOM LEFT

    // maze1.cells[i].walls[0];
    // maze1.cells[i].walls[1];
    // maze1.cells[i].walls[2];
    // maze1.cells[i].walls[3];

    if(direction == 2)
    {
        int left_border = (int)(x - width);
        if( (x - width) - left_border < 0.01 && maze1->cells[i].walls[3] == true ) return false;
        else return true;
    }

    if(direction == -2)
    {
        int right_border = (int)(x + width) + 1;
        if( right_border - (x + width)  < 0.01  &&  maze1->cells[i].walls[1] == true ) return false;
        else return true;
    }

    if(direction == 1)
    {
        int top_border = (int)(y + height) + 1;
        if( top_border - (y + height)  < 0.01  &&  maze1->cells[i].walls[0] == true ) return false;
        else return true;
    }

    if(direction == -1)
    {
        int bottom_border = (int)(y - height);
        if( (y - height) - bottom_border < 0.01  &&  maze1->cells[i].walls[2] == true ) return false;
        else return true;
    }

    return false;

}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}


