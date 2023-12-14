#pragma once
#include<iostream>
#include"Object.h"

class Listner
{
public:
	Listner();

	virtual void action(Object* obj);
};

class NextScene : public Listner
{
	void action(Object* obj);
};