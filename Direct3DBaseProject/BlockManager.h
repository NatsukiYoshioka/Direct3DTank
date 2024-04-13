#pragma once
#include<vector>
#include"Model.h"
#include"common.h"

using namespace DirectX;
using namespace std;

class Block;

class BlockManager
{
public:
    enum class BlockType
    {
        YELLOW,
        WOOD,
        RED,
        BLUE
    };

    BlockManager(vector<unique_ptr<DirectX::Model>>&& blockModelHandle, vector<vector<int>> mapchip);
    ~BlockManager();

    void Init();
    void Update();
    void Draw();
private:
    vector<Block*> m_blocks;
    int m_mapchip[mapSize][mapSize];        //マップチップ
};

