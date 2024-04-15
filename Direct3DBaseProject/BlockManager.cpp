#include "pch.h"
#include"Block.h"
#include "BlockManager.h"

BlockManager::BlockManager(vector<unique_ptr<DirectX::Model>>&& blockModelHandle, vector<vector<int>> map)
{
    m_map.assign(mapSize, vector<int>(mapSize, initializeNum));
    for (int i = initializeNum; i < mapSize; i++)
    {
        for (int j = initializeNum; j < mapSize; j++)
        {
            m_map[i][j] = map[i][j];
            switch (m_map[i][j])
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