#include<Windows.h>
namespace warships{

	static bool PlayerTurn = true;
	class Game;
	class Player;
	class Mouse;
	class Record;
	class Menu;
	class AI;
	class Map;

	class Mouse
	{
	public:
		enum ACTION_MODE{ LEFT_BUTTON, RIGHT_BUTTON };
		struct ACTION{
			ACTION_MODE mode;
			COORD coord;
		};
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
	};

	class Menu : public Mouse
	{
	public:

		void menu(Game&game, Record &record);
		void renderm(Game&game);

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


		unsigned int getPlayerShips()
		{
			return playerShips;
		}
		unsigned int getCompShips()
		{
			return compShips;
		}
		bool getIsGameBegin()
		{
			return isGameBegin;
		}
		bool getIsOver()
		{
			return isOver;
		}
		void destroyPlayerShip()
		{
			playerShips--;
		}
		void destroyCompShip()
		{
			compShips--;
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
		void update()
		{
			if (compShips == 0)
			{
				isWin = isOver = true;
			}
			else if (playerShips == 0)
				isOver = true;
		}

		void prepareGame(Record & record);
		void processinput(Game&game, Player player, Player enemy, Record & record, Menu&menu, Map&playerMap, Map&compMap);
		void run(Game&game);
	};

	class Record : public Game
	{

	public:

		struct RECORD{
			char * name;
			unsigned int pShips;
			unsigned int cShips;
		};
		RECORD record;
		void setName(char * a)
		{
			record.name = a;
		}
		void setPlayerShips(int a)
		{
			record.pShips = a;
		}
		void setCompShips(int a)
		{
			record.cShips = a;
		}
		char * getName()
		{
			return record.name;
		}
		int getPlayerShips()
		{
			return record.pShips;
		}
		int getCompShips()
		{
			return record.cShips;
		}

		void hallOfFame(const int x, const int y, Game&game);
		void setRecord(Game&game);
		void showRecords(Game&game);

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

	};

	class Map : public Game
	{
	public:
		int ** table_mode;
		int ** table_state;

		Map();

		void render(Game&game);
		void renderp();

		void setShips();
		int chekCoord(int y, int x);
		void SetShipAuto(int deck_);
	};

	class Player : public Game
	{
		friend class Ships;
	public:

		void openCell(Game&game, Map&map, unsigned int x, unsigned int y, bool AI = false);
		bool ChekDestroy(Map&map, const int y, const int x, const int cheky = -1, int const chekx = -1);
		void explosion(Map&map, unsigned int y, unsigned int x);


	};

	// _____________Artificial Intelligence____________
	class AI : public Game
	{
	public:
		void simpleAi(Game & game, Map&map, Player & player)
		{
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
						shoot_x = rand() % getWidth();
						shoot_y = rand() % getHeight();
					}
					shoot_dy += shoot_y;
					shoot_dx += shoot_x;
				} while (map.table_mode[shoot_dy][shoot_dx] != CLOSE);
				if (shoot_dx >= 0 && shoot_dy >= 0 && shoot_dx < getWidth() && shoot_dy < getHeight())
				{
					player.openCell(game, map, shoot_dx, shoot_dy, true);
					map.renderp();
				}
				game.update();
			}
		}
		void hardAi(Game & game, Map&map, Player& player)
		{
			static int shoot_x, shoot_y;
			static	short side = 0;
			static int shoot_dy = 0, shoot_dx = 0;
			static bool apple = false;
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
									if (map.table_mode[shoot_dy + shoot_y][shoot_dx + shoot_x] == OPEN)
										side++;
								}
								else
									side++;
							} while (!(shoot_dx + shoot_x >= 0 && shoot_dy + shoot_y >= 0 && shoot_dx + shoot_x < getWidth() && shoot_dy + shoot_y < getHeight()));
						} while (map.table_mode[shoot_dy + shoot_y][shoot_dx + shoot_x] != CLOSE);
					}

					shoot_dy += shoot_y;
					shoot_dx += shoot_x;

				} while (map.table_mode[shoot_dy][shoot_dx] != CLOSE);
				//___________________________________________________________________________
				if (shoot_dx >= 0 && shoot_dy >= 0 && shoot_dx < getWidth() && shoot_dy < getHeight())
				{
					hit++;
					player.openCell(game, map, shoot_dx, shoot_dy, compTurn);
					map.renderp();
					shoot_dy -= shoot_y;
					shoot_dx -= shoot_x;

					if (map.table_state[shoot_dy + shoot_y][shoot_dx + shoot_x] == DESTROY)// get vector
					{
						if (hit == 2)
						{
							apple = true;

						}
						if (shoot_dy > 0)
						{
							apple = false;
							if (shoot_dy + 1 + shoot_y < getHeight())// dy = 1
							{
								shoot_dy++;
							}
							else
							{
								shoot_dy = -1;
							}
						}
						else if (shoot_dy < 0)
						{
							apple = false;
							if (shoot_dy - 1 + shoot_y >= 0)// dy = -1
							{
								shoot_dy--;
							}
							else
							{
								shoot_dy = 1;
							}
						}
						else if (shoot_dx > 0)
						{
							apple = false;
							if (shoot_dx + 1 + shoot_x < getWidth())// dx = 1
							{
								shoot_dx++;
							}
							else
							{
								shoot_dx = -1;
							}
						}
						else if (shoot_dx < 0)
						{
							apple = false;
							if (shoot_dx - 1 + shoot_x >= 0)// dx = -1
							{
								shoot_dx--;
							}
							else
							{
								shoot_dx = 1;
							}
						}
					}
					else if (map.table_state[shoot_dy + shoot_y][shoot_dx + shoot_x] == MISS)
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
					else if (map.table_state[shoot_dy + shoot_y][shoot_dx + shoot_x] == EXPLODED)
					{
						apple = false;
						hit = 1;
						side = 0;
						shoot_dx = 0;
						shoot_dy = 0;
					}
				}
				else
				{
					shoot_dy -= shoot_y;
					shoot_dx -= shoot_x;
				}
			}
		}

	};
}
