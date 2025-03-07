#pragma once

#define MAXLEVEL 10



class GameEntity;
class Cell;

class Node
{
public:
	Cell* cell;
	GameEntity* object;
	Node* previous;
	Node* next;

	bool remove();
};

class Cell
{
private:
	Node* latest;

public:

	bool push(Node* object);
	void onRemove(Node* node);
	Node* getFirstObject();
};

class Tree
{
private:

	static Tree* instance;

	float left, top, width, height, splitW, splitH;
	int level;

	unsigned long totalSpaceCount;
	std::vector<int> spaceNumbers;
	std::vector<Cell*> cells;

	void init(int level, float left, float top, float right, float bottom);

	unsigned long BitSeparate32(unsigned long n);
	unsigned long Get2DMortonNumber(unsigned long x, unsigned long y);
	unsigned long GetPointElem(float pos_x, float pos_y);
	unsigned long getMortonNumber(float left, float top, float right, float bottom);

public:

	static Tree* GetInstance()
	{
		if (!instance)
		{
			instance = new Tree(50,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
		}

		return instance;
	}

	Tree(int level, float left, float top, float right, float bottom);

	void regist(CollisionBox& box, GameEntity* node);
	void createNewCell(unsigned long mortonNum);
	void getAllCollisionList();
	void getCollisionList(unsigned long mortonNumber,
		std::vector<GameEntity*>& collisionVec, std::vector<GameEntity*>& collisionStac);

};