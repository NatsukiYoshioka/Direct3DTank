#include "pch.h"
#include <fstream>
#include <string>
#include <sstream>
#include"common.h"
#include "Load.h"

Load* Load::m_load = nullptr;

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
void Load::ReadFile(string filePath, bool isHeader, bool isIndex)
{
	m_filePath = filePath;
	m_isHeader = isHeader;
	m_isIndex = isIndex;

	string buf;
	string commaBuf;

	//読み込むcsvファイルを開く
	ifstream file(m_filePath);

	//getline関数で1行ずつ読み込んでbufに格納
	for (int i = initializeNum; getline(file, buf); i++)
	{
		m_cell.push_back(vector<string>());

		//delim区切りごとにデータを読み込むためにistringstreamにする
		istringstream iStream(buf);

		for (int j = initializeNum; getline(iStream, commaBuf, m_delim); j++)
		{
			if (m_isHeader && m_isIndex)
			{
				if (i == initializeNum && j == initializeNum)continue;
				//ヘッダー情報の格納
				if (i == initializeNum && j != initializeNum)m_header.push_back(commaBuf);
				//インデックス情報の格納
				if (i != initializeNum && j == initializeNum)m_index.push_back(commaBuf);
				//要素の格納
				if (i != initializeNum && j != initializeNum)m_cell.at(i).push_back(commaBuf);
			}
			else if (m_isHeader)
			{
				//ヘッダー情報の格納
				if (i == initializeNum)m_header.push_back(commaBuf);
				//インデックス情報の格納
				if (i != initializeNum && j == initializeNum)m_index.push_back(string());
				//要素の格納
				if (i != initializeNum)m_cell.at(i).push_back(commaBuf);
			}
			else if (m_isIndex)
			{
				//ヘッダー情報の格納
				if (i == initializeNum && j != initializeNum)m_header.push_back(string());
				//インデックス情報の格納
				if (j == initializeNum)m_index.push_back(commaBuf);
				//要素の格納
				if (j != initializeNum)m_cell.at(i).push_back(commaBuf);
			}
			else
			{
				//ヘッダー情報の格納
				if (i == initializeNum)m_header.push_back(string());
				//インデックス情報の格納
				if (j == initializeNum)m_index.push_back(string());
				//要素の格納
				m_cell.at(i).push_back(commaBuf);
			}
		}
	}
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

		}
	}
}