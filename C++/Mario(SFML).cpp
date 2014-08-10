#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <conio.h>
#include <cstring>
#include <string>
#include <math.h>
#include <locale.h>
#include <Windows.h>


using namespace sf;




float offsetX=0, offsetY=0;
int sc=0,hit=0;
float dyp;
char score[20]="score 0";
bool eexit=0;
bool dishit=0;
bool nastflag=0;int nflag=0;//для настроек
FloatRect rectp;
Sprite glabsprite;
Texture t;
int volmus=0,volsou=0;




void texture()
{
    t.loadFromFile("Картинки\\Mario_Tileset.png");
    glabsprite.setTexture(t);
}




//Сохранение параметров
void save()
{
    FILE *pTextFile = fopen("Config.txt", "w");
    char *text0="Configuration\n";
    char *text1="1. Музыка:";
    char *text2="2. Звук:";
    char n1=';';
    char n2='\n';
    if(pTextFile==NULL)
    {
        printf("Problems");
    }
    fprintf(pTextFile, "%s%s%d%c%c%s%d%c", text0,text1,volmus,n1,n2,text2,volsou,n1);

    fclose(pTextFile);
}




//Загрузка начальных параметров
void loading()
{
    int i,sch=0,nm=200;
    bool flag=0;
    char arr[nm];

    FILE *pTextFile=fopen("Config.txt", "r");
    if(pTextFile==NULL)
    {
        save();
    }
    else
    {
        while(fgets(arr, nm, pTextFile)!=NULL)
        {
            flag=0;
            for(i=0;arr[i]!=';'&&arr[i]!='\0';i++)
            {
                if(arr[i]==':')
                {
                    sch++;
                    i++;
                    flag=1;
                }

                if(flag)
                {
                    switch(sch)
                    {
                        case 1:
                        volmus=volmus*10+(arr[i]-48);
                        break;

                        case 2:
                        volsou=volsou*10+(arr[i]-48);
                        break;
                    }
                }
            }
        }
    }
    fclose(pTextFile);
}



//Настройки
bool settings(RenderWindow &window,int sd=0,bool menu=0)
{
    int nx=464+volmus-sd,ny=142,nx2=464+volsou-sd,ny2=188;
    //int nflag=0;

    Texture nast2_texture8,run_texture9,run2_texture10;
    nast2_texture8.loadFromFile("Картинки\\Настройки2.png");
    run_texture9.loadFromFile("Картинки\\Бегунок.png");
    run2_texture10.loadFromFile("Картинки\\Бегунок.png");
    Sprite nast2(nast2_texture8),run(run_texture9),run2(run2_texture10);

    nast2.setPosition(350-sd,30);
    window.draw(nast2);

    run.setPosition(nx,ny);
    run2.setPosition(nx2,ny2);


    if(nflag==0)
    {
        if (IntRect(nx,ny,13,25).contains(Mouse::getPosition(window))) {nflag=1;}
        if (IntRect(nx2,ny2,13,25).contains(Mouse::getPosition(window))) {nflag=2;}
    }


    if(Mouse::isButtonPressed(Mouse::Left))
    {
        switch(nflag)
        {
            case 1:
            nx=Mouse::getPosition(window).x-5;
            if(nx<464-sd) nx=464-sd;
            if(nx>564-sd) nx=564-sd;
            run.setPosition(nx,ny);
            volmus=nx-464+sd;
            break;

            case 2:
            nx2=Mouse::getPosition(window).x-5;
            if(nx2<464-sd) nx2=464-sd;
            if(nx2>564-sd) nx2=564-sd;
            run2.setPosition(nx2,ny2);
            volsou=nx2-464+sd;
            break;
        }
    }
    else
    nflag=0;

    Event event;
    while (window.pollEvent(event))
    {
        if(event.type==Event::Closed) {menu=0;window.close();eexit=1;}

        if(event.mouseButton.button==Mouse::Left&&event.type==Event::MouseButtonReleased) {nflag=0;}

        if(event.key.code==Keyboard::Escape&&event.type==Event::KeyReleased) {nastflag=0;}
    }

    window.draw(run);
    window.draw(run2);

    return menu;
}





