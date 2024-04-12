#include "pch.h"
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
#include"common.h"
#include"json.hpp"
#include "Load.h"

Load* Load::m_load = nullptr;
string m_filename = "data.json";

//コンストラクタ
Load::Load() :
	m_isHeader(false),
	m_isIndex(false)
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
}

//データのロード
void Load::LoadData(unique_ptr<DX::DeviceResources> deviceResources)
{
	auto device = deviceResources->GetD3DDevice();

	m_states = make_unique<DirectX::CommonStates>(device);

	m_fxFactory = make_unique<DirectX::EffectFactory>(device);

	for (int i = initializeNum; i < m_cell.size(); i++)
	{
		for (int j = initializeNum; j < m_cell.at(i).size(); j++)
		{
			if (m_header.at(j) == m_tankHeader && m_cell.at(i).at(j) != "")
			{
				size_t size = strlen(m_cell.at(i).at(j).c_str());
				const wchar_t* cell = new const wchar_t[size];
				m_tankModelHandle.push_back(Model::CreateFromSDKMESH(device, cell, *m_fxFactory, ModelLoader_CounterClockwise | ModelLoader_IncludeBones));
			}
			if (m_header.at(j) == m_blockHeader && m_cell.at(i).at(j) != "")
			{
				size_t size = strlen(m_cell.at(i).at(j).c_str());
				const wchar_t* cell = new const wchar_t[size];
				m_blockModelHandle.push_back(Model::CreateFromCMO(device, cell, *m_fxFactory));
			}
		}
	}
}