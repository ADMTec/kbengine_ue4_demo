#include "Account.h"
#include "kbengine_ue4_demo.h"
#include "Entity.h"
#include "KBEngine.h"
#include "LogicEvents.h"

/*
	ÿ��ʵ�嶼��Ҫ���Լ�ע�ᣬ��ʽΪ
	ENTITYDEF_CLASS_REGISTER(ʵ��ģ�������̳�ģ��1���̳�ģ��N��...)

	��ʵ����û�м̳��κ�def�е���ʱʹ�øú�, ������ʵ��: class Monster : public Entity
	ENTITYDEF_CLASS_NO_DEFPARENT_REGISTER
*/
ENTITYDEF_CLASS_REGISTER(Account, GameObject)


Account::Account():
	GameObject(),
	characters(),
	lastSelCharacter(0)
{
}

Account::~Account()
{
}

void Account::__init__()
{
	// ע���¼�
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("reqCreateAvatar", "reqCreateAvatar", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqCreateAvatar& data = static_cast<const UKBEventData_reqCreateAvatar&>(*pEventData);
		reqCreateAvatar(data.roleType, data.name);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("reqRemoveAvatar", "reqRemoveAvatar", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqRemoveAvatar& data = static_cast<const UKBEventData_reqRemoveAvatar&>(*pEventData);
		reqRemoveAvatar(data.avatarInfos.dbid);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("selectAvatarGame", "selectAvatarGame", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_selectAvatarGame& data = static_cast<const UKBEventData_selectAvatarGame&>(*pEventData);
		selectAvatarGame(data.avatarInfos.dbid);
	});

	// ������½�ɹ��¼�
	UKBEventData_onLoginSuccessfully* pEventData = NewObject<UKBEventData_onLoginSuccessfully>();
	pEventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	pEventData->entity_id = id();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", pEventData);

	// �����������ý�ɫ�б�
	baseCall(TEXT("reqAvatarList"));
}

void Account::onDestroy()
{
	// ע��ע��������¼�
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void Account::reqCreateAvatar(uint8 roleType, const FString& name)
{
	DEBUG_MSG("Account::reqCreateAvatar(): roleType=%d", roleType);
	baseCall("reqCreateAvatar", roleType, name);
}

void Account::reqRemoveAvatar(uint64 dbid)
{
	DEBUG_MSG("Account::reqRemoveAvatar(): dbid=%lld", dbid);
	baseCall("reqRemoveAvatarDBID", dbid);
}

void Account::selectAvatarGame(uint64 dbid)
{
	DEBUG_MSG("Account::selectAvatarGame(): name=%lld", dbid);
	baseCall("selectAvatarGame", dbid);
}

void Account::onReqAvatarList(const KB_FIXED_DICT& datas)
{
	UKBEventData_onReqAvatarList* pEventData = NewObject<UKBEventData_onReqAvatarList>();

	const KB_FIXED_DICT& fixed_dict_values = datas;
	KB_ARRAY values = fixed_dict_values[TEXT("values")];

	for (auto& characterInfoItem : values)
	{
		FAVATAR_INFOS event_avatar;

		const KB_FIXED_DICT& characterInfo_fixed_dict = characterInfoItem;
		AVATAR_INFOS infos;

		infos.name = characterInfo_fixed_dict[TEXT("name")].GetValue<FString>();
		infos.dbid = characterInfo_fixed_dict[TEXT("dbid")];
		infos.level = characterInfo_fixed_dict[TEXT("level")];
		infos.roleType = characterInfo_fixed_dict[TEXT("roleType")];

		const KB_FIXED_DICT& data_fixed_dict = characterInfo_fixed_dict[TEXT("data")];

		infos.data.param1 = data_fixed_dict[TEXT("param1")];
		infos.data.param2 = data_fixed_dict[TEXT("param2")].GetValue<TArray<uint8>>();

		characters.Add(infos.dbid, infos);

		// fill eventData
		event_avatar.set(infos.dbid, infos.name, infos.roleType, infos.level, (lastSelCharacter == infos.dbid));
		pEventData->avatars.Add(event_avatar);
	}

	KBENGINE_EVENT_FIRE("onReqAvatarList", pEventData);
}

void Account::onCreateAvatarResult(uint8 retcode, const KB_FIXED_DICT& info)
{
	UKBEventData_onCreateAvatarResult* pEventData = NewObject<UKBEventData_onCreateAvatarResult>();

	const KB_FIXED_DICT& characterInfo_fixed_dict = info;
	AVATAR_INFOS infos;

	infos.name = characterInfo_fixed_dict[TEXT("name")].GetValue<FString>();
	infos.dbid = characterInfo_fixed_dict[TEXT("dbid")];
	infos.level = characterInfo_fixed_dict[TEXT("level")];
	infos.roleType = characterInfo_fixed_dict[TEXT("roleType")];

	const KB_FIXED_DICT& data_fixed_dict = characterInfo_fixed_dict[TEXT("data")];

	infos.data.param1 = data_fixed_dict[TEXT("param1")];
	infos.data.param2 = data_fixed_dict[TEXT("param2")].GetValue<TArray<uint8>>();

	if(retcode == 0)
		characters.Add(infos.dbid, infos);

	// fill eventData
	pEventData->avatarInfos.set(infos.dbid, infos.name, infos.roleType, infos.level, (lastSelCharacter == infos.dbid));
	pEventData->errorCode = retcode;

	// Error codes given by Account::reqCreateAvatar on the server
	if (retcode > 0)
	{
		if (retcode == 3)
			pEventData->errorStr = TEXT("Limiting the number of characters!");
		else
			pEventData->errorStr = TEXT("Unknown error!");
	}

	KBENGINE_EVENT_FIRE("onCreateAvatarResult", pEventData);
}

void Account::onRemoveAvatar(uint64 dbid)
{
	DEBUG_MSG("Account::onRemoveAvatar(): dbid=%lld", dbid);

	AVATAR_INFOS* infosFind = characters.Find(dbid);

	if (!infosFind)
		return;

	// ui event
	UKBEventData_onRemoveAvatar* pEventData = NewObject<UKBEventData_onRemoveAvatar>();
	pEventData->avatarInfos.set(infosFind->dbid, infosFind->name, infosFind->roleType, infosFind->level, (lastSelCharacter == infosFind->dbid));
	KBENGINE_EVENT_FIRE("onRemoveAvatar", pEventData);

	characters.Remove(dbid);
}