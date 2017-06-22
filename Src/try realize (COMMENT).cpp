//#include "game.h"
//#include"dynamic_array.h"
//#include<iostream>
//#include<Windows.h>
//#include<time.h>
//using namespace std;
//
//namespace warships{
//	bool PlayerTurn = true;
//
//	class Game;
//	class Player;
//	class Ships;
//
//	int Game::destroyPlayerShip()
//	{
//		playerShips--;
//	};
//	int Game::destroyCompShip()
//	{
//		compShips--;
//	};
//	int Game::getHeight()
//	{
//		int height = height_;
//		return height;
//	}
//	int Game::getWidth()
//	{
//		int width = width_;
//		return width;
//	}
//
//	/*	ACTION getAction()
//	{
//	ACTION action;
//	HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
//	SetConsoleMode(h_in, ENABLE_MOUSE_INPUT);
//
//	INPUT_RECORD all_events[256];
//	DWORD read_event;
//
//	while (true)
//	{
//	ReadConsoleInput(h_in, all_events, 256, &read_event);
//	if (all_events[0].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
//	{
//	action.mode = LEFT_BUTTON;
//	action.coord = all_events[0].Event.MouseEvent.dwMousePosition;
//	return action;
//	}
//
//
//	else if (all_events[0].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
//	{
//	action.mode = RIGHT_BUTTON;
//	action.coord = all_events[0].Event.MouseEvent.dwMousePosition;
//	return action;
//	}
//	}
//	}*/
//
//	void Game::render(int **table_mode, int ** table_state)
//	{
//		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//		SetConsoleCursorPosition(handle, { 0, 0 });
//		for (unsigned int y = 0; y < getHeight(); y++)
//		{
//			for (unsigned int x = 0; x < getWidth(); x++)
//			{
//				switch (table_mode[y][x])
//				{
//				case CLOSE:
//					if (table_state[y][x] == SHIP_HERE && isOver)
//					{
//						SetConsoleTextAttribute(handle, 7 * 16 + 9);
//						cout << (char)254;
//					}
//					else
//					{
//						SetConsoleTextAttribute(handle, 8);
//						cout << (char)219;
//					}
//					break;
//				case OPEN:
//					SetConsoleTextAttribute(handle, 7 * 16 + 9);
//					if (table_state[y][x] == EMPTY || table_state[y][x] == NEAR_SHIP)
//					{
//						cout << ' ';
//					}
//					else if (table_state[y][x] == MISS)
//					{
//						SetConsoleTextAttribute(handle, 3 * 16 + 9);
//						cout << '*';
//					}
//					else if (table_state[y][x] == DESTROY)
//					{
//						SetConsoleTextAttribute(handle, 8 * 16 + 12);
//						cout << (char)35;
//					}
//					else if (table_state[y][x] == EXPLODED)
//					{
//						SetConsoleTextAttribute(handle, 8 * 16 + 12);
//						cout << (char)253;
//					}
//					else
//						cout << table_state[y][x];
//					break;
//				}
//
//			}
//			cout << endl;
//		}
//		SetConsoleTextAttribute(handle, 8 + 0);
//	}
//
//	void Game::renderp(int **table_mode, int ** table_state)
//	{
//		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//		for (unsigned int y = 0; y < getHeight(); y++)
//		{
//			SetConsoleCursorPosition(handle, { 12, y });
//			for (unsigned int x = 0; x < getWidth(); x++)
//			{
//				switch (table_mode[y][x])
//				{
//				case CLOSE:
//					if (table_state[y][x] == EMPTY || table_state[y][x] == NEAR_SHIP)
//					{
//						SetConsoleTextAttribute(handle, 8);
//						cout << (char)219;
//					}
//					else if (table_state[y][x] == SHIP_HERE)
//					{
//						SetConsoleTextAttribute(handle, 7 * 16 + 9);
//						cout << (char)254;
//					}
//					break;
//				case OPEN:
//					SetConsoleTextAttribute(handle, 7 * 16 + 9);
//					if (table_state[y][x] == EMPTY || table_state[y][x] == NEAR_SHIP)
//					{
//						cout << ' ';
//					}
//					else if (table_state[y][x] == SHIP_HERE)
//					{
//						cout << (char)254;
//					}
//					else if (table_state[y][x] == MISS)
//					{
//						SetConsoleTextAttribute(handle, 3 * 16 + 9);
//						cout << '*';
//					}
//					else if (table_state[y][x] == DESTROY)
//					{
//						SetConsoleTextAttribute(handle, 8 * 16 + 12);
//						cout << (char)35;
//					}
//					else if (table_state[y][x] == EXPLODED)
//					{
//						SetConsoleTextAttribute(handle, 8 * 16 + 12);
//						cout << (char)253;
//					}
//					else
//						cout << table_state[y][x];
//					break;
//				}
//
//			}
//			cout << endl;
//		}
//		SetConsoleTextAttribute(handle, 8 + 0);
//		SetConsoleCursorPosition(handle, { 25, 0 });
//		SetConsoleTextAttribute(handle, 13);
//		cout << "Your Login :  " << record.name << endl;
//		SetConsoleTextAttribute(handle, 8 + 0);
//		SetConsoleCursorPosition(handle, { 25, 1 });
//		cout << "LEFT_BUTTON : Fire " << endl;
//		SetConsoleCursorPosition(handle, { 25, 2 });
//		cout << "RIGHT_BUTTON: Menu " << endl;
//		SetConsoleCursorPosition(handle, { 25, 3 });
//	}
//
//	void Game::prepareGame()
//	{
//		system("cls");
//		system("mode con cols=100 lines=75");
//
//		int height = 10, width = 10;
//		height_ = height;
//		width_ = width;
//
//		isOver = false;
//		compShips = 4 + 3 * 2 + 2 * 3 + 1 * 4;
//
//		record.name = new char[51];
//		cout << "HEY!!! Welcome to the World of Warships \nEnter ur name pls : ";
//		cin.getline(record.name, 50);
//
//
//		/*cout << "If u want set ships write : 0 \nIf u want set ships auto write : 1 \n";
//		bool auto_set = true;
//		cin >> auto_set;
//		cout << "If u want set mode EDITOR : 1 \nElse : 0 \n";
//		cin >> editor;*/
//
//		playerShips = compShips;
//		isWin = false;
//		isGameBegin = true;
//
//		system("cls");
//	}
//
//	void Game::update()
//	{
//		if (compShips == 0)
//		{
//			isWin = isOver = true;
//		}
//		else if (playerShips == 0)
//			isOver = true;
//	}
//	//void processinput(Player player, Player enemy)
//	//{
//	//	action = getAction();
//	//	switch (action.mode)
//	//	{
//	//	case LEFT_BUTTON:
//	//		if (action.coord.X >= 0 && action.coord.X < width_&&
//	//			action.coord.Y >= 0 && action.coord.Y < height_)
//	//			enemy.openCell(gm, action.coord.X, action.coord.Y); // Fasle - it's not computer turn
//	//		break;
//	//	case RIGHT_BUTTON:// records
//	//		renderm();
//	//		menu();
//	//		system("cls");
//	//		render(enemy.getTable_mode(), enemy.getTable_state());
//	//		renderp(player.getTable_mode(), player.getTable_state());
//	//		break;
//	//	}
//	//}
//
//
//	void Game::menu()
//	{
//
//		bool menu = true;
//		do
//		{
//			action = getAction();
//			switch (action.mode)
//			{
//			case LEFT_BUTTON:
//				if (action.coord.X >= 0 && action.coord.X < 10 && action.coord.Y >= 0 && action.coord.Y < 3)
//				{
//
//					menu = false;
//				}
//				if (action.coord.X >= 11 && action.coord.X < 20 && action.coord.Y >= 0 && action.coord.Y < 3 && isGameBegin)
//				{
//					record.ships = playerShips;
//					HallOfFame(0, 5);
//				}
//				break;
//			case RIGHT_BUTTON:
//				break;
//			}
//		} while (menu);
//
//
//
//
//	}
//	void Game::renderm()
//	{
//		system("cls");
//		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//		SetConsoleTextAttribute(handle, 7 * 16 + 9);
//		for (int y = 0; y < 3; y++)										// (0,0) - (10,3)
//		{
//			for (int x = 0; x < 10; x++)
//			{
//				SetConsoleCursorPosition(handle, { x, y });
//				if (y == 1 && x == 3)
//					cout << "PLAY";
//				else if (!(y == 1 && x >= 3 && x < 7))
//					cout << ' ';
//			}
//		}
//
//		if (isGameBegin)
//		{
//			SetConsoleTextAttribute(handle, 7 * 16 + 9);
//			for (int y = 0; y < 3; y++)										// (11,0) - (20,3)
//			{
//				for (int x = 11; x < 22; x++)
//				{
//					SetConsoleCursorPosition(handle, { x, y });
//					if (y == 1 && x == 12)
//						cout << "STATISTIC";
//					else if (!(y == 1 && x >= 12 && x < 21))
//						cout << ' ';
//				}
//			}
//		}
//
//		SetConsoleTextAttribute(handle, 7 + 0);
//	}
//	void Game::HallOfFame(int x, int y)
//	{
//
//		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//		SetConsoleCursorPosition(handle, { x, y });
//		if (record.name)
//			cout << "Login : " << record.name << " - ships : " << record.ships << endl;
//		/*FILE * f;
//		fopen_s(&f, "record.txt", "r");
//		if (!f)
//		{
//		cout << "Wrong filename!\n";
//		return;
//		}
//
//		while (!feof(f))
//		putchar(fgetc(f));
//
//		fclose(f);*/
//
//	}
//	void Game::run()
//	{
//		srand(time(0));
//		renderm();
//		menu();
//		prepareGame();
//		Player * player;
//		Player * enemy;
//		player = new Player;
//		enemy = new Player;
//
//		cout << enemy->getTable_mode()[1][1] << endl;
//
//		/*render(enemy->getTable_mode(), enemy->getTable_state());*/
//		/*	renderp(player->getTable_mode(), player->getTable_state());*/
//		//while (!isOver)
//		//	{
//		//	processinput(player, enemy);
//		//	update();
//		//	render(enemy.getTable_mode(), enemy.getTable_state());
//		//	renderp(player.getTable_mode(), player.getTable_state());
//		//	enemy.AI(gm, player);
//		//	update();
//		//	render(enemy.getTable_mode(), enemy.getTable_state());
//		//	renderp(player.getTable_mode(), player.getTable_state());
//		//	}
//		//render(enemy.getTable_mode(), enemy.getTable_state());
//		if (isWin)
//		{
//			/*record.ships = game.playerShips;
//			FILE * f;
//			fopen_s(&f, "record.txt", "a");
//
//			char ships[4];
//			_itoa(record.ships, ships, 10);
//			char * rec = record.name;
//
//			strcat(rec, " ");
//			strcat(rec, ships);
//			strcat(rec, "\n");
//			fputs(rec, f);
//			fclose(f);*/
//
//			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//			SetConsoleTextAttribute(handle, 13);
//			SetConsoleCursorPosition(handle, { 22, 11 });
//			cout << "WIN!!\n";
//
//		}
//		else
//		{
//			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//			SetConsoleTextAttribute(handle, 14);
//			SetConsoleCursorPosition(handle, { 22, 11 });
//			cout << "DEFEAT!!\n";
//		}
//	}
//
//
//
//	Player::Player()
//	{
//		create_array(table_mode, getHeight(), getWidth());// player field
//		fill_array(table_mode, getHeight(), getWidth(), 0);
//		create_array(table_state, getHeight(), getWidth());
//		fill_array(table_state, getHeight(), getWidth(), 0);
//		/*Ships * ship;*/
//
//	}
//	int Player:: ** getTable_mode()
//	{
//		return table_mode;
//	}
//	int Player:: ** getTable_state()
//	{
//		return table_state;
//	}
//
//
//	void Player::openCell(unsigned int x, unsigned int y)
//	{
//		switch (table_mode[y][x])
//		{
//		case OPEN:
//			break;
//		case CLOSE:
//			table_mode[y][x] = OPEN;
//			if (table_state[y][x] == SHIP_HERE)
//			{
//				table_state[y][x] = DESTROY;
//				destroyCompShip();
//
//
//				if (ChekDestroy(y, x))// need explosion?
//				{
//					table_state[y][x] = EXPLODED; // explosion
//					explosion(y, x);				  // Explosion of neighboring cells
//				}
//				Sleep(10);										//pause on explosion;
//				update();
//
//			}
//			else if (table_state[y][x] == EMPTY || table_state[y][x] == NEAR_SHIP)
//			{
//				table_state[y][x] = MISS;
//				PlayerTurn = false;
//				break;
//			}
//			break;
//		}
//	}
//	void Player::openCell(unsigned int x, unsigned int y, int** ptable_mode, int** ptable_state)
//	{
//		switch (table_mode[y][x])
//		{
//		case OPEN:
//			break;
//		case CLOSE:
//			ptable_mode[y][x] = OPEN;
//			if (table_state[y][x] == SHIP_HERE)
//			{
//				ptable_state[y][x] = DESTROY;
//				destroyPlayerShip();
//
//
//				if (ChekDestroy(y, x, ptable_mode, ptable_state, 10000, 10000))// need explosion?
//				{
//					ptable_state[y][x] = EXPLODED; // explosion
//					explosion(y, x, ptable_mode, ptable_state);		// Explosion of neighboring cells
//				}
//				Sleep(10);								//pause on explosion;
//				update();
//
//			}
//			else if (ptable_state[y][x] == EMPTY || ptable_state[y][x] == NEAR_SHIP)
//			{
//				ptable_state[y][x] = MISS;
//				PlayerTurn = false;
//				break;
//			}
//			break;
//		}
//	}
//	bool Player::ChekDestroy(const int y, const int x, const int cheky = 10000, int const chekx = 10000)
//	{
//		for (int i = 0; i < 4; i++)
//		{
//			int dy, dx;
//			switch (i)
//			{
//			case 0: dx = 0, dy = -1; break;
//			case 1: dx = 1, dy = 0; break;
//			case 2: dx = 0, dy = 1; break;
//			case 3: dx = -1, dy = 0; break;
//			}
//			dy += y;
//			dx += x;
//			if (dx >= 0 && dy >= 0 && dx < getWidth() && dy < getHeight())
//			{
//				if (table_state[dy][dx] == NEAR_SHIP || table_state[dy][dx] == MISS)
//					continue;
//				else if (table_state[dy][dx] == SHIP_HERE)
//				{
//					return false;
//					break;
//				}
//				else if (table_state[dy][dx] == DESTROY)
//				{
//					if (dy == cheky && dx == chekx)
//						continue;
//					else
//					{
//						if (ChekDestroy(dy, dx, y, x))
//							continue;
//						else
//							return false;
//					}
//				}
//			}
//		}
//		return true;
//	}
//	bool Player::ChekDestroy(const int y, const int x, int** ptable_mode, int** ptable_state, const int cheky = 10000, int const chekx = 10000)
//	{
//		for (int i = 0; i < 4; i++)
//		{
//			int dy, dx;
//			switch (i)
//			{
//			case 0: dx = 0, dy = -1; break;
//			case 1: dx = 1, dy = 0; break;
//			case 2: dx = 0, dy = 1; break;
//			case 3: dx = -1, dy = 0; break;
//			}
//			dy += y;
//			dx += x;
//			if (dx >= 0 && dy >= 0 && dx < getWidth() && dy < getHeight())
//			{
//				if (ptable_state[dy][dx] == NEAR_SHIP || ptable_state[dy][dx] == MISS)
//					continue;
//				else if (ptable_state[dy][dx] == SHIP_HERE)
//				{
//					return false;
//					break;
//				}
//				else if (ptable_state[dy][dx] == DESTROY)
//				{
//					if (dy == cheky && dx == chekx)
//						continue;
//					else
//					{
//						if (ChekDestroy(dy, dx, ptable_mode, ptable_state, y, x))
//							continue;
//						else
//							return false;
//					}
//				}
//			}
//		}
//		return true;
//	}
//	void Player::explosion(unsigned int y, unsigned int x)
//	{
//		for (int i = 0; i < 8; i++)
//		{
//			int dx, dy;
//			switch (i)
//			{
//			case 0: dx = 0, dy = -1; break;
//			case 1: dx = 1, dy = -1; break;
//			case 2: dx = 1, dy = 0; break;
//			case 3: dx = 1, dy = 1; break;
//			case 4: dx = 0, dy = 1; break;
//			case 5: dx = -1, dy = 1; break;
//			case 6: dx = -1, dy = 0; break;
//			case 7: dx = -1, dy = -1; break;
//			}
//			dx += x;
//			dy += y;
//			if (dx >= 0 && dy >= 0 && dx < getWidth() && dy < getHeight())
//			{
//				if (table_state[dy][dx] == DESTROY)
//				{
//					table_state[dy][dx] = EXPLODED;
//					explosion(dy, dx);
//				}
//				else if (table_state[dy][dx] == NEAR_SHIP)
//				{
//					table_mode[dy][dx] = OPEN;
//					table_state[dy][dx] = MISS;
//				}
//				else if (table_state[dy][dx] == EXPLODED || table_state[dy][dx] == MISS)
//				{
//					continue;
//				}
//			}
//		}
//	}
//	void Player::explosion(unsigned int y, unsigned int x, int** ptable_mode, int** ptable_state)
//	{
//		for (int i = 0; i < 8; i++)
//		{
//			int dx, dy;
//			switch (i)
//			{
//			case 0: dx = 0, dy = -1; break;
//			case 1: dx = 1, dy = -1; break;
//			case 2: dx = 1, dy = 0; break;
//			case 3: dx = 1, dy = 1; break;
//			case 4: dx = 0, dy = 1; break;
//			case 5: dx = -1, dy = 1; break;
//			case 6: dx = -1, dy = 0; break;
//			case 7: dx = -1, dy = -1; break;
//			}
//			dx += x;
//			dy += y;
//			if (dx >= 0 && dy >= 0 && dx < getWidth() && dy < getHeight())
//			{
//				if (ptable_state[dy][dx] == DESTROY)
//				{
//					ptable_state[dy][dx] = EXPLODED;
//					explosion(dy, dx, ptable_mode, ptable_state);
//				}
//				else if (ptable_state[dy][dx] == NEAR_SHIP)
//				{
//					ptable_mode[dy][dx] = OPEN;
//					ptable_state[dy][dx] = MISS;
//				}
//				else if (ptable_state[dy][dx] == EXPLODED || ptable_state[dy][dx] == MISS)
//				{
//					continue;
//				}
//			}
//		}
//	}
//
//
//	//void AI(Game game, Player player)
//	//{
//	//	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//	//	static int shoot_x, shoot_y;
//	//	static int shoot_dy = 0, shoot_dx = 0;
//	//	static unsigned int hit = 1;
//	//	while (!PlayerTurn)
//	//	{
//	//		bool compTurn = true;
//	//		do
//	//		{
//	//			if (hit == 1)
//	//			{
//	//				shoot_dx = 0;
//	//				shoot_dy = 0;
//	//				shoot_x = rand() % game.getWidth();
//	//				shoot_y = rand() % game.getHeight();
//	//			}
//	//			shoot_dy += shoot_y;
//	//			shoot_dx += shoot_x;
//	//		} while (table_mode[shoot_dy][shoot_dx] != game.CLOSE);
//	//		if (shoot_dx >= 0 && shoot_dy >= 0 && shoot_dx < game.getWidth() && shoot_dy < game.getHeight())
//	//		{
//	//			/*hit++;*/
//	//			openCell(game, shoot_dx, shoot_dy, player.getTable_mode(), player.getTable_state());
//	//			game.renderp(getTable_mode(), getTable_state());
//	//		}
//	//	}
//	//}
//	// _____________Artificial Intelligence____________
//
//	class Ships : public Player
//	{
//	private:
//
//	public:
//		Ships()
//		{
//			SetShipAuto(4);
//
//			SetShipAuto(3);
//			SetShipAuto(3);
//
//			SetShipAuto(2);
//			SetShipAuto(2);
//			SetShipAuto(2);
//
//			SetShipAuto(1);
//			SetShipAuto(1);
//			SetShipAuto(1);
//			SetShipAuto(1);
//		}
//		int chekCoord(int y, int x)
//		{
//			if (x >= 0 && y >= 0 && x < getWidth() && y < getHeight())
//			{
//				if (getTable_state()[y][x] == Game::EMPTY)
//				{
//					return 1;
//
//				}
//				else
//					return 0;
//			}
//			return 0;
//		}
//		void SetShipAuto(int deck_)
//		{
//			unsigned int cell_ships = 0;
//			bool mistake = true;
//			do
//			{
//				int x = rand() % getWidth();
//				int y = rand() % getHeight();
//				bool horizont = rand() % 2;
//
//				if (getTable_state()[y][x] == Game::EMPTY)
//				{
//					short empcl = 0;
//					for (int i = 0; i < deck_; i++)
//					{
//						if (horizont)
//						{
//							empcl += chekCoord(y, x + i);
//						}
//						else
//						{
//							empcl += chekCoord(y + i, x);
//						}
//					}
//
//					if (empcl == deck_ && horizont)
//					{
//						for (int i = 0; i < deck_; i++)
//						{
//							getTable_state()[y][x + i] = Game::SHIP_HERE;
//							++cell_ships;
//						}
//					}
//					else if (empcl == deck_ && !horizont)
//					{
//						for (int i = 0; i < deck_; i++)
//						{
//							getTable_state()[y + i][x] = Game::SHIP_HERE;
//							++cell_ships;
//						}
//					}
//				}
//			} while (cell_ships < deck_ && mistake);
//			//_______________________________________________________ chek
//			for (int y = 0; y < getHeight(); y++)
//				for (int x = 0; x < getWidth(); x++)
//				{
//					if (getTable_state()[y][x] == Game::SHIP_HERE)//_____________If there ship...
//						for (int i = 0; i < 8; i++)
//						{
//							int dx, dy;//_______________Chek cells near
//							switch (i)
//							{
//							case 0: dx = 0, dy = -1; break;
//							case 1: dx = 1, dy = -1; break;
//							case 2: dx = 1, dy = 0; break;
//							case 3: dx = 1, dy = 1; break;
//							case 4: dx = 0, dy = 1; break;
//							case 5: dx = -1, dy = 1; break;
//							case 6: dx = -1, dy = 0; break;
//							case 7: dx = -1, dy = -1; break;
//							}
//							dx += x;
//							dy += y;
//							if (dx >= 0 && dy >= 0 && dx < getWidth() && dy < getHeight())// ____ WIthin the game field
//								if (getTable_state()[dy][dx] == Game::EMPTY)
//								{
//									getTable_state()[dy][dx] = Game::NEAR_SHIP;
//								}
//						}
//				}
//		};
//	};
//
//
//
//
//
//	void main()
//	{
//
//		Game game;
//		game.run();
//		system("pause");
//
//	}
//
//
//}