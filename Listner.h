#pragma once
#include<iostream>
#include"Object.h"

class Listner
{
public:
	Listner();

	virtual void action();
};

class NextScene : public Listner
{
	void action();
};