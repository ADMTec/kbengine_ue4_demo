#include "Combat.h"
#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "kbe_scripts/LogicEvents.h"

Combat::Combat(Entity* entity) :
	self(entity)
{
}

Combat::~Combat()
{
}

void Combat::set_HP(int32 old)
{
	UKBEventData_set_HP* pEventData = NewObject<UKBEventData_set_HP>();
	pEventData->HP = HP;
	pEventData->entityID = self->id();
	KBENGINE_EVENT_FIRE("set_HP", pEventData);
}

void Combat::set_HP_Max(int32 old)
{
	UKBEventData_set_HP_Max* pEventData = NewObject<UKBEventData_set_HP_Max>();
	pEventData->HP_Max = HP_Max;
	pEventData->entityID = self->id();
	KBENGINE_EVENT_FIRE("set_HP_Max", pEventData);
}

void Combat::set_MP(int32 old)
{
	UKBEventData_set_MP* pEventData = NewObject<UKBEventData_set_MP>();
	pEventData->MP = MP;
	pEventData->entityID = self->id();
	KBENGINE_EVENT_FIRE("set_MP", pEventData);
}

void Combat::set_MP_Max(int32 old)
{
	UKBEventData_MP_Max* pEventData = NewObject<UKBEventData_MP_Max>();
	pEventData->MP_Max = MP_Max;
	pEventData->entityID = self->id();
	KBENGINE_EVENT_FIRE("set_MP_Max", pEventData);
}

void Combat::recvDamage(int32 attackerID, int32 skillID, int32 damageType, int32 damage)
{
	UKBEventData_recvDamage* pEventData = NewObject<UKBEventData_recvDamage>();
	pEventData->attackerID = attackerID;
	pEventData->skillID = skillID;
	pEventData->damageType = damageType;
	pEventData->damage = damage;
	pEventData->entityID = self->id();
	KBENGINE_EVENT_FIRE("recvDamage", pEventData);
}