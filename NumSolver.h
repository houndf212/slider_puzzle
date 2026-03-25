#pragma once

//#include <vector>
#include <stdint.h>
#include <assert.h>
#include <unordered_map>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

namespace num_puzzle {

struct stNextMove
{
    uint8_t m_toIndex[4];
    uint8_t m_len;
};

#ifndef NDEBUG

inline void
_print_mv(stNextMove mv)
{
    printf("{");
    for (uint8_t i=0; i<mv.m_len; ++i)
    {
        printf("%d ", mv.m_toIndex[i]);
    }
    printf("}");
}

#endif

template<uint8_t gRow, uint8_t gCol>
class NumStatus
{
    /*  0 1 2 .. nCol-1
    *  1 * nCol
    *  2 * nCol
    */
public:
    static constexpr uint8_t g_indexSize = gRow * gCol;
    static constexpr uint8_t g_null = 0;

#ifndef NDEBUG
    static void
    _print_puzzle()
    {
        printf("status:\n");
        for (uint8_t row = 0; row < gRow; ++row)
        {
            for (uint8_t col = 0; col < gCol; ++col)
            {
                uint8_t n = row * gCol + col + 1;
                if (g_indexSize == n)
                {
                    n = 0;
                }

                printf("%d ", n);
            }

            printf("\n");
        }

        printf("index:\n");

        for (uint8_t row = 0; row < gRow; ++row)
        {
            for (uint8_t col = 0; col < gCol; ++col)
            {
                uint8_t n = row * gCol + col;
                printf("%d ", n);
            }

            printf("\n");
        }
        printf("\n");
    }
#endif

    static void
    _make_init(uint8_t *status)
    {
        for (uint8_t i=0; i<g_indexSize - 1; ++i)
        {
            status[i] = i + 1;
        }

        status[g_indexSize - 1] = g_null;
        status[g_indexSize] = g_indexSize - 1;
    }

    static stNextMove
    _calc_to_index_move(int8_t curIndex)
    {
        /*      N-col
     * N-1  N  n + 1
     *      n + col
     */

        assert(0 <= curIndex && curIndex < g_indexSize);

        stNextMove m;
        m.m_len = 0;

        int8_t up    = curIndex - gCol;
        int8_t down  = curIndex + gCol;

        if (up >= 0)
        {
            m.m_toIndex[m.m_len++] = up;
        }

        if (down < g_indexSize)
        {
            m.m_toIndex[m.m_len++] = down;
        }

        if (0 != curIndex % gCol)
        {
            int8_t left  = curIndex - 1;
            m.m_toIndex[m.m_len++] = left;
        }

        int8_t right = curIndex + 1;

        if (right < g_indexSize && 0 != right % gCol)
        {
            m.m_toIndex[m.m_len++] = right;
        }
        uint8_t *beg = m.m_toIndex;
        uint8_t *end = beg + m.m_len;
        std::sort(beg, end);
        return m;
    }

#ifndef NDEBUG
    static bool
    _is_right_mv(uint8_t nullindex, uint8_t toIndex)
    {
        assert(0 <= nullindex && nullindex < g_indexSize);
        assert(0 <= toIndex && toIndex < g_indexSize);

        const stNextMove nextMV = _calc_to_index_move(nullindex);
        for (uint8_t i=0; i<nextMV.m_len; ++i)
        {
            if (nextMV.m_toIndex[i] == toIndex)
            {
                return true;
            }
        }

        return false;
    }
#endif
public:
    //NumStatus() : m_status {0} {}

    void from_array(const uint8_t *arr)
    {
        for (uint8_t i=0; i<g_indexSize; ++i)
        {
            m_status[i] = arr[i];

            if (g_null == arr[i])
            {
                m_status[g_indexSize] = i;
            }
        }
    }

    void init()
    {
        _make_init(m_status);
    }

    bool isDone() const
    {
        return _is_done(m_status);
    }

    uint8_t getNullIndex() const
    {
        return m_status[g_indexSize];
    }

    uint8_t getIndexNum(uint8_t index) const
    {
        assert(index < g_indexSize);
        return m_status[index];
    }

    void move_null(uint8_t toIndex)
    {
        uint8_t nullIndex = getNullIndex();

        assert(_is_right_mv(nullIndex, toIndex));

        std::swap(m_status[nullIndex], m_status[toIndex]);

        assert(g_null == m_status[toIndex]);

        m_status[g_indexSize] = toIndex;
    }

    size_t calc_hash() const
    {
        return std::_Hash_impl::hash(m_status, sizeof (m_status));
    }

