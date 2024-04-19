#pragma once
#include<vector>
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Tank;

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
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// �S�^���N�̕`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    static constexpr int m_player1 = 0;         //�v���C���[1��index
    static constexpr int m_player2 = 1;         //�v���C���[2��index
    static constexpr int m_playerNum = 2;       //�v���C���[��

    Tank* m_tank[m_playerNum];                  //�e�^���N�̃C���X�^���X
};

