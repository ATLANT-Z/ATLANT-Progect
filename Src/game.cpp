#include"dynamic_array.h"
#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;

bool PlayerTurn = true;

class Game;
class Player;
class Mouse;
class Record;

class Mouse
{
public:
	enum ACTION_MODE{ LEFT_BUTTON, RIGHT_BUTTON };
	struct ACTION{
		ACTION_MODE mode;
		COORD coord;
	};
	ACTION action;
public:
	ACTION getAction()
	{
		ACTION action;
		HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
		SetConsoleMode(h_in, ENABLE_MOUSE_INPUT);

		INPUT_RECORD all_events[256];
		DWORD read_event;

		while (true)
		{
			ReadConsoleInput(h_in, all_events, 256, &read_event);
			if (all_events[0].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				action.mode = LEFT_BUTTON;
				action.coord = all_events[0].Event.MouseEvent.dwMousePosition;
				return action;
			}


			else if (all_events[0].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				action.mode = RIGHT_BUTTON;
				action.coord = all_events[0].Event.MouseEvent.dwMousePosition;
				return action;
			}
		}
	}
	void processinput(Game&game, Player player, Player enemy, Record & record);
};


class Game : public Mouse
{
private:
	const unsigned int height_ = 10;
	const unsigned int width_ = 10;
	bool isOver;
	bool isWin;
	bool isGameBegin = false;
protected:

public:
	enum MODE{ CLOSE, OPEN };
	enum STATE{ EMPTY, SHIP_HERE, NEAR_SHIP, MISS, DESTROY, EXPLODED };
	unsigned int playerShips = 20;
	unsigned int compShips = 20;
	



	bool isGameOver()
	{
		return isOver;
	}
	void destroyPlayerShip()
	{
		playerShips--;
	}
	void destroyCompShip()
	{
		compShips --;
	}
	int getHeight()
	{
		int height = height_;
		return height;
	}
	int getWidth()
	{
		int width = width_;
		return width;
	}
	
	void prepareGame(Record & record);

	void update()
	{
		if (compShips == 0)
		{
			isWin = isOver = true;
		}
		else if (playerShips == 0)
			isOver = true;
	}

	void menu(Record &record);
	void renderm()
	{
		system("cls");
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 7 * 16 + 9);
		for (int y = 0; y < 3; y++)										// (0,0) - (10,3)
		{
			for (int x = 0; x < 10; x++)
			{
				SetConsoleCursorPosition(handle, { x, y });
				if (y == 1 && x == 3)
					cout << "PLAY";
				else if (!(y == 1 && x >= 3 && x < 7))
					cout << ' ';
			}
		}

		if (isGameBegin)
		{
			SetConsoleTextAttribute(handle, 7 * 16 + 9);
			for (int y = 0; y < 3; y++)										// (11,0) - (20,3)
			{
				for (int x = 11; x < 22; x++)
				{
					SetConsoleCursorPosition(handle, { x, y });
					if (y == 1 && x == 12)
						cout << "STATISTIC";
					else if (!(y == 1 && x >= 12 && x < 21))
						cout << ' ';
				}
			}
		}

		SetConsoleTextAttribute(handle, 7 + 0);
	}
	
	void run(Game&game);
};

class Record : public Game
{

public:

	struct RECORD{
		char * name;
		unsigned int ships;
	};
	RECORD record;
	void setRecordName(char * a)
	{
		record.name = a;
	}
	void setRecordShips(int a)
	{
		record.ships = a;
	}
	char * getRecordName()
	{
		return record.name;
	}
	int getRecordShips()
	{
		return record.ships;
	}

	void hallOfFame(int x, int y);
};

class Player : public Game
{
	friend class Ships;
protected:
	int ** table_mode;
	int ** table_state;
public:
	Player();
	
