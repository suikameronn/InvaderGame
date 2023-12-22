#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>

#include"Object.h"
#include"Mouse.h"
#include"Button.h"
//#include"Player.h"
//#include"Enemy.h"

using namespace std;

enum FONTS;

enum ObjType
{
	BUTTON,
	PLAYER,
	ENEMY
};

class Scene
{
protected:

	vector<Object*> drawList;

	vector<Object*> button_CheckList;
	vector<Object*> player_CheckList;
	vector<Object*> enemy_CheckList;

	void addObjectToScene(Text* text);
	void addObjectToScene(Button* button);

	/*Sceneクラス上で当たり判定を行いたい
	　マウスが判定になるものと、敵味方のビームが当たり判定の対象になるものを分けたい
	 　これは手作業でそれぞれのリストに入れる。
	  敵機と自分のような当たり判定も、敵味方をそれぞれ手作業で別のリストに入れる。
	  そして、当たった判定の場合の挙動はそれぞれのクラスを参照する
	  手作業でするところを、Sceneクラス上で、オブジェクトをリストに入れる関数を作り、その関数内で、オブジェクトのタイプを判定して、
	  自動で振り分ける*/

public:
	bool sceneChange;

	Scene();

	void hitCheckScene(Mouse* mouse);
	void drawScene(SDL_Renderer* gRenderer);
};