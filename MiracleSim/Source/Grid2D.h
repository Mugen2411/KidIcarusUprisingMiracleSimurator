#ifndef __INCLUDED_GRID2D__
#define __INCLUDED_GRID2D__

#include <vector>
#include <cassert>
#include <cstdint>
#include <iostream>
#include "BitManager.h"

/**
    @brief    二次元のグリッドを表すクラス

    @tparam    T   格納する型
 */
class Grid2D
{
public:
    /**
     * @brief デフォルトコンストラクタ
     */
    Grid2D()
        : m_data(), m_width(0), m_height(0)
    {
    }

    /**
        @brief    コンストラクタ

        @param[in]    height          高さ
        @param[in]    width           幅
        @param[in]    initialValue    初期値
    */
    Grid2D(int64_t height, int64_t width)
        : m_data(), m_width(width), m_height(height)
    {
    }

    /**
        @brief            指定した座標の値にアクセスする

        @param[in]    x   X座標
        @param[in]    y   Y座標

        @return         目的の座標の参照
     */
    bool Get(int64_t x, int64_t y)
    {
        return m_data.Get(GetIndex(x, y));
    }

    /**
        @brief            指定した座標の値を変更する

        @param[in]    x   X座標
        @param[in]    y   Y座標
        @param[in]    val 設定する値
     */
    void Set(int64_t x, int64_t y, bool val)
    {
        return m_data.Set(GetIndex(x, y), val);
    }

    /**
        @brief    高さの取得

        @return 高さ
     */
    int64_t GetHeight() const
    {
        return m_height;
    }

    /**
        @brief    幅の取得

        @return 幅
     */
    int64_t GetWidth() const
    {
        return m_width;
    }

    /**
        @brief    Indexの取得

        @param[in]    x       X座標
        @param[in]    y       Y座標

        @return     Index
     */
    int64_t GetIndex(int64_t x, int64_t y) const
    {
        assert(IsInner(x, y));

        return y * m_width + x;
    }

    /**
        @brief        X座標を取得する

        @param[in]    idx     インデックス

        @return     X座標
     */
    int64_t GetX(int64_t idx) const
    {
        assert(0 <= idx && idx < m_height * m_width);

        return idx % m_width;
    }

    /**
        @brief        Y座標を取得する

        @param[in]    idx     インデックス

        @return     Y座標
     */
    int64_t GetY(int64_t idx) const
    {
        assert(0 <= idx && idx < m_height * m_width);

        return idx / m_width;
    }

    /**
        @brief            座標がグリッドの内部か否か

        @param[in]    x       X座標
        @param[in]    y       Y座標

        @retval     true    グリッドの内部にいる
        @retval     false   グリッドの外側
     */
    bool IsInner(int64_t x, int64_t y) const
    {
        return 0 <= x && x < m_width && 0 <= y && y < m_height;
    }

    /**
        @brief        全てのマスに対して操作する

        @tparam     Func    関数の型

        @param[in]    func    操作する関数(引数としてidxとその地点の値が貰える)
     */
    template <class Func>
    void ForEach(Func func)
    {
        for (int i = 0; i < m_width * m_height; ++i)
        {
            func(i, m_data[i]);
        }
    }

    /**
     * @brief R×90度回転させたグリッドを取得
     * @param R 角度(直角)
     * @return 回転させたグリッド
     */
    Grid2D GetRotated(int R)
    {
        switch (R%4)
        {
        case 0:
        {
            return *this;
        }
        case 1:
        {
            Grid2D ret(m_width, m_height);
            for (int y = 0; y < m_height; ++y)
            {
                for (int x = 0; x < m_width; ++x)
                {
                    ret.Set(m_height - y - 1, x, Get(x, y));
                }
            }
            return ret;
        }
        case 2:
        {
            Grid2D ret(m_height, m_width);
            for (int y = 0; y < m_height; ++y)
            {
                for (int x = 0; x < m_width; ++x)
                {
                    ret.Set(m_width - x - 1, m_height - y - 1, Get(x, y));
                }
            }
            return ret;
        }
        case 3:
        {
            Grid2D ret(m_width, m_height);
            for (int y = 0; y < m_height; ++y)
            {
                for (int x = 0; x < m_width; ++x)
                {
                    ret.Set(y, m_width - x - 1, Get(x, y));
                }
            }
            return ret;
        }
        default:
            break;
        }

    }

private:
    BitManager m_data; //!< 本体となるビット列
    int64_t m_width;       //!< 幅
    int64_t m_height;      //!< 高さ
};

#endif //__INCLUDED_GRID2D__