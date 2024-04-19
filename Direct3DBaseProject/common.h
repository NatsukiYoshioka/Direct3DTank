#pragma once
#include <sstream>

using namespace std;

static constexpr int initializeNum = 0;             //�������萔

static constexpr int mapSize = 16;					//�}�b�v�̏c����

static constexpr float blockSize = 1.f;            //�u���b�N�̕�

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