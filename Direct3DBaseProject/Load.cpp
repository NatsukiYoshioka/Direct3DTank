#include "pch.h"
#include<locale>
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
#include"common.h"
#include"json.hpp"
#include "Load.h"

using json = nlohmann::json;

Load* Load::m_load = nullptr;
const string Load::m_fileName = "data.json";

//�R���X�g���N�^
Load::Load()
{
	
}

//�f�[�^�̉��
Load::~Load()
{

}

//�C���X�^���X����
void Load::CreateInstance()
{
	if (!m_load)
	{
		m_load = new Load();
	}
}

//�C���X�^���X�j��
void Load::DestroyInstance()
{
	if (m_load)
	{
		delete(m_load);
	}
}

//�t�@�C������f�[�^�擾
void Load::ReadFile()
{
	ifstream ifs(m_fileName.c_str());
	if (ifs.good())
	{
		ifs >> m_json;
	}
}

//�f�[�^�̃��[�h
void Load::LoadData(ID3D11Device* deviceResources)
{
	auto device = deviceResources;

	m_states = make_unique<DirectX::CommonStates>(device);

	m_fxFactory = make_unique<DirectX::EffectFactory>(device);

	//�v���C���[���f���̏������[�h
	string str = m_json["TankAPath"];
	m_tankModelHandle.push_back(Model::CreateFromSDKMESH(device, Widen(str).c_str(), *m_fxFactory, ModelLoader_CounterClockwise | ModelLoader_IncludeBones));
	m_tankPos.push_back({ m_json["TankAPosX"],m_json["TankAPosY"],m_json["TankAPosZ"] });

	str = m_json["TankBPath"];
	m_tankModelHandle.push_back(Model::CreateFromSDKMESH(device, Widen(str).c_str(), *m_fxFactory, ModelLoader_CounterClockwise | ModelLoader_IncludeBones));
	m_tankPos.push_back({ m_json["TankBPosX"],m_json["TankBPosY"],m_json["TankBPosZ"] });
	
	//�}�b�v�`�b�v�̃��[�h
	for (int i = initializeNum; i < m_json["Blocks"].size(); i++)
	{
		str = m_json["Blocks"].at(i);
		m_blockModelHandle.push_back(Model::CreateFromCMO(device, Widen(str).c_str(), *m_fxFactory));
	}

	//�}�b�v�`�b�v�̃��[�h
	m_map.assign(mapSize, vector<int>(mapSize, initializeNum));
	for (int i = initializeNum; i < mapSize; i++)
	{
		for (int j = initializeNum; j < mapSize; j++)
		{
			m_map.at(i).at(j) = m_json["Mapchip"][i].at(j);
		}
	}
}

//����������C�h������ɕϊ�
wstring Load::Widen(const string& str)
{
	wostringstream wstm;
	const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(wstm.getloc());
	for (size_t i = initializeNum; i < str.size(); ++i)
	{
		wstm << ctfacet.widen(str[i]);
	}
	return wstm.str();
}