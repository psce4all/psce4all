/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_instructionsview.h"

#include <QTreeView>

#include "qt_Instruction.h" 
#include "qt_instructionsmodel.h"
#include "qt_JumpDisplayDelegate.h"

#include "qt_logview.h"

qt_InstructionsView::qt_InstructionsView(QWidget *parent)
    : qt_TreeView(tr("Instructions"), parent)
    , model_(nullptr)
{
    treeView()->setHeaderHidden(true);
    treeView()->setItemsExpandable(false);
    treeView()->setRootIsDecorated(false);
    treeView()->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeView()->setSelectionMode(QAbstractItemView::ExtendedSelection);
    treeView()->setUniformRowHeights(true);
}

void qt_InstructionsView::setModel(qt_InstructionsModel *model)
{
    if (model != model_)
    {
        model_ = model;
        treeView()->setModel(model);

        zoomIn(0); // *sigh* too tired to understand why without doing that call I get wrong column width initially...

        connect(treeView()->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this](QItemSelection const &, QItemSelection const &) { updateSelection(); });

        updateSelection();
    }
}

void qt_InstructionsView::updateSelection()
{
    std::vector< const qt_Instruction * > instructions;

    bool needUpdate = false;

    if (model())
    {
        /*
        foreach (const QModelIndex &index, treeView()->selectionModel()->selectedIndexes())
        {
            // Process every row only once.
            if (index.column() == 0)
            {
                if (const qt_Instruction *instruction = model()->getInstruction(index))
                {
                    auto row = index.row();

                    // Some instructions should be handled in a group
                    for (auto size = instruction->size(); size > 4; size -= 4)
                    {
                        __debugbreak();

                        auto nextIndex = index.sibling(++row, 0);
                        if (nextIndex.isValid())
                        {
                            treeView()->selectionModel()->select(nextIndex, QItemSelectionModel::Select);
                        }
                    }
                }
            }
        }
        */

        foreach (QModelIndex const & index, treeView()->selectionModel()->selectedIndexes())
        {
            // Process every row only once.
            if (index.column() == 0)
            {
                if (qt_Instruction const * instruction = model()->getInstruction(index))
                {
                    if (!instruction->checkData())
                    {
                        needUpdate = true;
                    }
                    instructions.push_back(instruction);
                }
            }
        }
    }

    if (selectedInstructions_ != instructions || needUpdate)
    {
        selectedInstructions_.swap(instructions);
        emit instructionSelectionChanged();
    }
}

void qt_InstructionsView::highlightInstructions(std::vector< qt_Instruction const * > const & instructions, bool const ensureVisible)
{
    if (model())
    {
        model()->setHighlightedInstructions(instructions);

        if (ensureVisible && !instructions.empty())
        {
            treeView()->scrollTo(model()->getIndex(instructions.back()));
        }
    }
}

void qt_InstructionsView::setDocumentFont(QFont const & font)
{
    qt_TreeView::setDocumentFont(font);

    treeView()->resizeColumnToContents(qt_InstructionsModel::IMC_BACKWARD_JUMP);
    treeView()->resizeColumnToContents(qt_InstructionsModel::IMC_ADDRESS);
    treeView()->resizeColumnToContents(qt_InstructionsModel::IMC_OPCODE);
    treeView()->resizeColumnToContents(qt_InstructionsModel::IMC_INSTRUCTION);
    treeView()->resizeColumnToContents(qt_InstructionsModel::IMC_ADDRESS);
    treeView()->resizeColumnToContents(qt_InstructionsModel::IMC_FORWARD_JUMP);
    treeView()->resizeColumnToContents(qt_InstructionsModel::IMC_COMMENT);
}
