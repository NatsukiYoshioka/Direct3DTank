#include "pch.h"
#include"SceneManager.h"
#include"TankManager.h"
#include"Tank.h"
#include"BulletManager.h"
#include"Bullet.h"
#include"BlockManager.h"
#include"Block.h"
#include"common.h"
#include "SoundManager.h"

SoundManager::SoundManager(vector<string> soundfile, AudioEngine* audioEngine):
	m_isMoveStickLeft(false),
	m_isMoveStickRight(false)
{
	for (int i = initializeNum; i < soundfile.size(); i++)
	{
		m_sound.push_back(make_unique<SoundEffect>(audioEngine, Widen(soundfile.at(i)).c_str()));
		m_loopSound.push_back(m_sound.at(i)->CreateInstance());
	}
	Init();
}

SoundManager::~SoundManager()
{
	m_sound.clear();
	m_loopSound.clear();
}

void SoundManager::Init()
{
	m_isPlaySound.assign(m_sound.size(), false);
	m_fireSoundCount.assign(playerNum, initializeNum);
	m_isPlayBreakBlockSound.clear();
}

void SoundManager::Update(SceneManager* sceneManager, DirectX::GamePad::State padState, TankManager* tankManager, BulletManager* bulletManager, BlockManager* blockManager)
{
	for (int i = initializeNum; i < m_sound.size(); i++)
	{
		switch (i)
		{
			//決定サウンド
		case 0:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::TITLE && padState.IsAPressed() && !m_isPlaySound.at(i))
			{
				m_sound.at(i)->Play();
				m_isPlaySound.at(i) = true;
			}
			break;
			//選択サウンド
		case 1:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::TITLE && !m_isPlaySound.at(0))
			{
				if (padState.IsLeftThumbStickLeft() && !m_isMoveStickLeft)
				{
					m_sound.at(i)->Play();
					m_isMoveStickLeft = true;
					m_isMoveStickRight = false;
				}
				if (padState.IsLeftThumbStickRight() && !m_isMoveStickRight)
				{
					m_sound.at(i)->Play();
					m_isMoveStickLeft = false;
					m_isMoveStickRight = true;
				}
			}
			break;
			//説明書オープンサウンド
		case 2:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::TITLE && padState.IsAPressed() && !m_isPlaySound.at(i) && m_isMoveStickRight)
			{
				m_sound.at(i)->Play();
				m_isPlaySound.at(i) = true;
				m_isPlaySound.at(3) = false;
			}
			break;
			//説明書クローズサウンド
		case 3:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::TITLE && padState.IsBPressed() && !m_isPlaySound.at(i) && m_isMoveStickRight && m_isPlaySound.at(2))
			{
				m_sound.at(i)->Play();
				m_isPlaySound.at(i) = true;
				m_isPlaySound.at(0) = false;
				m_isPlaySound.at(2) = false;
			}
			break;
			//タイトルBGM
		case 4:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::TITLE && !m_isPlaySound.at(i))
			{
				m_loopSound.at(i)->SetVolume(m_BGMVolume);
				m_loopSound.at(i)->Play(true);
				m_isPlaySound.at(i) = true;
			}
			if (sceneManager->GetNowSceneState() != SceneManager::SCENE::TITLE)
			{
				m_loopSound.at(i)->Stop();
			}
			break;
			//戦車砲弾発射サウンド
		case 5:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::MAINGAME)
			{
				for (int j = initializeNum; j < tankManager->GetTanks().size(); j++)
				{
					if (bulletManager->GetBullets()[j].size() != m_fireSoundCount.at(j))
					{
						m_fireSoundCount.at(j) = bulletManager->GetBullets()[j].size();
						if (tankManager->GetTanks().at(j)->GetIsFire() && tankManager->GetTanks().at(j)->GetFireRecast() >= static_cast<float>(initializeNum))
						{
							m_sound.at(i)->Play();
						}
					}
				}
			}
			break;
			//砲弾ヒットサウンド
		case 6:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::MAINGAME)
			{
				for (int j = initializeNum; j < tankManager->GetTanks().size(); j++)
				{
					if (tankManager->GetTanks().at(j)->GetIsHitBullet())
					{
						m_sound.at(i)->Play();
					}
				}
			}
			break;
			//砲弾反射サウンド
		case 7:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::MAINGAME)
			{
				for (int j = initializeNum; j < playerNum; j++)
				{
					for (int l = initializeNum; l < bulletManager->GetBullets()[j].size(); l++)
					{
						if (bulletManager->GetBullets()[j].at(l)->GetIsHitBlock() && !bulletManager->GetBullets()[j].at(l)->GetIsBreak())
						{
							m_sound.at(i)->Play();
						}
					}
				}
			}
			break;
			//砲弾クラッシュサウンド
		case 8:
			for (int j = initializeNum; j < playerNum; j++)
			{
				for (int l = initializeNum; l < bulletManager->GetBullets()[j].size(); l++)
				{
					if (bulletManager->GetBullets()[j].at(l)->GetIsBreak())
					{
						m_sound.at(i)->Play();
					}
				}
			}
			break;
			//ブロック破壊サウンド
		case 9:
			for (int j = initializeNum; j < blockManager->GetBlocks().size(); j++)
			{
				if (m_isPlayBreakBlockSound.size() < blockManager->GetBlocks().size())
				{
					m_isPlayBreakBlockSound.push_back(false);
				}
				if (blockManager->GetBlocks().at(j)->GetBlockType() == BlockManager::BlockType::WOOD && blockManager->GetBlocks().at(j)->GetIsDestroy() && !m_isPlayBreakBlockSound.at(j))
				{
					m_sound.at(i)->Play();
					m_isPlayBreakBlockSound.at(j) = true;
				}
			}
			break;
		case 10:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::MAINGAME && !m_isPlaySound.at(i))
			{
				m_loopSound.at(i)->SetVolume(m_BGMVolume);
				m_loopSound.at(i)->Play(true);
				m_isPlaySound.at(i) = true;
			}
			if (sceneManager->GetNowSceneState() != SceneManager::SCENE::MAINGAME)
			{
				m_loopSound.at(i)->Stop();
			}
			break;
		case 11:
			if (sceneManager->GetNowSceneState() == SceneManager::SCENE::RESULT && !m_isPlaySound.at(i))
			{
				m_loopSound.at(i)->SetVolume(m_BGMVolume);
				m_loopSound.at(i)->Play(true);
				m_isPlaySound.at(i) = true;
			}
			if (sceneManager->GetNowSceneState() != SceneManager::SCENE::RESULT)
			{
				m_loopSound.at(i)->Stop();
			}
			break;
		}
	}
}