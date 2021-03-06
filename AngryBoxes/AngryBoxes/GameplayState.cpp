#include "GameplayState.h"

void GamePlayState::runSimulation()
{
	if(isSimulationStage == true)
	{

		isInputStage = true;
	}

	if(GameInput->getReleaseBox() == true)
	{
		GameInput->setReleaseBox(false);
	}
}

void GamePlayState::runInput()
{
	if(isInputStage == true)
	{
		GameInput->getInput();
	}

	if(GameInput->getReleaseBox() == true)
	{
		isSimulationStage = true;
		releaseBox();
		isInputStage = false;
	}
}

//Sets states to default upon moving to GamePlayState
void GamePlayState::Start(InputManager* Input)
{
	GameInput = Input;
	isInputStage = true;
	isSimulationStage = false;
	isCurrentState = true;
}

void GamePlayState::End()
{
	isInputStage = false;
	isSimulationStage = false;
	isCurrentState = false;
}

//Launches box if appropriate
void GamePlayState::releaseBox()
{
	if(isInputStage == true)
	{
	
		float xLength = 0;
		float yLength = 0;
		float releaseAngle = 0;
		float releaseVelocity = 0;
		float xVelocity = 0;
		float yVelocity = 0;

		xLength = GameInput->getXDragStart() - GameInput->getXDragEnd();
		yLength = GameInput->getYDragStart() - GameInput->getXDragEnd();

		//Setting x Length to 1 to avoid division by 0
		if(xLength == 0)
		{
			xLength = 1;
		}

		releaseAngle = -atan(yLength/xLength);

		releaseVelocity =  sqrt(pow(xLength, 2) + pow(yLength, 2)) * VELOCITY_MOD;

		yVelocity = sin(releaseAngle) * releaseVelocity;
		xVelocity = cos(releaseAngle) * releaseVelocity;

		vector.x = xVelocity;
		vector.y = yVelocity;
	}

	//Pass bird to sim and start sim
	GameInput->setReleaseBox(false);
}