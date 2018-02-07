#include "Gate.h"
#include "kbengine_ue4_demo.h"
#include "Entity.h"

/*
	ÿ��ʵ�嶼��Ҫ���Լ�ע�ᣬ��ʽΪ
	ENTITYDEF_CLASS_REGISTER(ʵ��ģ�������̳�ģ��1���̳�ģ��N��...)

	��ʵ����û�м̳��κ�def�е���ʱʹ�øú�, ������ʵ��: class Monster : public Entity
	ENTITYDEF_CLASS_NO_DEFPARENT_REGISTER
*/
ENTITYDEF_CLASS_REGISTER(Gate, GameObject, NPCObject)

Gate::Gate():
	GameObject(),
	NPCObject(this)
{
}

Gate::~Gate()
{
}