	void render()
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, { 0, 0 });
		for (unsigned int y = 0; y < getHeight(); y++)
		{
			for (unsigned int x = 0; x < getWidth(); x++)
			{
				switch (table_mode[y][x])
				{
				case CLOSE:
					if (table_state[y][x] == SHIP_HERE && isGameOver())
					{
						SetConsoleTextAttribute(handle, 7 * 16 + 9);
						cout << (char)254;
					}
					else
					{
						SetConsoleTextAttribute(handle, 8);
						cout << (char)219;
					}
					break;
				case OPEN:
					SetConsoleTextAttribute(handle, 7 * 16 + 9);
					if (table_state[y][x] == EMPTY || table_state[y][x] == NEAR_SHIP)
					{
						cout << ' ';
					}
					else if (table_state[y][x] == MISS)
					{
						SetConsoleTextAttribute(handle, 3 * 16 + 9);
						cout << '*';
					}
					else if (table_state[y][x] == DESTROY)
					{
						SetConsoleTextAttribute(handle, 8 * 16 + 12);
						cout << (char)35;
					}
					else if (table_state[y][x] == EXPLODED)
					{
						SetConsoleTextAttribute(handle, 8 * 16 + 12);
						cout << (char)253;
					}
					else
						cout << table_state[y][x];
					break;
				}

			}
			cout << endl;
		}
		SetConsoleTextAttribute(handle, 8 + 0);
	}
	void renderp()
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		for (unsigned int y = 0; y < getHeight(); y++)
		{
			SetConsoleCursorPosition(handle, { 12, y });
			for (unsigned int x = 0; x < getWidth(); x++)
			{
				switch (table_mode[y][x])
				{
				case CLOSE:
					if (table_state[y][x] == EMPTY || table_state[y][x] == NEAR_SHIP)
					{
						SetConsoleTextAttribute(handle, 8);
						cout << (char)219;
					}
					else if (table_state[y][x] == SHIP_HERE)
					{
						SetConsoleTextAttribute(handle, 7 * 16 + 9);
						cout << (char)254;
					}
					break;
				case OPEN:
					SetConsoleTextAttribute(handle, 7 * 16 + 9);
					if (table_state[y][x] == EMPTY || table_state[y][x] == NEAR_SHIP)
					{
						cout << ' ';
					}
					else if (table_state[y][x] == SHIP_HERE)
					{
						cout << (char)254;
					}
					else if (table_state[y][x] == MISS)
					{
						SetConsoleTextAttribute(handle, 3 * 16 + 9);
						cout << '*';
					}
					else if (table_state[y][x] == DESTROY)
					{
						SetConsoleTextAttribute(handle, 8 * 16 + 12);
						cout << (char)35;
					}
					else if (table_state[y][x] == EXPLODED)
					{
						SetConsoleTextAttribute(handle, 8 * 16 + 12);
						cout << (char)253;
					}
					else
						cout << table_state[y][x];
					break;
				}

			}
			cout << endl;
		}
		SetConsoleTextAttribute(handle, 8 + 0);
		
		SetConsoleCursorPosition(handle, { 25, 1 });
		cout << "LEFT_BUTTON : Fire " << endl;
		SetConsoleCursorPosition(handle, { 25, 2 });
		cout << "RIGHT_BUTTON: Menu " << endl;
		SetConsoleCursorPosition(handle, { 25, 3 });
	}
	
	void setShips()
	{
		SetShipAuto(4);

		SetShipAuto(3);
		SetShipAuto(3);

		SetShipAuto(2);
		SetShipAuto(2);
		SetShipAuto(2);

		SetShipAuto(1);
		SetShipAuto(1);
		SetShipAuto(1);
		SetShipAuto(1);
	}
	int chekCoord(int y, int x)
	{
		if (x >= 0 && y >= 0 && x < getWidth() && y < getHeight())
		{
			if (table_state[y][x] == EMPTY)
			{
				return 1;

			}
			else
				return 0;
		}
		return 0;
	}
	void SetShipAuto(int deck_)
	{
		unsigned int cell_ships = 0;
		bool mistake = true;
		do
		{
			int x = rand() % getWidth();
			int y = rand() % getHeight();
			bool horizont = rand() % 2;

			if (table_state[y][x] == EMPTY)
			{
				short empcl = 0;
				for (int i = 0; i < deck_; i++)
				{
					if (horizont)
					{
						empcl += chekCoord(y, x + i);
					}
					else
					{
						empcl += chekCoord(y + i, x);
					}
				}

				if (empcl == deck_ && horizont)
				{
					for (int i = 0; i < deck_; i++)
					{
						table_state[y][x + i] = SHIP_HERE;
						++cell_ships;
					}
				}
				else if (empcl == deck_ && !horizont)
				{
					for (int i = 0; i < deck_; i++)
					{
						table_state[y + i][x] = SHIP_HERE;
						++cell_ships;
					}
				}
			}
		} while (cell_ships < deck_ && mistake);
		//_______________________________________________________ chek
		for (int y = 0; y < getHeight(); y++)
			for (int x = 0; x < getWidth(); x++)
			{
				if (table_state[y][x] == SHIP_HERE)//_____________If there ship...
					for (int i = 0; i < 8; i++)
					{
						int dx, dy;//_______________Chek cells near
						switch (i)
						{
						case 0: dx = 0, dy = -1; break;
						case 1: dx = 1, dy = -1; break;
						case 2: dx = 1, dy = 0; break;
						case 3: dx = 1, dy = 1; break;
						case 4: dx = 0, dy = 1; break;
						case 5: dx = -1, dy = 1; break;
						case 6: dx = -1, dy = 0; break;
						case 7: dx = -1, dy = -1; break;
						}
						dx += x;
						dy += y;
						if (dx >= 0 && dy >= 0 && dx < getWidth() && dy < getHeight())// ____ WIthin the game field
							if (table_state[dy][dx] == EMPTY)
							{
								table_state[dy][dx] = NEAR_SHIP;
							}
					}
			}
	};

	void openCell(Game&game, unsigned int x, unsigned int y, bool AI = false)
	{
		switch (table_mode[y][x])
		{
		case OPEN:
			break;
		case CLOSE:
			table_mode[y][x] = OPEN;
			if (table_state[y][x] == SHIP_HERE)
			{
				table_state[y][x] = DESTROY;
				if (AI)
					game.destroyPlayerShip();
				else
					game.destroyCompShip();



				if (ChekDestroy(y, x))// need explosion?
				{
					table_state[y][x] = EXPLODED; // explosion
					explosion(y, x);				  // Explosion of neighboring cells
				}
				Sleep(10);										//pause on explosion;
				update();

			}
			else if (table_state[y][x] == EMPTY || table_state[y][x] == NEAR_SHIP)
			{
				table_state[y][x] = MISS;
				if (AI)
					PlayerTurn = true;
				else
					PlayerTurn = false;
				
				break;
			}
			break;
		}
	}
	bool ChekDestroy(const int y, const int x, const int cheky = 10000, int const chekx = 10000)
	{
		for (int i = 0; i < 4; i++)
		{
			int dy, dx;
			switch (i)
			{
			case 0: dx = 0, dy = -1; break;
			case 1: dx = 1, dy = 0; break;
			case 2: dx = 0, dy = 1; break;
			case 3: dx = -1, dy = 0; break;
			}
			dy += y;
			dx += x;
			if (dx >= 0 && dy >= 0 && dx < getWidth() && dy < getHeight())
			{
				if (table_state[dy][dx] == NEAR_SHIP || table_state[dy][dx] == MISS)
					continue;
				else if (table_state[dy][dx] == SHIP_HERE)
				{
					return false;
					break;
				}
				else if (table_state[dy][dx] == DESTROY)
				{
					if (dy == cheky && dx == chekx)
						continue;
					else
					{
						if (ChekDestroy(dy, dx, y, x))
							continue;
						else
							return false;
					}
				}
			}
		}
		return true;
	}
	void explosion(unsigned int y, unsigned int x)
	{
		for (int i = 0; i < 8; i++)
		{
			int dx, dy;
			switch (i)
			{
			case 0: dx = 0, dy = -1; break;
			case 1: dx = 1, dy = -1; break;
			case 2: dx = 1, dy = 0; break;
			case 3: dx = 1, dy = 1; break;
			case 4: dx = 0, dy = 1; break;
			case 5: dx = -1, dy = 1; break;
			case 6: dx = -1, dy = 0; break;
			case 7: dx = -1, dy = -1; break;
			}
			dx += x;
			dy += y;
			if (dx >= 0 && dy >= 0 && dx < getWidth() && dy < getHeight())
			{
				if (table_state[dy][dx] == DESTROY)
				{
					table_state[dy][dx] = EXPLODED;
					explosion(dy, dx);
				}
				else if (table_state[dy][dx] == NEAR_SHIP)
				{
					table_mode[dy][dx] = OPEN;
					table_state[dy][dx] = MISS;
				}
				else if (table_state[dy][dx] == EXPLODED || table_state[dy][dx] == MISS)
				{
					continue;
				}
			}
		}
	}


	void AI(Game & game, Player & player)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

		static int shoot_x, shoot_y;
		static	short side = 0;
		static int shoot_dy = 0, shoot_dx = 0;
		static bool apple = false;
		static unsigned int hit = 1;


		//while (!PlayerTurn)
		//{
		//	bool compTurn = true;
		//	do
		//	{
		//		if (hit == 1)
		//		{
		//			shoot_dx = 0;
		//			shoot_dy = 0;
		//			shoot_x = rand() % getWidth();
		//			shoot_y = rand() % getHeight();
		//		}
		//		shoot_dy += shoot_y;
		//		shoot_dx += shoot_x;
		//	} while (player.table_mode[shoot_dy][shoot_dx] != CLOSE);
		//	if (shoot_dx >= 0 && shoot_dy >= 0 && shoot_dx < getWidth() && shoot_dy < getHeight())
		//	{
		//		/*hit++;*/
		//		player.openCell(game, shoot_dx, shoot_dy,true);
		//		player.renderp();
		//	}
		//	game.update();
		//}
		while (!PlayerTurn)
		{
			bool compTurn = true;
			do
			{
				if (hit == 1)
				{
					shoot_dx = 0;
					shoot_dy = 0;
					shoot_x = rand() % getWidth();
					shoot_y = rand() % getHeight();
				}

				else if (apple)
				{
					do
					{
						do
						{
							shoot_dx = 0, shoot_dy = 0;
							switch (side)
							{
							case 0: shoot_dx = 0, shoot_dy = -1; break;
							case 1: shoot_dx = 1, shoot_dy = 0; break;
							case 2: shoot_dx = 0, shoot_dy = 1; break;
							case 3: shoot_dx = -1, shoot_dy = 0; break;
							}
							if (shoot_dx + shoot_x >= 0 && shoot_dy + shoot_y >= 0 && shoot_dx + shoot_x < getWidth() && shoot_dy + shoot_y < getHeight())
							{
								if (player.table_mode[shoot_dy + shoot_y][shoot_dx + shoot_x] == OPEN)
									side++;
							}
							else
								side++;
						} while (!(shoot_dx + shoot_x >= 0 && shoot_dy + shoot_y >= 0 && shoot_dx + shoot_x < getWidth() && shoot_dy + shoot_y < getHeight()));
					} while (player.table_mode[shoot_dy + shoot_y][shoot_dx + shoot_x] != CLOSE);
				}

				shoot_dy += shoot_y;
				shoot_dx += shoot_x;

			} while (player.table_mode[shoot_dy][shoot_dx] != CLOSE);
			//___________________________________________________________________________

			if (shoot_dx >= 0 && shoot_dy >= 0 && shoot_dx < getWidth() && shoot_dy < getHeight())
			{
				hit++;
				player.openCell(game, shoot_dx, shoot_dy, compTurn);
				player.renderp();
				shoot_dy -= shoot_y;
				shoot_dx -= shoot_x;

				if (player.table_state[shoot_dy + shoot_y][shoot_dx + shoot_x] == DESTROY)// get vector
				{
					if (hit == 2)
					{
						apple = true;

					}
					if (shoot_dy > 0)
					{

						if (shoot_dy + 1 + shoot_y < getHeight())// dy = 1
						{
							shoot_dy++;
							apple = false;
						}
						else if (shoot_dy != 0)
						{
							shoot_dy = -1;
							apple = false;
						}
					}
					else if (shoot_dy < 0)
					{
						if (shoot_dy - 1 + shoot_y >= 0)// dy = -1
						{
							shoot_dy--;
							apple = false;
						}
						else if (shoot_dy != 0)
						{
							shoot_dy = 1;
							apple = false;
						}
					}
					else if (shoot_dx > 0)
					{
						if (shoot_dx + 1 + shoot_x < getWidth())// dx = 1
						{
							shoot_dx++;
							apple = false;
						}
						else if (shoot_dx != 0)
						{
							shoot_dx = -1;
							apple = false;
						}
					}
					else if (shoot_dx < 0)
					{
						if (shoot_dx - 1 + shoot_x >= 0)// dx = -1
						{
							shoot_dx--;
							apple = false;
						}
						else if (shoot_dx != 0)
						{
							shoot_dx = 1;
							apple = false;
						}
					}
				}
				else if (player.table_state[shoot_dy + shoot_y][shoot_dx + shoot_x] == MISS)
				{
					if (shoot_dy == 0 && shoot_dx == 0)
					{
						hit = 1;
					}
					if (shoot_dy == 1 || shoot_dy == -1 || shoot_dx == 1 || shoot_dx == -1)
					{
						apple = true;
						side++;
					}

					if (shoot_dy > 1)
					{
						shoot_dy = -1;
					}
					else if (shoot_dy < -1)
					{
						shoot_dy = 1;
					}

					if (shoot_dx > 1)
					{
						shoot_dx = -1;
					}
					else if (shoot_dx < -1)
					{
						shoot_dx = 1;
					}
				}
				else if (player.table_state[shoot_dy + shoot_y][shoot_dx + shoot_x] == EXPLODED)
				{
					apple = false;
					hit = 1;
					side = 0;
					shoot_dx = 0;
					shoot_dy = 0;
				}
			}
		}
	}
	// _____________Artificial Intelligence____________
};

