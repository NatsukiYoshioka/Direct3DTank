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
	TitleScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos);

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

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//タイトルUI
	vector<Vector2> m_titleUIPos;									   //タイトルUI座標

	bool isFinish;			//シーンが終了したかどうか
};

