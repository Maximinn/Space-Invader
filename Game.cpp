#include "Game.h"
#include <conio.h>

unsigned int  Game::nb_Kill = 0;

//### TODO FUNCTIONS ***************************************
//-----------------------------------------------------
void Game::Ship_Laser_Create() {
	//### TODO	
	if (Nb_ShipLasers < 50) {
		Ship_Lasers[Nb_ShipLasers] = new Laser_Ship(My_Ship.coord.X, My_Ship.coord.Y - 1);
		Nb_ShipLasers++;
	}
	else {
		// trouve un obus inactif, rendu en haut de l'ecran
		for (int i = 0; i < Nb_ShipLasers; i++) {
			if (Ship_Lasers[i]->isAlive == false) {
				delete Ship_Lasers[i]; // libere la memoire
				Ship_Lasers[i] = new Laser_Ship(My_Ship.coord.X, My_Ship.coord.Y - 1);
				break;
			}
		}
	}
}

//-----------------------------------------------------
void Game::Enemy_Lasers_Move_All() {
	//### TODO	
	for (int i = 0; i < Nb_EnemyLasers; i++) {
		if (Enemy_Lasers[i]->isAlive)
		{
			Enemy_Lasers[i]->move();
		}
	}
}

//-----------------------------------------------------
bool Game::Check_Ship_Killed() {
	//### TODO	
	bool rep = false;
	for (int i = 0; i < Nb_EnemyLasers; i++) {
		if (Enemy_Lasers[i]->isAlive && My_Ship.coord.X == Enemy_Lasers[i]->coord.X && My_Ship.coord.Y == Enemy_Lasers[i]->coord.Y) {
			rep = (true);
			break;
		}
		else {
			rep = (false);
		}
	}
	return (rep);
}

//-------------------------------------------------------
void Game::Ship_Lasers_Move_All() {
	//### TODO	
	for (int i = 0; i < Nb_ShipLasers; i++) {
		if (Ship_Lasers[i]->isAlive) {
			Ship_Lasers[i]->move();
		}
	}

}

//-------------------------------------------------------
void Game::Create_Enemy_Laser(int x, int y) {
	//### TODO	
	if (Nb_EnemyLasers < 100)
	{
		Laser_Enemies* laserEnemie = new Laser_Enemies(x, y);
		Enemy_Lasers[Nb_EnemyLasers] = laserEnemie;
		Nb_EnemyLasers++;
	}
	else {
		// trouve un obus inactif, rendu en haut de l'ecran
		for (int i = 0; i < Nb_EnemyLasers; i++) {
			if (Enemy_Lasers[i]->isAlive == false) {
				delete Enemy_Lasers[i]; // libere la memoire
				Enemy_Lasers[i] = new Laser_Enemies(x, y);
				break;
			}
		}
	}

}

//-------------------------------------------------------
void Game::ETs_Move_All() {
	//### TODO	
	for (int i = 0; i < Nb_ETs; i++) {
		ET_List[i]->move();
	}

}

//-------------------------------------------------------
void Game::Check_ETs_Killed() {
	//### TODO	
	for (int i = 0; i < Nb_ShipLasers; i++) {
		if (Ship_Lasers[i]->isAlive) {
			for (int j = 0; j < Nb_ETs; j++)
			{
				if (ET_List[j]->isAlive && ET_List[j]->coord.X == Ship_Lasers[i]->coord.X && ET_List[j]->coord.Y == Ship_Lasers[i]->coord.Y)
				{
					ET_List[j]->kill();
					if (ET_List[j]->isAlive == false && j != Nb_ETs - 1) {
						delete ET_List[j];
						for (int l = j; l < Nb_ETs; l++) {
							ET_List[l] = ET_List[l + 1];
						}
					}
					Ship_Lasers[i]->kill();
					Nb_ETs--;
					nb_Kill++;

					if (nb_Kill <= 5) {
						score += 50;
					}
					else if (nb_Kill > 5 && nb_Kill <= 10) {
						level = 2;
						score += 100;
					}
					else if (nb_Kill > 10) {
						level = 3;
						score += 150;
					}

					break;
				}
			}
		}
	}
}

