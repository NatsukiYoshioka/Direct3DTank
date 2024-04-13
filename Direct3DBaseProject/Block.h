#pragma once
#include"Model.h"
#include"BlockManager.h"
#include"common.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Block
{
public:

    Block(unique_ptr<DirectX::Model>&& blockModelHandle, Vector3 pos, BlockManager::BlockType blockType);
    ~Block();

    void Update();
    void Draw();

private:
    unique_ptr<DirectX::Model> m_blockModelHandle;
    BlockManager::BlockType m_blockType;
    Vector3 m_pos;
    bool m_destroy;
};

