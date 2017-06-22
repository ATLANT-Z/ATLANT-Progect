#include<Windows.h>
namespace warships{
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
		void run();

		ACTION getAction();

		int destroyPlayerShip();
		int destroyCompShip();
		int getHeight();
		int getWidth();

		void prepareGame();

		void update();
		void processinput(Player player, Player enemy);
		void render(int **table_mode, int ** table_state);

		void renderp(int **table_mode, int ** table_state);

		void menu();
		void renderm();
		void HallOfFame(int x, int y);
	};

	class Player
	{
	private:
		int ** table_mode;
		int ** table_state;
	public:
		Player(Game game);
		int ** getTable_mode();
		int ** getTable_state();

		void openCell(Game game, unsigned int x, unsigned int y);
		void openCell(Game game, unsigned int x, unsigned int y, int** ptable_mode, int** ptable_state);
		bool ChekDestroy(Game game, const int y, const int x, const int cheky = 10000, int const chekx = 10000);
		bool ChekDestroy(Game game, const int y, const int x, int** ptable_mode, int** ptable_state, const int cheky = 10000, int const chekx = 10000);
		void explosion(Game game, unsigned int y, unsigned int x);
		void explosion(Game game, unsigned int y, unsigned int x, int** ptable_mode, int** ptable_state);

		void AI(Game game, Player player);
		// _____________Artificial Intelligence____________
	};

	class Ships
	{
	private:
		int deck_;
	public:
		Ships(Game game, Player player, int deck);
		int chekCoord(Game & game, Player player, int y, int x);
		void SetShipAuto(Game & game, Player player, int deck_);
	};


	
	
	
	

	
	

	


	
}