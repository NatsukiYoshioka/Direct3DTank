#pragma once
#include <sstream>

using namespace std;

static constexpr int initializeNum = 0;             //初期化定数

static constexpr int mapSize = 16;					//マップの縦横幅

static constexpr float blockSize = 1.f;				//ブロックの幅

static constexpr int player1 = 0;					//プレイヤー1のindex
static constexpr int player2 = 1;					//プレイヤー2のindex
static constexpr int playerNum = 2;					//プレイヤー数
static constexpr int maxHp = 5;                   //プレイヤーの最大残機

static constexpr float hemipartition = 2.f;			//半分割用

/// <summary>
/// jsonの値をwchar_t方に変換
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
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