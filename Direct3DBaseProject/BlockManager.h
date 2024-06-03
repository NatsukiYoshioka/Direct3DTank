#pragma once
#include<vector>
#include"Model.h"

using namespace DirectX;
using namespace std;

class Block;

/// <summary>
/// ステージ用ブロック管理クラス
/// </summary>
class BlockManager
{
public:
    /// <summary>
    /// ブロックの種類
    /// </summary>
    enum class BlockType
    {
        YELLOW,
        RED,
        BLUE,
        WOOD
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="blockModelHandle">ブロックモデルハンドル配列</param>
    /// <param name="map">マップ情報</param>
    BlockManager(vector<unique_ptr<DirectX::Model>>&& blockModelHandle, vector<unique_ptr<DirectX::Model>>&& groundBlockUnderWoodsModelHandle, vector<vector<int>> map);
    ~BlockManager();

    /// <summary>
    /// ステージの初期化
    /// </summary>
    void Init();

    /// <summary>
    /// 全ブロックの更新処理
    /// </summary>
    /// <param name="world">単位行列</param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// 全ブロックの描画処理
    /// </summary>
    /// <param name="context">context</param>
    /// <param name="states">m_states</param>
    /// <param name="view">m_view</param>
    /// <param name="projection">m_proj</param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// ブロックの取得
    /// </summary>
    /// <returns></returns>
    vector<Block*> GetBlocks() { return m_blocks; }

    /// <summary>
    /// 木ブロックの数取得
    /// </summary>
    /// <returns></returns>
    int GetWoodBlockNum()const { return m_woodBlockNum; }
private:
    vector<Block*> m_blocks;                //各ブロックのインスタンス
    int m_woodBlockNum;
};

