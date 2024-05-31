#include "pch.h"
#include<locale>
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
#include"common.h"
#include"json.hpp"
#include"BlockManager.h"
#include "Load.h"

using json = nlohmann::json;

Load* Load::m_load = nullptr;
const string Load::m_fileName = "data.json";

//�R���X�g���N�^
Load::Load():
	m_blockUnderWoods(initializeNum),
	m_tankTexture(nullptr),
	m_engineTexture(nullptr)
{
	
}

//�f�[�^�̉��
Load::~Load()
{
	m_states.reset();
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
void Load::LoadData(ID3D11Device* deviceResources, ID3D11DeviceContext* context)
{
	auto device = deviceResources;

	m_states = make_unique<DirectX::CommonStates>(device);

	m_fxFactory = make_unique<DirectX::EffectFactory>(device);
	

	//�v���C���[���f���̏������[�h
	string str = m_json["TankAPath"];
	m_tankModelHandle.push_back(Model::CreateFromSDKMESH(device, Widen(str).c_str(), *m_fxFactory, ModelLoader_CounterClockwise | ModelLoader_IncludeBones));
	m_tankPos.push_back({ m_json["TankAPosX"],m_json["TankAPosY"],m_json["TankAPosZ"] });

	str = m_json["TankBTexturePath1"];
	m_fxFactory->CreateTexture(Widen(str).c_str(), context, &m_tankTexture);
	str = m_json["TankBTexturePath2"];
	m_fxFactory->CreateTexture(Widen(str).c_str(), context, &m_engineTexture);
	str = m_json["TankBPath"];
	m_tankModelHandle.push_back(Model::CreateFromSDKMESH(device, Widen(str).c_str(), *m_fxFactory, ModelLoader_CounterClockwise | ModelLoader_IncludeBones));
	m_tankPos.push_back({ m_json["TankBPosX"],m_json["TankBPosY"],m_json["TankBPosZ"] });
	
	str = m_json["Bullet"];
	for (int i = initializeNum; i < m_maxBulletNum; i++)
	{
		m_bulletModelHandle.push_back(Model::CreateFromCMO(device, Widen(str).c_str(), *m_fxFactory));
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

	//�u���b�N�̃��[�h
	for (int i = initializeNum; i < mapSize; i++)
	{
		for (int j = initializeNum; j < mapSize; j++)
		{
			
			switch (m_map[i][j])
			{
			case static_cast<int>(BlockManager::BlockType::YELLOW):
				str = m_json["Blocks"].at(static_cast<int>(BlockManager::BlockType::YELLOW));
				break;
			case static_cast<int>(BlockManager::BlockType::WOOD):
				str = m_json["Blocks"].at(static_cast<int>(BlockManager::BlockType::WOOD));
				m_blockUnderWoods++;
				break;
			case static_cast<int>(BlockManager::BlockType::RED):
				str = m_json["Blocks"].at(static_cast<int>(BlockManager::BlockType::RED));
				break;
			case static_cast<int>(BlockManager::BlockType::BLUE):
				str = m_json["Blocks"].at(static_cast<int>(BlockManager::BlockType::BLUE));
				break;
			}
			m_blockModelHandle.push_back(Model::CreateFromCMO(device, Widen(str).c_str(), *m_fxFactory));
		}
	}

	//�؃u���b�N�̉��̒n�ʃu���b�N�̐������[�h
	str = m_json["Blocks"].at(static_cast<int>(BlockManager::BlockType::YELLOW));
	for (int i = initializeNum; i < m_blockUnderWoods; i++)
	{
		m_groundBlockModelHandle.push_back(Model::CreateFromCMO(device, Widen(str).c_str(), *m_fxFactory));
	}

	//�ؕЃp�[�e�B�N�����f���̃��[�h
	str = m_json["WoodParticle"];
	for (int i = initializeNum; i < m_maxWoodParticleNum; i++)
	{
		m_woodParticleModelHandle.push_back(Model::CreateFromCMO(device, Widen(str).c_str(), *m_fxFactory));
	}

	//�f�t�H���g�t�H���g�̃��[�h
	str = m_json["DefaultFont"];
	m_defaultFontHandle = make_unique<SpriteFont>(device, Widen(str).c_str());

	//�^�C�g��UI�̃��[�h
	m_titleUI.assign(m_json["TitleUI"].size(), nullptr);
	for (int i = initializeNum; i < m_titleUI.size(); i++)
	{
		str = m_json["TitleUI"].at(i);
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, Widen(str).c_str(), nullptr, m_titleUI.at(i).ReleaseAndGetAddressOf()));
		m_titleUIPos.push_back(Vector2(m_json["TitleUIPos"][i].at(m_xIndex), m_json["TitleUIPos"][i].at(m_yIndex)));
		m_titleUIScale.push_back(m_json["TitleUIScale"][i]);
	}

	//���C���Q�[��UI�̃��[�h
	m_mainGameUI.assign(m_json["MainGameUI"].size(), nullptr);
	for (int i = initializeNum; i < m_mainGameUI.size(); i++)
	{
		str = m_json["MainGameUI"].at(i);
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, Widen(str).c_str(), nullptr, m_mainGameUI.at(i).ReleaseAndGetAddressOf()));
		m_mainGameUIPos.push_back(Vector2(m_json["MainGameUIPos"][i].at(m_xIndex), m_json["MainGameUIPos"][i].at(m_yIndex)));
		m_mainGameUIScale.push_back(m_json["MainGameUIScale"][i]);
	}

	m_resultUI.assign(m_json["ResultUI"].size(), nullptr);
	for (int i = initializeNum; i < m_resultUI.size(); i++)
	{
		str = m_json["ResultUI"].at(i);
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, Widen(str).c_str(), nullptr, m_resultUI.at(i).ReleaseAndGetAddressOf()));
		m_resultUIPos.push_back(Vector2(m_json["ResultUIPos"][i].at(m_xIndex), m_json["ResultUIPos"][i].at(m_yIndex)));
		m_resultUIScale.push_back(m_json["ResultUIScale"][i]);
	}
}