//Сохранение и обработка результатов...
void savescore(char name[],char timearr[])
{
    int i,j,a=0,b,max,nom;
    int s;
    bool flag,flag2=0;
    int record[11];
    char arr[50],s1[10];//,name[50];
    char arr2[11][50];

    for(i=0;i<11;i++)
    for(j=0;j<50;j++)
    {
        arr2[i][j]=0;
        //name[j]=0;
        arr[j]=0;
    }


    //printf("%s",name);getch();


    //gets(name);
    for(i=0;name[i]!='\0';i++);
    name[i]=' ';
    name[i+1]='\0';
    itoa(sc,s1,10);
    strncat(name,s1,10);
    for(i=0;name[i]!='\0';i++);
    name[i]=' ';
    strncat(name,timearr,6);



    FILE *pTextFile=fopen("MarioScore.txt", "r");
    if(pTextFile==NULL)
    {
        printf("Не найден файл \n\n");
        FILE *pTextFile=fopen("MarioScore.txt","w");
        fclose(pTextFile);
    }
    else
    {
    for(i=0;i<11&&fgets(arr, 50, pTextFile)!=NULL;i++)
    {
        flag2=0;
        for(j=0,a=0;arr[j]!='\0';j++,a++)
        {
            if(arr[j]>='0'&&arr[j]<='9'||arr[j]==':'||arr[j]==' '||arr[j]>='a'&&arr[j]<='z'||arr[j]>='A'&&arr[j]<='Z')
            {
                arr2[i][j]=arr[j];
                a++;
                flag2=1;
            }
        }
        arr2[i][j]='\0';
        if(!flag2)
        i--;
    }
    a=i;
    }


    fclose(pTextFile);


    /*printf("%d\n\n\n",a);
    for(i=0;i<a;i++)
    {
        for(j=0;j<50;j++)
        printf("%d",arr2[i][j]);

        printf("\n\n");
    }*/


    for(i=0;i<a;i++)
    {
        s=0;
        flag=0;
        for(j=0;arr2[i][j]!=0;j++)
        {
            if(arr2[i][j]==' '&&!flag)
            {
                j++;
                flag=1;
            }
            if(arr2[i][j]==' '&&flag)
            {
                break;
            }
            if(flag&&arr2[i][j]>='0'&&arr2[i][j]<='9')
            {
                s=s*10+(arr2[i][j]-48);
            }
        }
        record[i]=s;
    }

    record[i]=sc;


    for(i=0;i<=a;i++)
    {
        max=record[i];
        nom=i;
        for(j=i;j<=a;j++)
        {
            if(max<record[j])
            {
                max=record[j];
                nom=j;
            }
        }
        record[nom]=record[i];
        record[i]=max;
    }

    /*printf("\n");
    for(i=0;i<=a;i++)
    printf("%d ",record[i]);*/


    for(i=0;record[i]!=sc;i++);

    b=i;

    if(a<10)
    a++;

    for(i=a;i>=b;i--)
    {
        for(j=0;j<50;j++)
        {
            arr2[i][j]=arr2[i-1][j];
        }
    }


    /*for(i=0;i<a;i++)
    {
        for(j=0;j<50;j++)
        printf("%c",arr2[i][j]);

        printf("\n");
    }
    printf("\n\n\n%s\n\n\n",name);*/


    for(i=0;name[i]!=0;i++)
    arr2[b][i]=name[i];

    arr2[b][i]='\0';



    /*for(i=0;i<a;i++)
    {
        for(j=0;j<50;j++)
        printf("%c",arr2[i][j]);

        printf("\n");
    }*/



    FILE *pText = fopen("MarioScore.txt", "w");
    for(i=0;i<=a&&i<10;i++)
    {
    if(i==0)
        fprintf(pText,"%s", arr2[i]);
    else
        fprintf(pText,"\n%s", arr2[i]);
    }
    fclose(pText);

}




