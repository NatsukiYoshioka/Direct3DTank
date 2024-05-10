#pragma once
#include"common.h"

class Bullet;
class TankManager;
class BlockManager;

using namespace DirectX;
using namespace std;

class BulletManager
{
public:
    BulletManager(vector<unique_ptr<DirectX::Model>>&& bulletModelHandle);
    ~BulletManager();

    void Update(DirectX::SimpleMath::Matrix world, TankManager* tankManager, BlockManager* blockManager);
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    vector<Bullet*> *GetBullets() { return m_bullets; }

private:
    vector<Bullet*> m_bullets[playerNum];
    vector<unique_ptr<DirectX::Model>> m_bulletModelHandle;

    static constexpr int m_maxBulletNum = 3;            //�������X�e�[�W��Ɍ��Ă�e�̍ő吔
    static constexpr float m_maxFireRecast = 5.f;       //���L���X�g����
};

