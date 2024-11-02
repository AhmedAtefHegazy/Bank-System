#include "CLoginScreen.h"

int main()
{
	while (true)
	{
		if (!CLoginScreen::ShowLoginScreen())
			break;
	}

	system("pause>0");

	return 0;
}