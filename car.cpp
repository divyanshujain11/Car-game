#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
using namespace std;

bool exitGame,gameOver, isMoving,bombExplode,dead;
int height,width,life=5,speed,score,myCarX,myCarY,highscore,highestScore[5],enemyX[4],enemyY[4]={-8,-28,-38},enemyPositionX,enemyPositionY,enemyNum;

string BombParticle1[4]={"o   o"," ooo "," ooo ","o   o"};
string BombParticle2[4]={" ooo ","o   o","o   o"," ooo "};
string myCar[4]={" # ",
                 "# #",
                 " # ",
                 "# #"};
void gotoXY(int x,int y){
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void hideCursor(){
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize=100;
    cursor.bVisible=false;
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
}
void startUp(){
    srand(time(NULL));
    exitGame=false;
    isMoving=false;
    gameOver=false;
    dead=false;
    height=20,width=19,myCarX=8,myCarY=16,speed=1,enemyNum=4,score=0;

    for(int i=0;i<enemyNum;i++){
        enemyPositionX=rand()%3;
        if(enemyPositionX==0)enemyX[i]==2;
        else if(enemyPositionX==1)enemyX[i]=8;
        else if(enemyPositionX==2)enemyX[i]=14;
    }

    enemyY[0]=-8;
     enemyY[1]=-18;
    enemyY[2]=-28;
    enemyY[3]=-38;
    
}


void LayOut(){
    for(int i=0;i<height;i++){
        gotoXY(0,i);
        cout<< "#                 #";
        if(i%2==0 && isMoving){
            gotoXY(6,i);
            cout<<"|     |";
    }
        else if(i%2 != 0 && !isMoving){
            gotoXY(6,i);
            cout<<"|     |";
        }
    gotoXY(5,21);
    cout<<"Life : "<<life;
     gotoXY(5,22);
    cout<<"Score : "<<score;
    }
}

void drawMyCar(){
    if(!dead){
        for(int i=0;i<4;i++){gotoXY(myCarX,myCarY+i);
        cout<<myCar[i];}
    }
    else {
        for(int i=0;i<4;i++){gotoXY(myCarX,myCarY+i);
        cout<<"   ";}        
    }
}

void drawMyEnemyCar(){
    for(int i=0;i<enemyNum;i++){
        if(enemyY[i]+3 > 0){
            gotoXY(enemyX[i],enemyY[i]+3);
            cout<<" # ";
        }
        if(enemyY[i]+2 > 0){
            gotoXY(enemyX[i],enemyY[i]+2);
            cout<<"# #";
        }
        if(enemyY[i]+1 > 0){
            gotoXY(enemyX[i],enemyY[i]+1);
            cout<<" # ";
        }
        if(enemyY[i] > 0){
            gotoXY(enemyX[i],enemyY[i]);
            cout<<"# #";
        }
        if(enemyY[i]+3 >= 20){
            gotoXY(enemyX[i],enemyY[i]+3);
            cout<<"   ";
        }
        if(enemyY[i]+2 >= 20){
            gotoXY(enemyX[i],enemyY[i]+2);
            cout<<"   ";
        }
        if(enemyY[i]+1 >= 20){
            gotoXY(enemyX[i],enemyY[i]+1);
            cout<<"   ";
        }
        if(enemyY[i] >= 20){
            gotoXY(enemyX[i],enemyY[i]);
            cout<<"   ";
        }
    }
}
//to control my car using keyboard
void input(){
    if(_kbhit()){
        switch (_getch())
        {
            case 72:
                 if(myCarX>0 && !dead)myCarY-=speed;
                 break;
            case 75:
                 if(myCarX>2 && !dead)myCarX-=6;
                 break;
            case 77:
                 if(myCarX<14 && !dead)myCarX+=6;
                 break;
            case 80:
                 if(myCarX<16 && !dead)myCarY+=speed;
                 break;
        }
    }
}
//all mechanics , rules and logics
void mecha(){
    srand(time(NULL));
    if(isMoving)isMoving=false;
    else isMoving=true;

    for(int i=0;i<enemyNum;i++)enemyY[i]++;
    for(int i=0;i<enemyNum;i++){
        if(enemyY[i]>21){
            enemyPositionX=rand()%3;
            if(enemyPositionX==0)enemyX[i]=2;
            else if(enemyPositionX==1)enemyX[i]=8;
            else if(enemyPositionX==2)enemyX[i]=14;
            enemyY[i]=-8;
            score++;
        }
    }
    for(int i=0;i<enemyNum;i++){
        if((myCarY<=enemyY[i]+3 && myCarY>=enemyY[i] || enemyY[i] >= myCarY && enemyY[i]<=myCarY+3)&& myCarX ==enemyX[i])dead=true;
    }
}
//Bomb explosion effect
void bombExplosion(){
    if(bombExplode){
        for(int i=0;i<4;i++){
            gotoXY(myCarX-1,myCarY-1+i);
            cout<<BombParticle1[i]<<endl;
        }
        bombExplode=false;
    }
    else{
         for(int i=0;i<4;i++){
            gotoXY(myCarX-1,myCarY-1+i);
            cout<<BombParticle2[i]<<endl;
        }
        bombExplode=false;
    }
    Sleep(100);
}


//character crash logic
void died(){
    if(dead){
        life--;
        int count=0;
        while(count!=10){
            input();
            bombExplosion();
            gotoXY(2,22);
            cout<<"you got "<< score <<" score!";
            count++;
         }
        gotoXY(2,22);
        cout<<"                 ";
        highestScore[life]=score;
        startUp();
    }
}

//trasnsition effect
void transistion(){
    for(int i=19;i>=0;i--){
        gotoXY(1,i);
        cout<<"###################";
        Sleep(15);
    }
    for(int i=1;i<20;i++){
        gotoXY(1,i);
        cout<<  "                   ";;
        Sleep(15);
    }
}

//Game over
void game_Over(){
    for(int i=0;i<life;i++){
        if(highestScore[i] >= highestScore[i-1])highscore =highestScore[i];
        else if(highestScore[i] <= highestScore[i-1])highscore=highestScore[i-1];
    }
    if(life==0){
        gameOver=true;
        do{
            gotoXY(0,0);cout<<  "###################";
            gotoXY(0,1);cout<<  "#                 #";
            gotoXY(0,2);cout<<  "#                 #";
            gotoXY(0,3);cout<<  "#                 #";
            gotoXY(0,4);cout<<  "#                 #";
            gotoXY(0,5);cout<<  "#                 #";
            gotoXY(0,6);cout<<  "#                 #";
            gotoXY(0,7);cout<<  "#   GAME OVER!!   #";
            gotoXY(0,8);cout<<  "#    HIGHSCORE    #";
            gotoXY(0,9);cout<<  "#"<< highscore <<"#";
            gotoXY(0,10);cout<< "#                 #";
            gotoXY(0,11);cout<< "#                 #";
            gotoXY(0,12);cout<< "#                 #";
            gotoXY(0,13);cout<< "#                 #";
            gotoXY(0,14);cout<< "#                 #";
            gotoXY(0,15);cout<< "#    PRESS 'x'    #";
            gotoXY(0,16);cout<< "#     TO EXIT     #";
            gotoXY(0,17);cout<< "#                 #";
            gotoXY(0,18);cout<< "#                 #";
            gotoXY(0,19);cout<< "###################";
            gotoXY(0,20);cout<< "#                 #";
            gotoXY(0,21);cout<< "#                 #";
        }while(getch()!='x');
        exit(1);
        
    }
}

//spiaral effect
void spiralEffect(){
    int row=1,col=1;
    int lastRow=height-2,lastCol=width-2;
    while(row<=lastRow && col<=lastCol){
        for(int i=col;i<=lastCol;i++){
            gotoXY(i,row);
            cout<<"#";
            Sleep(2);
        }row++;

        for(int i=row;i<=lastRow;i++){
            gotoXY(lastCol,i);
            cout<<"#";
        }lastCol--;
   
    if(row<=lastRow){
        for(int i=lastCol;i>=col;i--){
            gotoXY(i,lastRow);
            cout<<"#";
            Sleep(2);
        }lastRow--;
    }
    if(col<=lastCol){
        for(int i=lastRow;i>=row;i--){
            gotoXY(col,i);
            cout<<"#";
        }col++;
    }
    }
    row=1,col=1;
    lastRow=height-2,lastCol=width-2;
    while(row<=lastRow && col<=lastCol){
        for(int i=col;i<=lastCol;i++){
            gotoXY(i,row);
            cout<<" ";
            Sleep(2);
        }row++;

        for(int i=row;i<=lastRow;i++){
            gotoXY(lastCol,i);
            cout<<" ";
        }lastCol--;
   
    if(row<=lastRow){
        for(int i=lastCol;i>=col;i--){
            gotoXY(i,lastRow);
            cout<<" ";
            Sleep(1);
        }lastRow--;
    }
    if(col<=lastCol){
        for(int i=lastRow;i>=row;i--){
            gotoXY(col,i);
            cout<<" ";
        }col++;
    }
    }    
}
//Splash Green
void splashSreen(){
            gotoXY(0,0);cout<<  "###################";
            gotoXY(0,1);cout<<  "#                 #";
            gotoXY(0,2);cout<<  "#        #        #";
            gotoXY(0,3);cout<<  "#       ##        #";
            gotoXY(0,4);cout<<  "#        #        #";
            gotoXY(0,5);cout<<  "#        #        #";
            gotoXY(0,6);cout<<  "#       ###       #";
            gotoXY(0,7);cout<<  "#                 #";
            gotoXY(0,8);cout<<  "#     #  #  #     #";
            gotoXY(0,9);cout<<  "#     #  ## #     #";
            gotoXY(0,10);cout<< "#     #  # ##     #";
            gotoXY(0,11);cout<< "#     #  #  #     #";
            gotoXY(0,12);cout<< "#                 #";
            gotoXY(0,13);cout<< "#        #        #";
            gotoXY(0,14);cout<< "#       ##        #";
            gotoXY(0,15);cout<< "#        #        #";
            gotoXY(0,16);cout<< "#        #        #";
            gotoXY(0,17);cout<< "#       ###       #";
            gotoXY(0,18);cout<< "#                 #";
            gotoXY(0,19);cout<< "###################";
            Sleep(500);
}
//print game title
void games(){
    do{
            gotoXY(0,0);cout<<  "###################";
            gotoXY(0,1);cout<<  "#                 #";
            gotoXY(0,2);cout<<  "#   BRICK GAME    #";
            gotoXY(0,3);cout<<  "#                 #";
            gotoXY(0,4);cout<<  "#    RACE CAR     #";
            gotoXY(0,5);cout<<  "#                 #";
            gotoXY(0,6);cout<<  "#                 #";
            gotoXY(0,7);cout<<  "#                 #";
            gotoXY(0,8);cout<<  "#    #   |   #    #";
            gotoXY(0,9);cout<<  "#    #   |   #    #";
            gotoXY(0,10);cout<< "#    #   |   #    #";
            gotoXY(0,11);cout<< "#    #   |   #    #";
            gotoXY(0,12);cout<< "#                 #";
            gotoXY(0,13);cout<< "#                 #";
            gotoXY(0,14);cout<< "#                 #";
            gotoXY(0,15);cout<< "#                 #";
            gotoXY(0,16);cout<< "#  PRESS 'Space'  #";
            gotoXY(0,17);cout<< "#    TO START     #";
            gotoXY(0,18);cout<< "#                 #";
            gotoXY(0,19);cout<< "###################";
    }while(getch()!=32);
}

int main(){
    hideCursor();
    startUp();
    splashSreen();
    spiralEffect();
    transistion();
    games();
while(!dead){
    LayOut();
    input();
    mecha();
    drawMyCar();
    drawMyEnemyCar();
    died();
    game_Over();
    Sleep(50);
}
system("cls");
cout<<"\n\n\n\n\n\tThank you for playing";
}
