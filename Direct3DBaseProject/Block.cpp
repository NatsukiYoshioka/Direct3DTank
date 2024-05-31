#include "pch.h"
#include"common.h"
#include "Block.h"

//ブロックの生成
Block::Block(unique_ptr<DirectX::Model>&& blockModelHandle, Vector3 pos, BlockManager::BlockType blockType):
    m_blockType(blockType),
    m_blockModelHandle(move(blockModelHandle)),
    m_local(),
    m_pos(pos),
    m_endurance(m_maxEndurance),
    m_isDestroy(false)
{
    
}

//データ解放
Block::~Block()
{
    m_blockModelHandle.reset();
}

void Block::Init()
{
    m_isDestroy = false;
    m_endurance = m_maxEndurance;
    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents.x = m_extents;
    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents.y = m_extents;
    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents.z = m_extents;
}

//ブロックの更新
void Block::Update(DirectX::SimpleMath::Matrix world)
{
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(world, m_local);

    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center.x = m_pos.x;
    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center.y = m_pos.y;
    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center.z = m_pos.z;
}

//ブロックの描画
void Block::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    if (!m_isDestroy)
    {
        m_blockModelHandle->Draw(context, *states, m_local, view, projection);
    }
    
}

void Block::DecreaseEndurance()
{
    m_endurance--;
    if (m_endurance <= initializeNum)
    {
        m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents.x = static_cast<float>(initializeNum);
        m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents.y = static_cast<float>(initializeNum);
        m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents.z = static_cast<float>(initializeNum);
        m_isDestroy = true;
    }
}