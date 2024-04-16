#pragma once
#include<vector>
#include"Model.h"
#include"common.h"

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
        WOOD,
        RED,
        BLUE
    };

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="blockModelHandle">�u���b�N���f���n���h���z��</param>
    /// <param name="map">�}�b�v���</param>
    BlockManager(vector<unique_ptr<DirectX::Model>>&& blockModelHandle, vector<vector<int>> map);
    ~BlockManager();

    void Init();
    void Update(DirectX::SimpleMath::Matrix world);
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
private:
    vector<Block*> m_blocks;
};

