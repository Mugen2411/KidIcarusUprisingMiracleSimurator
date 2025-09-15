#pragma once
#include "MiracleID.h"
#include "Grid2D.h"
#include <unordered_map>
#include <unordered_set>
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

	/**
	 * @brief 候補リストに追加する
	 * @param ID 奇跡ID
	 * @param level レベル
	 */
	void AddCandidate(int ID, int level);

	/**
	 * @brief 候補リストから削除する
	 * @param ID 奇跡ID
	 * @param level レベル
	 */
	void DeleteCandidate(int ID);

	/**
	 * @brief 奇跡の名前全てを出力する
	 */
	void OutputNames();

	/**
	 * @brief 候補を出力する
	 */
	void OutputCandidates();

	/**
	 * @brief 現在の候補がパネルに入るか確認して入るかもしれない奇跡を出力する
	 */
	void Solve();

private:
	std::unordered_map<MiracleID, Grid2D> m_patterns;	//!< 全奇跡のパネル形状リスト
	std::unordered_map<int, std::string> m_names;		//!< 全奇跡の名前リスト
	std::unordered_map<int, int> m_maxLevels;		//!< 全奇跡のレベル最大値リスト

	std::unordered_set<MiracleID> m_candidate;		//!< 現在の候補リスト
};