// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KBECommon.h"

#include "interfaces/GameObject.h"
#include "interfaces/NPCObject.h"

/*
	��Ӧentity_defs/

	Ҫʵ��һ��KBE��Ӧ��ʵ����뾭�����¼���
	1: �ڷ�����entity_defs��entities.xml��ע��ʵ�岢ʵ��ʵ���def����
	2: �ڷ����������λ���磺assets/scriptsĿ¼��cell�� ȡ����ʵ��ӵ�иò��֣���base�� ȡ����ʵ��ӵ�иò��֣��ļ�����ʵ��ʵ��ķ���������py�ű�ģ��
	3: ��UE4�ͻ�����kbe_scripts�ļ�����ʵ��ʵ��Ŀͻ��˲��ֽű�ģ�飨����ͳһ��Ϊʵ��ű�����Ȼ��C++ʵ�֣���UE4ʵ��ʵ�����������¼���
		A����ʵ���ͷ�ļ��а��ո�ʽ����ENTITYDEF_DECLARE_ģ������ ���忴demo
		B����ʵ��CPP�ļ���ENTITYDEF_CLASS_REGISTER��ʵ��ע�ᣬ���忴demo
*/
class Gate : public GameObject, public NPCObject
{
public:
	Gate();
	virtual ~Gate();

public:
	// def�ж���Ŀͻ����漰����
};

/*
Declare all of the properties and methods of the KBE-Entity

Example:
	#define ENTITYDEF_DECLARE_[module name of Entity](PARENT_MODULE)	\
		ENTITYDEF_PROPERTY_*(PARENT_MODULE, xx_property)	\
		ENTITYDEF_METHOD_ARGS[0~20]_REGISTER(PARENT_MODULE, xx_method)
*/

#define ENTITYDEF_DECLARE_Gate(PARENT_MODULE)	