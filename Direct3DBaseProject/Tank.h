#pragma once
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Tank
{
public:
    /// <summary>
    /// �^���N�̏�����
    /// </summary>
    /// <param name="tankModelHandle"></param>
    /// <param name="pos"></param>
    Tank(unique_ptr<DirectX::Model>&& tankModelHandle, Vector3 pos);

    /// <summary>
    /// �C���X�^���X�j��
    /// </summary>
    ~Tank();

    /// <summary>
    /// �^���N�X�V����
    /// </summary>
    /// <param name="world">�P�ʍs��</param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// �^���N�`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    unique_ptr<DirectX::Model> m_tankModelHandle;       //�^���N���f���n���h��
    DirectX::ModelBone::TransformArray m_drawBones;     //�^���N�̕`��p�{�[��
    DirectX::ModelBone::TransformArray m_animBones;     //�^���N�̃A�j���[�V�����p�{�[��

    //�^���N�̃{�[���̎��
    uint32_t m_leftBackWheelBone;
    uint32_t m_rightBackWheelBone;
    uint32_t m_leftFrontWheelBone;
    uint32_t m_rightFrontWheelBone;
    uint32_t m_turretBone;
    uint32_t m_canonBone;
    uint32_t m_hatchBone;

    Vector3 m_pos;          //�^���N�̃x�N�g�����W
    XMMATRIX m_local;       //�^���N�̍s����W

    //�^���N�̃{�[����
    static const string m_tankBonesName;
    static const string m_leftBackWheelName;
    static const string m_rightBackWheelName;
    static const string m_leftFrontWheelName;
    static const string m_rightFrontWheelName;
    static const string m_turretName;
    static const string m_canonName;
    static const string m_hatchName;

    static constexpr float m_scale = 0.5f;
};

