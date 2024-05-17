#include "pch.h"
#include"Tank.h"
#include"Bullet.h"
#include"BulletManager.h"
#include"Block.h"
#include"BlockManager.h"
#include"SceneManager.h"
#include"common.h"
#include "TankManager.h"

const Vector3 TankManager::m_initTitleTankPos[] = { Vector3(2.5f,0.5f,11.5f),Vector3(6.5f,0.5f,12.f) };
const Vector3 TankManager::m_initResultTankPos[] = { Vector3(3.f,0.5f,11.5f),Vector3(6.f,0.5f,11.f) };

//全タンクの初期化
TankManager::TankManager(vector<unique_ptr<DirectX::Model>>&& tankModelHandle, vector<Vector3> pos, DirectX::GamePad* gamePad) :
    m_gamePad(gamePad)
{
    float playerAngle[playerNum];
    playerAngle[player1] = atan2f(pos.at(player1).z - pos.at(player2).z, pos.at(player1).x - pos.at(player2).x);
    playerAngle[player2] = atan2f(pos.at(player2).z - pos.at(player1).z, pos.at(player2).x - pos.at(player1).x);
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank.push_back(new Tank(move(tankModelHandle.at(i)), pos.at(i), playerAngle[i]));
    }
    InitTitle();
}

//インスタンス破棄
TankManager::~TankManager()
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        delete(m_tank[i]);
    }
}

void TankManager::InitTitle()
{
    float playerAngle[playerNum];
    playerAngle[player2] = atan2f(m_initTitleTankPos[player1].x - m_initTitleTankPos[player2].x, m_initTitleTankPos[player1].z - m_initTitleTankPos[player2].z);
    playerAngle[player1] = atan2f(m_initTitleTankPos[player2].x - m_initTitleTankPos[player1].x, m_initTitleTankPos[player2].z - m_initTitleTankPos[player1].z);
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank[i]->InitTitle(m_initTitleTankPos[i], playerAngle[i]);
    }
}

void TankManager::InitMainGame()
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank[i]->InitMainGame();
    }
}

void TankManager::InitResult()
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        if (m_tank[i]->GetIsBreak())
        {
            m_tank[i]->InitResult(m_initResultTankPos[0]);
        }
        else
        {
            m_tank[i]->InitResult(m_initResultTankPos[1]);
        }
    }
}

//全タンクの更新
void TankManager::Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager, BulletManager* bulletManager, SceneManager::SCENE sceneState)
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank[i]->Update(world, m_gamePad->GetState(i), sceneState);
    }

    m_tank[player1]->CheckHitBlockTank(m_tank[player2]->GetModelMesh().at(initializeNum)->boundingBox, m_tank[player2]->GetPos());
    m_tank[player2]->CheckHitBlockTank(m_tank[player1]->GetModelMesh().at(initializeNum)->boundingBox, m_tank[player1]->GetPos());
    
    for (int i = initializeNum; i < playerNum; i++)
    {
        for (int j = initializeNum; j < blockManager->GetBlocks().size(); j++)
        {
            //タンク関連とブロックとの当たり判定
            if (blockManager->GetBlocks().at(j)->GetBlockType() != BlockManager::BlockType::YELLOW)
            {
                m_tank[i]->CheckHitBlockTank(blockManager->GetBlocks().at(j)->GetModelMesh().at(initializeNum)->boundingBox, blockManager->GetBlocks().at(j)->GetPos());
            }
        }
    }
    for (int i = initializeNum; i < playerNum; i++)
    {
        for (int j = initializeNum; j < playerNum; j++)
        {
            for (int l = initializeNum; l < bulletManager->GetBullets()[j].size(); l++)
            {
                if (m_tank[i]->CheckHitBullet(bulletManager->GetBullets()[j].at(l)->GetBulletModelHandle()->meshes.at(initializeNum)->boundingBox, bulletManager->GetBullets()[j].at(l)->GetPos()))
                {
                    bulletManager->GetBullets()[j].erase(bulletManager->GetBullets()[j].begin() + l);
                }
            }
        }
    }
}

//全タンクの描画
void TankManager::Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) const
{
    m_tank[player1]->Draw(context, move(states), view, projection);
    m_tank[player2]->DrawFromTexture(context, move(states), view, projection);
}