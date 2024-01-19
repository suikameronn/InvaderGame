#include"Listner.h"

Listner::Listner()
{

}

void Listner::action()
{

}

void TitleToSelect::action()
{
	sceneNum = 1;
}

void SelectToTitle::action()
{
	sceneNum = 0;
}

void Test::action()
{
	cout << "ListnerTest" << endl;
}