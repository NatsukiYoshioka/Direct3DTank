#pragma once
#include <sstream>
#include<string>
#include<vector>
#include "DeviceResources.h"
#include"CommonStates.h"
#include"Effects.h"
#include"Model.h"
#include"json.hpp"

using json = nlohmann::json;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// �O���f�[�^���[�h�N���X
/// </summary>
class Load
{
private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Load();

	/// <summary>
	/// �i�[�����f�[�^�̉��
	/// </summary>
	~Load();

public:
	/// <summary>
	/// �C���X�^���X�̐���
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �C���X�^���X�̔j��
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�N���X�̃C���X�^���X</returns>
	static Load* GetInstance() { return m_load; }

	/// <summary>
	/// �t�@�C������f�[�^�̃p�X���擾
	/// </summary>
	/// <param name="filepath">csv�t�@�C���̃p�X</param>
	/// <param name="isHeader">�w�b�_�[�����邩�ǂ���</param>
	/// <param name="isIndex">�C���f�b�N�X�����邩�ǂ���</param>
	void ReadFile();

	/// <summary>
	/// �f�[�^�̃��[�h
	/// </summary>
	/// <param name="deviceResources">�Q�[���f�o�C�X</param>
	void LoadData(ID3D11Device* deviceResources);

	/// <summary>
	/// �^���N���f���n���h���z����擾
	/// </summary>
	/// <returns>�^���N���f���n���h���z��</returns>
	vector<unique_ptr<DirectX::Model>>&& GetTankModelHandle() { return move(m_tankModelHandle); }

	/// <summary>
	/// �^���N���W�z����擾
	/// </summary>
	/// <returns>�^���N���W�z��</returns>
	vector<Vector3> GetTankPos() { return m_tankPos; }

	/// <summary>
	/// �u���b�N���f���n���h���z����擾
	/// </summary>
	/// <returns>�u���b�N���f���n���h���z��</returns>
	vector<unique_ptr<DirectX::Model>>&& GetBlockModelHandle() { return move(m_blockModelHandle); }

	/// <summary>
	/// �؃u���b�N�̉��̒n�ʃu���b�N���擾
	/// </summary>
	/// <returns></returns>
	vector<unique_ptr<DirectX::Model>>&& GetGroundBlockUnderWoodsModelHandle() { return move(m_groundBlockModelHandle); }

	/// <summary>
	/// �}�b�v���̎擾
	/// </summary>
	/// <returns></returns>
	vector<vector<int>> GetMap() { return m_map; }

	/// <summary>
	/// �e���f���̎擾
	/// </summary>
	/// <returns></returns>
	vector<unique_ptr<DirectX::Model>>&& GetBulletModelHandle() { return move(m_bulletModelHandle); }

	/// <summary>
	/// �ؕЃp�[�e�B�N�����f���̎擾
	/// </summary>
	/// <returns></returns>
	vector<unique_ptr<DirectX::Model>>&& GetWoodParticleModelHandle() { return move(m_woodParticleModelHandle); }

	unique_ptr<DirectX::CommonStates>&& GetStates() { return move(m_states); }

private:
	static Load* m_load;				//���[�h�N���X�̃C���X�^���X

	static const string m_fileName;		//json�t�@�C����
	json m_json;						//json�t�@�C���̏����i�[

	unique_ptr<DirectX::CommonStates> m_states;
	unique_ptr<DirectX::IEffectFactory> m_fxFactory;

	vector<unique_ptr<DirectX::Model>> m_tankModelHandle;	//��Ԃ̃��f���n���h���z��
	vector<Vector3> m_tankPos;								//��Ԃ̍��W�z��

	vector<unique_ptr<DirectX::Model>> m_bulletModelHandle;			//�e�̃��f���n���h��

	vector<unique_ptr<DirectX::Model>> m_blockModelHandle;	//�}�b�v�p�u���b�N���f���̔z��
	vector<vector<int>> m_map;						//�}�b�v�`�b�v

	vector<unique_ptr<DirectX::Model>> m_groundBlockModelHandle;	//�u���b�N���f���n���h���z��
	int m_blockUnderWoods;							//�؃u���b�N�̉��ɂ���u���b�N�̐�

	vector<unique_ptr<DirectX::Model>> m_woodParticleModelHandle;
	static constexpr int m_maxWoodParticleNum = 60;

	static constexpr int m_maxBulletNum = 6;
};

