#pragma once
#include<string>
#include<vector>
#include "DeviceResources.h"
#include"CommonStates.h"
#include"Effects.h"
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Load
{
private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Load();

	/// <summary>
	/// 格納したデータの解放
	/// </summary>
	~Load();

public:
	/// <summary>
	/// インスタンスの生成
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// インスタンスの破棄
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>クラスのインスタンス</returns>
	static Load* GetInstance() { return m_load; }

	/// <summary>
	/// ファイルからデータのパスを取得
	/// </summary>
	/// <param name="filepath">csvファイルのパス</param>
	/// <param name="isHeader">ヘッダーがあるかどうか</param>
	/// <param name="isIndex">インデックスがあるかどうか</param>
	void ReadFile();

	/// <summary>
	/// データのロード
	/// </summary>
	/// <param name="deviceResources">ゲームデバイス</param>
	void LoadData(unique_ptr<DX::DeviceResources> deviceResources);

private:
	static Load* m_load;				//ロードクラスのインスタンス

	static const string m_fileName;
	string jsonStr;

	string m_filePath;					//ゲームに必要なデータのパスが入ったファイルのパス
	bool m_isHeader;						//ヘッダーがあるかどうか
	bool m_isIndex;						//インデックスがあるかどうか
	static constexpr char m_delim = ',';	//区切りの文字

	vector<string> m_header;				//ヘッダー名保管
	vector<string> m_index;				//インデックス名保管
	vector<vector<string>> m_cell;		//要素保管

	unique_ptr<DirectX::CommonStates> m_states;
	unique_ptr<DirectX::IEffectFactory> m_fxFactory;

	vector<unique_ptr<DirectX::Model>> m_tankModelHandle;
	vector<Vector3> m_tankPos;

	vector<unique_ptr<DirectX::Model>> m_blockModelHandle;
	static constexpr int m_mapSize = 48;
	char m_map[m_mapSize][m_mapSize];

	static constexpr const char* m_tankHeader = "TANK";
	static constexpr const char* m_blockHeader = "BLOCK";
};

