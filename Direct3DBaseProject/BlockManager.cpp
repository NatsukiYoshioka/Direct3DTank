#include "pch.h"
#include"Block.h"
#include "BlockManager.h"

BlockManager::BlockManager(vector<unique_ptr<DirectX::Model>>&& blockModelHandle, vector<vector<int>> mapchip)
{
    for (int i = initializeNum; i < mapSize; i++)
    {
        for (int j = initializeNum; j < mapSize; j++)
        {
            m_mapchip[i][j] = mapchip[i][j];
            switch (m_mapchip[i][j])
            {
            case static_cast<int>(BlockType::YELLOW):
                m_blocks.push_back(new Block(move(blockModelHandle.at(static_cast<int>(BlockType::YELLOW))), Vector3(j * blockSize, static_cast<float>(initializeNum), i * blockSize), BlockType::YELLOW));
                break;
            case static_cast<int>(BlockType::WOOD):
                m_blocks.push_back(new Block(move(blockModelHandle.at(static_cast<int>(BlockType::WOOD))), Vector3(j * blockSize, blockSize, i * blockSize), BlockType::WOOD));
                break;
            case static_cast<int>(BlockType::RED):
                m_blocks.push_back(new Block(move(blockModelHandle.at(static_cast<int>(BlockType::RED))), Vector3(j * blockSize, blockSize, i * blockSize), BlockType::RED));
                break;
            case static_cast<int>(BlockType::BLUE):
                m_blocks.push_back(new Block(move(blockModelHandle.at(static_cast<int>(BlockType::BLUE))), Vector3(j * blockSize, blockSize, i * blockSize), BlockType::BLUE));
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

void BlockManager::Update()
{

}

void BlockManager::Draw()
{

}