#include "pch.h"
#include"Tank.h"
#include"Block.h"
#include"BlockManager.h"
#include"common.h"
#include "TankManager.h"

//�S�^���N�̏�����
TankManager::TankManager(vector<unique_ptr<DirectX::Model>>&& tankModelHandle, unique_ptr<DirectX::Model>&& bulletModelHandle, vector<Vector3> pos) :
    m_gamePad(make_unique<GamePad>()),
    m_bulletModelHandle(move(bulletModelHandle))
{
    float playerAngle[playerNum];
    playerAngle[player1] = atan2f(pos.at(player1).z - pos.at(player2).z, pos.at(player1).x - pos.at(player2).x);
    playerAngle[player2] = atan2f(pos.at(player2).z - pos.at(player1).z, pos.at(player2).x - pos.at(player1).x);
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank[i] = new Tank(move(tankModelHandle.at(i)), m_bulletModelHandle.get(), pos.at(i), playerAngle[i]);
    }
}

//�C���X�^���X�j��
TankManager::~TankManager()
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        delete(m_tank[i]);
    }
}

//�S�^���N�̍X�V
void TankManager::Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager)
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank[i]->Update(world, m_gamePad->GetState(i));
    }
    //�^���N�֘A�ƃu���b�N�Ƃ̓����蔻��
    for (int i = initializeNum; i < playerNum; i++)
    {
        for (int j = initializeNum; j < blockManager->GetBlocks().size(); j++)
        {
            if (blockManager->GetBlocks().at(j)->GetBlockType() != BlockManager::BlockType::YELLOW)
            {
                m_tank[i]->CheckHitBlock(blockManager->GetBlocks().at(j)->GetModelMesh().at(initializeNum)->boundingBox, blockManager->GetBlocks().at(j)->GetPos());
            }
        }
    }
}

//�S�^���N�̕`��
void TankManager::Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) const
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank[i]->Draw(context, move(states), view, projection);
    }
}

//�R���g���[���[�̒��f����
void TankManager::SuspendGamePad()
{
    m_gamePad->Suspend();
}

//�R���g���[���[�̍ĊJ����
void TankManager::ResumeGamePad()
{
    m_gamePad->Resume();
}