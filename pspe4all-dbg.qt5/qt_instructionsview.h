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

    qt_InstructionsModel                 * model_;
    std::vector< qt_Instruction const * >  selectedInstructions_;

public:
    qt_InstructionsView(QWidget * parent = 0);

    qt_InstructionsModel * model() const
    {
        return model_;
    }

    void setModel(qt_InstructionsModel * model);

    std::vector< qt_Instruction const * > const & selectedInstructions() const
    {
        return selectedInstructions_;
    }

public slots:
    void highlightInstructions(std::vector< qt_Instruction const * > const & instructions, bool const ensureVisible = true);
    
    virtual void setDocumentFont(QFont const & font) override;

signals:
    void instructionSelectionChanged();
    void deleteSelectedInstructions();
    void decompileSelectedInstructions();

private slots:
    void updateSelection();
};
