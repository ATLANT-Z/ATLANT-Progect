#include"game.h"
#include"dynamic_array.h"
#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;
namespace warships
{
	Map::Map()
	{
		create_array(table_mode, getHeight(), getWidth());// player field
		fill_array(table_mode, getHeight(), getWidth(), 0);
		create_array(table_state, getHeight(), getWidth());
		fill_array(table_state, getHeight(), getWidth(), 0);
		setShips();
	}
	void Map::render(Game&game)
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
					if (table_state[y][x] == SHIP_HERE && game.getIsOver())
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
	void Map::renderp()
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
	void Map::setShips()
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
	int Map::chekCoord(int y, int x)
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
	void Map::SetShipAuto(int deck_)
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

	void Player::openCell(Game&game, Map&map, unsigned int x, unsigned int y, bool AI)
	{
		switch (map.table_mode[y][x])
		{
		case OPEN:
			break;
		case CLOSE:
			map.table_mode[y][x] = OPEN;
			if (map.table_state[y][x] == SHIP_HERE)
			{
				map.table_state[y][x] = DESTROY;
				if (AI)
					game.destroyPlayerShip();
				else
					game.destroyCompShip();



				if (ChekDestroy(map, y, x))// need explosion?
				{
					map.table_state[y][x] = EXPLODED; // explosion
					explosion(map, y, x);				  // Explosion of neighboring cells
				}
				Sleep(10);										//pause on explosion;
				update();

			}
			else if (map.table_state[y][x] == EMPTY || map.table_state[y][x] == NEAR_SHIP)
			{
				map.table_state[y][x] = MISS;
				if (AI)
					PlayerTurn = true;
				else
					PlayerTurn = false;

				break;
			}
			break;
		}
	}
	bool Player::ChekDestroy(Map&map, const int y, const int x, const int cheky, int const chekx)
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
				if (map.table_state[dy][dx] == NEAR_SHIP || map.table_state[dy][dx] == MISS)
					continue;
				else if (map.table_state[dy][dx] == SHIP_HERE)
				{
					return false;
					break;
				}
				else if (map.table_state[dy][dx] == DESTROY)
				{
					if (dy == cheky && dx == chekx)
						continue;
					else
					{
						if (ChekDestroy(map, dy, dx, y, x))
							continue;
						else
							return false;
					}
				}
			}
		}
		return true;
	}
	void Player::explosion(Map&map, unsigned int y, unsigned int x)
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
				if (map.table_state[dy][dx] == DESTROY)
				{
					map.table_state[dy][dx] = EXPLODED;
					explosion(map, dy, dx);
				}
				else if (map.table_state[dy][dx] == NEAR_SHIP)
				{
					map.table_mode[dy][dx] = OPEN;
					map.table_state[dy][dx] = MISS;
				}
				else if (map.table_state[dy][dx] == EXPLODED || map.table_state[dy][dx] == MISS)
				{
					continue;
				}
			}
		}
	}

	void Record::hallOfFame(const int x, const int y)
	{

		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, { x, y });
		if (record.name)
			cout << "Login : " << record.name << " - ships : " << record.pShips << "    Enemy ships : " << record.cShips << endl;
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

	void Menu::menu(Game&game, Record &record)
	{
		renderm(game);
		bool menu = true;
		do
		{
			action = getAction();
			switch (action.mode)
			{
			case Game::LEFT_BUTTON:
				if (action.coord.X >= 0 && action.coord.X < 10 && action.coord.Y >= 0 && action.coord.Y < 3)
				{
					menu = false;
				}
				if (action.coord.X >= 11 && action.coord.X < 20 && action.coord.Y >= 0 && action.coord.Y < 3 && game.getIsGameBegin())
				{
					record.setPlayerShips(game.getPlayerShips());
					record.setCompShips(game.getCompShips());
					record.hallOfFame(0, 5);
				}
				break;
			case Game::RIGHT_BUTTON:
				break;
			}
		} while (menu);
	}
	void Menu::renderm(Game&game)
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

		if (game.getIsGameBegin())
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

	void Game::processinput(Game&game, Player player, Player enemy, Record & record, Menu&menu, Map&playerMap, Map&compMap)
	{
		action = getAction();
		switch (action.mode)
		{
		case LEFT_BUTTON:
			if (action.coord.X >= 0 && action.coord.X < game.getWidth() &&
				action.coord.Y >= 0 && action.coord.Y < game.getHeight())
				enemy.openCell(game, compMap, action.coord.X, action.coord.Y); // Fasle - it's not computer turn
			break;
		case RIGHT_BUTTON:// records
			menu.menu(game, record);
			system("cls");
			compMap.render(game);
			playerMap.renderp();
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

		record.setName(name);

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
		cout << "Your Login :  " << record.getName() << endl;
		SetConsoleTextAttribute(handle, 8 + 0);
	}

	void Game::run(Game&game)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		srand(time(0));
		Menu menu;
		Record record;
		menu.menu(game, record);
		prepareGame(record);
		Map playerMap;
		Map compMap;
		Player player;
		Player comp;
		Mouse mouse;
		AI computer;
		compMap.render(game);
		playerMap.renderp();
		while (!isOver)
		{
			processinput(game, player, comp, record, menu, playerMap, compMap);
			update();
			compMap.render(game);
			playerMap.renderp();
			computer.hardAi(game, playerMap, player);
			update();
			compMap.render(game);
			playerMap.renderp();

			SetConsoleTextAttribute(handle, 13);
			SetConsoleCursorPosition(handle, { 22, 11 });
			cout << compShips;
		}
		compMap.render(game);
		if (isWin)
		{

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

}