Player :: Player()
{
	create_array(table_mode, getHeight(), getWidth());// player field
	fill_array(table_mode, getHeight(), getWidth(), 0);
	create_array(table_state, getHeight(), getWidth());
	fill_array(table_state, getHeight(), getWidth(), 0);
	setShips();

}

void Mouse::processinput(Game&game,Player player, Player enemy, Record & record)
{
	action = getAction();
	switch (action.mode)
	{
	case LEFT_BUTTON:
		if (action.coord.X >= 0 && action.coord.X < game.getWidth() &&
			action.coord.Y >= 0 && action.coord.Y < game.getHeight())
			enemy.openCell(game,action.coord.X, action.coord.Y); // Fasle - it's not computer turn
		break;
	case RIGHT_BUTTON:// records
		game.renderm();
		game.menu(record);
		system("cls");
		enemy.render();
		player.renderp();
		break;
	}
}

void Game::prepareGame(Record & record)
{
	system("cls");
	system("mode con cols=100 lines=75");

	isOver = false;
	char * name = new char[51];

	cout << "HEY!!! Welcome to the World of Warships \nEnter ur name pls : ";
	cin.getline(name, 50);

	record.setRecordName(name);

	/*cout << "If u want set ships write : 0 \nIf u want set ships auto write : 1 \n";
	bool auto_set = true;
	cin >> auto_set;
	cout << "If u want set mode EDITOR : 1 \nElse : 0 \n";
	cin >> editor;*/

	isWin = false;
	isGameBegin = true;

	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { 25, 0 });
	SetConsoleTextAttribute(handle, 13);
	cout << "Your Login :  " << record.getRecordName() << endl;
	SetConsoleTextAttribute(handle, 8 + 0);
}
void Record :: hallOfFame(int x, int y)
{

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { x, y });
	if (record.name)
		cout << "Login : " << record.name << " - ships : " << record.ships << "    Enemy ships : " << compShips << endl;
	/*FILE * f;
	fopen_s(&f, "record.txt", "r");
	if (!f)
	{
	cout << "Wrong filename!\n";
	return;
	}

	while (!feof(f))
	putchar(fgetc(f));

	fclose(f);*/

}

