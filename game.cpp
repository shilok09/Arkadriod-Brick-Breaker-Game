//============================================================================
// Name        : SHILOK KUMAR
// ROLL NO     : 23I-2502
// Copyright   : (c) Reserved
// Description : Basic 2D game of BrickBreaker
//===========================================================================


#ifndef Brickbreaker_CPP_
#define Brickbreaker_CPP_
#include "util.h";
#include "game_objects.h";
#include <iostream>
#include<fstream>
#include <random>
#include <string>
#include <cmath> 
using namespace std;


class Game : public Ball, public Paddle, public Bricks{
private:
//---XXX---XXX---XXX---XXX---GAME VARIABLES---XXX---XXX---XXX---XXX---XXX---XXX
    static Ball ball;
    static Paddle paddle;
    static Bricks blocks;
   
    static Green green;
    static bool paddleDoubled;
    static Pink pink;
    static bool paddleHalved;
    static Red red;
    static Yellow yellow;



    static int *highScore;
    static int state;
    static int option;
    static int select;
    static int lives;
    static int   width;
    static int   score;
    static int   height;
    string       title;
    static int   mouseX;    
    static int   mouseY;
    static float angle;
    static bool flag;
    static bool reset_flag;
    static int counter;
    static bool tap;
    static int hitCount;
    static int index;
   

    
public:
//---XXX---XXX---XXX---XXX---GAME CONSTRUCTOR---XXX---XXX---XXX---XXX---XXX---XXX
Game(int width, int height, const std::string& title, int argc, char* argv[]) 
    :title(title)
   {   
       
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	    glutInitWindowPosition(50, 50);            
	    glutInitWindowSize(width, height);          
    	glutCreateWindow(title.c_str());           
        glMatrixMode (GL_PROJECTION);
	    glLoadIdentity();
	    glOrtho(0, width, 0, height, -1, 1); 
	    glMatrixMode (GL_MODELVIEW);
	    glLoadIdentity();

        Game::width=width;

        //Rectangle:

        Game::paddle.setRectWidth(100);
        Game::paddle.setRectHeight(30);

        //Ball:
        Game::ball.setBallX((width/2)+50);
        Game::ball.setBallY(30+30+ball.getRadius()); //rectX + rectHeight + radius
        //BallSpeed:
        Game::ball.setSpeed(5.0f);
        
        //blocks
        Game::blocks.setBlockX(80);
        Game::blocks.setBlockY(20);
        Game::blocks.setRows(height/blocks.getBlockY());
        Game::blocks.setCols(width/blocks.getBlockX());
       
        Game::blocks.Allocate(blocks.getRows(),blocks.getCols());
       
        
        Game::green.allocate(blocks.getRows(),blocks.getCols());
        Game::pink.allocate(blocks.getRows(),blocks.getCols());
        Game::red.allocate(blocks.getRows(),blocks.getCols());
        Game::yellow.allocate(blocks.getRows(),blocks.getCols());
        
        for(int i=0;i<3;i++)
        {Game::highScore[i]=0;}
      
        
       reset();

}
~Game(){}


static void keyboard(unsigned char key, int x, int y) {
        srand(time(NULL));

        if(key=='S' || key=='s')
        {Game::score=0;Game::lives=2;}    // S -- START
       
        if(key == 32 && tap==true){  //SPACE -- BALL JUMP

        //Ball Moves at angle theta;
        angle = rand()%180+5;
        angle = angle*(M_PI/180);

        //Components of Ball Default Speed
        float x=cos(angle)*ball.getSpeed();
        float y=sin(angle)*ball.getSpeed();

        Game::ball.setSpeedX(x);
        Game::ball.setSpeedY(y);

        Game::tap=false;

        }

    if(key == KEY_ESC){
        Game::state = 0;
    }
    else if(key == 13){
        switch(option){
            case 0:     //START GAME
                Game::score=0;
                Game::lives=2;
                reset();
                Game::state = 1;
            break;
            case 1:    //RESUME GAME
                Game::state = 1;
            break;
            case 2:    //HIGHSCORE
               Game::state=2;
            break;
            case 3:    //EXIT
                exit(0);
            break;
            
        }
    }
}
static void SpecialKeys(int key, int mouseX, int mouseY) {
    if (key == GLUT_KEY_UP) {
        switch (state) {
        case 0:
            if (option > 0) {
                Game::option--;}
                Game::select = 390 - Game::option* 50;
            
            break;
        }
    }
    else if (key == GLUT_KEY_DOWN) {
        switch (state) {
        case 0:
            if (option < 3) {
                Game::option++;
                Game::select = 390 - option * 50;
            }
            break;
        }
    }

    glutPostRedisplay();
}
static void MouseMotion(int x, int y){
    if(Game::lives==0){
        return;
    }
   
    Game::mouseX = x;
    Game::mouseY = 600 - y;

    if(tap==true)
    Game::ball.setBallX(mouseX-ball.getRadius()*2 + 25);
  


    Game::paddle.setRectX(mouseX-paddle.getRectWidth()/2);
    Game::paddle.setRectY(paddle.getRectHeight());

//----xxx---xx-[if paddle goes outside boundry]-xx---xx---xx----
    if (Game::paddle.getRectX()<0) {
        Game::paddle.setRectX(0);
    } else if (Game::paddle.getRectX() + Game::paddle.getRectWidth()>Game::width) {
        Game::paddle.setRectX(Game::width - Game::paddle.getRectWidth());
    }
    
    glutPostRedisplay();
}; //MOUSE MOTION FUNCTION
static void updateHighScores() {
    //FINDING MAX SCORE
    bool updated = false;
    for (int i=0;i<3;i++) {
        if (score>highScore[i]) {
            for (int j=2;j>i;j--) {
                Game::highScore[j]=highScore[j-1];
            }
            Game::highScore[i]=score;
            updated = true;
            break;
        }
    }

    if (!updated) {
        Game::highScore[2] = score;
        updated = true;
    }

     ofstream File("highscore.txt");
    if (File.is_open()) {
        for (int i=0; i<3;i++) {
            File<<highScore[i]<<endl;
        }
        File.close();
    }else {
        cout << "-^-FILE NOT OPENED-^-" << endl;
    }

}

void getHighScores(){
    ifstream readFile("highscore.txt");
    for(int i=0;i<3;i++){
        readFile >> Game::highScore[i];
    }
    readFile.close();
}
static void Display() {
    srand(time(NULL));
        glClear(GL_COLOR_BUFFER_BIT);
        switch(Game::state) 
        {
            case 0:
                    DrawRoundRect(200,100,400,400,colors[TEAL],0);
                    DrawRoundRect(270, select, 200, 40, colors[NAVY], 0);
                    DrawString(300, 450, "BALL BREAKER GAME", colors[FLORAL_WHITE]);
                    DrawString(300, 400, "Start Game", colors[WHITE]);
                    DrawString(300, 350, "Resume Game", colors[WHITE]);
                    DrawString(300, 300, "High Scores", colors[WHITE]);
                    DrawString(300, 250, "Exit", colors[WHITE]);
                    break;
            case 2:
                   DrawRoundRect(200,100,400,400,colors[TEAL],0);
                   DrawRoundRect(270, 180, 250, 300, colors[MEDIUM_PURPLE], 0);
                   DrawString(330, 450, "HIGH SCORES", colors[FLORAL_WHITE]);
                   DrawString(330, 400, "FIRST  -- " + Num2Str(highScore[0]), colors[WHITE]);
                   DrawString(330, 350, "SECOND -- " + Num2Str(highScore[1]), colors[WHITE]);
                   DrawString(330, 300, "THIRD  -- " + Num2Str(highScore[2]), colors[WHITE]);
                   break;
            case 1: {
                    //---xxx---xxx---GAME OBJECTS---xxx---xxx---xxx---xxx
                    //BRICKS
                    for (int i=0; i<blocks.getRows(); i++) {
                         for (int j=0; j<blocks.getCols();j++) {
                            if(blocks.getElement(i,j)!=0){
                               
                                int PosX=j*blocks.getBlockX();
                                int PosY=height-i*blocks.getBlockY();

                                //DRAWING BRICKS WITH DIFFERENT COLORS
                                switch(blocks.getElement(i,j)){
                                    case 1: DrawRectangle(PosX, PosY, blocks.getBlockX(), blocks.getBlockY(), colors[LIME_GREEN]);break;
                                    case 2: DrawRectangle(PosX, PosY, blocks.getBlockX(), blocks.getBlockY(), colors[DARK_GOLDEN_ROD]);break;
                                    case 3: DrawRectangle(PosX, PosY, blocks.getBlockX(), blocks.getBlockY(), colors[LIGHT_CORAL]);break;
                                    case 4: DrawRectangle(PosX, PosY, blocks.getBlockX(), blocks.getBlockY(), colors[DARK_RED]);break;
                                    case 5: DrawRectangle(PosX, PosY, blocks.getBlockX(), blocks.getBlockY(), colors[DARK_BLUE]);break;
                                    
                                }
                               
                                
                            }
                            else{
            
                                 //RANDOM COLOR BLOCKS BACKGROUND
                                int x = j*blocks.getBlockX();
                                int y = height-i*blocks.getBlockY();
                            
                                float dim[3];
                                dim[0]=(rand()%256)/255.0;
                                dim[1]=(rand()%256)/255.0;
                                dim[2]=(rand()%256)/255.0; 
                                for (int i=0; i<3;i++) {
                                   dim[i]/=6.5;
                                }

                                DrawRectangle(x, y, blocks.getBlockX(), blocks.getBlockY(),dim);
                                }
                        }            
                     } 

                    // //POWER UPS 
                    for (int i = 0; i < blocks.getRows(); i++) {
                        for (int j = 0; j < blocks.getCols(); j++) {

                            if (blocks.getColor(i, j) == *colors[LIME_GREEN] && blocks.getElement(i, j) == 0 && green.isactive() && green.getElement(i,j)) {

                                 int x=j*blocks.getBlockX();
                                 int y=height-(i*blocks.getBlockY())+green.getY(); 
                                  
                                  if (y<=0) {
                                    y=height-(i*blocks.getBlockY());
                                   }
                                   
                                DrawTriangle(x-20,y-20,x+20,y-20,x,y+20,colors[LIME_GREEN]);
                                break;
                            }
                            else if (blocks.getColor(i, j) == *colors[LIGHT_CORAL] && blocks.getElement(i, j) == 0 && pink.isactive() && pink.getElement(i,j)){
                                 int x=j*blocks.getBlockX();
                                 int y=height-(i*blocks.getBlockY())+pink.getY(); 
                                  
                                  if (y<=0) {
                                    y=height-(i*blocks.getBlockY());
                                   }
                                   
                                DrawSquare(x,y,20,colors[LIGHT_CORAL]);
                                break;
                            }
                            else if (blocks.getColor(i, j) == *colors[DARK_RED] && blocks.getElement(i, j) == 0 && red.isactive() && red.getElement(i,j)){
                                 int x=j*blocks.getBlockX();
                                 int y=height-(i*blocks.getBlockY())+red.getY(); 
                                  
                                  if (y<=0) {
                                    y=height-(i*blocks.getBlockY());
                                   }
                                   
                                DrawRectangle(x,y,40,20,colors[DARK_RED]);
                                break;
                            }
                            else if (blocks.getColor(i, j) == *colors[DARK_GOLDEN_ROD] && blocks.getElement(i, j) == 0 && yellow.isactive() && yellow.getElement(i,j)){
                                 int x=j*blocks.getBlockX();
                                 int y=height-(i*blocks.getBlockY())+yellow.getY(); 
                                  
                                  if (y<=0) {
                                    y=height-(i*blocks.getBlockY());
                                   }
                                   
                               DrawSquare(x,y,20,colors[DARK_GOLDEN_ROD]);
                                break;
                            }

                        }
                    }

              
                                
                  
                    //PADDLE
                    switch(paddle.getColor()){
                        case 1:DrawRoundRect(paddle.getRectX(),paddle.getRectY(),paddle.getRectWidth(),paddle.getRectHeight(),colors[LIME_GREEN],14);break;
                        case 2:DrawRoundRect(paddle.getRectX(),paddle.getRectY(),paddle.getRectWidth(),paddle.getRectHeight(),colors[DARK_GOLDEN_ROD],14);break;
                        case 3:DrawRoundRect(paddle.getRectX(),paddle.getRectY(),paddle.getRectWidth(),paddle.getRectHeight(),colors[LIGHT_CORAL],14);break;
                        case 4:DrawRoundRect(paddle.getRectX(),paddle.getRectY(),paddle.getRectWidth(),paddle.getRectHeight(),colors[RED],14);break;
                        case 5:DrawRoundRect(paddle.getRectX(),paddle.getRectY(),paddle.getRectWidth(),paddle.getRectHeight(),colors[DARK_BLUE],14);break;
                        case 6:DrawRoundRect(paddle.getRectX(),paddle.getRectY(),paddle.getRectWidth(),paddle.getRectHeight(),colors[LIGHT_STEEL_BLUE],14);break;
                    }
                     
                    //BALL
                    switch(ball.getColor()){
                        case 1:DrawCircle(ball.getBallX(),ball.getBallY(),ball.getRadius(),colors[LIME_GREEN]);break;
                        case 2:DrawCircle(ball.getBallX(),ball.getBallY(),ball.getRadius(),colors[DARK_GOLDEN_ROD]);break;
                        case 3:DrawCircle(ball.getBallX(),ball.getBallY(),ball.getRadius(),colors[LIGHT_CORAL]);break;
                        case 4:DrawCircle(ball.getBallX(),ball.getBallY(),ball.getRadius(),colors[RED]);break;;
                        case 5:DrawCircle(ball.getBallX(),ball.getBallY(),ball.getRadius(),colors[DARK_BLUE]);break;

                    }
                    
                    
                    //SCORE
                    DrawString(0,height-30,"SCORE: ",colors[WHITE]);
                    string score=Num2Str(Game::score);
                    DrawString(80,height-30,score,colors[WHITE]);
            
                    //LIVES
                    DrawString(width/2,height-30,"LIVES: ",colors[WHITE]);
                    string lives=Num2Str(Game::lives);
                    DrawString(width/2 + 60,height-30,lives,colors[WHITE]);
                    //MY NAME
                    DrawString(650,height-30,"SHILOK KUMAR",colors[WHITE]);

                    //DISPLAYING LIVES MESSAGE 
                    if(flag==true && Game::lives > 0 && tap){
                    DrawString(344,height/2,"LIVE COUNT: ",colors[CYAN]);
                    string lives=Num2Str(Game::lives);
                    DrawString(344+120,height/2,lives,colors[CYAN]);
                    }
            
                    if(reset_flag && tap && Game::lives!=0){
                       DrawString(280, height / 2-20, "[PRESS 'SPACE' TO START ]", colors[AQUA]);
                    }
                    //GAMEOVER MESSAGE
                    if(Game::lives==0){
                    DrawRoundRect(240,220,320,100,colors[NAVY],0);
                    DrawString(344, height / 2, "GAME OVER", colors[AQUA]);
                    DrawString(320, height / 2-30,"YOUR SCORE: ", colors[AQUA]);
                    DrawString(453, height / 2-30,score, colors[AQUA]);
                    DrawString(264, height / 2-60, "[PRESS 'S' TO START AGAIN ]", colors[AQUA]);
                    }

                    break;

                }
           }
            glutSwapBuffers(); 
     }            
        
static void update() {
    if (Game::lives == 0)
        { return; } //GAMEOVER
        glutPassiveMotionFunc(MouseMotion); // Mouse motion

    //PUTTING BALL ON PADDLE IF IT GOES BOTTOM
    if (Game::ball.getBallY() == 0.0f) {
        Game::ball.setBallX((width / 2) + 50);
        Game::ball.setBallY(30 + 30 + ball.getRadius());
    } else {

        //MOVE BALL
        Game::ball.addX(Game::ball.getSpeedX());
        Game::ball.addY(Game::ball.getSpeedY());

        // BALL BOUNDRY COLLISIONS
        if (ball.getBallX()-ball.getRadius()*2 <= 0.0f) {          // Left
            
            Game::ball.setBallX(0.0f + Game::ball.getRadius() * 2);
            Game::ball.setSpeedX(abs(Game::ball.getSpeedX()));

        } else if (ball.getBallX() + ball.getRadius() * 2 >= width) { // Right
            
            Game::ball.setBallX(width - (Game::ball.getRadius() * 2));
            Game::ball.setSpeedX(-abs(Game::ball.getSpeedX()));
        }
        if (ball.getBallY() + ball.getRadius() * 2 >= height) {      // Up
            
            Game::ball.setBallY(height - (Game::ball.getRadius() * 2));
            Game::ball.setSpeedY(-abs(Game::ball.getSpeedY()));
            
        } else if (ball.getBallY() <= 0.0f) {                               // Down
            
            Game::lives--;
            if (Game::lives == 0)
                Game::updateHighScores();
            Game::reset();
            Game::flag = true;
        }

        // BALL PADDLE COLLISIONS
        if (ball.getBallX() + (ball.getRadius() * 2.0f) >= paddle.getRectX() && //BALL RIGHT SIDE & PADDLE LEFT SIDE 
            ball.getBallX() <= paddle.getRectX() + paddle.getRectWidth() &&     //BALL LEFT SIDE AND PADDLE RIGHT SIDE
            ball.getBallY() + (ball.getRadius() * 2.0f) >= paddle.getRectY() && //BALL TOP & PADDLE Y
            ball.getBallY() <= paddle.getRectY() + paddle.getRectHeight()) {   // BALL Y & PADDLE HEIGHT
            
            paddle.setColor(ball.getColor());//changing Paddle color

            // Check if the ball is coming from above or below the paddle
            if (ball.getSpeedY() > 0) {  

                Game::ball.setBallY(paddle.getRectY() - (Game::ball.getRadius() * 2.0f)); // MOVE BALL
                Game::ball.setSpeedY(-abs(Game::ball.getSpeedY()));                       //REVERSE SPEED

            } else if (ball.getSpeedY() < 0) {                                          
                Game::ball.setBallY(paddle.getRectY() + paddle.getRectHeight());       
                Game::ball.setSpeedY(abs(ball.getSpeedY()));                          
            }

            //INCREASING SPEED 
            float magnitude = sqrt(Game::ball.getSpeedX() * Game::ball.getSpeedX() + Game::ball.getSpeedY() * Game::ball.getSpeedY());
            float factor = 1.2f;
            if (magnitude > 0) {
                float x = Game::ball.getSpeedX() * factor;
                float y = Game::ball.getSpeedY() * factor;
                Game::ball.setSpeedX(x);
                Game::ball.setSpeedY(y);
            }
        }

        
        int width= blocks.getBlockX();
        int length = blocks.getBlockY();
        int radius = Game::ball.getRadius();

        // Loop through all bricks
        for (int i = 0; i < blocks.getRows(); i++) {
            for (int j = 0; j < blocks.getCols(); j++) {
                if (blocks.getElement(i, j) != 0) {
                    int brickX = j * width;
                    int brickY = height - i * length;

                    //POSITION OF BALL
                    int ballX = Game::ball.getBallX() - radius;
                    int ballY = Game::ball.getBallY() - radius;

                    //BOUNDRIES OF BRICK AND BALL
                   
                    int brick_right = brickX+width;
                    int brick_top   = brickY+length;
                    
                    int ballRight = ballX + radius * 2;
                    int ballBottom = ballY + radius * 2;

                    //COLLISION
                    if (ballRight >=brickX && ballX<=brick_right &&
                        ballBottom>=brickY && ballY<=brick_top) {

                        Game::hitCount = blocks.getHit(i, j);
                        Game::hitCount = hitCount - 1;          // DECREMENTING HIT COUNT
                        blocks.setHit(i, j, hitCount);         // UPDATING HITS

                        if (hitCount==0) {
                            blocks.setElement(i, j, 0);
                            
                            ball.setColor(blocks.getColor(i,j));
                            
                            int row=i;
                            int col=j;

                            Game::score++;
                            //ACTIVATING POWERUPS
                            if (blocks.getColor(row,col) == *colors[LIME_GREEN] && blocks.getElement(row,col) == 0 && !green.isactive() && green.getElement(i,j)!=0) {
                                 green.active(true);
                            }
                            else if(blocks.getColor(row,col) == *colors[LIGHT_CORAL] && blocks.getElement(row,col) == 0 && !pink.isactive() && pink.getElement(i,j)!=0) {
                                    pink.active(true);
                                }
                            else if(blocks.getColor(row,col) == *colors[DARK_RED] && blocks.getElement(row,col) == 0 && !red.isactive() && red.getElement(i,j)!=0) {
                                red.active(true);
                            }
                            else if(blocks.getColor(row,col) == *colors[DARK_GOLDEN_ROD] && blocks.getElement(row,col) == 0 && !yellow.isactive() && yellow.getElement(i,j)!=0) {
                                yellow.active(true);
                            }
                           }


                    Game::ball.setSpeedY(-Game::ball.getSpeedY());          //REVERSE BALL
                    Game::ball.setBallPosition(Game::ball.getBallX(), brickY-radius-1);
                }
            }
        }}
       

        for (int i = 0; i < blocks.getRows(); i++) {
            for (int j = 0; j < blocks.getCols(); j++) {
                if(blocks.getColor(i,j) == *colors[LIME_GREEN]  && blocks.getElement(i,j) == 0 && green.isactive() && green.getElement(i,j)==1) {
                    
                    green.move(2);

                    int PosX = j*blocks.getBlockX();
                    int PosY = height-(i*blocks.getBlockY())+green.getY();

                    //POWERUP COLLIDES PADDLE
                    if (PosX >= paddle.getRectX() && PosX <= paddle.getRectX() + paddle.getRectWidth() &&
                        PosY <= paddle.getRectHeight()) {
                        
                        doublePaddle(); //CALLING POWERUP EFFECT
                        Game::green.setElement(i,j);
                        Game::green.setY(0);
                        Game::green.active(false);
                    }

                    if (PosY <= 0) {
                        Game::green.setElement(i,j);
                        Game::green.setY(0);
                        Game::green.active(false);
                    }
                }
           else if(blocks.getColor(i,j) == *colors[LIGHT_CORAL] && blocks.getElement(i,j) == 0 && pink.isactive()  && pink.getElement(i,j)==1){
                        pink.move(4);
                        int PosX = j*blocks.getBlockX();
                        int PosY = height-(i*blocks.getBlockY())+pink.getY();
                        
                        //POWERUP COLLIDES PADDLE
                        if(PosX>=paddle.getRectX() && PosX<=(paddle.getRectX()+paddle.getRectWidth()) &&
                           PosY<=paddle.getRectHeight()){
                             halvedPaddle(); //CALLING POWERDOWN EFFECT 
                             Game::pink.setY(0);
                             Game::pink.setElement(i,j);
                             Game::pink.active(false);
                           }

                        if(PosY <= 0) {
                        Game::pink.setY(0);
                        Game::pink.setElement(i,j);
                        Game::pink.active(false);
                    }
                }
           else if(blocks.getColor(i,j) == *colors[DARK_RED] && blocks.getElement(i,j) == 0 && red.isactive()  && red.getElement(i,j)==1){
                        red.move(4);
                        int PosX = j*blocks.getBlockX();
                        int PosY = height-(i*blocks.getBlockY())+red.getY();
                        //POWERUP COLLIDES PADDLE
                        if(PosX>=paddle.getRectX() && PosX<=(paddle.getRectX()+paddle.getRectWidth()) &&
                           PosY<=paddle.getRectHeight()){
                              
                             Game::red.setY(0);
                             Game::red.setElement(i,j);
                             Game::red.active(false);
                           }

                        if(PosY <= 0) {
                        Game::red.setY(0);
                        Game::red.setElement(i,j);
                        Game::red.active(false);
                    }
                }
                else if(blocks.getColor(i,j) == *colors[DARK_GOLDEN_ROD] && blocks.getElement(i,j) == 0 && yellow.isactive()  && yellow.getElement(i,j)==1){
                        yellow.move(4);
                        int PosX = j*blocks.getBlockX();
                        int PosY = height-(i*blocks.getBlockY())+yellow.getY();
                        //POWERUP COLLIDES PADDLE
                        if(PosX>=paddle.getRectX() && PosX<=(paddle.getRectX()+paddle.getRectWidth()) &&
                           PosY<=paddle.getRectHeight()){
                             
                             Game::yellow.setY(0);
                             Game::yellow.setElement(i,j);
                             Game::yellow.active(false);
                           }

                        if(PosY <= 0) {
                        Game::yellow.setY(0);
                        Game::yellow.setElement(i,j);
                        Game::yellow.active(false);
                    }
                }
            }
          }
         }
 glutPostRedisplay();
 }
void run(int m){
  getHighScores();
  glutDisplayFunc(Display);     //DISPLAYING OBJECTS
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(SpecialKeys);
  glutIdleFunc(update); //UPDATING GAME STATE 
  glutMainLoop();    //MAIN LOOP
}
static void reset(){

    Game::reset_flag=true;

     Game::ball.setSpeedX(0);
     Game::ball.setSpeedY(0);
     Game::ball.setColor(4);

     Game::tap=true;
    
     Game::paddle.setRectX(width/2);
     Game::paddle.setRectY(30);
     Game::paddle.setColor(6);

     Game::ball.setBallX((Game::width/2)+50);
     Game::ball.setBallY(30+30+Game::ball.getRadius());
    
     Game::blocks.MakeTrue(3,10,0,10);
     Game::red.allocate(blocks.getRows(),blocks.getCols());
     Game::pink.allocate(blocks.getRows(),blocks.getCols());
     Game::green.allocate(blocks.getRows(),blocks.getCols());
     Game::yellow.allocate(blocks.getRows(),blocks.getCols());


};

static void timer(int value) {
    if (paddleDoubled){
            paddle.setRectWidth(paddle.getRectWidth()/2);
            Game::paddleDoubled = false; 
        }
    else if(paddleHalved){
        paddle.setRectWidth(paddle.getRectWidth()*2);
        Game::paddleHalved= false; 
    }
   
    }
static void doublePaddle(){
    paddle.setRectWidth(paddle.getRectWidth()*2);
    Game::paddleDoubled=true;
    glutTimerFunc(3000,timer,0);
};
static void halvedPaddle(){
    paddle.setRectWidth(paddle.getRectWidth()/2);
    Game::paddleHalved=true;
    glutTimerFunc(3000,timer,0);
}  

};

Ball Game::ball;
Paddle Game::paddle;
Bricks Game::blocks;
Green Game::green;
Pink Game::pink;
Red Game::red;
Yellow Game::yellow;
int* Game::highScore=new int [3];
int Game::state=0;
int Game::option = 0; 
int Game::select = 390 - option*50;
bool Game::flag=false;
bool Game::tap=false;
bool Game::reset_flag=false;
int Game::counter=3;
int Game::lives=2;
int Game::score=0;
int Game::width=800;
int Game::height=600;
int Game::mouseX = 0;
int Game::mouseY = 0;
float Game::angle=0.0f;
int Game::hitCount=0;
int Game::index=0;
bool Game::paddleDoubled=false;
bool Game::paddleHalved=false;





int main(int argc, char*argv[]) {
srand(time(NULL));
	Game brickbreaker(800,600,"Brick Breaker",argc, argv); 
    brickbreaker.run(0); 
	
	return 1;
}
#endif 