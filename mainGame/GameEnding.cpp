#include "GameEnding.h"

GameEnding::GameEnding()
{

}

GameEnding::~GameEnding()
{
}

bool GameEnding::Ending(int score)
{
	system("mode con cols=100 lines=25 | title ���׼�Ŭ");
	bool isKeyInput = false;
	bool isRestartGame = false;

	system("cls");
	for (int i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("\n");
	for (int i = 0; i < 50; i++)
	{
		printf("��");
	}


	printf("\n\n\n");

	printf("���� %d \n", score);
	printf("������� ���ϸ� r, ���� ���Ḧ ���ϸ� q�� �Է��ϼ���.\n");

	printf("\n\n\n");

	for (int i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("\n");
	for (int i = 0; i < 50; i++)
	{
		printf("��");
	}


	while (isKeyInput == false)
	{
		if (_kbhit())
		{
			char ckey = _getch();
			if (ckey == 'r' || ckey == 'R')
			{
				isKeyInput = true;
				isRestartGame = true;
			}
			else if (ckey == 'q' || ckey == 'Q')
			{
				isKeyInput = true;
			}

		}
		else {}
		Sleep(1);
	}
	system("cls");
	Sleep(500);

	return isRestartGame;
}	
