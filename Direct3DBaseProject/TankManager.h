#pragma once
#include<vector>
#include"common.h"
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Tank;
class BlockManager;
class BulletManager;

class TankManager
{
public:
    /// <summary>
    /// �S�^���N�̏�����
    /// </summary>
    /// <param name="tankModelHandle">�^���N�̃��f���n���h��</param>
    /// <param name="pos">�^���N�̏������W</param>
    TankManager(vector<unique_ptr<DirectX::Model>>&& tankModelHandle, vector<Vector3> pos);

    /// <summary>
    /// �C���X�^���X�j��
    /// </summary>
    ~TankManager();

    /// <summary>
    /// �S�^���N�̍X�V����
    /// </summary>
    /// <param name="world">�P�ʍs��</param>
    void Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager, BulletManager* bulletManager);

    /// <summary>
    /// �S�^���N�̕`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)const;

    /// <summary>
    /// �R���g���[���[�̒��f����
    /// </summary>
    void SuspendGamePad();

    /// <summary>
    /// �R���g���[���[�̍ĊJ����
    /// </summary>
    void ResumeGamePad();

    /// <summary>
    /// �^���N�̎擾
    /// </summary>
    /// <returns></returns>
    vector<Tank*> GetTanks() { return m_tank; }
private:
    vector<Tank*> m_tank;                  //�e�^���N�̃C���X�^���X
    unique_ptr<DirectX::GamePad> m_gamePad;   //�R���g���[���[�̏�Ԃ��Ǘ�����|�C���^

    static constexpr int m_maxBulletNum = 3;            //�������X�e�[�W��Ɍ��Ă�e�̍ő吔
};

