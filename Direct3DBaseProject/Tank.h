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
    Tank(unique_ptr<DirectX::Model>&& tankModelHandle, DirectX::Model *bulletModelHandle, Vector3 pos, float angle);

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

private:
    DirectX::Model *m_bulletModelHandle;                //�e�̃��f���n���h��
    vector<Bullet*> m_bullets;                          //�e�N���X
    static constexpr int m_maxBulletNum = 2;            //�������X�e�[�W��Ɍ��Ă�e�̍ő吔
    float m_fireRecast;                                 //�e���ēx�łĂ�悤�ɂȂ�܂ł̎���
    static constexpr float m_maxFireRecast = 5.f;       //���L���X�g����
    static constexpr float m_recastSpeed = 0.01f;        //���L���X�g�N�[���^�C���X�s�[�h

    unique_ptr<DirectX::Model> m_tankModelHandle;       //�^���N���f���n���h��
    DirectX::ModelBone::TransformArray m_drawBones;     //�^���N�̕`��p�{�[��
    DirectX::ModelBone::TransformArray m_animBones;     //�^���N�̃A�j���[�V�����p�{�[��

    DirectX::BoundingBox m_box;
    unique_ptr<GeometricPrimitive> m_shape;

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
    XMMATRIX m_local;       //�^���N�̍s����W
    float m_angle;          //�^���N�̌���
    static constexpr float m_speed = 0.01f;    //�^���N�̃X�s�[�h

    bool m_isMove;            //�����Ă��邩�ǂ���
    bool m_isMoveLeft;        //�^���b�g�����ɓ�������
    bool m_isMoveRight;       //�^���b�g���E�ɓ�������
    bool m_isFire;
    static constexpr float m_wheelRotationSpeed = 5.f;  //�^���N�̃z�C�[���̉�]�X�s�[�h
    float m_turretRotation;                             //�^���b�g�̉�]�l
    static constexpr float m_turretRotationSpeed = 0.025f; //�^���N�̃^���b�g�̉�]�X�s�[�h

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
    Matrix m_shapeLocal;
};

