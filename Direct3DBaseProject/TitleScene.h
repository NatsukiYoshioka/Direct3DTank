#pragma once

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class BaseScene;

class TitleScene:public BaseScene
{
public:
	/// <summary>
	/// タイトルシーンの生成
	/// </summary>
	TitleScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale);

	/// <summary>
	/// タイトルシーンの破棄
	/// </summary>
	~TitleScene();

	/// <summary>
	/// タイトルシーンの更新
	/// </summary>
	/// <param name="">pad state</param>
	void Update(DirectX::GamePad::State);

	/// <summary>
	/// タイトルシーンの描画
	/// </summary>
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch);

	/// <summary>
	/// シーンが終了したかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	static const Vector2 m_titlePos;	//タイトルの座標
	static const Vector2 m_titleScale;	//タイトルのスケール
	static constexpr const wchar_t* m_title = L"vs TANK!";	//タイトル名

	static const Vector2 m_playPos;						//PLAYボタン座標
	static const Vector2 m_playScale;					//PLAYボタンのスケール
	static constexpr const wchar_t* m_play = L"PLAY";	//PLAY文字列

	static const Vector2 m_controlsPos;							//操作説明ボタン座標
	static const Vector2 m_controlsScale;						//操作説明ボタンのスケール
	static constexpr const wchar_t* m_controls = L"CONTROLS";	//CONTROLS文字列

	static constexpr float m_fixButtonY = 20.f;					//ボタンの文字列Y軸修正量

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//タイトルUI
	vector<Vector2> m_titleUIPos;									   //タイトルUI座標
	vector<float> m_titleUIScale;									   //タイトルUIスケール

	int m_nowSelect;									//選択しているindex
	static constexpr float m_timeSpeed = 2.f;			//時間の進むスピード
	static constexpr int m_leftIndex = 3;				//ボタン左
	static constexpr int m_rightIndex = 4;				//ボタン右
	static constexpr int m_descriptionUIIndex = 5;

	static constexpr float m_UIDepth = 0.f;
	static constexpr float m_stringDepth = 0.1f;
	static constexpr float m_descriptionUIDepth = 0.1f;

	bool isFinish;			//シーンが終了したかどうか
};

