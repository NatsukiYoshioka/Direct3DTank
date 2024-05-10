#pragma once
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Bullet;

class Tank
{
public:
    /// <summary>
    /// �^���N�̏�����
    /// </summary>
    /// <param name="tankModelHandle"></param>
    /// <param name="pos"></param>
    Tank(unique_ptr<DirectX::Model>&& tankModelHandle, Vector3 pos, float angle);

    /// <summary>
    /// �C���X�^���X�j��
    /// </summary>
    ~Tank();

    /// <summary>
    /// �^���N�X�V����
    /// </summary>
    /// <param name="world">�P�ʍs��</param>
    void Update(DirectX::SimpleMath::Matrix world, DirectX::GamePad::State padState);

    /// <summary>
    /// �^���N�`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* deviceContext, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// �^���N�̍��W�擾
    /// </summary>
    /// <returns>�^���N���W</returns>
    Vector3 GetPos() const { return m_pos; }

    /// <summary>
    /// ���͍X�V����
    /// </summary>
    void UpdateInput(DirectX::GamePad::State padState);

    /// <summary>
    /// �A�j���[�V�����X�V
    /// </summary>
    void UpdateAnimation();

    /// <summary>
    /// �e�̔��ˍX�V����
    /// </summary>
    void UpdateBullets(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// �u���b�N�Ƃ̓����蔻��
    /// </summary>
    /// <param name="blockBox"></param>
    void CheckHitBlock(BoundingBox blockBox, Vector3 blockPos);

    /// <summary>
    /// �e�Ƃ̓����蔻��
    /// </summary>
    /// <param name="bulletBox"></param>
    /// <param name="bulletPos"></param>
    bool CheckHitBullet(BoundingBox bulletBox, Vector3 bulletPos);

    /// <summary>
    /// ���W�̎擾
    /// </summary>
    /// <returns></returns>
    Vector3 GetPos() { return m_pos; }

    /// <summary>
    /// �^���N�̃^���b�g�̃A���O�����擾
    /// </summary>
    /// <returns></returns>
    float GetTurretAngle() { return m_turretRotation; }

    /// <summary>
    /// �e�̔��˃��L���X�g���Ԏ擾
    /// </summary>
    /// <returns></returns>
    float GetFireRecast() { return m_fireRecast; }

    /// <summary>
    /// ���������ǂ����擾
    /// </summary>
    /// <returns></returns>
    bool GetIsFire() { return m_isFire; }

    int GetHP() { return m_hp; }

private:
    int m_hp;
    static constexpr int m_maxHp = 5;

    float m_fireRecast;                                 //�e���ēx�łĂ�悤�ɂȂ�܂ł̎���
    static constexpr float m_maxFireRecast = 2.5f;       //���L���X�g����
    static constexpr float m_recastSpeed = 0.01f;        //���L���X�g�N�[���^�C���X�s�[�h

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

    Vector2 m_direction;    //�^���N�̌����x�N�g��
    Vector3 m_pos;          //�^���N�̃x�N�g�����W
    XMMATRIX m_world;        
    XMMATRIX m_local;       //�^���N�̍s����W
    XMMATRIX m_hitLocal;    //�u���b�N�ɓ����������̍s��
    float m_angle;          //�^���N�̌���
    static constexpr float m_speed = 0.02f;    //�^���N�̃X�s�[�h

    bool m_isMove;            //�����Ă��邩�ǂ���
    bool m_isMoveLeft;        //�^���b�g�����ɓ�������
    bool m_isMoveRight;       //�^���b�g���E�ɓ�������
    bool m_isFire;            //�e�𔭎˂������ǂ���
    bool m_isHitBlock;        //�u���b�N�Ɠ����������ǂ���
    bool m_isHitBullet;       //�e�Ɠ����������ǂ���
    static constexpr float m_wheelRotationSpeed = 5.f;  //�^���N�̃z�C�[���̉�]�X�s�[�h
    float m_turretRotation;                             //�^���b�g�̉�]�l
    static constexpr float m_turretRotationSpeed = 0.05f; //�^���N�̃^���b�g�̉�]�X�s�[�h

    //�^���N�̃{�[����
    static const string m_tankBonesName;
    static const string m_leftBackWheelName;
    static const string m_rightBackWheelName;
    static const string m_leftFrontWheelName;
    static const string m_rightFrontWheelName;
    static const string m_turretName;
    static const string m_canonName;
    static const string m_hatchName;

    static constexpr float m_scale = 0.2f;
    static constexpr float m_boundingboxExtents = 0.5f;
};

