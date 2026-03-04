#include "NineSolver.h"
#include <assert.h>
#include <functional>
#include <unordered_map>
#include <fstream>

using namespace std;

namespace nine_puzzle {

/*  0 1 2
 *  3 4 5
 *  6 7 8
 */

constexpr static uint8_t g_indexSize = 9;

struct stNextMove
{
    const uint8_t  *m_arr;
    const uint8_t   m_len;
};

constexpr const uint8_t g_0[] = {1, 3};
constexpr const uint8_t g_1[] = {0, 2, 4};
constexpr const uint8_t g_2[] = {1, 5};
constexpr const uint8_t g_3[] = {0, 4, 6};
constexpr const uint8_t g_4[] = {1, 3, 5, 7};
constexpr const uint8_t g_5[] = {2, 4, 8};
constexpr const uint8_t g_6[] = {3, 7};
constexpr const uint8_t g_7[] = {4, 6, 8};
constexpr const uint8_t g_8[] = {5, 7};

constexpr stNextMove g_nextMoveList[] =
    {
    {g_0, sizeof(g_0)},
    {g_1, sizeof(g_1)},
    {g_2, sizeof(g_2)},
    {g_3, sizeof(g_3)},
    {g_4, sizeof(g_4)},
    {g_5, sizeof(g_5)},
    {g_6, sizeof(g_6)},
    {g_7, sizeof(g_7)},
    {g_8, sizeof(g_8)},
};

static_assert(sizeof(g_nextMoveList) / sizeof(g_nextMoveList[0]) == g_indexSize, "");

constexpr const char g_finish[g_indexSize + 1] =
    {1, 2, 3, 4, 5, 6, 7, 8, 0, 8};

const uint64_t g_p1 = *reinterpret_cast<const size_t *>(g_finish);
const uint16_t g_p2 = *reinterpret_cast<const size_t *>(g_finish + 8);

#ifndef NDEBUG

bool is_right_mv(uint8_t nullindex, uint8_t toIndex)
{
    assert(0 <= nullindex && nullindex < g_indexSize);
    assert(0 <= toIndex && toIndex < 9);

    const stNextMove *nextMV = &g_nextMoveList[nullindex];
    for (uint8_t i=0; i<nextMV->m_len; ++i)
    {
        if (nextMV->m_arr[i] == toIndex)
        {
            return true;
        }
    }

    return false;
}
#endif

class nineStatus
{
public:
    void init()
    {
        uint64_t *p1 = reinterpret_cast<uint64_t*>(m_status);
        uint16_t *p2 = reinterpret_cast<uint16_t*>(m_status + 8);

        *p1 = g_p1;
        *p2 = g_p2;
    }

    void from_array(const uint8_t *arr)
    {
        for (uint8_t i=0; i<g_indexSize; ++i)
        {
            m_status[i] = arr[i];

            if (0 == arr[i])
            {
                m_status[g_indexSize] = i;
            }
        }
    }

    uint8_t nullIndex() const
    {
        return m_status[g_indexSize];
    }

    uint8_t getIndexNum(uint8_t index) const
    {
        assert( index < g_indexSize);
        return m_status[index];
    }

    bool isDone() const
    {
        const uint64_t *p1 = reinterpret_cast<const uint64_t*>(m_status);
        const uint16_t *p2 = reinterpret_cast<const uint16_t*>(m_status + 8);

        return g_p1 == *p1 && g_p2 == *p2;
    }

    void move_null(uint8_t toIndex)
    {
        uint8_t nullIndex = m_status[g_indexSize];

        assert(is_right_mv(nullIndex, toIndex));

        std::swap(m_status[nullIndex], m_status[toIndex]);

        assert(0 == m_status[toIndex]);

        m_status[g_indexSize] = toIndex;
    }

    size_t calc_hash() const
    {
        return std::_Hash_impl::hash(m_status, sizeof (m_status));
    }

