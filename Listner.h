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

class TitleToSelect : public Listner
{
	void action() override;
};

class SelectToTitle : public Listner
{
	void action() override;
};

class Test :public Listner
{
	void action() override;
};