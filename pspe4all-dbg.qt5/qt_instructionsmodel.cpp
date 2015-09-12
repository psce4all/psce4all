/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_instructionsmodel.h"

#include <algorithm>

#include <QColor>

qt_InstructionsModel::qt_InstructionsModel(QObject *parent, std::shared_ptr< const qt_Instructions > instructions)
    : QAbstractItemModel(parent)
    , instructions_(std::move(instructions))
{
    std::vector< const qt_Instruction * > vector;

    if (instructions_)
    {
        instructionsVector_.reserve(instructions_->size());

        for (auto const &instruction : *instructions_.get())
        {
            instructionsVector_.push_back(&instruction.second);
        }
    }
}

void qt_InstructionsModel::setHighlightedInstructions(std::vector< const qt_Instruction * > instructions)
{
    beginResetModel();

    std::sort(instructions.begin(), instructions.end());
    highlightedInstructions_ = std::move(instructions);

    endResetModel();
}

const qt_Instruction *qt_InstructionsModel::getInstruction(const QModelIndex &index) const
{
    return static_cast< const qt_Instruction * >(index.internalPointer());
}

QModelIndex qt_InstructionsModel::getIndex(const qt_Instruction *instruction) const
{
    assert(instruction);

    auto i = std::lower_bound(instructionsVector_.begin(), instructionsVector_.end(), instruction, [](const qt_Instruction *a, const qt_Instruction *b)
    {
        return a->addr() < b->addr();
    });

    if (i != instructionsVector_.end() && *i == instruction)
    {
        return index(i - instructionsVector_.begin(), 0, QModelIndex());
    }
    else
    {
        return QModelIndex();
    }
}

int qt_InstructionsModel::rowCount(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
    {
        return instructionsVector_.size();
    }
    else
    {
        return 0;
    }
}

int qt_InstructionsModel::columnCount(const QModelIndex & /*parent*/) const
{
    return IMC_COUNT;
}

QModelIndex qt_InstructionsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row < rowCount(parent))
    {
        return createIndex(row, column, const_cast< qt_Instruction * >(instructionsVector_[row]));
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex qt_InstructionsModel::parent(const QModelIndex & /*index*/) const
{
    return QModelIndex();
}

QVariant qt_InstructionsModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        auto instruction = getInstruction(index);
        assert(instruction);

        switch (index.column())
        {
        case IMC_ADDRESS:
            return tr("%1").arg(instruction->addr(), 8, 16, QChar('0')).toUpper();
        case IMC_OPCODE:
            return tr("%1").arg(*p32u32(instruction->addr()), 8, 16, QChar('0')).toUpper();
        case IMC_BACKWARD_JUMP:
            break;
        case IMC_INSTRUCTION:
            return tr("%1").arg(instruction->toString());
        case IMC_FORWARD_JUMP:
            break;
        default:
            break;
        }
    }
    else if (role == Qt::BackgroundRole)
    {
        auto instruction = getInstruction(index);
        assert(instruction);

        if (std::binary_search(highlightedInstructions_.begin(), highlightedInstructions_.end(), instruction))
        {
            return QColor(Qt::lightGray);
        }
        else if (index.column() == IMC_ADDRESS)
        {
            return QColor(Qt::lightGray);
        }
    }
    else if (role == Qt::ToolTipRole)
    {
        auto instruction = getInstruction(index);
        assert(instruction);

        if (index.column() == IMC_INSTRUCTION)
        {
            QString tooltip;
            if (instruction->addr_x86_64())
            {
                csh handle;
                if (capstone::Open)
                {
                    cs_err err = capstone::Open(CS_ARCH_X86, CS_MODE_64, &handle);

                    if (CS_ERR_OK == err)
                    {
                        char out[256];
                        auto insn = (cs_insn *)capstone::Malloc(handle);
                        auto address = (u8 const *)instruction->addr_x86_64();
                        auto left = instruction->size_x86_64();
                        auto offset = u64(address);

                        //return QString("64-bit x86 instructions at address %1, byte-length is %2").arg(instruction->addr_x86_64(), 8, 16, QChar('0')).arg(instruction->size_x86_64());

                        tooltip.append("<nobr><pre>");

                        while (left)
                        {
                            auto previous_size = left;

                            if (capstone::Disasm(handle, &address, &left, &offset, insn))
                            {
                                capstone::Disassemble(out, *insn, true);

                                tooltip.append(QString("<code>"));
                                tooltip.append(QString(out));
                                tooltip.append(QString("</code><br>"));
                            }
                            else
                            {
                                break;
                            }
                        }

                        tooltip.append("</pre></nobr>");
                    }
                    else
                    {
                        return QString("invalid capstone.dll");
                    }

                    capstone::Close(&handle);
                }
                else
                {
                    return QString("no capstone.dll loaded");
                }

                return tooltip;
            }
            return QVariant();
        }
    }
    return QVariant();
}

const std::vector< const qt_Instruction * > &qt_InstructionsModel::getInstructions() const
{
    return instructionsVector_;
}
