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
	void LoadData(ID3D11Device* deviceResources, ID3D11DeviceContext* context);

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

	/// <summary>
	/// D3DState�I�u�W�F�N�g�̎擾
	/// </summary>
	/// <returns></returns>
	DirectX::CommonStates* GetStates() { return m_states.get(); }

	/// <summary>
	/// ��Ԃ̕ʂ̃e�N�X�`�����擾
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetTankTexture() { return m_tankTexture; }

	/// <summary>
	/// ��Ԃ̃G���W���̕ʂ̃e�N�X�`�����擾
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetEngineTexture() { return m_engineTexture; }

	/// <summary>
	/// �f�t�H���g�t�H���g�擾
	/// </summary>
	/// <returns></returns>
	unique_ptr<DirectX::SpriteFont>&& GetDefaultFont() { return move(m_defaultFontHandle); }

	/// <summary>
	/// �^�C�g��UI�̎擾
	/// </summary>
	/// <returns></returns>
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> GetTitleUI() { return m_titleUI; }

	/// <summary>
	/// �^�C�g��UI�̍��W�擾
	/// </summary>
	/// <returns></returns>
	vector<Vector2> GetTitleUIPos() { return m_titleUIPos; }

	/// <summary>
	/// �^�C�g��UI�̃X�P�[���擾
	/// </summary>
	/// <returns></returns>
	vector<float> GetTitleUIScale() { return m_titleUIScale; }

	/// <summary>
	/// ���C���Q�[��UI�̎擾
	/// </summary>
	/// <returns></returns>
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> GetMainGameUI() { return m_mainGameUI; }

	/// <summary>
	/// ���C���Q�[��UI�̍��W�擾
	/// </summary>
	/// <returns></returns>
	vector<Vector2> GetMainGameUIPos() { return m_mainGameUIPos; }

	/// <summary>
	/// ���C���Q�[��UI�̃X�P�[���擾
	/// </summary>
	/// <returns></returns>
	vector<float> GetMainGameUIScale() { return m_mainGameUIScale; }

private:
	static Load* m_load;				//���[�h�N���X�̃C���X�^���X

	static const string m_fileName;		//json�t�@�C����
	json m_json;						//json�t�@�C���̏����i�[

	unique_ptr<DirectX::CommonStates> m_states;		//D3DState�I�u�W�F�N�g
	unique_ptr<DirectX::IEffectFactory> m_fxFactory;//���f�����[�h�p�w���p�[�I�u�W�F�N�g

	unique_ptr<DirectX::SpriteFont> m_defaultFontHandle;			//�Q�[�����̃f�t�H���g�t�H���g

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//�^�C�g��UI
	vector<Vector2> m_titleUIPos;									   //�^�C�g��UI���W
	vector<float> m_titleUIScale;									   //�^�C�g��UI�X�P�[��

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_mainGameUI;	//���C���Q�[��UI
	vector<Vector2> m_mainGameUIPos;										//���C���Q�[��UI���W
	vector<float> m_mainGameUIScale;										//���C���Q�[��UI�X�P�[��

	static constexpr int m_xIndex = 0;
	static constexpr int m_yIndex = 1;

	vector<unique_ptr<DirectX::Model>> m_tankModelHandle;	//��Ԃ̃��f���n���h���z��
	vector<Vector3> m_tankPos;								//��Ԃ̍��W�z��
	ID3D11ShaderResourceView* m_tankTexture;				//��Ԃ̕ʂ̃e�N�X�`��
	ID3D11ShaderResourceView* m_engineTexture;				//��Ԃ̕ʂ̃G���W���e�N�X�`��

	vector<unique_ptr<DirectX::Model>> m_bulletModelHandle;			//�e�̃��f���n���h��

	vector<unique_ptr<DirectX::Model>> m_blockModelHandle;	//�}�b�v�p�u���b�N���f���̔z��
	vector<vector<int>> m_map;						//�}�b�v�`�b�v

	vector<unique_ptr<DirectX::Model>> m_groundBlockModelHandle;	//�u���b�N���f���n���h���z��
	int m_blockUnderWoods;							//�؃u���b�N�̉��ɂ���u���b�N�̐�

	vector<unique_ptr<DirectX::Model>> m_woodParticleModelHandle;	//�؃u���b�N�̔j��G�t�F�N�g�p�p�[�e�B�N�����f��
	static constexpr int m_maxWoodParticleNum = 60;					//�p�[�e�B�N���̍ő吔

	static constexpr int m_maxBulletNum = 6;						//�e�̍ő吔
};

