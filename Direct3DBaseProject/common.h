#pragma once
#include <sstream>

using namespace std;

static constexpr int initializeNum = 0;             //�������萔

static constexpr int mapSize = 16;					//�}�b�v�̏c����

static constexpr float blockSize = 1.f;				//�u���b�N�̕�

static constexpr int player1 = 0;					//�v���C���[1��index
static constexpr int player2 = 1;					//�v���C���[2��index
static constexpr int playerNum = 2;				//�v���C���[��

inline wstring Widen(const string& str)
{
	wostringstream wstm;
	const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(wstm.getloc());
	for (size_t i = initializeNum; i < str.size(); ++i)
	{
		wstm << ctfacet.widen(str[i]);
	}
	return wstm.str();
}