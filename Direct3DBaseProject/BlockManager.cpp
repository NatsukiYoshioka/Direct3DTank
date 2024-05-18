#include "pch.h"
#include"common.h"
#include"Block.h"
#include "BlockManager.h"

//�u���b�N�C���X�^���X�̐���
BlockManager::BlockManager(vector<unique_ptr<DirectX::Model>>&& blockModelHandle, vector<unique_ptr<DirectX::Model>>&& groundBlockUnderWoodsModelHandle, vector<vector<int>> map)
{
    int groundBlockUnderWoodsNum = 0;
    for (int i = initializeNum; i < mapSize; i++)
    {
        for (int j = initializeNum; j < mapSize; j++)
        {
            switch (map[i][j])
            {
            case static_cast<int>(BlockType::YELLOW):
                m_blocks.push_back(new Block(move(blockModelHandle.at(i * mapSize + j)), Vector3(j * blockSize, static_cast<float>(initializeNum), i * blockSize), BlockType::YELLOW));
                break;
            case static_cast<int>(BlockType::WOOD):
                m_blocks.push_back(new Block(move(blockModelHandle.at(i * mapSize + j)), Vector3(j * blockSize, blockSize, i * blockSize), BlockType::WOOD));
                m_blocks.push_back(new Block(move(groundBlockUnderWoodsModelHandle.at(groundBlockUnderWoodsNum)), Vector3(j * blockSize, static_cast<float>(initializeNum), i * blockSize), BlockType::YELLOW));
                groundBlockUnderWoodsNum++;
                break;
            case static_cast<int>(BlockType::RED):
                m_blocks.push_back(new Block(move(blockModelHandle.at(i * mapSize + j)), Vector3(j * blockSize, blockSize, i * blockSize), BlockType::RED));
                break;
            case static_cast<int>(BlockType::BLUE):
                m_blocks.push_back(new Block(move(blockModelHandle.at(i * mapSize + j)), Vector3(j * blockSize, blockSize, i * blockSize), BlockType::BLUE));
                break;
            }
        }
    }
}

//�S�u���b�N�̔j��
BlockManager::~BlockManager()
{
    if (m_blocks.size() > initializeNum)
    {
        for (int i = initializeNum; i < m_blocks.size(); i++)
        {
            delete(m_blocks.at(i));
        }
    }
}

//�X�e�[�W�̏�����
void BlockManager::Init()
{

}

//�S�u���b�N�̍X�V����
void BlockManager::Update(DirectX::SimpleMath::Matrix world)
{
    for (int i = initializeNum; i < m_blocks.size(); i++)
    {
        m_blocks.at(i)->Update(world);
    }
}

//�S�u���b�N�̕`��
void BlockManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    for (int i = initializeNum; i < m_blocks.size(); i++)
    {
        m_blocks.at(i)->Draw(context, states, view, projection);
    }
}