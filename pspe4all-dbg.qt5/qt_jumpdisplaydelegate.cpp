/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_jumpdisplaydelegate.h"

#include <QPainter>

qt_JumpDisplayDelegate::qt_JumpDisplayDelegate(bool isForward, QObject *parent)
    : m_laneWidth(80 / m_nLanes)
    , m_jumpLanes(isForward)
{
}

void qt_JumpDisplayDelegate::update(const std::vector< const qt_Instruction * > &insnList, unsigned nVisibleInsns)
{
	m_jumpLanes.calculateLanes(insnList, nVisibleInsns);
}

QSize qt_JumpDisplayDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QRect r = option.rect;

	return QSize(85, r.height());
}

void qt_JumpDisplayDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

	qt_JumpTargetDisplay::LaneValue_t lanes[m_nLanes];

	int row = index.row();
	QRect r = option.rect;

    QLinearGradient gradient;

    if (m_jumpLanes.isForward())
    {
        gradient.setStart(r.left() + 5, 0);
        gradient.setFinalStop(r.left() + 85, 0);
    }
    else
    {
        gradient.setStart(r.left() + 80, 0);
        gradient.setFinalStop(r.left(), 0);
    }
    gradient.setColorAt(0.0 / 16., QColor(164, 196, 0));   // Lime
    gradient.setColorAt(1.0 / 16., QColor(96, 169, 23));   // Green
    gradient.setColorAt(2.0 / 16., QColor(0, 138, 0));     // Emerald
    gradient.setColorAt(3.0 / 16., QColor(0, 171, 169));   // Teal
    gradient.setColorAt(4.0 / 16., QColor(27, 161, 226));  // Cyan
    gradient.setColorAt(5.0 / 16., QColor(0, 80, 239));    // Cobalt
    gradient.setColorAt(6.0 / 16., QColor(106, 0, 255));   // Indigo
    gradient.setColorAt(7.0 / 16., QColor(170, 0, 255));   // Violet
    gradient.setColorAt(8.0 / 16., QColor(244, 114, 208)); // Pink
    gradient.setColorAt(9.0 / 16., QColor(216, 0, 115));   // Magenta
    gradient.setColorAt(10. / 16., QColor(162, 0, 37));    // Crimson
    gradient.setColorAt(11. / 16., QColor(229, 20, 0));    // Red
    gradient.setColorAt(12. / 16., QColor(250, 104, 0));   // Orange
    gradient.setColorAt(13. / 16., QColor(240, 163, 10));  // Amber
    gradient.setColorAt(14. / 16., QColor(227, 200, 0));   // Yellow
    gradient.setColorAt(15. / 16., QColor(130, 90, 44));   // Brown

	if (!m_jumpLanes.getLanes(row, lanes))
    {
        memset(lanes, qt_JumpTargetDisplay::LANE_NONE, sizeof(lanes));
    }

	for (unsigned lane = 0; lane < m_nLanes; lane++)
    {
		int x = r.x() + m_laneWidth * lane;
		int w = r.width() / m_nLanes;

		QPen pen(QBrush(gradient), 1);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::FlatCap);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setCosmetic(true);

		painter->setPen(pen);
        painter->setBrush(QBrush(gradient));
        painter->setRenderHint(QPainter::Antialiasing);

		switch (lanes[lane])
		{
        case qt_JumpTargetDisplay::LANE_LINE_DOWN:
            painter->setPen(pen);
            drawLine(painter, false, x, w, &r);
			break;
        case qt_JumpTargetDisplay::LANE_LINE_UP:
            painter->setPen(pen);
            drawLine(painter, true, r.width() - x, w, &r);
            break;
        case qt_JumpTargetDisplay::LANE_END_DOWN:
            painter->setPen(pen);
            drawLineEnd(painter, false, x, w, &r);
			break;
        case qt_JumpTargetDisplay::LANE_END_UP:
            painter->setPen(pen);
            drawLineEnd(painter, true, r.width() - x, w, &r);
			break;
        case qt_JumpTargetDisplay::LANE_START_DOWN:
            painter->setPen(pen);
            drawLineStart(painter, false, x, w, &r);
			break;
        case qt_JumpTargetDisplay::LANE_START_UP:
            painter->setPen(pen);
            drawLineStart(painter, true, r.width() - x, w, &r);
			break;
        case qt_JumpTargetDisplay::LANE_START_LONG_DOWN:
			pen.setStyle(Qt::DotLine);
			painter->setPen(pen);
			drawLineStart(painter, false, x, w, &r);
			break;
        case qt_JumpTargetDisplay::LANE_START_LONG_UP:
			pen.setStyle(Qt::DotLine);
			painter->setPen(pen);
            drawLineStart(painter, true, r.width() - x, w, &r);
			break;
        case qt_JumpTargetDisplay::LANE_END_LONG_DOWN:
			pen.setStyle(Qt::DotLine);
			painter->setPen(pen);
			drawLineEnd(painter, false, x, w, &r);
			break;
        case qt_JumpTargetDisplay::LANE_END_LONG_UP:
			pen.setStyle(Qt::DotLine);
			painter->setPen(pen);
            drawLineEnd(painter, true, r.width() - x, w, &r);
			break;
		default:
			break;
		}
	}
}

