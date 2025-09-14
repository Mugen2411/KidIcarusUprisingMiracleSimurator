#pragma once
#include "MiracleID.h"
#include "Grid2D.h"
#include <unordered_map>
#include <string>

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

	/**
	 * @brief	読み込み
	 * @param	pFilePath	ファイルパス 
	 * @return	読み込みの成否
	 */
	bool Load(const char* pFilePath);

private:
	std::unordered_map<MiracleID, Grid2D> m_patterns;	//!< 全奇跡のパネル形状リスト
	std::unordered_map<int, std::string> m_names;		//!< 全奇跡の名前リスト
};