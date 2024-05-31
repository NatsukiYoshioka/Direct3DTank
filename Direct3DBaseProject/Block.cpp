#include "pch.h"
#include"common.h"
#include "Block.h"

//�u���b�N�̐���
Block::Block(unique_ptr<DirectX::Model>&& blockModelHandle, Vector3 pos, BlockManager::BlockType blockType):
    m_blockType(blockType),
    m_blockModelHandle(move(blockModelHandle)),
    m_local(),
    m_pos(pos),
    m_endurance(m_maxEndurance),
    m_isDestroy(false)
{
    
}

//�f�[�^���
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

//�u���b�N�̍X�V
void Block::Update(DirectX::SimpleMath::Matrix world)
{
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(world, m_local);

    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center.x = m_pos.x;
    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center.y = m_pos.y;
    m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center.z = m_pos.z;
}

//�u���b�N�̕`��
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