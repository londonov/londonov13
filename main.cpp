#include <SFML/Graphics.hpp>
#include <ctime>
//#include <time.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;

/*

const int M = 20; //������ ������� � �������(�������)
const int N = 10; //������ ������� � �������

*/
/*
class road
{
public:
    width=200;

};

class car{

public:
    xsize=10;
    ysize=20;
};
*/

struct Car
{
    const float maxspeed=200;
    float x= 100;
    float y= 200;
    float speed=60;
    bool inversed=false;
} cars[5];

int main()
{
    srand(time(0)); //��������� ��������� �����


    Font font;// ��������� ������ ��� �������� �����
    font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������, ���� ���� ������ ���� � ����� ������ �������
    Text speedtext("60", font, 20);
    speedtext.setPosition(520,40);
    std::string mystr;
    Image i2,i3;
    Texture t1, t2, t3,t4; //��������� �������

    i2.loadFromFile("images/enemycar_l.png");
    i3.loadFromFile("images/mycar_l.png");
    i2.createMaskFromColor(Color(255, 255, 255));
    i3.createMaskFromColor(Color(255, 255, 255));

    t1.loadFromFile("images/road.png");
    t2.loadFromImage(i2);
    t3.loadFromImage(i3);
    t4.loadFromFile("images/wheel.png");
	RenderWindow window(VideoMode(640, 480), "The Game!"); // ���� 320 �� 480 �������� ��������� the game
    Sprite enemy(t2), background(t1), mycar(t3), wheel(t4); //������ ������� �� �������

    cars[0].x=100;
    cars[0].y=250;
    wheel.setPosition(500,300);
    //wheel.setOrigin(565, 365);
    Clock clock;
    float times=0;
    float timer =0;
    int dx=0;
    float delay =0.01;
    bool throttle=0;
    bool breaks=0;
    int rotation=0;

    cars[1].y=30;
    cars[2].y=-130;
    cars[3].y=-260;
    while (window.isOpen())
    {

        float times = clock.getElapsedTime().asSeconds(); //���������� ��������� ����� � ��������
		clock.restart(); //������������� ���� ������ ��� � ������ �����
		timer += times;   //����� ������ �������������

        wheel.setPosition(550,200);
        //wheel.setOrigin(565, 365);
        wheel.setOrigin(sf::Vector2f(64, 63)); //������ ����������� ���� 129 �� 127
		Event e;  //����� � ������� �������� ��������� ������� �������� ������� �������, �������� ����
		while (window.pollEvent(e))
		{

			if (e.type == Event::Closed)   //���� ���� ������� �������� ���� ��������� ���� � ����������� ��� �������
				window.close();

			if (e.type == Event::KeyPressed)          //� ������ ������� ������
			{

                if (e.key.code == Keyboard::Up) throttle = true;
				else if (e.key.code == Keyboard::Left) dx = -1;
				else if (e.key.code == Keyboard::Right) dx = 1;
				else if (e.key.code == Keyboard::Down) breaks=true;
			}
			else dx=0;
		}
        if (dx)
        {
            cars[0].x=cars[0].x+0.1*dx;
            if (dx<0)
            {
                if (rotation ==0)
                    rotation= 364;
                if (rotation>350)
                    rotation--;// * 180 / 3.14159265);
            }
            else
                if (rotation ==0)
                    rotation= 1;
                if (rotation<15)
                    rotation++;// * 180 / 3.14159265);
               // rotation=20; //* 180 / 3.14159265);

        }else rotation =0;

        if ((throttle)&&(cars[0].speed<cars[0].maxspeed))
        {
            cars[0].speed+=1;
        }
        if ((breaks)&&(cars[0].speed>0))
        {
                cars[0].speed-=10;
                if (cars[0].speed<0)
                    cars[0].speed=0;
        }


        if (timer>delay)
        {
            timer=0;

            if ((throttle)&&(cars[0].speed<cars[0].maxspeed))
            {
                cars[0].speed+=1;
            }
            if ((breaks)&&(cars[0].speed>0))
            {
                cars[0].speed-=10;
                if (cars[0].speed<0)
                    cars[0].speed=0;
            }
            for (int i=1;i<=3;i++)
            {
                 cars[i].y=cars[i].y+ 0.02*(cars[0].speed-cars[i].speed);
                 if ((cars[i].y>600)||(cars[i].y<-3600))
                 {
                     cars[i].x=210+rand()%110;
                     cars[i].y=-150;
                     cars[i].speed=50+rand()%20;
                 }
            }


        }


        throttle= false;
        breaks= false;

        mystr="speed"+std::to_string(cars[0].speed);
        speedtext.setString(mystr);
        window.clear();
        mycar.setRotation(rotation);

        wheel.setRotation(rotation);
        //wheel.setPosition(500-127*sin(rotation*3.14159265/180),400-125*cos(rotation*3.14159265/180)) ; //������ ������� �� y � ������� 127
        mycar.setPosition(cars[0].x,cars[0].y);

        for (int i=0;i<=3;i++)
        {
            enemy.setPosition(cars[i].x,cars[i].y);
        }

        for (int i=0;i<=3;i++)
        {
            //for (int j=0;j<=3;j++)
            int j=0;
            {
                if (i!=j)
                {
                    //58 132 my care
                    //57 110 enemy
                    // if ((cars[i].y>0)&&(cars[i].y<480)&&((abs(cars[i].x-cars[j].x))<57)&&(((abs(cars[i].y-cars[j].y))<110)))
                     if ((cars[i].y>0)&&(cars[i].y<480)&&(abs((cars[i].x+29-cars[j].x-28))<5)&&(((abs(cars[i].y+66-cars[j].y-55))<10)))
                     {
                        std::cout<<"you crashed i= "<<i<< " i x="<<cars[i].x<<" i y="<< cars[i].y<< "j ="<<j<< " j x="<<cars[j].x<<" j y="<<cars[j].y  <<std::endl;
                     }
                }
            }
        }
        window.draw(background);
        window.draw(enemy);
        window.draw(mycar);
        window.draw(speedtext);
        window.draw(wheel);
        //public void Draw(Texture2D texture, Vector2 position, Rectangle? sourceRectangle, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects effects, float layerDepth);
        //wheel.Draw(player,  new Vector2(x_player_pos,y_player_pos) + new Vector2(32,32) , null, Color.White, angle, new Vector2(32,32), 1.0f, SpriteEffects.None, 0.0f);
        window.display();
    }

	/*
	Texture t1, t2, t3; //��������� �������
	t1.loadFromFile("images/tiles.png"); //������ �� ������� ����� �������� ������
	t2.loadFromFile("images/background.png"); //���
	t3.loadFromFile("images/frame.png"); //����� �������� ���� �������
	// �������� �������� ���� � �������� ����� ���������� 180 �� 360 ��������

	Sprite s(t1), background(t2), frame(t3); //������ ������� �� �������

	int dx = 0; //������� ������� ������ �������� ������
	bool rotate = 0;//������� ������� ������ �������� ������
	int colorNum = 1;
	float timer = 0, delay = 0.3;

	Clock clock; // ����� ������� �������� ��������� �����

//    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    time_t seconds;
    Font font;// ��������� ������ ��� �������� �����
    font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������, ���� ���� ������ ���� � ����� ������ �������
    Text text("000", font, 20);//������� ������ ��� ������ � �������. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
    text.setColor(Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
    text.setPosition(20 , 20 ); //������������� ������� �� ������
    char buff[100];
    string mystr;
    for (int i=0;i<N-1;i++)
        field[M-1][i]=3;
    while (window.isOpen())
    {

        float times = clock.getElapsedTime().asSeconds(); //���������� ��������� ����� � ��������
		clock.restart(); //������������� ���� ������ ��� � ������ �����
		timer += times;   //����� ������ �������������

		Event e;  //����� � ������� �������� ��������� ������� �������� ������� �������, �������� ����
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)   //���� ���� ������� �������� ���� ��������� ���� � ����������� ��� �������
				window.close();

			if (e.type == Event::KeyPressed)          //� ������ ������� ������
				if (e.key.code == Keyboard::Up) rotate = true;
				else if (e.key.code == Keyboard::Left) dx = -1;
				else if (e.key.code == Keyboard::Right) dx = 1;
				else if (e.key.code == Keyboard::Down) timer = delay+1;;
		}



		//// <- Move -> ///
		for (int i = 0; i<4; i++)
		{
			b[i] = a[i];
			a[i].x += dx; //�������� � ���������� ������
		}
		//���� ��� ��������� ���������� ����� �� ������� ������� ��� ������������ � ������������� � ������� ��������, ���������� ������ ���������� ��������� ������
		if (!check())
			for (int i = 0; i<4; i++)
				a[i] = b[i];

		//////Rotate//////
		if (rotate) // ���� ������������ ����� �������� ������
		{
			Point p = a[1]; //center of rotation
			for (int i = 0; i<4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) // ���� �� ������ ��������  ���������� ������ ����������
				for (int i = 0; i<4; i++)
					a[i] = b[i];
		}

		///////Tick//////
		if (timer>delay)
		{
			for (int i = 0; i<4; i++)
			{
				b[i] = a[i];
				a[i].y += 1;
			}

			if (!check())  // ���� ������ ����������� � ��������� ������� ��� ���������� ��
			{
				for (int i = 0; i<4; i++)  //��������� ������������ ������ � ������
					field[b[i].y][b[i].x] = colorNum;

				colorNum = 1 + rand() % 7;  //���� ����� ������
				int n = rand() % 7;			//��� ����� ������

				for (int i = 0; i<4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
					///////check lines//////////
		//��������� �� �������� �� �����, �� ����� �� ��������� ��
		int k = M - 1; //������ � ������� ����� ����
		int color_ch=0;
		for (int i = M - 1; i > 0; i--) //�� ������
		{
			int count = 0;
			for (int j = 0; j < N; j++) // �� ������
			{
				if (field[i][j])
					count++;
				field[k][j] = field[i][j];
				cout<<"for (int j = 0; j < N; j++)"<<endl;
			}
			cout<<"for (int i = M - 1; i > 0; i--)"<<endl;
			if (count < N) //���� ����� ����������� ��������� � ������ ����� ������ �� �������������� ������ ���� ����� ��������� � ����������
			{	k--;	}
			else
            {


                for(int jj=0;jj<N;jj++)
                {
                    field[k][jj]=color_ch;
                    s.setTextureRect(IntRect(field[k][jj] * 18, 0, 18, 18)); //������ �������� ���� � �������� ����� 180 ��������� �� 10 ������ ���������� ���� ������ 18 ��������
                    s.setPosition(jj * 18, i * 18); //���������� � ������� �������� �� ����� ������
                    s.move(28, 31); //offset  �������� ������ ���� �� ���� ��������� ������ ����� ������ 31 ������ 28
                    window.draw(s);
                }

				window.display();
            }

        }//for (int i = M - 1; i > 0; i--) //�� ������
            timer = 0;
		}//if (timer>delay)






		dx = 0;
		rotate = 0;
		delay = 0.3;

		/////////draw//////////
		window.clear(Color::White); //������� ����
		window.draw(background);    //������ ���

		//������ �������� ����������� � �������
		for (int i = 0; i<M; i++)
			for (int j = 0; j<N; j++)
			{
				if (field[i][j] == 0) continue; // ���� ������ �������� ��������� �������� �����

				//������ ���������� ��������� ����� � �������
				s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18)); //������ �������� ���� � �������� ����� 180 ��������� �� 10 ������ ���������� ���� ������ 18 ��������
				s.setPosition(j * 18, i * 18); //���������� � ������� �������� �� ����� ������
				s.move(28, 31); //offset  �������� ������ ���� �� ���� ��������� ������ ����� ������ 31 ������ 28
				window.draw(s);
			}

		//������ ������� �������
		for (int i = 0; i<4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			s.move(28, 31); //offset �������� �� ����
			window.draw(s); //������ ������� ������
		}


        time(&seconds);
        mystr=ctime(&seconds);
        text.setString(mystr);


        window.draw(frame); // ������ �����
         window.draw(text);
		window.display();  // ���������� �� ������ �� ��� ���������� �� ����
    };
    */
    return 0;
}