void Game::menu(Record &record)
{
	bool menu = true;
	do
	{
		action = getAction();
		switch (action.mode)
		{
		case LEFT_BUTTON:
			if (action.coord.X >= 0 && action.coord.X < 10 && action.coord.Y >= 0 && action.coord.Y < 3)
			{

				menu = false;
			}
			if (action.coord.X >= 11 && action.coord.X < 20 && action.coord.Y >= 0 && action.coord.Y < 3 && isGameBegin)
			{
				record.setRecordShips(playerShips);
				record.hallOfFame(0, 5);
			}
			break;
		case RIGHT_BUTTON:
			break;
		}
	} while (menu);




}

void Game::run(Game&game)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));
	renderm();
	Record record;
	menu(record);
	prepareGame(record);
	Player player;
	Player enemy;
	Mouse mouse;
	enemy.render();
	player.renderp();
	while (!isOver)
	{
		mouse.processinput(game,player, enemy,record);
		update();
		enemy.render();
		player.renderp();
		enemy.AI(game,player);
		update();
		enemy.render();
		player.renderp();
		
		SetConsoleTextAttribute(handle, 13);
		SetConsoleCursorPosition(handle, { 22, 11 });
		cout << compShips;
	}
	enemy.render();
	if (isWin)
	{
		/*record.ships = game.playerShips;
		FILE * f;
		fopen_s(&f, "record.txt", "a");

		char ships[4];
		_itoa(record.ships, ships, 10);
		char * rec = record.name;

		strcat(rec, " ");
		strcat(rec, ships);
		strcat(rec, "\n");
		fputs(rec, f);
		fclose(f);*/

		SetConsoleTextAttribute(handle, 13);
		SetConsoleCursorPosition(handle, { 22, 11 });
		cout << "WIN!!\n";

	}
	else
	{
		SetConsoleTextAttribute(handle, 14);
		SetConsoleCursorPosition(handle, { 22, 11 });
		cout << "DEFEAT!!\n";
	}
}




void main()
{

	Game game;
	game.run(game);
	system("pause");



}
