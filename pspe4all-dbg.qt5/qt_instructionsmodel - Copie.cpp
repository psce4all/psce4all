/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_FunctionsModel.h"

#include <algorithm>

#include <QColor>

qt_FunctionsModel::qt_FunctionsModel(QObject *parent, std::shared_ptr< const qt_Instructions > instructions)
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

void qt_FunctionsModel::setHighlightedInstructions(std::vector< const qt_Instruction * > instructions)
{
    beginResetModel();

    std::sort(instructions.begin(), instructions.end());
    highlightedInstructions_ = std::move(instructions);

    endResetModel();
}

const qt_Instruction *qt_FunctionsModel::getInstruction(const QModelIndex &index) const
{
    return static_cast< const qt_Instruction * >(index.internalPointer());
}

QModelIndex qt_FunctionsModel::getIndex(const qt_Instruction *instruction) const
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

int qt_FunctionsModel::rowCount(const QModelIndex &parent) const
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

int qt_FunctionsModel::columnCount(const QModelIndex & /*parent*/) const
{
    return IMC_COUNT;
}

QModelIndex qt_FunctionsModel::index(int row, int column, const QModelIndex &parent) const
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

QModelIndex qt_FunctionsModel::parent(const QModelIndex & /*index*/) const
{
    return QModelIndex();
}

QVariant qt_FunctionsModel::data(const QModelIndex &index, int role) const
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

const std::vector< const qt_Instruction * > &qt_FunctionsModel::getInstructions() const
{
    return instructionsVector_;
}
#if 0

#include "functionanalysis.h"
#include "console.h"
#include "memory.h"
#include "function.h"

FunctionAnalysis::FunctionAnalysis(uint base, uint size)
{
    _base = base;
    _size = size;
    _data = new unsigned char[_size + MAX_DISASM_BUFFER];
    MemRead((void*)_base, _data, _size, 0);
}

FunctionAnalysis::~FunctionAnalysis()
{
    delete[] _data;
}

const unsigned char* FunctionAnalysis::TranslateAddress(uint addr)
{
    return (addr >= _base && addr < _base + _size) ? _data + (addr - _base) : nullptr;
}

void FunctionAnalysis::Analyse()
{
    dputs("analysis started...");
    DWORD ticks = GetTickCount();

    PopulateReferences();
    dprintf("%u called functions populated\n", _functions.size());
    AnalyseFunctions();

    dprintf("analysis finished in %ums!\n", GetTickCount() - ticks);
}

void FunctionAnalysis::SetMarkers()
{
    FunctionDelRange(_base, _base + _size);
    for(auto & function : _functions)
    {
        if(!function.end)
            continue;
        FunctionAdd(function.start, function.end, false);
    }
}

void FunctionAnalysis::SortCleanup()
{
    //sort & remove duplicates
    std::sort(_functions.begin(), _functions.end());
    auto last = std::unique(_functions.begin(), _functions.end());
    _functions.erase(last, _functions.end());
}

void FunctionAnalysis::PopulateReferences()
{
    //linear immediate reference scan (call <addr>, push <addr>, mov [somewhere], <addr>)
    for(uint i = 0; i < _size;)
    {
        uint addr = _base + i;
        if(_cp.Disassemble(addr, TranslateAddress(addr), MAX_DISASM_BUFFER))
        {
            uint ref = GetReferenceOperand();
            if(ref)
                _functions.push_back({ ref, 0 });
            i += _cp.Size();
        }
        else
            i++;
    }
    SortCleanup();
}

void FunctionAnalysis::AnalyseFunctions()
{
    for(size_t i = 0; i < _functions.size(); i++)
    {
        FunctionInfo & function = _functions[i];
        if(function.end)  //skip already-analysed functions
            continue;
        uint maxaddr = _base + _size;
        if(i < _functions.size() - 1)
            maxaddr = _functions[i + 1].start;

        //dprintf("analysing function %p-??? maxaddr: %p\n", function.start, maxaddr);
        uint end = FindFunctionEnd(function.start, maxaddr);
        if(end)
            function.end = end;
    }
}

uint FunctionAnalysis::FindFunctionEnd(uint start, uint maxaddr)
{
    //disassemble first instruction for some heuristics
    if(_cp.Disassemble(start, TranslateAddress(start), MAX_DISASM_BUFFER))
    {
        //JMP [123456] ; import
        if(_cp.InGroup(CS_GRP_JUMP) && _cp.x86().operands[0].type == X86_OP_MEM)
            return 0;
    }

    //linear search with some trickery
    uint end = 0;
    uint jumpback = 0;
    for(uint addr = start, fardest = 0; addr < maxaddr;)
    {
        if(_cp.Disassemble(addr, TranslateAddress(addr), MAX_DISASM_BUFFER))
        {
            if(addr + _cp.Size() > maxaddr)  //we went past the maximum allowed address
                break;

            const cs_x86_op & operand = _cp.x86().operands[0];
            if(_cp.InGroup(CS_GRP_JUMP) && operand.type == X86_OP_IMM)   //jump
            {
                uint dest = (uint)operand.imm;

                if(dest >= maxaddr)   //jump across function boundaries
                {
                    //currently unused
                }
                else if(dest > addr && dest > fardest)   //save the farthest JXX destination forward
                {
                    fardest = dest;
                }
                else if(end && dest < end && _cp.GetId() == X86_INS_JMP)   //save the last JMP backwards
                {
                    jumpback = addr;
                }
            }
            else if(_cp.InGroup(CS_GRP_RET))   //possible function end?
            {
                end = addr;
                if(fardest < addr)  //we stop if the farthest JXX destination forward is before this RET
                    break;
            }

            addr += _cp.Size();
        }
        else
            addr++;
    }
    return end < jumpback ? jumpback : end;
}

uint FunctionAnalysis::GetReferenceOperand()
{
    for(int i = 0; i < _cp.x86().op_count; i++)
    {
        const cs_x86_op & operand = _cp.x86().operands[i];
        if(_cp.InGroup(CS_GRP_JUMP))  //skip jumps
            continue;
        if(operand.type == X86_OP_IMM)  //we are looking for immediate references
        {
            uint dest = (uint)operand.imm;
            if(dest >= _base && dest < _base + _size)
                return dest;
        }
    }
    return 0;
}

#endif