void qt_JumpDisplayDelegate::drawLine(QPainter* painter, bool backward, int x, int w, QRect* rect) const
{
    int x1 = backward ? (x - 5 - w / 2) : (5 + x + w / 2);
    int y1 = rect->y();
    int y2 = y1 + rect->height();
	
    painter->drawLine(x1, y1, x1, y2);
}

void qt_JumpDisplayDelegate::drawLineStart(QPainter* painter, bool backward, int x, int w, QRect* rect) const
{
    int x1 = backward ? (x - 5 - w / 2) : (5 + x + w / 2);
    int y1 = rect->y() + rect->height() / 2;
    int y2 = backward ? rect->y() : rect->y() + rect->height();
	
    painter->drawEllipse(x1 - 2, y1 - 2, 4, 4);
	painter->drawLine(x1, y1, x1, y2);
}

void qt_JumpDisplayDelegate::drawLineEnd(QPainter* painter, bool backward, int x, int w, QRect* rect) const
{
    int x1 = backward ? (x - 5 - w / 2) : (5 + x + w / 2);
    int x2 = backward ? rect->x() + rect->width() : rect->x();
    int y1 = backward ? rect->y() + rect->height() : rect->y();
    int y2 = rect->y() + rect->height() / 2;

	int arrowDir = backward ? -1 : 1;
	QPolygon polygon;

    painter->drawLine(x1, y1, x1, y2 - 3 * arrowDir);
    painter->drawLine(x1, y2 - 3 * arrowDir, x1 - 3 * arrowDir, y2);

    QPen pen(painter->pen());
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);

    polygon
        << QPoint(x1 - 3 * arrowDir, y2)
        << QPoint(x2, y2)
		<< QPoint(x2 + 5 * arrowDir, y2 - 5)
		<< QPoint(x2 + 5 * arrowDir, y2 + 5)
		<< QPoint(x2, y2);

	painter->drawPolygon(polygon);
}

class qt_InstructionPair
{
public:
    qt_InstructionPair(const qt_Instruction *start, const qt_Instruction *end, int distance)
        : m_start(start)
        , m_end(end)
        , m_distance((distance < 0) ? -distance : distance)
    {
    }

    const qt_Instruction *m_start;
    const qt_Instruction *m_end;
    unsigned              m_distance;
};

qt_JumpTargetDisplay::qt_JumpTargetDisplay(bool isForward) :
m_isForward(isForward), m_nRows(1)
{
    m_lanes = new LaneValue_t[m_nLanes * m_nRows];
}

qt_JumpTargetDisplay::~qt_JumpTargetDisplay()
{
    delete[] m_lanes;
}

void qt_JumpTargetDisplay::calculateLanes(const std::vector< const qt_Instruction * > &insnList, unsigned nVisibleInsns)
{
    m_nRows = insnList.size();
    m_nVisibleInsns = nVisibleInsns;

    if (m_nRows)
    {
        delete[] m_lanes;

        m_starts.clear();
        m_ends.clear();
        m_insnNrs.clear();
        m_lanes = new LaneValue_t[m_nLanes * m_nRows];

        memset(m_lanes, LANE_INVALID, m_nLanes * m_nRows * sizeof(LaneValue_t));

        InstructionPairList_t pairs;
        std::vector< const qt_Instruction * > srcs;
        std::map< u32, const qt_Instruction * > insnMap;
        unsigned nr = 0;

        for (auto cur : insnList)
        {
            insnMap[cur->addr()] = cur;
            m_insnNrs[cur] = nr;

            if (auto insn = cur->insn())
            {
                if (insn->flags & (INSN_UNCOND_BRANCH_DELAY | INSN_COND_BRANCH_DELAY | INSN_COND_BRANCH_LIKELY))
                {
                    srcs.push_back(cur);
                }
            }
            nr++;
        }

        // Get all pairs
        for (auto start : srcs)
        {
            auto insn = start->insn();
            auto target = (insn->flags & INSN_UNCOND_BRANCH_DELAY) ? (((start->addr() + 4) & 0xF0000000) + (start->data() & 0x03FFFFFF) << 2) : start->addr() + 4 + short(start->data());
            auto end = insnMap[target];

            if (end)
            {
                if (m_isForward)
                {
                    if (target <= start->addr())
                    {
                        continue;
                    }
                }
                else
                {
                    if (target > start->addr())
                    {
                        continue;
                    }
                }

                qt_InstructionPair *pair = new qt_InstructionPair(start, end, m_insnNrs[end] - m_insnNrs[start]);
                pairs.push_back(pair);
                m_starts[start->addr()] = pair;
                m_ends[end->addr()].push_back(pair);
            }
        }

        const qt_Instruction *lanes[m_nLanes];

        memset((void *)lanes, 0, sizeof(const qt_Instruction *) * m_nLanes);

        unsigned row;
        if (m_isForward)
        {
            row = 0;

            for (auto it = insnList.begin(); it != insnList.end(); ++it, ++row)
            {
                auto cur = *it;
                auto curLane = &m_lanes[row * m_nLanes];
                auto startPair = m_starts[cur->addr()];
                auto endPairs = m_ends[cur->addr()];

                if (startPair)
                {
                    allocateLane(startPair->m_start, startPair->m_end, lanes);
                }

                fillLane(curLane, cur, lanes);

                for (auto p : endPairs)
                {
                    deallocateLane(p->m_start, p->m_end, lanes);
                }
            }
        }
        else
        {
            row = insnList.size() - 1;

            for (auto it = insnList.rbegin(); it != insnList.rend(); ++it, --row)
            {
                auto cur = *it;
                auto curLane = &m_lanes[row * m_nLanes];
                auto startPair = m_starts[cur->addr()];
                auto endPairs = m_ends[cur->addr()];

                if (startPair)
                {
                    allocateLane(startPair->m_start, startPair->m_end, lanes);
                }

                fillLane(curLane, cur, lanes);

                for (auto p : endPairs)
                {
                    deallocateLane(p->m_start, p->m_end, lanes);
                }
            }
        }

        for (auto p : pairs)
        {
            delete p;
        }
    }
}

