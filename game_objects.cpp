#include "game_objects.h";
#include "util.h";
#include<string>

//---xxx---DEFINING BALL CLASS---xxx---
int Ball::ballX = 0;
int Ball::ballY = 0;
int Ball::radius = 10;

float Ball::defaultspeed=0.0f;
float Ball::speedX=0.0f;
float Ball::speedY=0.0f;
int Ball::color=4;

Ball::Ball() {};
Ball::~Ball() {};

int Ball::getBallX() {return ballX;}
int Ball::getBallY() {return ballY;}
int Ball::getRadius(){return radius;}

float Ball::getSpeed(){return defaultspeed; }
float Ball::getSpeedX(){return speedX;}
float Ball::getSpeedY(){return speedY;}
int  Ball::getColor(){return color;}


void Ball::setBallX(int x)      {ballX=x;}
void Ball::setBallY(int y)      {ballY=y;}
void Ball::setBallRadius(int r) {radius=r;}

void Ball::setSpeed(int s)      {defaultspeed=s;}
void Ball::setSpeedX(int x)     {speedX=x;}
void Ball::setSpeedY(int y)     {speedY=y;}
void Ball::setColor(int x)    {Ball::color=x;}

void Ball::addX(int x){ballX+=x;}
void Ball::addY(int y){ballY+=y;}

void Ball::setBallPosition(int x, int y) {ballX = x; ballY = y;}

//---xxx---DEFINING PADDLE CLASS---xxx---
int Paddle::rectX = 0;
int Paddle::rectY = 0;
int Paddle::rectWidth = 0;
int Paddle::rectHeight = 0;
int Paddle::color = 6;

Paddle::Paddle(){};
Paddle::~Paddle(){};

int Paddle::getRectX()      {return rectX;}
int Paddle::getRectY()      {return rectY;}
int Paddle::getRectWidth()  {return rectWidth;}
int Paddle::getRectHeight() {return rectHeight;}
int Paddle::getColor()      {return color;}


void Paddle::setRectX(int x)          {rectX=x;}
void Paddle::setRectY(int y)          {rectY=y;}
void Paddle::setRectWidth(int width)  {rectWidth=width;}
void Paddle::setRectHeight(int height){rectHeight=height;}
void Paddle::setColor(int x)          {Paddle::color=x;}

//---xxx---DEFINING BRICKS CLASS---xxx---

int  Bricks:: blockX=0;
int  Bricks:: blockY=0;
int **Bricks::blocks = nullptr;
 
int  Bricks:: rows=0;
int  Bricks:: cols=0;
int **Bricks::hit=nullptr;
int **Bricks::color=nullptr;

Bricks::Bricks(){};
Bricks::~Bricks(){};

void Bricks::Allocate(int r,int c){
    rows=r;
    cols=c;
    totalBlocks=rows*cols;

    Bricks::blocks = new int *[rows];
    for (int i=0; i<rows;i++) {
         Bricks::blocks[i] = new int [cols];
         for (int j=0; j<cols;j++) {
             Bricks::blocks[i][j]=0;
         }
      }
    Bricks::hit = new int*[rows];
    for(int i=0;i<rows;i++){
        Bricks::hit[i]= new int [cols];
        for (int j=0; j<cols;j++) {
             Bricks::hit[i][j]=0;
         }
    }
    Bricks::color = new int*[rows];
    for(int i=0;i<rows;i++){
        Bricks::color[i]= new int[cols];
    }
  


}

void Bricks::MakeTrue(int startRow, int r, int startCol, int c) {
    for (int i = startRow; i <= r; i++) {
        for (int j = startCol; j <= c; j++) {
            Bricks::blocks[i][j] = rand() % 5 + 1;
                 if (Bricks::blocks[i][j] == 1) {Bricks::hit[i][j] = 1; Bricks::color[i][j]=1;}
            else if (Bricks::blocks[i][j] == 2) {Bricks::hit[i][j] = 2; Bricks::color[i][j]=2;} 
            else if (Bricks::blocks[i][j] == 3) {Bricks::hit[i][j] = 2; Bricks::color[i][j]=3;} 
            else if (Bricks::blocks[i][j] == 4) {Bricks::hit[i][j] = 3; Bricks::color[i][j]=4;}
            else if (Bricks::blocks[i][j] == 5) {Bricks::hit[i][j] = 3; Bricks::color[i][j]=5;}
        }
    }


}

int  Bricks::getBlockX() {return blockX;}
int  Bricks::getBlockY() {return blockY;}
int  Bricks::getRows()   {return rows;}
int  Bricks::getCols()   {return cols;}
int  Bricks::getTotalBlocks(){return totalBlocks;}
int  Bricks::getElement(int r,int c){return blocks[r][c];}
int  Bricks::getHit(int r,int c){return hit[r][c];}
int Bricks::getColor(int r,int c){return color[r][c];}

void Bricks::setBlockX(int x)         {blockX=x;}
void Bricks::setBlockY(int y)         {blockY=y;}
void Bricks::setRows(int r)           {rows=r;}
void Bricks::setCols(int c)           {cols=c;}
void Bricks::setTotalBlocks(int total){totalBlocks=total;}
void Bricks::setElement(int rows,int cols,int x){blocks[rows][cols]=x;}
void Bricks::setHit(int r,int c,int x){hit[r][c]=x;}
//void Bricks::setColor(int r,int c,std::string x){color[r][c]=x;}
// Bricks::setBlocks(bool** blocksArray){}


// // //---xxx---POWERUP CLASS---xxx---

//----xxx----xxx---xxx---xxx---xxx--xxx---
int PowerUp::x=0;
int PowerUp::y=0;
bool PowerUp::make=false;
int **PowerUp::arr=nullptr;

void PowerUp::allocate(int r,int c){
    PowerUp::arr=new int *[r];
    for(int i=0;i<r;i++){
        PowerUp::arr[i]=new int [c];
        for(int j=0;j<c;j++){
            PowerUp::arr[i][j]=1;
        }
    }
}

void PowerUp::active(bool x){PowerUp::make=x;}
bool PowerUp::isactive(){return make;}
void PowerUp::move(int x){PowerUp::y-=x;}
void PowerUp::setX(int a){x=a;}
void PowerUp::setY(int b){y=b;}
void PowerUp::setElement(int r,int c){PowerUp::arr[r][c]=0;}
int PowerUp::getElement(int r,int c){return arr[r][c];}

int PowerUp::getX(){return x;}
int PowerUp::getY(){return y;}

//----xxx----xxx---xxx---xxx---xxx--xxx---
Pink::Pink(){};
Red::Red(){};
Green::Green(){};
Yellow::Yellow(){};