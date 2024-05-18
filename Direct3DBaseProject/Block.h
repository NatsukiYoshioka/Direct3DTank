#pragma once
#include"Model.h"
#include"BlockManager.h"
#include"CommonStates.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Block
{
public:

    /// <summary>
    /// �u���b�N�̏�����
    /// </summary>
    /// <param name="blockModelHandle"></param>
    /// <param name="pos"></param>
    /// <param name="blockType"></param>
    Block(unique_ptr<DirectX::Model>&& blockModelHandle, Vector3 pos, BlockManager::BlockType blockType);

    /// <summary>
    /// �f�[�^�̉��
    /// </summary>
    ~Block();

    /// <summary>
    /// �u���b�N�̍��W�ݒ�
    /// </summary>
    /// <param name="world"></param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// �u���b�N�̕`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// �u���b�N�̎�ނ��擾
    /// </summary>
    /// <returns></returns>
    BlockManager::BlockType GetBlockType()const { return m_blockType; }

    /// <summary>
    /// ���f���̃��b�V�����擾
    /// </summary>
    /// <returns></returns>
    ModelMesh::Collection GetModelMesh() { return m_blockModelHandle->meshes; }

    /// <summary>
    /// ���f���̍��W���擾
    /// </summary>
    /// <returns></returns>
    Vector3 GetPos()const { return m_pos; }

private:
    unique_ptr<DirectX::Model> m_blockModelHandle;      //�u���b�N�̃��f���n���h��
    BlockManager::BlockType m_blockType;                //�u���b�N�̎��
    XMMATRIX m_local;                                   //���f���̍s����
    Vector3 m_pos;                                      //���f���̍��W   
    bool m_destroy;                                     //��ꂽ���ǂ���

    static constexpr float m_extents = 1.f;             //�����蔻��͈̔�
};

