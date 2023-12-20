#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>

#include"Object.h"
#include"Mouse.h"

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
	int sceneChanger();

	vector<Object*> drawList;

	vector<Object*> Button_checkList;
	vector<Object*> Player_checkList;
	vector<Object*> Enemy_checkList;

	/*Scene�N���X��œ����蔻����s������
	�@�}�E�X������ɂȂ���̂ƁA�G�����̃r�[���������蔻��̑ΏۂɂȂ���̂𕪂�����
	 �@����͎��Ƃł��ꂼ��̃��X�g�ɓ����B
	  �G�@�Ǝ����̂悤�ȓ����蔻����A�G���������ꂼ����Ƃŕʂ̃��X�g�ɓ����B
	  �����āA������������̏ꍇ�̋����͂��ꂼ��̃N���X���Q�Ƃ���
	  ���Ƃł���Ƃ�����AScene�N���X��ŁA�I�u�W�F�N�g�����X�g�ɓ����֐������A���̊֐����ŁA�I�u�W�F�N�g�̃^�C�v�𔻒肵�āA
	  �����ŐU�蕪����*/

public:
	bool sceneChange;

	Scene();

	virtual void otherUpdate_virtual();

	void hitCheckScene(Mouse* mouse);
	void drawScene(SDL_Renderer* gRenderer);
};