#pragma once

#include <iostream>

/**
    @brief	ビット管理型
 */
class BitManager
{
public:
    /**
        @brief	デフォルトコンストラクタ
    */
    BitManager()
        : m_data(0ull)
    {};

    /**
        @brief	コンストラクタ

        @param[in]	val 初期値
     */
    BitManager(uint64_t val)
        : m_data(val)
    {};

    /**
        @brief	uint64_t型への変換を許可する

        @return uint64_t型に変換されたデータ
    */
    operator uint64_t() const
    {
        return m_data;
    }

    /**
        @brief	全てfalseで初期化されたビットマネージャを取得

        @return 全てfalseで初期化されたビットマネージャ
     */
    static BitManager AllFalse()
    {
        return Filled(0);
    }

    /**
        @brief	全てtrueで初期化されたビットマネージャを取得

        @return 全てtrueで初期化されたビットマネージャ
     */
    static BitManager AllTrue()
    {
        return Filled(NUM_DIGIT);
    }

    /**
        @brief	差分で初期化されたビットマネージャ

        @param[in]	lhs 左辺
        @param[in]	rhs 右辺
        @return 左辺と右辺で異なるビットだけ立てたビットマネージャ
     */
    static BitManager Difference(const BitManager& lhs, const BitManager& rhs)
    {
        return BitManager(lhs.m_data ^ rhs.m_data);
    }

    /**
        @brief	下からnum個のビットをtrueで埋め、それ以外がfalseのビットマネージャ

        @param[in]	num ビットを立てる個数
        @return 概要通りのビットマネージャ
     */
    static BitManager Filled(int num)
    {
        _ValidateBitNum(num);

        BitManager retval = 0;
        for (int i = 0; i < num; ++i)
        {
            retval.Set(i, true);
        }
        return retval;
    }

    /**
        @brief	1つの要素だけtrue、他がfalseのビットマネージャ

        @param[in]	idx trueにするインデックス
        @return 概要を満たすビットマネージャ
     */
    static BitManager Onehot(int idx)
    {
        BitManager retval = AllFalse();
        retval.Set(idx, true);
        return retval;
    }

    /**
        @brief	コピーコンストラクタ

        @param[in]	rhs コピー元
     */
    BitManager(const BitManager& rhs)
        : m_data(rhs.m_data)
    {}

    /**
        @brief	コピー代入演算子

        @param[in]	rhs コピー元
        @return 自身の参照
     */
    BitManager& operator=(const BitManager& rhs)
    {
        m_data = rhs.m_data;
        return *this;
    }

    /**
        @brief	idx番目のビットが立っているか取得する

        @param[in]	idx インデックス
        @return idx番目のビット
     */
    bool Get(int idx)
    {
        _ValidateIndex(idx);
        return m_data & (1ull << idx);
    }

    /**
        @brief	idx番目のビットをvalにする

        @param[in]	idx インデックス
        @param[in]	val 適用する状態
     */
    void Set(int idx, bool val)
    {
        _ValidateIndex(idx);
        uint64_t filter = 1ull << idx;
        if (val)
        {
            m_data |= filter;
        }
        else
        {
            m_data &= ~filter;
        }
    }

    /**
        @brief	trueになっているビットの数を取得

        @return trueになっているビットの数
     */
    int GetCount()
    {
        int retval = 0;
        for (int i = 0; i < NUM_DIGIT; ++i)
        {
            if (Get(i))
            {
                ++retval;
            }
        }
        return retval;
    }

    /**
        @brief	フラグの内容をでバッグ出力する
        @note   提出などでは使わない想定
     */
    void DebugOutput()
    {
        for (int i = 0; i < NUM_DIGIT; ++i)
        {
            if ((m_data >> i) & 1)
            {
                std::cerr << 1;
            }
            else
            {
                std::cerr << 0;
            }
        }
        std::cerr << std::endl;
    }

    /**
        @brief	前置インクリメント演算子

        @return 自身の参照
     */
    BitManager& operator++()
    {
        ++m_data;
        return *this;
    }

    /**
        @brief	後置インクリメント演算子

        @return インクリメント前のコピー
     */
    BitManager operator++(int)
    {
        BitManager retval = *this;
        operator++();
        return retval;
    }

    /**
        @brief	等価演算子

        @param[in]	rhs 比較対象
        @return 自身と右辺が等しいか
     */
    bool operator==(const BitManager& rhs)
    {
        return m_data == rhs.m_data;
    }

    /**
        @brief	不等価演算子

        @param[in]	rhs 比較対象
        @return 自身と右辺が等しくないか
     */
    bool operator!=(const BitManager& rhs)
    {
        return !operator==(rhs);
    }

private:
    /**
        @brief	インデックスが正しいか検証する

        @param[in]	idx インデックス
     */
    static void _ValidateIndex(int idx)
    {
        if (idx < 0 || NUM_DIGIT <= idx)
        {
            std::cerr << "BitManager: Index Error!" << std::endl;
        }
    }

    /**
        @brief	ビットの個数指定が正しいか検証する

        @param[in]	num 個数
     */
    static void _ValidateBitNum(int num)
    {
        if (num < 0 || NUM_DIGIT < num)
        {
            std::cerr << "BitManager: Bit Num Error!" << std::endl;
        }
    }

public:
    static constexpr int NUM_DIGIT = 64; //!< 桁数

private:
    uint64_t m_data; //!< 本体
};