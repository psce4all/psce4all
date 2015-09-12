/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "qt_instruction.h"

#include <unordered_map>
#include <list>

class qt_InstructionPair;

typedef std::list< qt_InstructionPair * > InstructionPairList_t;
typedef std::unordered_map< uint64_t, qt_InstructionPair *> InstructionPairStartMap_t;
typedef std::unordered_map< uint64_t, std::list< qt_InstructionPair * > > InstructionPairEndMap_t;

class qt_JumpTargetDisplay
{
public:
    typedef enum
    {
        LANE_NONE,
        LANE_LINE_DOWN,
        LANE_LINE_UP,
        LANE_START_DOWN,
        LANE_START_UP,
        LANE_START_LONG_UP,
        LANE_START_LONG_DOWN,
        LANE_END_DOWN,
        LANE_END_UP,
        LANE_END_LONG_DOWN,
        LANE_END_LONG_UP,

        LANE_INVALID,

        LANE_N_VALUES,
    } LaneValue_t;

    qt_JumpTargetDisplay(bool isForward);

    ~qt_JumpTargetDisplay();

    void calculateLanes(const std::vector< const qt_Instruction * > &insnList, unsigned nVisibleInsns);

    bool getLanes(unsigned insnNr, LaneValue_t *lanesOut) const;

    bool const isForward() const { return m_isForward; }

private:
    typedef std::unordered_map< const qt_Instruction *, unsigned > InstructionNrMap_t;

    void allocateLane(const qt_Instruction *start, const qt_Instruction *end, const qt_Instruction **lanes);
    void deallocateLane(const qt_Instruction *start, const qt_Instruction *end, const qt_Instruction **lanes);

    void fillLane(LaneValue_t *curRow, const qt_Instruction *cur, const qt_Instruction **lanes);

    bool                      m_isForward;
    unsigned                  m_nRows;
    LaneValue_t              *m_lanes;
    InstructionNrMap_t        m_insnNrs;
    InstructionPairStartMap_t m_starts;
    InstructionPairEndMap_t   m_ends;
    unsigned                  m_nVisibleInsns;
    static const unsigned int m_nLanes = 8;
};

#include <QItemDelegate>

class qt_JumpDisplayDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
    qt_JumpDisplayDelegate(bool isForward, QObject *parent = 0);

    void  update(const std::vector< const qt_Instruction * > &insnList, unsigned nVisibleInsns);
	void  paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    void  drawLine(QPainter *painter, bool backward, int x, int w, QRect *rect) const;
	void  drawLineStart(QPainter *painter, bool backward, int x, int w, QRect *rect) const;
    void  drawLineEnd(QPainter *painter, bool backward, int x, int w, QRect *rect) const;


    static const unsigned int m_nLanes = 8;
	unsigned int              m_laneWidth;
	qt_JumpTargetDisplay      m_jumpLanes;
};

