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
	void LoadData(ID3D11Device* deviceResources, ID3D11DeviceContext* context);

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

	/// <summary>
	/// D3DStateオブジェクトの取得
	/// </summary>
	/// <returns></returns>
	DirectX::CommonStates* GetStates() { return m_states.get(); }

	/// <summary>
	/// 戦車の別のテクスチャを取得
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetTankTexture() { return m_tankTexture; }

	/// <summary>
	/// 戦車のエンジンの別のテクスチャを取得
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetEngineTexture() { return m_engineTexture; }

	/// <summary>
	/// デフォルトフォント取得
	/// </summary>
	/// <returns></returns>
	unique_ptr<DirectX::SpriteFont>&& GetDefaultFont() { return move(m_defaultFontHandle); }

	/// <summary>
	/// タイトルUIの取得
	/// </summary>
	/// <returns></returns>
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> GetTitleUI() { return m_titleUI; }

	/// <summary>
	/// タイトルUIの座標取得
	/// </summary>
	/// <returns></returns>
	vector<Vector2> GetTitleUIPos() { return m_titleUIPos; }

	/// <summary>
	/// タイトルUIのスケール取得
	/// </summary>
	/// <returns></returns>
	vector<float> GetTitleUIScale() { return m_titleUIScale; }

	/// <summary>
	/// メインゲームUIの取得
	/// </summary>
	/// <returns></returns>
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> GetMainGameUI() { return m_mainGameUI; }

	/// <summary>
	/// メインゲームUIの座標取得
	/// </summary>
	/// <returns></returns>
	vector<Vector2> GetMainGameUIPos() { return m_mainGameUIPos; }

	/// <summary>
	/// メインゲームUIのスケール取得
	/// </summary>
	/// <returns></returns>
	vector<float> GetMainGameUIScale() { return m_mainGameUIScale; }

private:
	static Load* m_load;				//ロードクラスのインスタンス

	static const string m_fileName;		//jsonファイル名
	json m_json;						//jsonファイルの情報を格納

	unique_ptr<DirectX::CommonStates> m_states;		//D3DStateオブジェクト
	unique_ptr<DirectX::IEffectFactory> m_fxFactory;//モデルロード用ヘルパーオブジェクト

	unique_ptr<DirectX::SpriteFont> m_defaultFontHandle;			//ゲーム内のデフォルトフォント

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//タイトルUI
	vector<Vector2> m_titleUIPos;									   //タイトルUI座標
	vector<float> m_titleUIScale;									   //タイトルUIスケール

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_mainGameUI;	//メインゲームUI
	vector<Vector2> m_mainGameUIPos;										//メインゲームUI座標
	vector<float> m_mainGameUIScale;										//メインゲームUIスケール

	static constexpr int m_xIndex = 0;
	static constexpr int m_yIndex = 1;

	vector<unique_ptr<DirectX::Model>> m_tankModelHandle;	//戦車のモデルハンドル配列
	vector<Vector3> m_tankPos;								//戦車の座標配列
	ID3D11ShaderResourceView* m_tankTexture;				//戦車の別のテクスチャ
	ID3D11ShaderResourceView* m_engineTexture;				//戦車の別のエンジンテクスチャ

	vector<unique_ptr<DirectX::Model>> m_bulletModelHandle;			//弾のモデルハンドル

	vector<unique_ptr<DirectX::Model>> m_blockModelHandle;	//マップ用ブロックモデルの配列
	vector<vector<int>> m_map;						//マップチップ

	vector<unique_ptr<DirectX::Model>> m_groundBlockModelHandle;	//ブロックモデルハンドル配列
	int m_blockUnderWoods;							//木ブロックの下にあるブロックの数

	vector<unique_ptr<DirectX::Model>> m_woodParticleModelHandle;	//木ブロックの破壊エフェクト用パーティクルモデル
	static constexpr int m_maxWoodParticleNum = 60;					//パーティクルの最大数

	static constexpr int m_maxBulletNum = 6;						//弾の最大数
};

