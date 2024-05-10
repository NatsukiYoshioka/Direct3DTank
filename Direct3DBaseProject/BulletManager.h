#pragma once

class Bullet;
class TankManager;
class BlockManager;

using namespace DirectX;
using namespace std;

class BulletManager
{
public:
    BulletManager(unique_ptr<DirectX::Model>&& bulletModelHandle);
    ~BulletManager();

    void Update(DirectX::SimpleMath::Matrix world, TankManager* tankManager, BlockManager* blockManager);
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    vector<Bullet*> m_bullets[playerNum];
    DirectX::Model* m_bulletModelHandle;
};

