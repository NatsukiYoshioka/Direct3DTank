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

//コンストラクタ
Load::Load()
{
	
}

//データの解放
Load::~Load()
{

}

//インスタンス生成
void Load::CreateInstance()
{
	if (!m_load)
	{
		m_load = new Load();
	}
}

//インスタンス破棄
void Load::DestroyInstance()
{
	if (m_load)
	{
		delete(m_load);
	}
}

//ファイルからデータ取得
void Load::ReadFile()
{
	ifstream ifs(m_fileName.c_str());
	if (ifs.good())
	{
		ifs >> m_json;
	}
}

//データのロード
void Load::LoadData(ID3D11Device* deviceResources)
{
	auto device = deviceResources;

	m_states = make_unique<DirectX::CommonStates>(device);

	m_fxFactory = make_unique<DirectX::EffectFactory>(device);

	//プレイヤーモデルの情報をロード
	string str = m_json["TankAPath"];
	m_tankModelHandle.push_back(Model::CreateFromSDKMESH(device, Widen(str).c_str(), *m_fxFactory, ModelLoader_CounterClockwise | ModelLoader_IncludeBones));
	m_tankPos.push_back({ m_json["TankAPosX"],m_json["TankAPosY"],m_json["TankAPosZ"] });

	str = m_json["TankBPath"];
	m_tankModelHandle.push_back(Model::CreateFromSDKMESH(device, Widen(str).c_str(), *m_fxFactory, ModelLoader_CounterClockwise | ModelLoader_IncludeBones));
	m_tankPos.push_back({ m_json["TankBPosX"],m_json["TankBPosY"],m_json["TankBPosZ"] });
	
	//マップチップのロード
	str = m_json["YellowBlock"];
	m_blockModelHandle.push_back(Model::CreateFromCMO(device, Widen(str).c_str(), *m_fxFactory));

	str = m_json["WoodBlock"];
	m_blockModelHandle.push_back(Model::CreateFromCMO(device, Widen(str).c_str(), *m_fxFactory));

	str = m_json["RedBlock"];
	m_blockModelHandle.push_back(Model::CreateFromCMO(device, Widen(str).c_str(), *m_fxFactory));

	str = m_json["BlueBlock"];
	m_blockModelHandle.push_back(Model::CreateFromCMO(device, Widen(str).c_str(), *m_fxFactory));

	//マップチップのロード
	m_map.assign(mapSize, vector<int>(mapSize, initializeNum));
	for (int i = initializeNum; i < mapSize; i++)
	{
		for (int j = initializeNum; j < mapSize; j++)
		{
			switch (i)
			{
			case 0:
				m_map.at(i).at(j) = m_json["Mapchip0"][j];
				break;
			case 1:
				m_map.at(i).at(j) = m_json["Mapchip1"][j];
				break;
			case 2:
				m_map.at(i).at(j) = m_json["Mapchip2"][j];
				break;
			case 3:
				m_map.at(i).at(j) = m_json["Mapchip3"][j];
				break;
			case 4:
				m_map.at(i).at(j) = m_json["Mapchip4"][j];
				break;
			case 5:
				m_map.at(i).at(j) = m_json["Mapchip5"][j];
				break;
			case 6:
				m_map.at(i).at(j) = m_json["Mapchip6"][j];
				break;
			case 7:
				m_map.at(i).at(j) = m_json["Mapchip7"][j];
				break;
			case 8:
				m_map.at(i).at(j) = m_json["Mapchip8"][j];
				break;
			case 9:
				m_map.at(i).at(j) = m_json["Mapchip9"][j];
				break;
			case 10:
				m_map.at(i).at(j) = m_json["Mapchip10"][j];
				break;
			case 11:
				m_map.at(i).at(j) = m_json["Mapchip11"][j];
				break;
			case 12:
				m_map.at(i).at(j) = m_json["Mapchip12"][j];
				break;
			case 13:
				m_map.at(i).at(j) = m_json["Mapchip13"][j];
				break;
			case 14:
				m_map.at(i).at(j) = m_json["Mapchip14"][j];
				break;
			case 15:
				m_map.at(i).at(j) = m_json["Mapchip15"][j];
				break;
			}
		}
	}
}

//文字列をワイド文字列に変換
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