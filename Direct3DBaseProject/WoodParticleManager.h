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
    /// �������ƃf�[�^�̎擾
    /// </summary>
    /// <param name="woodModelHandle"></param>
    WoodParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle);

    /// <summary>
    /// �f�[�^���
    /// </summary>
    ~WoodParticleManager();

    /// <summary>
    /// ������
    /// </summary>
    void Init();

    /// <summary>
    /// �p�[�e�B�N���̍X�V
    /// </summary>
    /// <param name="world"></param>
    /// <param name="blockManager"></param>
    void Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager);

    /// <summary>
    /// �p�[�e�B�N���̕`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
private:
    vector<unique_ptr<DirectX::Model>> m_woodParticleModelHandle;       //�p�[�e�B�N���̃��f���n���h��
    vector<WoodParticle*> m_woodParticles;                              //�e�p�[�e�B�N���̃C���X�^���X
    vector<bool> m_isUseWoodParticle;                                   //�p�[�e�B�N�����g�������ǂ���
    vector<bool> m_isSponeWoodParticle;                                 //�p�[�e�B�N�����o���������ǂ���
    int m_woodIndex;                                                    //�؃u���b�N�̔ԍ�
};

