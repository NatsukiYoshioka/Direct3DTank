#include "pch.h"
#include "Block.h"

Block::Block(unique_ptr<DirectX::Model>&& blockModelHandle, Vector3 pos, BlockManager::BlockType blockType):
    m_blockType(blockType),
    m_blockModelHandle(move(blockModelHandle)),
    m_pos(pos),
    m_destroy(false)
{
    
}

Block::~Block()
{

}

void Block::Update()
{

}

void Block::Draw()
{

}