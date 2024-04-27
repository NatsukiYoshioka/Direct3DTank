#include "pch.h"
#include"common.h"
#include "Block.h"

Block::Block(unique_ptr<DirectX::Model>&& blockModelHandle, Vector3 pos, BlockManager::BlockType blockType):
    m_blockType(blockType),
    m_blockModelHandle(move(blockModelHandle)),
    m_local(),
    m_pos(pos),
    m_destroy(false)
{
    
}

Block::~Block()
{
    m_blockModelHandle.reset();
}

void Block::Update(DirectX::SimpleMath::Matrix world)
{
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(world, m_local);

    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center.x = m_pos.x;
    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center.y = m_pos.y;
    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center.z = m_pos.z;
}

void Block::Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    m_blockModelHandle->Draw(context, *states, m_local, view, projection);
}