//-------------------------------------------------------
void Game::Enemies_Create() {
	clock_t t;

	t = clock() - last_ET_time;
	if ((((float)t) / CLOCKS_PER_SEC) > ET_Period) {
		last_ET_time = clock();
		//### TODO	
		if (Nb_ETs < 10)
		{
			ET_List[Nb_ETs] = new Enemy_Fast;
			verifieEnemyExiste(ET_List[Nb_ETs]);
			Nb_ETs++;
			if (nb_Kill <= 5) {
				for (int i = 0; i < Nb_ETs; i++) {
					Create_Enemy_Laser(ET_List[i]->coord.X, ET_List[i]->coord.Y + 1);
				}
			}
			else if (nb_Kill > 5 && nb_Kill <= 10) {

				for (int i = 0; i < Nb_ETs; i++) {
					Create_Enemy_Laser(ET_List[i]->coord.X + 1, ET_List[i]->coord.Y + 1);
				}
				for (int i = 0; i < Nb_ETs; i++) {
					Create_Enemy_Laser(ET_List[i]->coord.X - 1, ET_List[i]->coord.Y + 1);
				}

			}
			else if (nb_Kill > 10) {

				for (int i = 0; i < Nb_ETs; i++) {
					Create_Enemy_Laser(ET_List[i]->coord.X, ET_List[i]->coord.Y + 1);
				}
				for (int i = 0; i < Nb_ETs; i++) {
					Create_Enemy_Laser(ET_List[i]->coord.X + 1, ET_List[i]->coord.Y + 1);
				}
				for (int i = 0; i < Nb_ETs; i++) {
					Create_Enemy_Laser(ET_List[i]->coord.X - 1, ET_List[i]->coord.Y + 1);
				}
			}

		}
		else
		{
			for (int i = 0; i < Nb_ETs; i++)
			{
				if (!ET_List[i]->isAlive) {
					delete ET_List[i];
					ET_List[i] = new Enemy_Fast;
					verifieEnemyExiste(ET_List[i]);
					break;
				}
			}
		}
	}
}

//-------------------------------------------------------
int Game::Enemies_Get_Total_Alive() {
	//### TODO	
	int Total_Alive_enemies = 0;
	for (int i = 0; i < Nb_ETs; i++)
	{
		if (ET_List[i]->isAlive)
		{
			Total_Alive_enemies++;
		}
	}
	return(Total_Alive_enemies);// none were ever created, so don't return 0
}

//-------------------------------------------------------
bool Game::Enemies_Check_All_Killed() {
	//### TODO	
	if (Nb_ETs == 0) {
		return(true);
	}
	else {
		return(false);
	}


}

void Game::verifieEnemyExiste(Enemy_Fast * enemy)
{
	bool rep = false;
	int i = 0;
	while (!rep && i < Nb_ETs)
	{
		if (ET_List[i]->isAlive && ET_List[i]->coord.X == enemy->coord.X && ET_List[i]->coord.Y == enemy->coord.Y)
		{

			delete enemy;
			enemy = new Enemy_Fast;
			i = 0;
			break;
		}
		else {
			i++;
		}

	}
}


//*****************************************************************8
// Constructor --------------------------------------------------
Game::Game()
{
	// initialize game variables
	score = 0;
	level = 1;
	Nb_ShipLasers = 0;
	Nb_EnemyLasers = 0;
	Nb_ETs = 0;
	ET_Period = 5;// seconds
	nb_Kill = 0;
}

// destructor --------------------------------------
Game::~Game()
{
	// delete the ETs Ennemy_Fast  --------------------------
	for (int i = 1; i <= Nb_ETs; i++) {
		delete ET_List[i - 1];
	}

	// delete the ship lasers --------------------------
	for (int i = 1; i <= Nb_ShipLasers; i++) {
		delete Ship_Lasers[i - 1];
	}

	// delete the enemy lasers --------------------------
	for (int i = 1; i <= Nb_EnemyLasers; i++) {
		delete Enemy_Lasers[i - 1];
	}
}

