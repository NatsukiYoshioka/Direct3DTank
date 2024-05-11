#pragma once
#include <sstream>
#include<string>
#include<vector>
#include "DeviceResources.h"
#include"CommonStates.h"
#include"Effects.h"
#include"Model.h"
#include"json.hpp"

using json = nlohmann::json;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// 外部データロードクラス
/// </summary>
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
	void LoadData(ID3D11Device* deviceResources);

	/// <summary>
	/// タンクモデルハンドル配列を取得
	/// </summary>
	/// <returns>タンクモデルハンドル配列</returns>
	vector<unique_ptr<DirectX::Model>>&& GetTankModelHandle() { return move(m_tankModelHandle); }

	/// <summary>
	/// タンク座標配列を取得
	/// </summary>
	/// <returns>タンク座標配列</returns>
	vector<Vector3> GetTankPos() { return m_tankPos; }

	/// <summary>
	/// ブロックモデルハンドル配列を取得
	/// </summary>
	/// <returns>ブロックモデルハンドル配列</returns>
	vector<unique_ptr<DirectX::Model>>&& GetBlockModelHandle() { return move(m_blockModelHandle); }

	/// <summary>
	/// 木ブロックの下の地面ブロックを取得
	/// </summary>
	/// <returns></returns>
	vector<unique_ptr<DirectX::Model>>&& GetGroundBlockUnderWoodsModelHandle() { return move(m_groundBlockModelHandle); }

	/// <summary>
	/// マップ情報の取得
	/// </summary>
	/// <returns></returns>
	vector<vector<int>> GetMap() { return m_map; }

	/// <summary>
	/// 弾モデルの取得
	/// </summary>
	/// <returns></returns>
	vector<unique_ptr<DirectX::Model>>&& GetBulletModelHandle() { return move(m_bulletModelHandle); }

	/// <summary>
	/// 木片パーティクルモデルの取得
	/// </summary>
	/// <returns></returns>
	vector<unique_ptr<DirectX::Model>>&& GetWoodParticleModelHandle() { return move(m_woodParticleModelHandle); }

	unique_ptr<DirectX::CommonStates>&& GetStates() { return move(m_states); }

private:
	static Load* m_load;				//ロードクラスのインスタンス

	static const string m_fileName;		//jsonファイル名
	json m_json;						//jsonファイルの情報を格納

	unique_ptr<DirectX::CommonStates> m_states;
	unique_ptr<DirectX::IEffectFactory> m_fxFactory;

	vector<unique_ptr<DirectX::Model>> m_tankModelHandle;	//戦車のモデルハンドル配列
	vector<Vector3> m_tankPos;								//戦車の座標配列

	vector<unique_ptr<DirectX::Model>> m_bulletModelHandle;			//弾のモデルハンドル

	vector<unique_ptr<DirectX::Model>> m_blockModelHandle;	//マップ用ブロックモデルの配列
	vector<vector<int>> m_map;						//マップチップ

	vector<unique_ptr<DirectX::Model>> m_groundBlockModelHandle;	//ブロックモデルハンドル配列
	int m_blockUnderWoods;							//木ブロックの下にあるブロックの数

	vector<unique_ptr<DirectX::Model>> m_woodParticleModelHandle;
	static constexpr int m_maxWoodParticleNum = 60;

	static constexpr int m_maxBulletNum = 6;
};

