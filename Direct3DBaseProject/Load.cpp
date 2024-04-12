#include "pch.h"
#include <fstream>
#include <string>
#include <sstream>
#include"common.h"
#include "Load.h"

Load* Load::m_load = nullptr;

//�R���X�g���N�^
Load::Load() :
	m_isHeader(false),
	m_isIndex(false)
{

}

//�f�[�^�̉��
Load::~Load()
{

}

//�C���X�^���X����
void Load::CreateInstance()
{
	if (!m_load)
	{
		m_load = new Load();
	}
}

//�C���X�^���X�j��
void Load::DestroyInstance()
{
	if (m_load)
	{
		delete(m_load);
	}
}

//�t�@�C������f�[�^�擾
void Load::ReadFile(string filePath, bool isHeader, bool isIndex)
{
	m_filePath = filePath;
	m_isHeader = isHeader;
	m_isIndex = isIndex;

	string buf;
	string commaBuf;

	//�ǂݍ���csv�t�@�C�����J��
	ifstream file(m_filePath);

	//getline�֐���1�s���ǂݍ����buf�Ɋi�[
	for (int i = initializeNum; getline(file, buf); i++)
	{
		m_cell.push_back(vector<string>());

		//delim��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�ɂ���
		istringstream iStream(buf);

		for (int j = initializeNum; getline(iStream, commaBuf, m_delim); j++)
		{
			if (m_isHeader && m_isIndex)
			{
				if (i == initializeNum && j == initializeNum)continue;
				//�w�b�_�[���̊i�[
				if (i == initializeNum && j != initializeNum)m_header.push_back(commaBuf);
				//�C���f�b�N�X���̊i�[
				if (i != initializeNum && j == initializeNum)m_index.push_back(commaBuf);
				//�v�f�̊i�[
				if (i != initializeNum && j != initializeNum)m_cell.at(i).push_back(commaBuf);
			}
			else if (m_isHeader)
			{
				//�w�b�_�[���̊i�[
				if (i == initializeNum)m_header.push_back(commaBuf);
				//�C���f�b�N�X���̊i�[
				if (i != initializeNum && j == initializeNum)m_index.push_back(string());
				//�v�f�̊i�[
				if (i != initializeNum)m_cell.at(i).push_back(commaBuf);
			}
			else if (m_isIndex)
			{
				//�w�b�_�[���̊i�[
				if (i == initializeNum && j != initializeNum)m_header.push_back(string());
				//�C���f�b�N�X���̊i�[
				if (j == initializeNum)m_index.push_back(commaBuf);
				//�v�f�̊i�[
				if (j != initializeNum)m_cell.at(i).push_back(commaBuf);
			}
			else
			{
				//�w�b�_�[���̊i�[
				if (i == initializeNum)m_header.push_back(string());
				//�C���f�b�N�X���̊i�[
				if (j == initializeNum)m_index.push_back(string());
				//�v�f�̊i�[
				m_cell.at(i).push_back(commaBuf);
			}
		}
	}
}

//�f�[�^�̃��[�h
void Load::LoadData(unique_ptr<DX::DeviceResources> deviceResources)
{
	auto device = deviceResources->GetD3DDevice();

	m_states = make_unique<DirectX::CommonStates>(device);

	m_fxFactory = make_unique<DirectX::EffectFactory>(device);

	for (int i = initializeNum; i < m_cell.size(); i++)
	{
		for (int j = initializeNum; j < m_cell.at(i).size(); j++)
		{

		}
	}
}