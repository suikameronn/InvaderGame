#include"GameEntity.h"

#include"ObjectTree.h"

Tree* Tree::instance = nullptr;

bool Node::remove()
{
	if (!cell)//���łɏ������Ă��Ȃ������ꍇ
	{
		return false;
	}

	cell->onRemove(this);

	if (previous)
	{
		previous->next = next;
	}
	if (next)
	{
		next->previous = previous;
	}

	previous = nullptr;
	next = nullptr;

	cell = nullptr;

	return true;
}

bool Cell::push(Node* node)
{
	if (!node)
	{
		return false;
	}

	if (node->cell == this)
	{
		return false;
	}

	if (!latest)
	{
		latest = node;//��ԂɐV�K�o�^
	}
	else
	{
		//�X�^�b�N�@��ɐς�ł���
		node->next = latest;
		latest->previous = node;
		latest = node;
	}

	node->cell = this;

	return true;
}

void Cell::onRemove(Node* node)
{
	if (latest == node)
	{
		if (latest)
		{
			latest = node->next;
		}
	}
}

Node* Cell::getFirstObject()
{
	return latest;
}

Tree::Tree(int level, float left, float top, float right, float bottom)
{
	init(level, left, top, right, bottom);
}

void Tree::init(int level, float left, float top, float right, float bottom)
{
	if (level > MAXLEVEL + 1)
	{
		return;
	}

	spaceNumbers.resize(MAXLEVEL + 1);
	spaceNumbers[0] = 1;
	for (int i = 1; i < MAXLEVEL + 1; i++)
	{
		spaceNumbers[i] = spaceNumbers[i - 1] * 4;//�e�������x���̗̈�̐����L�^���Ă���
	}

	totalSpaceCount = (spaceNumbers[level + 1] - 1) / 3;//���䋉���̘a
	cells.resize(totalSpaceCount);

	this->left = left;
	this->top = top;
	this->width = right - left;
	this->height = bottom - top;
	this->splitW = width / (1 << level);//�����̋�ԕ���������̈�̒P�ʕ������߂�
	this->splitH = height / (1 << level);//�P�ʍ������߂�

	this->level = level;
}

void Tree::regist(CollisionBox& box, GameEntity* object)
{
	float left, top, bottom, right;
	box.getCollisionBoxCoords(left, top, bottom, right);

	unsigned long mortonNum = getMortonNumber(left,top,bottom,right);
	if (mortonNum < totalSpaceCount)
	{
		if(!cells[mortonNum])
		createNewCell(mortonNum);

		Node* node = new Node();
		node->object = object;

		cells[mortonNum]->push(node);
	}
}

void Tree::createNewCell(unsigned long mortonNum)
{
	while (!cells[mortonNum])
	{
		cells[mortonNum] = new Cell();

		mortonNum = (mortonNum - 1) >> 2;//���[�g���ԍ���4�Ŋ���e��Ԃɍs��
		if (mortonNum >= totalSpaceCount)
		{
			break;//���[�g�������̍ő�
		}
	}
}

// �r�b�g�𕪊�����
unsigned long Tree::BitSeparate32(unsigned long n)
{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	return (n | (n << 1)) & 0x55555555;
}

// 2D���[�g����Ԕԍ��Z�o�֐�
unsigned long Tree::Get2DMortonNumber(unsigned long x, unsigned long y)
{
	return (unsigned long)(BitSeparate32(x) | (BitSeparate32(y) << 1));
}

// ���W�����`4���ؗv�f�ԍ��ϊ��֐�
unsigned long Tree::GetPointElem(float pos_x, float pos_y)
{
	return Get2DMortonNumber((unsigned long)((pos_x - left) / splitW), (unsigned long)((pos_y - top) / splitH));
}


unsigned long Tree::getMortonNumber(float left,float top,float bottom,float right)
{
	// �ŏ����x���ɂ�����e���ʒu���Z�o
	unsigned long LT = GetPointElem(left, top);
	unsigned long RB = GetPointElem(right, bottom);

	// ��Ԕԍ��̔r���I�_���a����
	// �������x�����v�Z
	unsigned long Def = RB ^ LT;//�r���I�_���a���v�Z
	unsigned int HiLevel = 0;
	unsigned int i;
	for (i = 0; i < level; i++)
	{
		unsigned long Check = (Def >> (i * 2)) & 0x3;//0x3=0011 �E�[��r�b�g�̂ݎ擾
		if (Check != 0)
			HiLevel = i + 1;
	}

	//���`4���؂���v�Z�����e��Ԃ̃��x���Ƃ�
	unsigned long SpaceNum = RB >> (HiLevel * 2);
	unsigned long AddNum = (spaceNumbers[level - HiLevel] - 1) / 3;
	SpaceNum += AddNum;

	if (SpaceNum > totalSpaceCount)
		return 0xffffffff;

	return SpaceNum;
}

void Tree::getAllCollisionList()
{
	if (!cells[0])
	{
		return;
	}

	std::vector<GameEntity*> collisionVec;
	std::vector<GameEntity*> collisionStac;

	getCollisionList(0,collisionVec,collisionStac);

	for (int i = 0; i < collisionVec.size(); i += 2)
	{
		collisionVec[i]->hitCheck(collisionVec[i + 1]->getCollisionBox());
	}
}

void Tree::getCollisionList(unsigned long mortonNumber,
	std::vector<GameEntity*>& collisionVec, std::vector<GameEntity*>& collisionStac)
{
	Node* node = cells[mortonNumber]->getFirstObject();

	//�Z���ɓo�^���ꂽ�I�u�W�F�N�g�Ƃ��̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���������X�g�ɓo�^����
	while (node)
	{
		Node* next = node->next;
		while (next)
		{
			collisionVec.push_back(node->object);
			collisionVec.push_back(next->object);
			next = next->next;
		}

		for (auto itr = collisionStac.begin(); itr != collisionStac.end(); itr++)
		{
			collisionVec.push_back(node->object);
			collisionVec.push_back(*itr);
		}

		node = node->next;
	}

	bool childFrag = false;
	unsigned long objNum = 0;
	unsigned long nextElem;

	for (int i = 0; i < 4; i++)
	{
		nextElem = mortonNumber * 4 + 1 + i;
		if (nextElem < totalSpaceCount && cells[mortonNumber * 4 + 1 + i])
		{
			if (!childFrag)
			{
				node = cells[mortonNumber]->getFirstObject();
				while (node)
				{
					collisionStac.push_back(node->object);
					objNum++;
					node = node->next;
				}
			}

			childFrag = true;
			getCollisionList(mortonNumber * 4 + 1 + i,collisionVec,collisionStac);
		}
	}

	if (childFrag)
	{
		for (int i = 0; i < objNum; i++)
		{
			collisionStac.pop_back();
		}
	}
}