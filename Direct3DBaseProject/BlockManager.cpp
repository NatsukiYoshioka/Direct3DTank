#include "pch.h"
#include"Block.h"
#include "BlockManager.h"

BlockManager::BlockManager(vector<unique_ptr<DirectX::Model>>&& blockModelHandle, vector<vector<int>> map)
{
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

BlockManager::~BlockManager()
{

}

void BlockManager::Init()
{

}

void BlockManager::Update(DirectX::SimpleMath::Matrix world)
{
    for (int i = initializeNum; i < m_blocks.size(); i++)
    {
        m_blocks.at(i)->Update(world);
    }
}

void BlockManager::Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    for (int i = initializeNum; i < m_blocks.size(); i++)
    {
        m_blocks.at(i)->Draw(context, move(states), view, projection);
    }
}