void qt_JumpTargetDisplay::fillLane(LaneValue_t *curRow, const qt_Instruction *cur, const qt_Instruction **lanes)
{
    auto ends = m_ends[cur->addr()];
    auto start = m_starts[cur->addr()];

    for (unsigned i = 0; i < m_nLanes - 1; i++)
    {
        auto p = lanes[i];

        if (p)
        {
            if (start && cur == start->m_start && p == start->m_start)
            {
                curRow[i] = m_isForward ? LANE_START_DOWN : LANE_START_UP;
            }
            else if (!ends.empty())
            {
                bool found = false;

                for (auto e : ends)
                {
                    if (e->m_end == cur && p == e->m_start && e->m_distance < m_nVisibleInsns)
                    {
                        curRow[i] = m_isForward ? LANE_END_DOWN : LANE_END_UP;
                        found = true;
                    }

                    if (!found)
                    {
                        curRow[i] = m_isForward ? LANE_LINE_DOWN : LANE_LINE_UP;
                    }
                }
            }
            else
            {
                curRow[i] = m_isForward ? LANE_LINE_DOWN : LANE_LINE_UP;
            }
        }
        else
        {
            curRow[i] = LANE_NONE;
        }
    }

    if (start && start->m_distance >= m_nVisibleInsns)
    {
        curRow[m_nLanes - 1] = m_isForward ? LANE_START_LONG_DOWN : LANE_START_LONG_UP;
    }
    else if (!ends.empty())
    {
        bool found = false;

        for (auto e : ends)
        {
            if (e->m_end == cur && e->m_distance > m_nVisibleInsns)
            {
                curRow[m_nLanes - 1] = m_isForward ? LANE_END_LONG_DOWN : LANE_END_LONG_UP;
                found = true;
            }
        }

        if (!found)
        {
            curRow[m_nLanes - 1] = LANE_NONE;
        }
    }
    else
    {
        curRow[m_nLanes - 1] = LANE_NONE;
    }
}

void qt_JumpTargetDisplay::allocateLane(const qt_Instruction *start, const qt_Instruction *end, const qt_Instruction **lanes)
{
    if (start && end)
    {
        int distance = m_insnNrs[end] - m_insnNrs[start];

        if (distance < 0)
        {
            distance = -distance;
        }

        // Too large
        if (distance <= (int)m_nVisibleInsns)
        {
            unsigned i;

            for (i = 0; i < m_nLanes - 1; i++)
            {
                auto cur = lanes[i];
                if (!cur)
                {
                    break;
                }
            }
            // Can't fit this one, so skip it
            if (i != m_nLanes - 1)
            {
                lanes[i] = start;
            }
        }
    }
}

void qt_JumpTargetDisplay::deallocateLane(const qt_Instruction *start, const qt_Instruction *end, const qt_Instruction **lanes)
{
    if (start && end)
    {
        unsigned i;

        for (i = 0; i < m_nLanes - 1; i++)
        {
            if (lanes[i] == start)
            {
                break;
            }
        }

        if (i != m_nLanes - 1)
        {
            lanes[i] = nullptr;
        }
    }
}

bool qt_JumpTargetDisplay::getLanes(unsigned insnNr, qt_JumpTargetDisplay::LaneValue_t *lanesOut) const
{
    if (insnNr < m_nRows)
    {
        memcpy(lanesOut, &m_lanes[insnNr * m_nLanes], m_nLanes * sizeof(LaneValue_t));
        return true;
    }
    return false;
}
