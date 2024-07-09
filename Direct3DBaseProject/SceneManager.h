#pragma once

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class BaseScene;
class TankManager;

class SceneManager
{
private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="gamePad">DirectX::GamePad</param>
	SceneManager(DirectX::GamePad* gamePad, unique_ptr<DirectX::SpriteFont>&& defaultFontHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mainGameUI, vector<Vector2> mainGameUIPos, vector<float> mainGameUIScale, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resultUI, vector<Vector2> resultUIPos, vector<float> resultUIScale);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();
public:
	/// <summary>
	/// シーンの種類
	/// </summary>
	enum class SCENE
	{
		TITLE,
		MAINGAME,
		RESULT
	};

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <param name="gamePad">DIrectX::GamePad</param>
	static void CreateInstance(DirectX::GamePad* gamePad, unique_ptr<DirectX::SpriteFont>&& defaultFontHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mainGameUI, vector<Vector2> mainGameUIPos, vector<float> mainGameUIScale, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resultUI, vector<Vector2> resultUIPos, vector<float> resultUIScale);

	/// <summary>
	/// インスタンス破棄
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns></returns>
	static SceneManager* GetInstance() { return m_sceneManager; }

	/// <summary>
	/// シーンの状態取得
	/// </summary>
	/// <returns></returns>
	SCENE GetNowSceneState()const { return m_sceneState; }

	/// <summary>
	/// シーンが変わったかどうか取得
	/// </summary>
	/// <returns></returns>
	bool GetIsChange() { return isChange; }

	/// <summary>
	/// シーンのインスタンス取得
	/// </summary>
	/// <returns></returns>
	BaseScene* GetSceneInstance() { return m_nowScene; }

	/// <summary>
	/// シーンの遷移処理
	/// </summary>
	/// <param name="sceneState"></param>
	void ChangeScene(SCENE sceneState);

	/// <summary>
	/// シーンの更新
	/// </summary>
	/// <param name="tankManager"></param>
	void Update(TankManager* tankManager, bool isFinishFadeout, bool isFinishFadein, float elapsedTime);

	/// <summary>
	/// シーンの描画
	/// </summary>
	void Draw(DirectX::SpriteBatch* spriteBatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources);

private:
	static SceneManager* m_sceneManager;				//シングルトンのインスタンス
	BaseScene* m_nowScene;								//シーンのインスタンス
	SCENE m_sceneState;									//シーンの状態

	DirectX::GamePad* m_gamePad;						//ゲームパッドヘルパーオブジェクト

	unique_ptr<DirectX::SpriteFont> m_defaultFontHandle;//デフォルトフォントハンドル

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//タイトルUI
	vector<Vector2> m_titleUIPos;									   //タイトルUI座標
	vector<float> m_titleUIScale;									   //タイトルUIスケール

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_mainGameUI; //タイトルUI
	vector<Vector2> m_mainGameUIPos;									   //タイトルUI座標
	vector<float> m_mainGameUIScale;									   //タイトルUIスケール

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_resultUI;	//リザルトUI
	vector<Vector2> m_resultUIPos;											//リザルトUI座標
	vector<float> m_resultUIScale;											//リザルトUIスケール

	bool isChange;										//シーンが変わったかどうか
};