void menu(RenderWindow &window)
{
    Font font;
    font.loadFromFile("tomb.ttf");
    Text Score("0",font,15);
    Score.setColor(Color::White);
    Text Score2("0",font,15);
    Score2.setColor(Color::White);
    Text Score3("0",font,15);
    Score3.setColor(Color::White);


    bool menu=1;
    bool rekflag=0;
    int nm=100;
    char name[nm],scr[nm],tim[nm];
    int i,a;
    char arr[nm];
    arr[0]='\0';
    //int nflag=0;
    //int nx=464+volmus,ny=142,nx2=464+volsou,ny2=188;



    Texture glav_texture1,nov_texture2,rek_texture3,nast_texture4,vix_texture5,rek2_texture6,cursor_texture7;
	glav_texture1.loadFromFile("Картинки\\Главный.png");
	nov_texture2.loadFromFile("Картинки\\Новая.png");
    rek_texture3.loadFromFile("Картинки\\Рекорды.png");
    nast_texture4.loadFromFile("Картинки\\Настройки.png");
    vix_texture5.loadFromFile("Картинки\\Главныйвыход.png");
    rek2_texture6.loadFromFile("Картинки\\Рекорды2.png");
    cursor_texture7.loadFromFile("Картинки\\Курсор.png");;
	Sprite glav(glav_texture1),nov(nov_texture2),rek(rek_texture3),nast(nast_texture4),vix(vix_texture5),rek2(rek2_texture6),cursor(cursor_texture7);
	int MenuNum=0;
	glav.setPosition(0,0);
	nov.setPosition(35,110);
    rek.setPosition(35,170);
    nast.setPosition(35,230);
    vix.setPosition(35,290);
    rek2.setPosition(350,30);


/////меню
	while(menu)
	{

	    Event event;
        while (window.pollEvent(event))
        {
            if(event.type==Event::Closed) {menu=0;window.close();eexit=1;}

            if(event.key.code==Keyboard::Escape&&event.type==Event::KeyReleased) {rekflag=0;nastflag=0;}
		}


        int h=115;
	   nov.setColor(Color::Black);
	   rek.setColor(Color::Black);
	   nast.setColor(Color::Black);
	   vix.setColor(Color::Black);
	   MenuNum=0;
	   window.clear(Color(0,0,0));

	   if (IntRect(35,110,155,30).contains(Mouse::getPosition(window))) {nov.setColor(Color::Yellow); MenuNum=1;}
       if (IntRect(35,170,125,30).contains(Mouse::getPosition(window))) {rek.setColor(Color::Yellow); MenuNum=2;}
       if (IntRect(35,230,150,30).contains(Mouse::getPosition(window))) {nast.setColor(Color::Yellow); MenuNum=3;}
       if (IntRect(35,290,90,30).contains(Mouse::getPosition(window))) {vix.setColor(Color::Yellow); MenuNum=4;}

	   if (Mouse::isButtonPressed(Mouse::Left))
	     {
			 if (MenuNum==1) {rekflag=0;menu=0;}

			 if (MenuNum==2) {nastflag=0;rekflag=1;}

			 if (MenuNum==3) {rekflag=0;nastflag=1;}

			 if (MenuNum==4) {rekflag=0;menu=0;window.close();eexit=1;}

	     }


		    window.draw(glav);
            window.draw(nov);
			window.draw(rek);
			window.draw(nast);
			window.draw(vix);


            if(rekflag)
            {
                window.draw(rek2);

                FILE *pTextFile=fopen("MarioScore.txt", "r");
                if(pTextFile==NULL)
                {
                    printf("Не найден файл \n\n");
                    FILE *pTextFile=fopen("MarioScore.txt","w");
                    fclose(pTextFile);
                }
                else
                {
                    while(fgets(arr, nm, pTextFile)!=NULL)
                    {
                    for(i=0;arr[i]!=' ';i++)
                    {
                        name[i]=arr[i];
                    }
                    name[i]='\0';

                    for(i++,a=0;arr[i]!=' ';i++,a++)
                    {
                        scr[a]=arr[i];
                    }
                    scr[a]='\0';

                    for(i++,a=0;arr[i]!='\0';i++,a++)
                    {
                        tim[a]=arr[i];
                    }
                    tim[a]='\0';

                    h+=20;
                    Score.setPosition(370,h);
                    Score.setString(name);
                    Score.setColor(Color::Blue);
                    window.draw(Score);

                    Score2.setPosition(480,h);
                    Score2.setString(scr);
                    Score2.setColor(Color::Blue);
                    window.draw(Score2);

                    Score3.setPosition(530,h);
                    Score3.setString(tim);
                    Score3.setColor(Color::Blue);
                    window.draw(Score3);
                    }
                }
                fclose(pTextFile);
            }


            if(nastflag) {menu=settings(window,0,menu);}



            //Курсор
            cursor.setPosition(Mouse::getPosition(window).x,Mouse::getPosition(window).y);
            window.draw(cursor);
            //Курсор


		window.display();
	}
////////////////
}


