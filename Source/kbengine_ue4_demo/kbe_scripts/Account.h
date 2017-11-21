// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"

#include "interfaces/GameObject.h"

/*
	��Ӧentity_defs/

	Ҫʵ��һ��KBE��Ӧ��ʵ����뾭�����¼���
	1: �ڷ�����entity_defs��entities.xml��ע��ʵ�岢ʵ��ʵ���def����
	2: �ڷ����������λ���磺assets/scriptsĿ¼��cell�� ȡ����ʵ��ӵ�иò��֣���base�� ȡ����ʵ��ӵ�иò��֣��ļ�����ʵ��ʵ��ķ���������py�ű�ģ��
	3: ��UE4�ͻ�����kbe_scripts�ļ�����ʵ��ʵ��Ŀͻ��˲��ֽű�ģ�飨����ͳһ��Ϊʵ��ű�����Ȼ��C++ʵ�֣���UE4ʵ��ʵ�����������¼���
		A����ʵ���ͷ�ļ��а��ո�ʽ����ENTITYDEF_DECLARE_ģ������ ���忴demo
		B����ʵ��CPP�ļ���ENTITYDEF_CLASS_REGISTER��ʵ��ע�ᣬ���忴demo
*/
class Account : public GameObject
{
public:
	Account();
	virtual ~Account();

public:
	virtual void __init__() override;
	virtual void onDestroy() override;

	void reqCreateAvatar(uint8 roleType, const FString& name);
	void reqRemoveAvatar(uint64 dbid);
	void selectAvatarGame(uint64 dbid);

	void onReqAvatarList(const KB_FIXED_DICT& datas);
	void onCreateAvatarResult(uint8 retcode, const KB_FIXED_DICT& info);
	void onRemoveAvatar(uint64 dbid);

	struct AVATAR_DATA
	{
		int8 param1;
		TArray<uint8> param2;
	};

	struct AVATAR_INFOS
	{
		uint64 dbid;
		FString name;
		uint8 roleType;
		uint16 level;
		AVATAR_DATA data;
	};

	TMap<uint64, AVATAR_INFOS> characters;

	// def�ж���Ŀͻ����漰����
	DBID lastSelCharacter;
};

/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/

#define ENTITYDEF_DECLARE_Account(PARENT_MODULE)	\
	ENTITYDEF_PROPERTY_REGISTER(PARENT_MODULE, lastSelCharacter)	\
	ENTITYDEF_METHOD_ARGS1_REGISTER(PARENT_MODULE, onReqAvatarList)	\
	ENTITYDEF_METHOD_ARGS1_REGISTER(PARENT_MODULE, onRemoveAvatar)	\
	ENTITYDEF_METHOD_ARGS2_REGISTER(PARENT_MODULE, onCreateAvatarResult)
