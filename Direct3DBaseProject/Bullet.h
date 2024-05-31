#pragma once
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Bullet
{
public:
    /// <summary>
    /// �e���ˎ��̏��ݒ�
    /// </summary>
    /// <param name="bulletModelHandle"></param>
    /// <param name="pos"></param>
    /// <param name="angle"></param>
    Bullet(DirectX::Model* bulletModelHandle, DirectX::SimpleMath::Vector3 pos, float angle, int bulletIndex);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Bullet();

    /// <summary>
    /// �e�̍X�V
    /// </summary>
    /// <param name="world"></param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// �e�̕`��
    /// </summary>
    /// <param name="deviceContext"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* deviceContext, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// �e�̃��f���n���h���擾
    /// </summary>
    /// <returns></returns>
    DirectX::Model* GetBulletModelHandle() { return m_bulletModelHandle; }

    /// <summary>
    /// ���W�̎擾
    /// </summary>
    /// <returns></returns>
    Vector3 GetPos() { return m_pos; }

    /// <summary>
    /// �X�e�[�W�u���b�N�Ƃ̓����蔻��
    /// </summary>
    /// <param name="blockBox"></param>
    /// <param name="blockPos"></param>
    bool CheckHitBlock(BoundingBox blockBox, Vector3 blockPos);

    /// <summary>
    /// �e����ꂽ���擾
    /// </summary>
    /// <returns></returns>
    bool GetIsBreak() { return m_isBreak; }

    /// <summary>
    /// �e�̃��f���z��̔ԍ����擾
    /// </summary>
    /// <returns></returns>
    const int GetBulletIndex() { return m_bulletIndex; }

    /// <summary>
    /// �^���N�ɓ����������ɌĂяo��
    /// </summary>
    void HitTank() { m_isBreak = true; }

private:
    DirectX::Model* m_bulletModelHandle;            //�e���f���n���h��
    const int m_bulletIndex;
    Vector3 m_pos;                                  //�e�̍��W
    XMMATRIX m_local;                               //�e�̏����i�[�����s��
    XMMATRIX m_world;
    static constexpr float m_scale = 0.1f;          //�e�̑傫��
    float m_angle;                                  //�e�̌���
    Vector3 m_direction;                            //�e�̕����x�N�g��
    static constexpr float m_speed = 0.04f;         //�e�̓����X�s�[�h         

    //�e�̓����蔻��͈�
    static constexpr float m_boundingboxExtentsX = 0.2f;
    static constexpr float m_boundingboxExtentsY = 0.1f;
    static constexpr float m_boundingboxExtentsZ = 0.2f;

    bool m_isHitBlock;                              //�u���b�N�Ɠ����������ǂ���
    bool m_isBreak;                                 //�e����ꂽ���ǂ���
    int m_boundBlockCount;                          //�u���b�N�ɒ��˕Ԃ�����
    static constexpr int m_maxBoundCount = 5;       //�u���b�N�ɒ��˕Ԃ�ő��

    static constexpr float m_fireFrontWidth = 1.f;  //�e�̔��˕�
};

