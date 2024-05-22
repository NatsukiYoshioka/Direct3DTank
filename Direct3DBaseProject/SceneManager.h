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
	SceneManager(DirectX::GamePad* gamePad, unique_ptr<DirectX::SpriteFont>&& defaultFontHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale);

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
	static void CreateInstance(DirectX::GamePad* gamePad, unique_ptr<DirectX::SpriteFont>&& defaultFontHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale);

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
	/// シーンの遷移処理
	/// </summary>
	/// <param name="sceneState"></param>
	void ChangeScene(SCENE sceneState);

	/// <summary>
	/// シーンの更新
	/// </summary>
	/// <param name="tankManager"></param>
	void Update(TankManager* tankManager);

	/// <summary>
	/// シーンの描画
	/// </summary>
	void Draw(DirectX::SpriteBatch* spriteBatch);

private:
	static SceneManager* m_sceneManager;				//シングルトンのインスタンス
	BaseScene* m_nowScene;								//シーンのインスタンス
	SCENE m_sceneState;									//シーンの状態

	DirectX::GamePad* m_gamePad;						//ゲームパッドヘルパーオブジェクト

	unique_ptr<DirectX::SpriteFont> m_defaultFontHandle;//デフォルトフォントハンドル

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//タイトルUI
	vector<Vector2> m_titleUIPos;									   //タイトルUI座標
	vector<float> m_titleUIScale;									   //タイトルUIスケール

	bool isChange;										//シーンが変わったかどうか
};

