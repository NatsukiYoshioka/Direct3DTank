#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class WoodParticle;
class BlockManager;

class WoodParticleManager
{
public:
    /// <summary>
    /// 初期化とデータの取得
    /// </summary>
    /// <param name="woodModelHandle"></param>
    WoodParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle);

    /// <summary>
    /// データ解放
    /// </summary>
    ~WoodParticleManager();

    /// <summary>
    /// 初期化
    /// </summary>
    void Init();

    /// <summary>
    /// パーティクルの更新
    /// </summary>
    /// <param name="world"></param>
    /// <param name="blockManager"></param>
    void Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager);

    /// <summary>
    /// パーティクルの描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
private:
    vector<unique_ptr<DirectX::Model>> m_woodParticleModelHandle;       //パーティクルのモデルハンドル
    vector<WoodParticle*> m_woodParticles;                              //各パーティクルのインスタンス
    vector<bool> m_isUseWoodParticle;                                   //パーティクルを使ったかどうか
    vector<bool> m_isSponeWoodParticle;                                 //パーティクルが出現したかどうか
    int m_woodIndex;                                                    //木ブロックの番号
};

