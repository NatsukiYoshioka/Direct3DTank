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
    /// <summary>
    /// �C���X�^���X����
    /// </summary>
    /// <param name="bulletModelHandle"></param>
    BulletManager(vector<unique_ptr<DirectX::Model>>&& bulletModelHandle);

    /// <summary>
    /// �C���X�^���X�j��
    /// </summary>
    ~BulletManager();

    /// <summary>
    /// �e�S�̂̍X�V
    /// </summary>
    /// <param name="world">���[���h�P�ʍs��</param>
    /// <param name="tankManager">��ԊǗ��N���X</param>
    /// <param name="blockManager">�u���b�N�Ǘ��N���X</param>
    void Update(DirectX::SimpleMath::Matrix world, TankManager* tankManager, BlockManager* blockManager);

    /// <summary>
    /// �e�̕`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// �e�e�̎擾
    /// </summary>
    /// <returns></returns>
    vector<Bullet*> *GetBullets() { return m_bullets; }

private:
    vector<Bullet*> m_bullets[playerNum];               //�v���C���[���Ƃ̒e�̃N���X�z��
    vector<unique_ptr<DirectX::Model>> m_bulletModelHandle;//�e�̃��f���n���h��

    static constexpr int m_maxBulletNum = 3;            //�������X�e�[�W��Ɍ��Ă�e�̍ő吔
    static constexpr float m_maxFireRecast = 5.f;       //���L���X�g����

    bool m_isUsedBullet[m_maxBulletNum * playerNum];
};

