#include<iostream>

//Enum that helps identifying player turn.
namespace PlayerTurn
{
	enum PlayerTurn
	{
		PLAYER1,
		PLAYER2,
	};
}

//Enum that helps identifying the result of the game.
namespace Result
{
	enum Result
	{
		PLAYER1,
		PLAYER2,
		DRAW,
	};
}

//Class that controls everything of the game except taking inputs from the players.
class TicTacToe
{
private:
	//Space where the game is played.
	static int matrix[3][3];

protected:
	//Function that decides the winner.
	bool check()
	{
		for(int i=0; i<3; i++)
		{
			//Checks if any of the row is filled with the same input.
			if(matrix[i][0] == matrix[i][1] and matrix[i][0] == matrix[i][2] and matrix[i][0] != -1)
				return true;

			//Checks if any of the column is filled with the same input.
			if(matrix[0][i] == matrix[1][i] and matrix[0][i] == matrix[2][i] and matrix[0][i] != -1) 
				return true;
		}

		//Checks if the diagonal is filled with the same input.
		if(matrix[0][0] == matrix[1][1] and matrix[1][1] == matrix[2][2] and matrix[1][1] != -1)
			return true;
			
		if(matrix[0][2] == matrix[1][1] and matrix[1][1]== matrix[2][0] and matrix[1][1] != -1)
			return true;

		//Tells that winner cannot be declared for now.
		return false;
	}

	//Identifies if the move is valid and makes the required changes.
	bool makeChanges(int input, int row, int column)
	{
		if(matrix[row][column] != -1)
			return false;
		else
		{
			matrix[row][column] = input;
			return true;
		}
	}

public:
	//Sets the values of each space to -1 which later helps in identifying if the space is being filled for the first time.
	TicTacToe()
	{
		for(int i = 0; i<3; i++)
			for(int j = 0; j<3; j++)
				matrix[i][j] = -1;
	}

public:
	//Checks if the TicTacToe is full.
	static bool isFull();
	//Prints TicTacToe.
	static void printMatrix();
};

//Player1 class. Controls the moves of the player1.
class PlayerOne : public TicTacToe
{

public:
	//Gets input form the player1.
	bool getInput()
	{
		int row, column;
		std::cout<<"Enter the position where you want to play your turn....";
		std::cin>>row>>column;
		bool success = makeChanges(0, row, column);
		return success;
	}

	//Checks if the player1 has won the game.
	bool getResult()
	{
		bool result = check();
		return result;
	}
};

//Player1 class. Controls the moves of the player2.
class PlayerTwo : public TicTacToe
{
public:
	//Gets input form the player2.
	bool getInput()
	{
		int row, column;
		std::cout<<"Enter the position where you want to play your turn....";
		std::cin>>row>>column;
		bool success = makeChanges(1, row, column);
		return success;
	}

	//Checks if the player2 has won the game.
	bool getResult()
	{
		bool result = check();
		return result;
	}

};

//Forward declaration of the class variables.
int TicTacToe::matrix[3][3];

bool TicTacToe::isFull()
{
	bool value = 1;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(TicTacToe::matrix[i][j] == -1)
				value = 0;
			if(value == 0) break;
		}
		if(value == 0) break;
	}
	return value;
}

void TicTacToe::printMatrix()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
			std::cout<<matrix[i][j]<<" ";
		std::cout<<"\n";
	}
}

int main()
{
	PlayerOne player1;
	PlayerTwo player2;

	PlayerTurn::PlayerTurn turn_to_play = PlayerTurn::PLAYER1; //First turn will be played by player1.
	Result::Result winner = Result::DRAW;	

	while(true)
	{
		if(turn_to_play == PlayerTurn::PLAYER1)
		{
			while(true)
			{
				bool success = player1.getInput();
				if(success == 0)
				{
					std::cout<<"Invalid play!! The place is already filled. Play again\n";
					continue;
				}
				else
					break;
			}
			bool result = player1.getResult();
			if(result)
			{
				winner = Result::PLAYER1;
				break;
			}
			else if(TicTacToe::isFull())
			{
				winner = Result::DRAW;
				break;
			}
			turn_to_play = PlayerTurn::PLAYER2; //So that next turn is played by palyer2 and not by player1 again.
		}
		else
		{
			while(true)
			{
				bool success = player2.getInput();
				if(success == 0)
				{
					std::cout<<"Invalid play!! The place is already filled. Play again\n";
					continue;
				}
				else
					break;
			}
			bool result = player2.getResult();
			if(result)
			{
				winner = Result::PLAYER2;
				break;
			}
			else if(TicTacToe::isFull())
			{
				winner = Result::DRAW;
				break;
			}
			turn_to_play = PlayerTurn::PLAYER1; //So that next turn is played by palyer1 and not by player2 again.
		}
		TicTacToe::printMatrix();
	}
	
	if(winner == Result::PLAYER1) std::cout<<"Player1 wins";
	else if(winner == Result::PLAYER2) std::cout<<"Player2 wins";
	else std::cout<<"Game was Drawn\n";
	
	return 0;
}

//Shorten the main function.
//Try to use more advanced class concepts.