#pragma once
#include"Model.h"
#include"BlockManager.h"
#include"CommonStates.h"
#include"common.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Block
{
public:

    Block(unique_ptr<DirectX::Model>&& blockModelHandle, Vector3 pos, BlockManager::BlockType blockType);
    ~Block();

    void Update(DirectX::SimpleMath::Matrix world);
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    unique_ptr<DirectX::Model> m_blockModelHandle;
    BlockManager::BlockType m_blockType;
    XMMATRIX m_local;
    Vector3 m_pos;
    bool m_destroy;
};

