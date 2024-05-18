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

    /// <summary>
    /// データの解放
    /// </summary>
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
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// ブロックの種類を取得
    /// </summary>
    /// <returns></returns>
    BlockManager::BlockType GetBlockType()const { return m_blockType; }

    /// <summary>
    /// モデルのメッシュを取得
    /// </summary>
    /// <returns></returns>
    ModelMesh::Collection GetModelMesh() { return m_blockModelHandle->meshes; }

    /// <summary>
    /// モデルの座標を取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPos()const { return m_pos; }

private:
    unique_ptr<DirectX::Model> m_blockModelHandle;      //ブロックのモデルハンドル
    BlockManager::BlockType m_blockType;                //ブロックの種類
    XMMATRIX m_local;                                   //モデルの行列情報
    Vector3 m_pos;                                      //モデルの座標   
    bool m_destroy;                                     //壊れたかどうか

    static constexpr float m_extents = 1.f;             //当たり判定の範囲
};

