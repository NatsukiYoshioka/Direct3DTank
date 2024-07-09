#include "pch.h"
#include"BaseScene.h"
#include"TitleScene.h"
#include"MainGameScene.h"
#include"ResultScene.h"
#include"Tank.h"
#include"TankManager.h"
#include"common.h"
#include "SceneManager.h"

SceneManager* SceneManager::m_sceneManager = nullptr;

//コンストラクタ
SceneManager::SceneManager(DirectX::GamePad* gamePad, unique_ptr<DirectX::SpriteFont>&& defaultFontHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mainGameUI, vector<Vector2> mainGameUIPos, vector<float> mainGameUIScale, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resultUI, vector<Vector2> resultUIPos, vector<float> resultUIScale):
	m_sceneState(SCENE::TITLE),
	m_defaultFontHandle(move(defaultFontHandle)),
	m_titleUI(titleUI),
	m_titleUIPos(titleUIPos),
	m_titleUIScale(titleUIScale),
	m_mainGameUI(mainGameUI),
	m_mainGameUIPos(mainGameUIPos),
	m_mainGameUIScale(mainGameUIScale),
	m_resultUI(resultUI),
	m_resultUIPos(resultUIPos),
	m_resultUIScale(resultUIScale),
	isChange(false)
{
	m_gamePad = gamePad;
	m_nowScene = new TitleScene(m_titleUI, m_titleUIPos, m_titleUIScale);
}

//デストラクタ
SceneManager::~SceneManager()
{
	m_defaultFontHandle.reset();
	for (int i = initializeNum; i < m_titleUI.size(); i++)
	{
		m_titleUI.at(i).Reset();
	}
}

//インスタンス生成
void SceneManager::CreateInstance(DirectX::GamePad* gamePad, unique_ptr<DirectX::SpriteFont>&& defaultFontHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mainGameUI, vector<Vector2> mainGameUIPos, vector<float> mainGameUIScale, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resultUI, vector<Vector2> resultUIPos, vector<float> resultUIScale)
{
	if (!m_sceneManager)
	{
		m_sceneManager = new SceneManager(gamePad, move(defaultFontHandle), titleUI, titleUIPos, titleUIScale, mainGameUI, mainGameUIPos, mainGameUIScale, resultUI, resultUIPos, resultUIScale);
	}
}

//インスタンス破棄
void SceneManager::DestroyInstance()
{
	if (m_sceneManager)
	{
		delete(m_sceneManager);
	}
}

//シーン遷移処理
void SceneManager::ChangeScene(SCENE sceneState)
{
	if (m_nowScene != NULL)
	{
		delete(m_nowScene);
	}

	m_sceneState = sceneState;

	switch (m_sceneState)
	{
	case SCENE::TITLE:
		m_nowScene = new TitleScene(m_titleUI, m_titleUIPos, m_titleUIScale);
		break;
	case SCENE::MAINGAME:
		m_nowScene = new MainGameScene(m_mainGameUI, m_mainGameUIPos, m_mainGameUIScale);
		break;
	case SCENE::RESULT:
		m_nowScene = new ResultScene(m_resultUI, m_resultUIPos, m_resultUIScale);
		break;
	}
}

//シーンの更新
void SceneManager::Update(TankManager* tankManager, bool isFinishFadeout, bool isFinishFadein, float elapsedTime)
{
	m_nowScene->Update(m_gamePad->GetState(player1), tankManager, elapsedTime);
	if (m_nowScene->GetIsFinish() || (m_sceneState == SCENE::MAINGAME && (tankManager->GetTanks().at(player1)->GetIsBreak() || tankManager->GetTanks().at(player2)->GetIsBreak())))
	{
		isChange = true;
		if (isFinishFadeout)
		{
			switch (m_sceneState)
			{
			case SCENE::TITLE:
				ChangeScene(SCENE::MAINGAME);
				break;
			case SCENE::MAINGAME:
				ChangeScene(SCENE::RESULT);
				break;
			case SCENE::RESULT:
				ChangeScene(SCENE::TITLE);
				break;
			}
		}
	}
	else
	{
		isChange = false;
	}
}

//シーンの描画
void SceneManager::Draw(DirectX::SpriteBatch* spriteBatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources)
{
	if (m_sceneState == SCENE::MAINGAME)
	{
		m_nowScene->Draw(m_defaultFontHandle.get(), spriteBatch, context, states, view, projection, primitiveBatch, basicEffect, inputLayout, deviceResources);
	}
	else
	{
		m_nowScene->Draw(m_defaultFontHandle.get(), spriteBatch);
	}
}