int Game::getScore() {
	return score;
}

int Game::getLevel() {
	return level;
}

// ---------------------------------------------------------------
// Play() function starts and ends the game
// return: 0=>Game Over, 1=>You win, 2=>You Quit
// type e to quit/exit game
// --------------------------------------------------------------
int Game::Play() {

	char Key_Pressed; // key pressed by player on keyboard

	//----------------------------------------------------
	// set window dimension 100 columns, 42 lines
	system("CLS");
	UIKit::setWindowDimensions(0, 0, 100, 42);

	// left game frame with ship etc... 
	// the game field is 40 columns X 40 lines
	// so make the frame around 41 columns, 43 lines, color 15
	UIKit::frame(0, 0, 41, 42, 15);

	// right frame for level display, color 11
	UIKit::frame(49, 3, 70, 5, 11);

	// right frame for score display, color 11
	UIKit::frame(49, 6, 70, 8, 11);

	// show the ship
	My_Ship.show();

	// create at least 1 ET (Enemy_Fast), those move from left to right
	ET_List[0] = new Enemy_Fast;
	Nb_ETs = 1;
	Create_Enemy_Laser(ET_List[0]->coord.X, ET_List[0]->coord.Y + 1);
	last_ET_time = clock();// time when the last ennemy was created

	Game_Paused = false;

	// MASTER GAME LOOP ---------------------------------------------
	while (true) {

		Sleep(50); // slow down the game loop

		//Read keyboard input -----------------------
		if (_kbhit()) {
			Key_Pressed = _getch();
		}
		else {
			Key_Pressed = 0;
		}

		if (Key_Pressed == 'h') {
			// pause the game
			Game_Paused = true;
			continue; // skip the rest and restart from top of while loop
		}
		else if (Key_Pressed == 0 and Game_Paused) {
			// no key pressed, stay paused
			continue; // skip the rest and restart from top of while loop
		}
		else {
			// key was pressed, resume game
			Game_Paused = false;
		}

		switch (Key_Pressed) {
		case 'e':
			return(2);// User quit the game before the end

		case 32:
			// spacebar ASCII code = 32
			// Create new ship lasers
			// ### TODO
			Ship_Laser_Create();
			break;

		case 'k':
		case 'l':
			// Move ship ---------------------------------
			My_Ship.move(Key_Pressed);
			break;
		}
		// end of switch ------------------------------------------


		// move the enemy lasers ----------------------------
		// ### TODO
		Enemy_Lasers_Move_All();

		// check if ship killed by enemy fire ---------------
		// ### TODO
		if (Check_Ship_Killed()) {
			return(0); // Game Over
		}

		// move the ship lasers -----------------------------
		// ### TODO
		Ship_Lasers_Move_All();

		// move the ETs (Enemy_Fast) ------------------------
		// ### TODO
		ETs_Move_All();

		// check ETs killed ---------------------------------
		// ### TODO
		Check_ETs_Killed();

		// Count how many enemies are alive
		// stop game if 10 enemies alive (as per problem requirement)
		// ### TODO
		if (Enemies_Get_Total_Alive() >= 10) {
			return(0); // Game Over
		}

		// Check if all enemies were killed
		// End game or change level
		// ### TODO
		if (Enemies_Check_All_Killed()) {
			return(1); // you win
		}

		// periodically create more ETs  ---------------------
		// ### TODO 
		Enemies_Create();

		// Update game info in the right frame ---------------
		UIKit::color(Game_Info_Color);

		// level 
		UIKit::gotoXY(50, 4); // go in level box
		std::cout << "Level    : " << level;

		// score
		UIKit::gotoXY(50, 7); // go in score box
		std::cout << "Score    : " << score;
	}

}