    bool equal(const NumStatus &other) const
    {
        return 0 == ::memcmp(m_status, other.m_status, sizeof(m_status));
    }

    void print() const
    {
        for (uint8_t row=0; row<gRow; ++row)
        {
            for (uint8_t col=0; col<gCol; ++col)
            {
                uint8_t n = row * gCol + col;
                assert(n < g_indexSize);
                printf("%2d ", m_status[n]);
            }
            printf("\n");
        }
        printf("null: %d\n", m_status[g_indexSize]);
    }

private:
    uint8_t m_status[g_indexSize + 1];
};

template<typename ST>
struct NumStatusHash
{
    bool operator()(const ST &s1, const ST &s2) const
    {
        return s1.equal(s2);
    }

    size_t operator()(const ST &s1) const
    {
        return s1.calc_hash();
    }
};

struct stMoveNode
{
    const stMoveNode *m_preNode;
    uint8_t m_moveIndex;
    uint8_t m_moveNum;
};


template<uint8_t gRow, uint8_t gCol>
class NumSolver
{
    using ST = NumStatus<gRow, gCol>;
    using Hash = NumStatusHash<ST>;
    using StatusHash = std::unordered_map<ST, stMoveNode, Hash, Hash>;
public:
    void buildAllStatus()
    {

#if 0
        ST::_print_puzzle();
#endif

        std::array<stNextMove, ST::g_indexSize> g_nextMoveList;
        for (uint8_t i=0; i<ST::g_indexSize; ++i)
        {
            g_nextMoveList[i] = ST::_calc_to_index_move(i);
#if 0
            printf("%d to ", i);
            _print_mv(g_nextMoveList[i]);
            printf("\n");
#endif
        }

        // init
        using node_t = typename StatusHash::value_type;
        const node_t *pInitNode;
        {
            ST initSt;
            initSt.init();

#if 0
            printf("init status:\n");
            initSt.print();
#endif

            stMoveNode initMV;
            initMV.m_preNode   = nullptr;
            initMV.m_moveIndex = 0;
            initMV.m_moveNum   = 0;
            auto ret = m_allStatus.emplace(initSt, initMV);
            assert(ret.second);
            pInitNode = ret.first.operator->();
        }

        std::vector<const node_t *> curNodeVec;
        std::vector<const node_t *> nextNodeVec;

        curNodeVec.push_back(pInitNode);

        ST stBuffer;

        int level = 0;
        while (false == curNodeVec.empty())
        {
            assert(true == nextNodeVec.empty());

            for (const node_t *pCurNode : curNodeVec)
            {
                const ST &curSt = pCurNode->first;
                const stMoveNode &curInfo = pCurNode->second;
                auto curNullIndex = curSt.getNullIndex();
                const stNextMove *nextMV = &g_nextMoveList[curNullIndex];
                for (uint8_t i=0; i<nextMV->m_len; ++i)
                {
                    uint8_t toIndex = nextMV->m_toIndex[i];

                    stBuffer = curSt;
                    stBuffer.move_null(toIndex);

                    auto ret = m_allStatus.try_emplace(stBuffer);
                    if (false == ret.second)
                    {
                        continue;
                    }

                    node_t *nextNode = ret.first.operator->();

                    stMoveNode &nextInfo = nextNode->second;
                    nextInfo.m_preNode   = &curInfo;
                    nextInfo.m_moveIndex = toIndex;
                    nextInfo.m_moveNum   = curSt.getIndexNum(toIndex);

                    nextNodeVec.push_back(nextNode);
                }
            }

            printf("level: %d, all: %lu, cur: %lu, next: %lu\n",
                   level, m_allStatus.size(), curNodeVec.size(), nextNodeVec.size());

            curNodeVec.swap(nextNodeVec);
            nextNodeVec.clear();
            level++;
        }
    }

    bool solve(const uint8_t *curStatus, uint8_t nSize) const
    {
        assert(ST::g_indexSize == nSize);
        printf("Num Solver:\n");

        ST st;
        st.from_array(curStatus);

        st.print();

        auto it = m_allStatus.find(st);
        if (it == m_allStatus.end())
        {
            printf("%s", "Error Num Solver: cannot find\n");
            st.print();
            return false;
        }

        const stMoveNode *pNode = &it->second;
        printf("move num list: ");
        size_t n = 0;
        while (pNode->m_preNode)
        {
            printf("%d ",pNode->m_moveNum);
            pNode = pNode->m_preNode;
            ++n;
        }
        printf("step: %lu\n", n);

        return true;
    }
private:
    StatusHash m_allStatus;
};

}

