#pragma once
#include"Model.h"
#include"BlockManager.h"
#include"CommonStates.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Block
{
public:

    /// <summary>
    /// ブロックの初期化
    /// </summary>
    /// <param name="blockModelHandle"></param>
    /// <param name="pos"></param>
    /// <param name="blockType"></param>
    Block(unique_ptr<DirectX::Model>&& blockModelHandle, Vector3 pos, BlockManager::BlockType blockType);

    ~Block();

    /// <summary>
    /// ブロックの座標設定
    /// </summary>
    /// <param name="world"></param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// ブロックの描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    unique_ptr<DirectX::Model> m_blockModelHandle;
    DirectX::BoundingBox m_box;
    unique_ptr<GeometricPrimitive> m_shape;
    BlockManager::BlockType m_blockType;
    XMMATRIX m_local;
    Vector3 m_pos;
    bool m_destroy;
};