const int H = 17;
const int W = 200;


String TileMap[H] = {
"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0                                                 0",
"0                                                                                    w                                                               0                                                 0",
"0                   w                                  w                   w                                                                         0                                                 0",
"0                                      w                                       kk                                                                    0                                                 0",
"0                  ccccc                                                      k  k    k    k                                                         0                                 rr   r  rr  rrr 0",
"0                 ccccccc                                                     k      kkk  kkk  w                                                     0                                 r r r r r r  r  0",
"0                  ccccc                                                r     k       k    k                                                         0                                 r r rrr rr   r  0",
"0                                                                      rr     k  k                                   cccc   c  c   ccc               0                                 r r r r r r  r  0",
"0                                                                     rrr      kk                     e              c   c  c  c  c   c              0                                 rr  r r r r  r  0",
"0               c    kckck                                           rrrr                             e              c   c  cccc  c   c              0                                                 0",
"0                                      t0                           rrsrr                            rrr             c   c  c  c  c   c              0                                   ccccc ccccc   0",
"0Ge                                    00              t0          rriirr            G                               cccc   c  c   ccc               0                                 cc  c ccc c  cc 0",
"0 e         d    g       d             00              00         iiiiiii                                                                            0                                    cc     cc    0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP000000000000000000000000000000PPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP000000000000000000000000000000PPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP000000000000000000000000000000PPPPPPPPPPPPPPPPPPPP",
};

String sTile[H]=TileMap;



class PLAYER
{
public:
float currentFrame;
float dx;
bool onGround,notspr=0,flip=1;
float timer=0,timer2=0;
bool record=0;

    PLAYER()
   {
    texture();
	rectp = FloatRect(100,180,16,16);
	dx=dyp=0.1;
	currentFrame = 0;
   }


   void update(float time)
   {

	 rectp.left += dx * time;
     Collision(0);


	 if (!onGround) dyp=dyp+0.0005*time;
	 rectp.top += dyp*time;
	 onGround=false;
     Collision(1);


     currentFrame += time * 0.005;
     if (currentFrame > 3) currentFrame -= 3;


    if (dx==0&&!notspr&&flip) glabsprite.setTextureRect(IntRect(82,144,16,16));
    if (dx==0&&!notspr&&!flip) glabsprite.setTextureRect(IntRect(82+16,144,-16,16));

    if (dx>0&&!notspr) {glabsprite.setTextureRect(IntRect(112+31*int(currentFrame),144,16,16));flip=1;}
	if (dx<0&&!notspr) {glabsprite.setTextureRect(IntRect(112+31*int(currentFrame)+16,144,-16,16));flip=0;}


	if(dishit)
	{
	    timer2+=time;
	    if(timer2>100)
	    {
	        notspr=1;
	        glabsprite.setTextureRect(IntRect(0,20,16,16));
	    }
	    if(timer2>300)
	    {
	        notspr=0;
	        timer2=0;
	    }
	}


	 glabsprite.setPosition(rectp.left - offsetX, rectp.top - offsetY);

	 dx=0;


	 //Урон по персонажу
        switch(hit)
        {
            case 1:
            timer+=time;
            if(timer>3000)
            {
                hit=0;
                timer=0;
                dishit=0;
                notspr=0;
                //glabsprite.setColor(Color::Green);
            }
            break;
        }
	//Урон по персонажу


   }


