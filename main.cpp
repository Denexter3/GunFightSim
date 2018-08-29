#include <iostream>
#include <unistd.h>
#include<time.h>

class bullet{
public:
    int CordX;
    int CordY;
};

void irng()
{
    srand(time(NULL));
}

int rng()
{
    int random;
    for(int i=0; i<2; i++)
    {
        random=rand()% 3;
    }
    return random-1;
}

class team
{
public:
    int CordX;
    int CordY;
    int HP=2;

    void shoot(int& BCordX, int& BCordY){
        BCordX=CordX;
        BCordY=CordY-1;
    }

    void ChnPos(int ChnBy)
    {
        bool CanChange=false;
        while(CanChange==false)
        {
            if((CordX+ChnBy>0) && (CordX+ChnBy<=19))
            {
                CanChange=true;
                CordX+=ChnBy;
            }
            else
            {
                ChnBy=rng();
            }
        }

    }

};

class world
{
public:
    int cordx=19;
    int cordy=20;

    void update(int firstX, int firstY, int seconX, int seconY, int BCordX, int BCordY)
    {
        for(int buffY=1; buffY<=cordy; buffY++)
        {
            std::cout << "\n";
            for(int buffX=1; buffX<=cordx; buffX++)
            {
                if((buffX==firstX) && (buffY==firstY)) std::cout << "M";
                else if((buffX==seconX) && (buffY==seconY)) std::cout << "H";
                else if((buffX==BCordX) && (buffY==BCordY)) std::cout << "!";
                else std::cout << ".";
            }
        }

    }
};

void TooFar(int& FCordX, int& SCordX);

void strafe();

int main()
{
    bool game=true;
    bullet Bullet;
    bool BulletShot=false;
    irng();
    world Wrld;
    team first;
    team secon;
    first.CordX=10;
    first.CordY=2;
    secon.CordX=10;
    secon.CordY=18;
    while(game)
    {
        Wrld.update(first.CordX, first.CordY, secon.CordX, secon.CordY, Bullet.CordX, Bullet.CordY);
        if(abs(first.CordX-secon.CordX)>2) TooFar(first.CordX, secon.CordX);
        usleep(500000);
        if(first.CordX==secon.CordX)
        {
            if(BulletShot==false){
                secon.shoot(Bullet.CordX, Bullet.CordY);
                BulletShot=true;
            }
            first.ChnPos(1);
            secon.ChnPos(-1);
        }
        else
        {
            first.ChnPos(rng());
            secon.ChnPos(rng());
        }

        if(BulletShot){
        Bullet.CordY=Bullet.CordY-3;
        }
        if(Bullet.CordY<0) BulletShot=false;
        if((Bullet.CordX==first.CordX) && (Bullet.CordY==first.CordY)){

        break;
        }
        std::cout << "\033[2J\033[1;1H";

    }
    return 0;
}

void TooFar(int& FirstX, int& SeconX)
{
    int averge=(FirstX+SeconX)/2;
    if(FirstX>averge) FirstX--;
    if(FirstX<averge) FirstX++;
    if(SeconX>averge) SeconX--;
    if(SeconX<averge) SeconX++;
}
