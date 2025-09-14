#pragma once
#include "MiracleID.h"
#include "Grid2D.h"
#include <unordered_map>

/**
 * @brief 実際に実現性判定を行うクラス
 */
class Solver
{
public:
	/**
	 * @brief デフォルトコンストラクタ
	 */
	Solver()
	{
	}

private:
	std::unordered_map<MiracleID, Grid2D<char>> m_patterns;
};