   void Collision(int num)
    {

	for (int i = rectp.top/16 ; i<(rectp.top+rectp.height)/16; i++)
		for (int j = rectp.left/16; j<(rectp.left+rectp.width)/16; j++)
			 {
				 if ((TileMap[i][j]=='P') || (TileMap[i][j]=='k') || (TileMap[i][j]=='0') || (TileMap[i][j]=='r') || (TileMap[i][j]=='t'))
				                         {
												   if (dyp>0 && num==1)
												   { rectp.top =   i*16 -  rectp.height;  dyp=0;   onGround=true; }
											       if (dyp<0 && num==1)
												   { rectp.top = i*16 + 16;   dyp=0;}
												   if (dx>0 && num==0)
												   { rectp.left =  j*16 -  rectp.width; }
											       if (dx<0 && num==0)
												   { rectp.left =  j*16 +16;}
										 }

				 if (TileMap[i][j]=='c') {
                                                TileMap[i][j]=' ';
                                                Score(1);
			                          	 }

                if (TileMap[i][j]=='i') {
                                                TileMap[i][j]=' ';
                                                Score(2);
			                          	 }

                if (TileMap[i][j]=='s') {
                                                TileMap[i][j]=' ';
                                                TileMap[12][75]='c'; TileMap[12][76]='c'; TileMap[12][77]='c'; TileMap[12][78]='c'; TileMap[12][79]='c';
                                                TileMap[11][75]='c'; TileMap[11][76]='c'; TileMap[11][77]='c'; TileMap[11][78]='c'; TileMap[11][79]='c';
			                          	 }

                if (TileMap[i][j]=='e') {
                                                record=1;
			                          	 }
			 }

    }


    void Score(int a)
    {
        sc+=a;
        score[6]='\0';
        char s1[10];
        itoa(sc,s1,10);
        strncat(score,s1,10);

        //Бонус
        if(sc>100)
        {
            TileMap[13][149]=' '; TileMap[12][149]=' ';
        }
    }


    //функции возвращений
    //FloatRect rectp() {return rect;}
    //int dyp() {return dy;}

    //+++++++++++++++++++Изменение цвета+++++++++++++++++
    //void izm() {printf("aa");glabsprite.setColor(Color::Red);}

};



class ENEMY: public PLAYER
{

public:

float dx,dy;
FloatRect rect;
Sprite sprite2;
float currentFrame;
bool life;
float timer=0;
bool dis=false;
Texture t;


   void set(int x, int y)
   {
    t.loadFromFile("Картинки\\Mario_Tileset.png");
	sprite2.setTexture(t);
	rect = FloatRect(x,y,16,16);

    dx=0.05;
	currentFrame = 0;
	life=true;
   }

   void update(float time,int x0,int y0)
   {//printf("%d",rectplayer.intersects( rect ));

	 rect.left += dx * time;

     Collision();


     currentFrame += time * 0.005;
     if (currentFrame > 2) currentFrame -= 2;

    sprite2.setTextureRect(IntRect(18*int(currentFrame),   0, 16,16));
    if (!life) sprite2.setTextureRect(IntRect(58, 0, 16,16));


    //Перс+моб
    if  (rectp.intersects( rect ))
		 {
			 if (life)
			 {
                if (dyp>0)
                { dx=0; dyp=-0.2; life=false; Score(10);}
                else
                { dx*=-1; if(hit==0) {hit=1; dyp=-0.15; /*glabsprite.setColor(Color::Red)*/dishit=1; Score(-10);}  }
			 }
		 }

		 if(!life)
		 {
		     timer+=time;
		     if(timer>1000)
		     {
		         dis=true;
		         if(timer>11000||(Keyboard::isKeyPressed(Keyboard::R)))
		         {
		             life=true;
		             set(x0,y0);
		             dis=false;
		             timer=0;
		         }
		     }
		 }
    //Перс+моб



	sprite2.setPosition(rect.left - offsetX, rect.top - offsetY);


   }


   void Collision()
  {

	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 if ((TileMap[i][j]=='P') || (TileMap[i][j]=='0') || (TileMap[i][j]=='i'))
            {
                if (dx>0)
                { rect.left =  j*16 - rect.width; dx*=-1; }
                else if (dx<0)
                { rect.left =  j*16 + 16;  dx*=-1; }
            }
  }


};






