#include "NPC.h"
#include "kbengine_ue4_demo.h"
#include "Entity.h"


/*
	ÿ��ʵ�嶼��Ҫ���Լ�ע�ᣬ��ʽΪ
	ENTITYDEF_CLASS_REGISTER(ʵ��ģ�������̳�ģ��1���̳�ģ��N��...)
*/
ENTITYDEF_CLASS_REGISTER(NPC, GameObject, NPCObject, Motion)

NPC::NPC():
	GameObject(),
	NPCObject(this),
	Motion(this)
{
}

NPC::~NPC()
{
}
