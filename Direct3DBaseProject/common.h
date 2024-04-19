#pragma once
#include <sstream>

using namespace std;

static constexpr int initializeNum = 0;             //初期化定数

static constexpr int mapSize = 16;					//マップの縦横幅

static constexpr float blockSize = 1.f;            //ブロックの幅

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