int main()
{
    setlocale(LC_ALL, "Russian");
    bool pause=false,end=false,cur=false,esc=false;
    int MenuNum=0;
    bool game;


    sf::RenderWindow window(VideoMode(600, 400, 32), "Game");

    window.setMouseCursorVisible(false);

    loading();

    menu(window);

while(!eexit)
{
    char timearr[6]="00:00",ttt[3];
    int timer=0,t1=0,t2=0;

    game=1;

    Font font;
    if (!font.loadFromFile("tomb.ttf"))
        return EXIT_FAILURE;

    Text Score("0",font,15);
    Score.setPosition(10,10);
    Score.setColor(Color::Green);


    Score.setString(score);



    //Время
    Text GameT("00:00",font,15);
    GameT.setPosition(550,10);
    GameT.setColor(Color::Green);

    GameT.setString(timearr);




	Texture tileSet;
	tileSet.loadFromFile("Картинки\\Mario_Tileset.png");


	PLAYER Mario;
	ENEMY  enemy1;
	ENEMY  enemy2;
	ENEMY  enemy3;
	enemy1.set(54*16,13*16);
	enemy2.set(38*16,13*16);
	enemy3.set(80*16,13*16);


	Sprite tile(tileSet);



    //Для записи рекорда
    Texture ok_texture,otm_texture,fon_texture;
    ok_texture.loadFromFile("Картинки\\Окей.png");
    otm_texture.loadFromFile("Картинки\\Отмена.png");
    fon_texture.loadFromFile("Картинки\\Рекорд.png");
    Sprite ok(ok_texture);
    Sprite otm(otm_texture);
    Sprite fon(fon_texture);
    ok.setPosition(210,200);
    otm.setPosition(300,200);
    fon.setPosition(150,100);

    Font font2;
    font2.loadFromFile("font.ttf");

    bool mouse;
    int i=0;
    char sentence[50]={};
    String header="Enter your name";

    Text text(sentence,font,20);
    text.setColor(Color::Blue);
    Text titletext(header,font2,25);
    titletext.setColor(Color::Black);
    titletext.setPosition(190,120);
    //Для записи рекорда




	//Для паузы
    Texture menu_texture1,menu_texture2,menu_texture3,menu_texture4,menu_texture5,cursor_texture6;
	menu_texture1.loadFromFile("Картинки\\Пауза.png");
	menu_texture2.loadFromFile("Картинки\\Продолжить.png");
	menu_texture3.loadFromFile("Картинки\\Настройкидляпаузы.png");
    menu_texture4.loadFromFile("Картинки\\Главное меню.png");
    menu_texture5.loadFromFile("Картинки\\Выход.png");
    cursor_texture6.loadFromFile("Картинки\\Курсор.png");
	Sprite menu1(menu_texture1),menu2(menu_texture2),nas(menu_texture3),menu3(menu_texture4),menu4(menu_texture5),cursor(cursor_texture6);
	menu1.setPosition(175,30);
	menu2.setPosition(245,150);
	nas.setPosition(245,200);
    menu3.setPosition(245,250);
    menu4.setPosition(245,300);
    //Для паузы



	SoundBuffer buffer;
	buffer.loadFromFile("Музыка\\Jump.ogg");
	Sound sound(buffer);
	sound.setVolume(volsou);

    Music music;
    music.openFromFile("Музыка\\Mario_Theme.ogg");
    music.setVolume(volmus);
    music.play();

    music.setLoop(true);



	Clock clock,clock2;

    while (window.isOpen()&&game)
    {
        //Громкость
        sound.setVolume(volsou);
        music.setVolume(volmus);
        //Громкость


		float time=clock.getElapsedTime().asMicroseconds();
		clock.restart();

		window.setVerticalSyncEnabled(true);
		time=time/500;//меняет скорость игры
		if(time>20) time=20;

        //Игровое время(рассчет)
        float time2=clock2.getElapsedTime().asMilliseconds();

		if(!pause) {time2+=timer;timer=0;}

		if(time2>1000&&!pause)
		{
		    clock2.restart();
		    t1++;
		    if(t1==60)
		    {
		        timearr[3]='0';
		        timearr[4]='0';
		        timearr[5]='\0';
		        t1=0;
		        t2++;
		    }
		}

		if(t2>9)
		{
		    itoa(t2,timearr,10);
		    timearr[2]=':';
		}
		if(t2<10&&t2!=0)
		{
            timearr[0]='0';
            timearr[1]=48+t2;
            timearr[2]=':';
		}

		if(t1>9)
		{
		    itoa(t1,ttt,10);
		    timearr[3]='\0';
		    strncat(timearr,ttt,3);
		}
		if(t1<10&&t1!=0)
		{
            timearr[3]='0';
            timearr[4]=48+t1;
            timearr[5]='\0';
		}




        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                window.close();
                eexit=1;
                break;

                case Event::TextEntered:
                if(Mario.record)
                {
                if(event.text.unicode>=32&&event.text.unicode<=126&&i<8)
                {
                    sentence[i]=(char)event.text.unicode;
                    i++;
                    sentence[i]='\0';
                }
                else
                if(event.text.unicode==8&&i>0)
                {
                    i--;
                    sentence[i]='\0';
                }
                text.setString(sentence);
                text.setPosition(190,165);
                }
                break;

                case Event::KeyReleased:
                if(event.key.code==Keyboard::Escape)
                {
                    esc=0;
                    if(nastflag&&!esc)
                    {
                        esc=1;
                        nastflag=0;
                    }

                    if(!nastflag&&!pause&&!Mario.record&&!esc)
                    {
                        esc=1;
                        pause=1;
                        timer=time2;
                    }

                    if(!nastflag&&!esc)
                    {
                        esc=1;
                        nastflag=0;
                        pause=0;
                        cur=0;
                        clock2.restart();
                    }
                }
                break;
            }
		}




        //Ввод рекорда
        if(Mario.record)
        {
            cur=1;
            MenuNum=0;
            mouse=0;
            ok.setColor(Color::Black);
            otm.setColor(Color::Black);

            if (IntRect(210,200,30,20).contains(Mouse::getPosition(window))) {ok.setColor(Color::Yellow); MenuNum=1;}
            if (IntRect(300,200,82,20).contains(Mouse::getPosition(window))) {otm.setColor(Color::Yellow); MenuNum=2;}


            if(Keyboard::isKeyPressed(Keyboard::Escape))  end=1;
            if(Keyboard::isKeyPressed(Keyboard::Return))  { end=1;savescore(sentence,timearr); }

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                switch(MenuNum)
                {
                    case 1:
                    end=1;
                    savescore(sentence,timearr);
                    break;

                    case 2:
                    end=1;
                    break;
                }
            }

		}



        //if (Keyboard::isKeyPressed(Keyboard::Escape)&&!pause&&!Mario.record)
        //{ pause=1;timer=time2;Sleep(300); }


        //Пауза
        if(pause)
        {
            cur=1;
            MenuNum=0;
            menu2.setColor(Color::Black);
            nas.setColor(Color::Black);
            menu3.setColor(Color::Black);
            menu4.setColor(Color::Black);

            if(!nastflag)
            {
                if (IntRect(245,150,110,20).contains(Mouse::getPosition(window))) {menu2.setColor(Color::Yellow); MenuNum=1;}
                if (IntRect(245,200,90,18).contains(Mouse::getPosition(window))) {nas.setColor(Color::Yellow); MenuNum=2;}
                if (IntRect(245,250,116,18).contains(Mouse::getPosition(window))) {menu3.setColor(Color::Yellow); MenuNum=3;}
                if (IntRect(245,300,55,15).contains(Mouse::getPosition(window))) {menu4.setColor(Color::Yellow); MenuNum=4;}
            }

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                switch(MenuNum)
                {
                    case 1:
                    nastflag=0;
                    pause=0;
                    cur=0;
                    //Sleep(300);
                    clock2.restart();
                    break;

                    case 2:
                    nastflag=1;
                    break;

                    case 3:
                    nastflag=0;
                    end=1;
                    //Sleep(300);
                    break;

                    case 4:
                    window.close();
                    eexit=1;
                    break;
                }
            }

            //if (Keyboard::isKeyPressed(Keyboard::Escape)&&!nastflag)  { nastflag=0;pause=0;cur=0;Sleep(300);clock2.restart(); }
        }


        if(!pause&&!Mario.record)
        {

		if (Keyboard::isKeyPressed(Keyboard::Left))    Mario.dx=-0.1;

	    if (Keyboard::isKeyPressed(Keyboard::Right))    Mario.dx=0.1;

	    if (Keyboard::isKeyPressed(Keyboard::Up))	if (Mario.onGround) { dyp=-0.27;Mario.onGround=false;sound.play(); }





		 Mario.update(time);
		 enemy1.update(time,54*16,13*16);
		 enemy2.update(time,38*16,13*16);
		 enemy3.update(time,80*16,13*16);
		 Score.setString(score);
		 GameT.setString(timearr);
        }

        //Окончание
        if(end)
        {
            end=0;
            music.stop();
            dishit=0;
            cur=0;
            Mario.record=0;
            pause=0;
            sc=0;
            offsetX=0;
            offsetY=0;
            hit=0;
            rectp = FloatRect(100,180,16,16);
            for(int i=0;i<H;i++)
            {
                for(int p=0;p<W;p++)
                {
                    TileMap[i][p]=sTile[i][p];
                }
            }
            Mario.Score(0);
            menu(window);
            game=0;
        }



		 if (rectp.left>200) offsetX = rectp.left-200;           //смещение




		 window.clear(Color(107,140,255));

		 for (int i=0; i<H; i++)
			 for (int j=0; j<W; j++)
			  {
				if (TileMap[i][j]=='P')  tile.setTextureRect( IntRect(143-16*3,112,16,16) );

				if (TileMap[i][j]=='k')  tile.setTextureRect( IntRect(143,112,16,16) );

   			    if (TileMap[i][j]=='c')  tile.setTextureRect( IntRect(143-16,112,16,16) );

				if (TileMap[i][j]=='t')  tile.setTextureRect( IntRect(0,47,32,95-47) );

				if (TileMap[i][j]=='g')  tile.setTextureRect( IntRect(0,16*9-5,3*16,16*2+5) );

				if (TileMap[i][j]=='G')  tile.setTextureRect( IntRect(145,222,222-145,255-222) );

			    if (TileMap[i][j]=='d')  tile.setTextureRect( IntRect(0,106,74,127-106) );

				if (TileMap[i][j]=='w')  tile.setTextureRect( IntRect(99,224,140-99,255-224) );

				if (TileMap[i][j]=='r')  tile.setTextureRect( IntRect(143-32,112,16,16) );

				if (TileMap[i][j]=='i')  tile.setTextureRect( IntRect(143-32,112,16,16) );

				if (TileMap[i][j]=='s')  tile.setTextureRect( IntRect(143-32,112,16,16) );

				if (TileMap[i][j]=='e')  tile.setTextureRect( IntRect(143-32,112+16,16,16) );

				if ((TileMap[i][j]==' ') || (TileMap[i][j]=='0')) continue;

  			    tile.setPosition(j*16-offsetX,i*16 - offsetY) ;
		        window.draw(tile);
		     }



		window.draw(glabsprite);

		if(!enemy1.dis)
	    window.draw(enemy1.sprite2);
	    if(!enemy2.dis)
	    window.draw(enemy2.sprite2);
	    if(!enemy3.dis)
	    window.draw(enemy3.sprite2);

	    window.draw(Score);

	    window.draw(GameT);

	    if(pause&&!nastflag)
	    {
	        window.draw(menu1);
	        window.draw(menu2);
	        window.draw(nas);
	        window.draw(menu3);
	        window.draw(menu4);
	    }

	    if(Mario.record)
	    {
	        window.draw(fon);
	        window.draw(text);
            window.draw(titletext);
            window.draw(ok);
            window.draw(otm);
	    }

	    //Настройки
	    if(nastflag) settings(window,175);
	    //Настройки

	    //Курсор
	    if(cur)
	    {
            cursor.setPosition(Mouse::getPosition(window).x,Mouse::getPosition(window).y);
            window.draw(cursor);
	    }
        //Курсор

		window.display();
    }

}
    //Сохранение настроек
    save();

    return 0;
}

