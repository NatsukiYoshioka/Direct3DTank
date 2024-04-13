#pragma once
#include <sstream>
#include<string>
#include<vector>
#include "DeviceResources.h"
#include"CommonStates.h"
#include"Effects.h"
#include"Model.h"
#include"json.hpp"
#include"common.h"

using json = nlohmann::json;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

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
	/// const wchar_t* �ϊ��֐�
	/// </summary>
	/// <param name="str">�ϊ�����ϐ�</param>
	/// <returns>�ϊ������ϐ�</returns>
	wstring Widen(const string& str);

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

	vector<vector<int>> GetMap() { return m_map; }

private:
	static Load* m_load;				//���[�h�N���X�̃C���X�^���X

	static const string m_fileName;		//json�t�@�C����
	json m_json;						//json�t�@�C���̏����i�[

	string m_filePath;					//�Q�[���ɕK�v�ȃf�[�^�̃p�X���������t�@�C���̃p�X

	unique_ptr<DirectX::CommonStates> m_states;
	unique_ptr<DirectX::IEffectFactory> m_fxFactory;

	vector<unique_ptr<DirectX::Model>> m_tankModelHandle;	//��Ԃ̃��f���n���h���z��
	vector<Vector3> m_tankPos;								//��Ԃ̍��W�z��

	vector<unique_ptr<DirectX::Model>> m_blockModelHandle;	//�}�b�v�p�u���b�N���f���̔z��
	vector<vector<int>> m_map;						//�}�b�v�`�b�v
};

