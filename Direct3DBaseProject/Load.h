#pragma once
#include<string>
#include<vector>
#include "DeviceResources.h"
#include"CommonStates.h"
#include"Effects.h"
#include"Model.h"

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
	void LoadData(unique_ptr<DX::DeviceResources> deviceResources);

private:
	static Load* m_load;				//���[�h�N���X�̃C���X�^���X

	static const string m_fileName;
	string jsonStr;

	string m_filePath;					//�Q�[���ɕK�v�ȃf�[�^�̃p�X���������t�@�C���̃p�X
	bool m_isHeader;						//�w�b�_�[�����邩�ǂ���
	bool m_isIndex;						//�C���f�b�N�X�����邩�ǂ���
	static constexpr char m_delim = ',';	//��؂�̕���

	vector<string> m_header;				//�w�b�_�[���ۊ�
	vector<string> m_index;				//�C���f�b�N�X���ۊ�
	vector<vector<string>> m_cell;		//�v�f�ۊ�

	unique_ptr<DirectX::CommonStates> m_states;
	unique_ptr<DirectX::IEffectFactory> m_fxFactory;

	vector<unique_ptr<DirectX::Model>> m_tankModelHandle;
	vector<Vector3> m_tankPos;

	vector<unique_ptr<DirectX::Model>> m_blockModelHandle;
	static constexpr int m_mapSize = 48;
	char m_map[m_mapSize][m_mapSize];

	static constexpr const char* m_tankHeader = "TANK";
	static constexpr const char* m_blockHeader = "BLOCK";
};

