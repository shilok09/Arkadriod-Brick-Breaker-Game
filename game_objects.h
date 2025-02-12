#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H
#include<string>


class Ball {
private:
    static int ballX;
    static int ballY;
    static int radius;
    static float defaultspeed;
    static float speedX;
    static float speedY;
    static int  color;

public:
   
    Ball();
    ~Ball();

    static int getBallX();
    static int getBallY();
    static int getRadius();

    float getSpeed();
    float getSpeedX();
    float getSpeedY();
    int  getColor();

    void setBallX(int x);
    void setBallY(int y);
    void setBallRadius(int r);
    
    void setSpeed(int s);
    void setSpeedX(int x);
    void setSpeedY(int y);
    void setColor(int x);

    void addX(int x);
    void addY(int y);
    

    static void setBallPosition(int x, int y);
};

class Paddle {
private:
    static int rectX;
    static int rectY;
    static int rectWidth;
    static int rectHeight;
    static int color;

public:
    
    Paddle();
    ~Paddle();

    static int getRectX();
    static int getRectY();
    static int getRectWidth();
    static int getRectHeight();
    static int getColor();

    static void setRectX(int x);
    static void setRectY(int y);
    static void setRectWidth(int width);
    static void setRectHeight(int height);
    static void  setColor(int x);
};
class Bricks{
    private:

    static int   blockX;
    static int   blockY;
    static int **blocks;
    int          totalBlocks;
    static int **color;
    static int   rows;
    static int   cols;
    static int **hit;

    public:
    Bricks();
    ~Bricks();

    void Allocate(int rows,int cols);
    void MakeTrue(int startRow, int r, int startCol, int c);

    int    getBlockX();
    int    getBlockY();
    //bool **getBlocks();
    int    getRows();
    int    getCols();
    int    getTotalBlocks();
    int getHit(int r,int c);
    int getElement(int rows,int cols);
    int getColor(int r,int c);
  
    void setElement(int rows,int cols,int x);
    static void setHit(int r,int c,int x);
    static void setBlockX(int x);
    static void setBlockY(int y);
    //static void setBlocks(bool** blocksArray);
    static void setRows(int rows);
    static void setCols(int cols);
           void setTotalBlocks(int total);


};

class PowerUp{
    protected:
    static int x;
    static int y;
    static bool make;
    static int **arr;

    public:
    PowerUp(){}
    void allocate(int r,int c);
    void active(bool x);
    bool isactive();
    void move(int x);
    void setX(int a);
    void setY(int b);
    int getElement(int r,int c);
    void setElement(int r,int c);


    int getX();
    int getY();
    
};
class Pink:public PowerUp{
    public:
    Pink();
};
class Red:public PowerUp{
    public:
    Red();;
};
class Green:public PowerUp{
    public:
    Green();
};
class Yellow:public PowerUp{
    public:
    Yellow();
};




#endif 
