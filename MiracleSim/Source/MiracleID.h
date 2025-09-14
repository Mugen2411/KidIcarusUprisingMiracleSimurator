#pragma once

/**
 * @brief 奇跡ID
 */
class MiracleID
{
public:
	/**
	 * @brief デフォルトコンストラクタ
	 */
	MiracleID()
		: m_id(INVALID)
		, m_level(INVALID)
	{
	}

	/**
	 * @brief コンストラクタ
	 * @param ID 奇跡ID
	 * @param level レベル
	 */
	MiracleID(int ID, int level)
		: m_id(ID)
		, m_level(level)
	{
	}

	/**
	 * @brief	IDが有効かどうか
	 * @return	有効ならtrue
	 */
	bool IsValid() const
	{
		return m_id != INVALID && m_level != INVALID;
	}

	/**
	 * @brief 等価演算子
	 * @param rhs 右辺
	 * @return 右辺と等しいならtrue
	 */
	bool operator=(const MiracleID& rhs) const
	{
		return m_id == rhs.m_id && m_level == rhs.m_level;
	}

	/**
	 * @brief 小なり演算子
	 * @param rhs 右辺
	 * @return 奇跡ID > レベルの優先度で小さいとする
	 */
	bool operator<(const MiracleID& rhs) const
	{
		if (m_id < rhs.m_id)
		{
			return true;
		}
		if (m_id > rhs.m_id)
		{
			return false;
		}
		if (m_level < rhs.m_level)
		{
			return true;
		}
		return false;
	}

	/**
	 * @brief int型へのキャストをサポート
	 */
	operator int() const
	{
		return m_id * MAX_LEVEL + m_level;
	}
public:
	static constexpr int MAX_LEVEL = 4;	//!< レベルの最大値
	static constexpr int INVALID = -1;	//!< 無効値

private:
	int m_id;		//!< 奇跡ID
	int m_level;	//!< 奇跡レベル(1～4)
};

#include <functional>

namespace std
{
	/**
		@brief	ビット管理クラスのハッシュ値を計算する

		@tparam	 BitManagerを指定
	 */
	template <>
	struct hash<MiracleID>
	{
		/**
			@brief	呼び出し演算子

			@param[in]	val 対象
			@return ハッシュ値
		 */
		size_t operator()(const MiracleID& val) const
		{
			return std::hash<int>()(val);
		}
	};
}