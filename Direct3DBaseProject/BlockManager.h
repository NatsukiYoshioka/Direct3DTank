#pragma once
#include<vector>
#include"Model.h"

using namespace DirectX;
using namespace std;

class Block;

/// <summary>
/// �X�e�[�W�p�u���b�N�Ǘ��N���X
/// </summary>
class BlockManager
{
public:
    /// <summary>
    /// �u���b�N�̎��
    /// </summary>
    enum class BlockType
    {
        YELLOW,
        RED,
        BLUE,
        WOOD
    };

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="blockModelHandle">�u���b�N���f���n���h���z��</param>
    /// <param name="map">�}�b�v���</param>
    BlockManager(vector<unique_ptr<DirectX::Model>>&& blockModelHandle, vector<unique_ptr<DirectX::Model>>&& groundBlockUnderWoodsModelHandle, vector<vector<int>> map);
    ~BlockManager();

    /// <summary>
    /// �X�e�[�W�̏�����
    /// </summary>
    void Init();

    /// <summary>
    /// �S�u���b�N�̍X�V����
    /// </summary>
    /// <param name="world">�P�ʍs��</param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// �S�u���b�N�̕`�揈��
    /// </summary>
    /// <param name="context">context</param>
    /// <param name="states">m_states</param>
    /// <param name="view">m_view</param>
    /// <param name="projection">m_proj</param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// �u���b�N�̎擾
    /// </summary>
    /// <returns></returns>
    vector<Block*> GetBlocks() { return m_blocks; }

    /// <summary>
    /// �؃u���b�N�̐��擾
    /// </summary>
    /// <returns></returns>
    int GetWoodBlockNum()const { return m_woodBlockNum; }
private:
    vector<Block*> m_blocks;                //�e�u���b�N�̃C���X�^���X
    int m_woodBlockNum;
};

