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
    m_box = BoundingBox(m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Center, m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents);
}

Block::~Block()
{
    m_blockModelHandle.reset();
}

void Block::Update(DirectX::SimpleMath::Matrix world)
{
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(world, m_local);
}

void Block::Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    m_shape = GeometricPrimitive::CreateBox(context, XMFLOAT3(m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents.x * extentsWidth, m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents.y * extentsWidth, m_blockModelHandle->meshes.at(initializeNum)->boundingBox.Extents.z * extentsWidth));
    m_shape->Draw(m_local, view, projection, Colors::White);
    m_blockModelHandle->Draw(context, *states, m_local, view, projection);
}