    bool equal(const nineStatus &other) const
    {
        const uint64_t *p1 = reinterpret_cast<const uint64_t*>(m_status);
        const uint16_t *p2 = reinterpret_cast<const uint16_t*>(m_status + 8);
        const uint64_t *p3 = reinterpret_cast<const uint64_t*>(other.m_status);
        const uint16_t *p4 = reinterpret_cast<const uint16_t*>(other.m_status + 8);

        return *p1 == *p3 && *p2 == *p4;
    }

    void print() const
    {
        printf("%d %d %d\n", m_status[0], m_status[1], m_status[2]);
        printf("%d %d %d\n", m_status[3], m_status[4], m_status[5]);
        printf("%d %d %d\n", m_status[6], m_status[7], m_status[8]);
        printf("null: %d\n", m_status[g_indexSize]);
    }
private:
    uint8_t m_status[g_indexSize + 1];
};

struct nineStatusHash
{
    bool operator()(const nineStatus &s1, const nineStatus &s2) const
    {
        return s1.equal(s2);
    }

    size_t operator()(const nineStatus &s1) const
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

using StatusHash = std::unordered_map<nineStatus, stMoveNode, nineStatusHash, nineStatusHash>;

}

static nine_puzzle::StatusHash *
_cast_to(void *p)
{
    return reinterpret_cast<nine_puzzle::StatusHash *>(p);
}

NineSolver::NineSolver()
{
    m_statusData = new nine_puzzle::StatusHash;
}

NineSolver::~NineSolver()
{
    auto p = _cast_to(m_statusData);
    delete p;
}

void NineSolver::buildAllStatus()
{
    using namespace nine_puzzle;
    // init
    using node_t = StatusHash::value_type;

    auto hash = _cast_to(m_statusData);

    const node_t *pInitNode;
    {
        nineStatus initSt;
        initSt.init();

        stMoveNode initMV;
        initMV.m_preNode   = nullptr;
        initMV.m_moveIndex = 0;
        initMV.m_moveNum   = 0;
        auto ret = hash->emplace(initSt, initMV);
        assert(ret.second);
        pInitNode = ret.first.operator->();
    }

    std::vector<const node_t *> curNodeVec;
    std::vector<const node_t *> nextNodeVec;

    curNodeVec.push_back(pInitNode);

    nineStatus stBuffer;

    int level = 0;
    while (false == curNodeVec.empty())
    {
        assert(true == nextNodeVec.empty());

        for (const node_t *pCurNode : curNodeVec)
        {
            const nineStatus &curSt = pCurNode->first;
            const stMoveNode &curInfo = pCurNode->second;
            auto curNullIndex = curSt.nullIndex();
            const stNextMove *nextMV = &g_nextMoveList[curNullIndex];
            for (uint8_t i=0; i<nextMV->m_len; ++i)
            {
                uint8_t toIndex = nextMV->m_arr[i];

                stBuffer = curSt;
                stBuffer.move_null(toIndex);

                auto ret = hash->try_emplace(stBuffer);
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
               level, hash->size(), curNodeVec.size(), nextNodeVec.size());

        curNodeVec.swap(nextNodeVec);
        nextNodeVec.clear();
        level++;
    }
#if 0
    std::ofstream out("all.txt");
    for (const auto &pp : *hash)
    {
        const nineStatus &st = pp.first;
        st.print_array(out);
    }
#endif
}

bool NineSolver::solve(
    const uint8_t *curStatus) const
{
    auto hash = _cast_to(m_statusData);

    nine_puzzle::nineStatus st;
    st.from_array(curStatus);

    st.print();

    auto it = hash->find(st);
    if (it == hash->end())
    {
        printf("%s", "Error: cannot find\n");
        st.print();
        return false;
    }

    const nine_puzzle::stMoveNode *pNode = &it->second;
    printf("move num list: ");
    size_t n = 0;
    while (pNode->m_preNode)
    {
        printf("%d ",pNode->m_moveNum);
        pNode = pNode->m_preNode;
        ++n;
    }
    printf("step: %d\n", n);

    return true;
}
