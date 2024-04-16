#pragma once
#include<vector>
#include"Model.h"
#include"common.h"

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
        WOOD,
        RED,
        BLUE
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="blockModelHandle">ブロックモデルハンドル配列</param>
    /// <param name="map">マップ情報</param>
    BlockManager(vector<unique_ptr<DirectX::Model>>&& blockModelHandle, vector<vector<int>> map);
    ~BlockManager();

    void Init();
    void Update(DirectX::SimpleMath::Matrix world);
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
private:
    vector<Block*> m_blocks;
};

