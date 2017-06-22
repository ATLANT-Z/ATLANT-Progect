#include "game.h"
#include"dynamic_array.h"
#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;

namespace warships{

	bool PlayerTurn = true; 

	class Game;
	class Player;
	class Ship;

	/*bool editor = false;*/
	class Game
	{
		friend class Player;
	private:
		unsigned int height_;
		unsigned int width_;

		bool isOver;
		bool isWin;
		bool isGameBegin = false;
	protected:
		unsigned int playerShips;
		unsigned int compShips;
	public:
		enum MODE{ CLOSE, OPEN };
		enum STATE{ EMPTY, SHIP_HERE, NEAR_SHIP, MISS, DESTROY, EXPLODED };
		enum ACTION_MODE{ LEFT_BUTTON, RIGHT_BUTTON };

		struct ACTION{
			ACTION_MODE mode;
			COORD coord;
		};
		struct RECORD{
			char * name;
			unsigned int ships;
		};
		RECORD record;
		ACTION action;
		

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

		int destroyPlayerShip()
		{
			playerShips--;
		};
		int destroyCompShip()
		{
			compShips--;
		};
		int getHeight()
		{
			return height_;
		}
		int getWidth()
		{
			return width_;
		}

		void prepareGame()
		{
			system("cls");
			system("mode con cols=100 lines=75");

			int height = 10, width = 10;
			height_ = height;
			width_ = width;

			


			isOver = false;
			compShips = 4 + 3 * 2 + 2 * 3 + 1 * 4;

			record.name = new char[51];
			cout << "HEY!!! Welcome to the World of Warships \nEnter ur name pls : ";
			cin.getline(record.name, 50);


			/*cout << "If u want set ships write : 0 \nIf u want set ships auto write : 1 \n";
			bool auto_set = true;
			cin >> auto_set;
			cout << "If u want set mode EDITOR : 1 \nElse : 0 \n";
			cin >> editor;*/

			playerShips = compShips;
			isWin = false;
			isGameBegin = true;

			system("cls");
		}
		
		void update()
		{
			if (compShips == 0)
			{
				isWin = isOver = true;
			}
			else if (playerShips == 0)
				isOver = true;
		}
		void processinput(Player player, Player enemy)
		{
			action = getAction();
			switch (action.mode)
			{
			case LEFT_BUTTON:
				if (action.coord.X >= 0 && action.coord.X < width_&&
					action.coord.Y >= 0 && action.coord.Y < height_)
					enemy.openCell(gm, action.coord.X, action.coord.Y); // Fasle - it's not computer turn
				break;
			case RIGHT_BUTTON:// records
				renderm();
				menu();
				system("cls");
				render(enemy.getTable_mode(), enemy.getTable_state());
				renderp(player.getTable_mode(), player.getTable_state());
				break;
			}
		}
		void render(int **table_mode, int ** table_state)
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
						if (table_state[y][x] == SHIP_HERE && isOver)
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

		void renderp(int **table_mode, int ** table_state)
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
			SetConsoleCursorPosition(handle, { 25, 0 });
			SetConsoleTextAttribute(handle, 13);
			cout << "Your Login :  " << record.name << endl;
			SetConsoleTextAttribute(handle, 8 + 0);
			SetConsoleCursorPosition(handle, { 25, 1 });
			cout << "LEFT_BUTTON : Fire " << endl;
			SetConsoleCursorPosition(handle, { 25, 2 });
			cout << "RIGHT_BUTTON: Menu " << endl;
			SetConsoleCursorPosition(handle, { 25, 3 });
		}

