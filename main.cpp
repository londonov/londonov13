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

const int M = 20; //высота стакана в клетках(ячейках)
const int N = 10; //ширина стакана в клетках

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
    srand(time(0)); //генератор случайных чисел


    Font font;// объявляем объект для хранения шрифт
    font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта, этот файл должен быть в папке нашего проекта
    Text speedtext("60", font, 20);
    speedtext.setPosition(520,40);
    std::string mystr;
    Image i2,i3;
    Texture t1, t2, t3,t4; //объявляем тектуры

    i2.loadFromFile("images/enemycar_l.png");
    i3.loadFromFile("images/mycar_l.png");
    i2.createMaskFromColor(Color(255, 255, 255));
    i3.createMaskFromColor(Color(255, 255, 255));

    t1.loadFromFile("images/road.png");
    t2.loadFromImage(i2);
    t3.loadFromImage(i3);
    t4.loadFromFile("images/wheel.png");
	RenderWindow window(VideoMode(640, 480), "The Game!"); // окно 320 на 480 пикселей подписано the game
    Sprite enemy(t2), background(t1), mycar(t3), wheel(t4); //делаем спрайты из текстур

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

        float times = clock.getElapsedTime().asSeconds(); //записываем прошедшее время в секундах
		clock.restart(); //перезапускаем часы каждый раз в начале цикла
		timer += times;   //общий таймер увеличивается

        wheel.setPosition(550,200);
        //wheel.setOrigin(565, 365);
        wheel.setOrigin(sf::Vector2f(64, 63)); //размер изображения руля 129 на 127
		Event e;  //класс в котором хранятся системные события например нажатие клавиши, закрытие окна
		while (window.pollEvent(e))
		{

			if (e.type == Event::Closed)   //если есть событие закрытие окна закрываем окно и освобождаем все ресурсы
				window.close();

			if (e.type == Event::KeyPressed)          //в случае нажатия кнопок
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
        //wheel.setPosition(500-127*sin(rotation*3.14159265/180),400-125*cos(rotation*3.14159265/180)) ; //размер рисунка по y в пикселя 127
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
	Texture t1, t2, t3; //объявляем тектуры
	t1.loadFromFile("images/tiles.png"); //кубики из которых будут состоять фигуры
	t2.loadFromFile("images/background.png"); //фон
	t3.loadFromFile("images/frame.png"); //рамка рабочего поля стакана
	// обратите внимание поле в пределах рамки получается 180 на 360 пикселей

	Sprite s(t1), background(t2), frame(t3); //делаем спрайты из текстур

	int dx = 0; //признак нажатия кнопки смещения фигуры
	bool rotate = 0;//признак нажатия кнопки вращения фигуры
	int colorNum = 1;
	float timer = 0, delay = 0.3;

	Clock clock; // класс который измеряет прошедшее время

//    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    time_t seconds;
    Font font;// объявляем объект для хранения шрифт
    font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта, этот файл должен быть в папке нашего проекта
    Text text("000", font, 20);//создаем объект для работы с текстом. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
    text.setPosition(20 , 20 ); //устанавливаем позицию на экране
    char buff[100];
    string mystr;
    for (int i=0;i<N-1;i++)
        field[M-1][i]=3;
    while (window.isOpen())
    {

        float times = clock.getElapsedTime().asSeconds(); //записываем прошедшее время в секундах
		clock.restart(); //перезапускаем часы каждый раз в начале цикла
		timer += times;   //общий таймер увеличивается

		Event e;  //класс в котором хранятся системные события например нажатие клавиши, закрытие окна
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)   //если есть событие закрытие окна закрываем окно и освобождаем все ресурсы
				window.close();

			if (e.type == Event::KeyPressed)          //в случае нажатия кнопок
				if (e.key.code == Keyboard::Up) rotate = true;
				else if (e.key.code == Keyboard::Left) dx = -1;
				else if (e.key.code == Keyboard::Right) dx = 1;
				else if (e.key.code == Keyboard::Down) timer = delay+1;;
		}



		//// <- Move -> ///
		for (int i = 0; i<4; i++)
		{
			b[i] = a[i];
			a[i].x += dx; //изменяем х координату фигуры
		}
		//если при изменении координаты вышли за границы стакана или совместилась с находившимися в стакане фигурами, возвращаем старые координаты элементов фигуры
		if (!check())
			for (int i = 0; i<4; i++)
				a[i] = b[i];

		//////Rotate//////
		if (rotate) // если пользователь задал вращение фигуры
		{
			Point p = a[1]; //center of rotation
			for (int i = 0; i<4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) // если не прошли проверку  возвращаем старые координаты
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

			if (!check())  // если фигура столкнулась с границами стакана или содержимым то
			{
				for (int i = 0; i<4; i++)  //вписываем упокоившуюся фигуру в стакан
					field[b[i].y][b[i].x] = colorNum;

				colorNum = 1 + rand() % 7;  //цвет новой фигуры
				int n = rand() % 7;			//тип новой фигуры

				for (int i = 0; i<4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
					///////check lines//////////
		//проверяем не сплошная ли линия, не нужно ли провалить ее
		int k = M - 1; //высота в клетках минус один
		int color_ch=0;
		for (int i = M - 1; i > 0; i--) //по высоте
		{
			int count = 0;
			for (int j = 0; j < N; j++) // по ширине
			{
				if (field[i][j])
					count++;
				field[k][j] = field[i][j];
				cout<<"for (int j = 0; j < N; j++)"<<endl;
			}
			cout<<"for (int i = M - 1; i > 0; i--)"<<endl;
			if (count < N) //если число заполненных элементов в уровне равно ширине то перерисовываем поверх него иначе переходим к следующему
			{	k--;	}
			else
            {


                for(int jj=0;jj<N;jj++)
                {
                    field[k][jj]=color_ch;
                    s.setTextureRect(IntRect(field[k][jj] * 18, 0, 18, 18)); //ширину рабочего поля в пределах рамки 180 разделить на 10 клеток получается одна клетка 18 пикселей
                    s.setPosition(jj * 18, i * 18); //координата в клетках умножить на длину клетки
                    s.move(28, 31); //offset  смещение начала поля от края благодаря ширине рамки сверху 31 сборку 28
                    window.draw(s);
                }

				window.display();
            }

        }//for (int i = M - 1; i > 0; i--) //по высоте
            timer = 0;
		}//if (timer>delay)






		dx = 0;
		rotate = 0;
		delay = 0.3;

		/////////draw//////////
		window.clear(Color::White); //очищаем окно
		window.draw(background);    //рисуем фон

		//рисуем элементы находящиеся в стакане
		for (int i = 0; i<M; i++)
			for (int j = 0; j<N; j++)
			{
				if (field[i][j] == 0) continue; // если пустая начинаем следующую итерацию цикла

				//рисуем квадратики элекменты фигур в стакане
				s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18)); //ширину рабочего поля в пределах рамки 180 разделить на 10 клеток получается одна клетка 18 пикселей
				s.setPosition(j * 18, i * 18); //координата в клетках умножить на длину клетки
				s.move(28, 31); //offset  смещение начала поля от края благодаря ширине рамки сверху 31 сборку 28
				window.draw(s);
			}

		//рисуем летящий элемент
		for (int i = 0; i<4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			s.move(28, 31); //offset смещение от края
			window.draw(s); //рисуем элемент фигуры
		}


        time(&seconds);
        mystr=ctime(&seconds);
        text.setString(mystr);


        window.draw(frame); // рисуем рамку
         window.draw(text);
		window.display();  // отображаем на экране то что нарисовано на окне
    };
    */
    return 0;
}
