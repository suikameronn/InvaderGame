#pragma once
#include<iostream>
#include"Object.h"

extern int sceneNum;

class Listner
{
public:
	Listner();
	virtual void action();
};

class NextScene : public Listner
{
	void action() override;
};