		void menu()
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
						record.ships = playerShips;
						HallOfFame(0, 5);
					}
					break;
				case RIGHT_BUTTON:
					break;
				}
			} while (menu);




		}
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
		void HallOfFame(int x, int y)
		{

			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(handle, { x, y });
			if (record.name)
				cout << "Login : " << record.name << " - ships : " << record.ships << endl;
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
		void run()
		{
			srand(time(0));
			renderm();
			menu();
			prepareGame();
			static Player player(gm);
			static Player enemy(gm);
			render(enemy.getTable_mode(), enemy.getTable_state());
			renderp(player.getTable_mode(), player.getTable_state());
			while (!isOver)
			{
				processinput(player, enemy);
				update();
				render(enemy.getTable_mode(), enemy.getTable_state());
				renderp(player.getTable_mode(), player.getTable_state());
				enemy.AI(gm, player);
				update();
				render(enemy.getTable_mode(), enemy.getTable_state());
				renderp(player.getTable_mode(), player.getTable_state());
			}
			render(enemy.getTable_mode(), enemy.getTable_state());
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

				HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, 13);
				SetConsoleCursorPosition(handle, { 22, 11 });
				cout << "WIN!!\n";

			}
			else
			{
				HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, 14);
				SetConsoleCursorPosition(handle, { 22, 11 });
				cout << "DEFEAT!!\n";
			}
		}
	}gm;

	class Player
	{
	private:
		int ** table_mode;
		int ** table_state;
	public:
		Player(Game game)
		{
			create_array(table_mode, game.getHeight(), game.getWidth());// player field
			fill_array(table_mode, game.getHeight(), game.getWidth(), 0);
			create_array(table_state, game.getHeight(), game.getWidth());
			fill_array(table_state, game.getHeight(), game.getWidth(), 0);
			Ships(game, pl, 4);

			Ships(game, pl, 3);
			Ships(game, pl, 3);

			Ships(game, pl, 2);
			Ships(game, pl, 2);
			Ships(game, pl, 2);

			Ships(game, pl, 1);
			Ships(game, pl, 1);
			Ships(game, pl, 1);
			Ships(game, pl, 1);

		}
		int ** getTable_mode()
		{
			return table_mode;
		}
		int ** getTable_state()
		{
			return table_state;
		}

		void openCell(Game game, unsigned int x, unsigned int y)
		{
			switch (table_mode[y][x])
			{
			case game.OPEN:
				break;
			case game.CLOSE:
				table_mode[y][x] = game.OPEN;
				if (table_state[y][x] == game.SHIP_HERE)
				{
					table_state[y][x] = game.DESTROY;
					game.destroyCompShip();


					if (ChekDestroy(game, y, x))// need explosion?
					{
						table_state[y][x] = game.EXPLODED; // explosion
						explosion(game, y, x);				  // Explosion of neighboring cells
					}
					Sleep(10);										//pause on explosion;
					game.update();

				}
				else if (table_state[y][x] == game.EMPTY || table_state[y][x] == game.NEAR_SHIP)
				{
					table_state[y][x] = game.MISS;
					PlayerTurn = false;
					break;
				}
				break;
			}
		}
		void openCell(Game game, unsigned int x, unsigned int y, int** ptable_mode, int** ptable_state)
		{
			switch (table_mode[y][x])
			{
			case game.OPEN:
				break;
			case game.CLOSE:
				ptable_mode[y][x] = game.OPEN;
				if (table_state[y][x] == game.SHIP_HERE)
				{
					ptable_state[y][x] = game.DESTROY;
					game.destroyPlayerShip();


					if (ChekDestroy(game, y, x, ptable_mode, ptable_state, 10000, 10000))// need explosion?
					{
						ptable_state[y][x] = game.EXPLODED; // explosion
						explosion(game, y, x, ptable_mode, ptable_state);		// Explosion of neighboring cells
					}
					Sleep(10);								//pause on explosion;
					game.update();

				}
				else if (ptable_state[y][x] == game.EMPTY || ptable_state[y][x] == game.NEAR_SHIP)
				{
					ptable_state[y][x] = game.MISS;
					PlayerTurn = false;
					break;
				}
				break;
			}
		}
		bool ChekDestroy(Game game, const int y, const int x, const int cheky = 10000, int const chekx = 10000)
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
				if (dx >= 0 && dy >= 0 && dx < game.getWidth() && dy < game.getHeight())
				{
					if (table_state[dy][dx] == game.NEAR_SHIP || table_state[dy][dx] == game.MISS)
						continue;
					else if (table_state[dy][dx] == game.SHIP_HERE)
					{
						return false;
						break;
					}
					else if (table_state[dy][dx] == game.DESTROY)
					{
						if (dy == cheky && dx == chekx)
							continue;
						else
						{
							if (ChekDestroy(game, dy, dx, y, x))
								continue;
							else
								return false;
						}
					}
				}
			}
			return true;
		}
		bool ChekDestroy(Game game, const int y, const int x, int** ptable_mode, int** ptable_state, const int cheky = 10000, int const chekx = 10000)
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
				if (dx >= 0 && dy >= 0 && dx < game.getWidth() && dy < game.getHeight())
				{
					if (ptable_state[dy][dx] == game.NEAR_SHIP || ptable_state[dy][dx] == game.MISS)
						continue;
					else if (ptable_state[dy][dx] == game.SHIP_HERE)
					{
						return false;
						break;
					}
					else if (ptable_state[dy][dx] == game.DESTROY)
					{
						if (dy == cheky && dx == chekx)
							continue;
						else
						{
							if (ChekDestroy(game, dy, dx, ptable_mode, ptable_state, y, x))
								continue;
							else
								return false;
						}
					}
				}
			}
			return true;
		}
		void explosion(Game game, unsigned int y, unsigned int x)
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
				if (dx >= 0 && dy >= 0 && dx < game.getWidth() && dy < game.getHeight())
				{
					if (table_state[dy][dx] == game.DESTROY)
					{
						table_state[dy][dx] = game.EXPLODED;
						explosion(game, dy, dx);
					}
					else if (table_state[dy][dx] == game.NEAR_SHIP)
					{
						table_mode[dy][dx] = game.OPEN;
						table_state[dy][dx] = game.MISS;
					}
					else if (table_state[dy][dx] == game.EXPLODED || table_state[dy][dx] == game.MISS)
					{
						continue;
					}
				}
			}
		}
		void explosion(Game game, unsigned int y, unsigned int x, int** ptable_mode, int** ptable_state)
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
				if (dx >= 0 && dy >= 0 && dx < game.getWidth() && dy < game.getHeight())
				{
					if (ptable_state[dy][dx] == game.DESTROY)
					{
						ptable_state[dy][dx] = game.EXPLODED;
						explosion(game, dy, dx, ptable_mode, ptable_state);
					}
					else if (ptable_state[dy][dx] == game.NEAR_SHIP)
					{
						ptable_mode[dy][dx] = game.OPEN;
						ptable_state[dy][dx] = game.MISS;
					}
					else if (ptable_state[dy][dx] == game.EXPLODED || ptable_state[dy][dx] == game.MISS)
					{
						continue;
					}
				}
			}
		}
		
		void AI(Game game, Player player)
		{
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

			static int shoot_x, shoot_y;
			static int shoot_dy = 0, shoot_dx = 0;
			static unsigned int hit = 1;

			while (!PlayerTurn)
			{
				bool compTurn = true;
				do
				{
					if (hit == 1)
					{
						shoot_dx = 0;
						shoot_dy = 0;
						shoot_x = rand() % game.getWidth();
						shoot_y = rand() % game.getHeight();
					}
					shoot_dy += shoot_y;
					shoot_dx += shoot_x;

				} while (table_mode[shoot_dy][shoot_dx] != game.CLOSE);
				if (shoot_dx >= 0 && shoot_dy >= 0 && shoot_dx < game.getWidth() && shoot_dy < game.getHeight())
				{
					/*hit++;*/
					openCell(game, shoot_dx, shoot_dy, player.getTable_mode(), player.getTable_state());
					game.renderp(getTable_mode(), getTable_state());
				}
			}
		}
		// _____________Artificial Intelligence____________
	}pl;

	class Ships
	{
	private:
		int deck_;
	public:
		Ships(Game game, Player player, int deck)
		{
			deck_ = deck;
			SetShipAuto(game, player, deck_);
		}
		int chekCoord(Game & game, Player player, int y, int x)
		{
			if (x >= 0 && y >= 0 && x < game.getWidth() && y < game.getHeight())
			{
				if (player.getTable_state()[y][x] == game.EMPTY)
				{
					return 1;

				}
				else
					return 0;
			}
			return 0;
		}
		void SetShipAuto(Game & game,Player player,int deck_)
		{
			unsigned int cell_ships = 0;
			bool mistake = true;
			do
			{
				int x = rand() % game.getWidth();
				int y = rand() % game.getHeight();
				bool horizont = rand() % 2;

				if (player.getTable_state()[y][x] == game.EMPTY)
				{
					short empcl = 0;
					for (int i = 0; i < deck_; i++)
					{
						if (horizont)
						{
							empcl += chekCoord(game, player, y, x + i);
						}
						else
						{
							empcl += chekCoord(game, player, y + i, x);
						}
					}

					if (empcl == deck_ && horizont)
					{
						for (int i = 0; i < deck_; i++)
						{
							player.getTable_state()[y][x + i] = game.SHIP_HERE;
							++cell_ships;
						}
					}
					else if (empcl == deck_ && !horizont)
					{
						for (int i = 0; i < deck_; i++)
						{
							player.getTable_state()[y + i][x] = game.SHIP_HERE;
							++cell_ships;
						}
					}
				}
			} while (cell_ships < deck_ && mistake);
			//_______________________________________________________ chek
			for (int y = 0; y < game.getHeight(); y++)
				for (int x = 0; x < game.getWidth(); x++)
				{
					if (player.getTable_state()[y][x] == game.SHIP_HERE)//_____________If there ship...
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
							if (dx >= 0 && dy >= 0 && dx < game.getWidth() && dy < game.getHeight())// ____ WIthin the game field
								if (player.getTable_state()[dy][dx] == game.EMPTY)
								{
									player.getTable_state()[dy][dx] = game.NEAR_SHIP;
								}
						}
				}
		};
	};
	 
}