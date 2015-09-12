/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "qt_treeview.h"

class qt_Instruction;

class qt_InstructionsModel;

class qt_InstructionsView : public qt_TreeView
{
    Q_OBJECT

    qt_InstructionsModel                 *model_;
    std::vector< const qt_Instruction * > selectedInstructions_;

public:
    qt_InstructionsView(QWidget *parent = 0);

    qt_InstructionsModel *model() const
    {
        return model_;
    }

    void setModel(qt_InstructionsModel *model);

    const std::vector<const qt_Instruction *> &selectedInstructions() const
    {
        return selectedInstructions_;
    }

public slots:
    void highlightInstructions(const std::vector< const qt_Instruction * > &instructions, bool ensureVisible = true);
    
    virtual void setDocumentFont(const QFont &font) override;

signals:
    void instructionSelectionChanged();
    void deleteSelectedInstructions();
    void decompileSelectedInstructions();

private slots:
    void updateSelection();
};
