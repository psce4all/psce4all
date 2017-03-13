/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <memory> /* std::shared_ptr */
#include <vector>

#include <QAbstractItemModel>

#include "qt_Instruction.h"

class qt_InstructionsModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Columns
    {
        IMC_BACKWARD_JUMP,
        IMC_ADDRESS,
        IMC_OPCODE,
        IMC_INSTRUCTION,
        IMC_FORWARD_JUMP,
        IMC_COMMENT,
        IMC_COUNT
    };

    qt_InstructionsModel(QObject *parent = nullptr, std::shared_ptr< const qt_Instructions > instructions = nullptr, std::shared_ptr< u32 > pc = nullptr);

    void setHighlightedInstructions(std::vector< const qt_Instruction * > instructions);

    const qt_Instruction *getInstruction(const QModelIndex &index) const;
    const std::vector< const qt_Instruction * > &getInstructions() const;

    QModelIndex getIndex(const qt_Instruction *instruction) const;

    int         rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int         columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant    data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

private:
    std::shared_ptr< const qt_Instructions > instructions_;
	std::shared_ptr< u32                   > pc_;
	std::vector< const qt_Instruction *    > instructionsVector_;
    std::vector< const qt_Instruction *    > highlightedInstructions_;
};
