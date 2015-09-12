/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <memory> /* std::shared_ptr */
#include <vector>
#include <map>
#include <unordered_map>
#include <cstddef>

#include "Allegrex.h"
#include "capstone.h"
#include "hal.os.Module.h"

namespace capstone
{
    static hal::os::Module module("capstone.dll");

    static auto Open = (cs_err(*)(cs_arch arch, cs_mode mode, csh * handle))module["cs_open"];
    static auto Close = (cs_err(*)(csh * handle))module["cs_close"];
    static auto Free = (void(*)(cs_insn * insn, size_t count))module["cs_free"];
    static auto Malloc = (cs_insn * (*)(csh ud))module["cs_malloc"];
    static auto Disasm = (bool(*)(csh ud, const uint8_t ** code, size_t * size, uint64_t * address, cs_insn * insn))module["cs_disasm_iter"];

    static char * Disassemble(char * out, cs_insn & insn, bool use_underscore = false)
    {
        char address[32];

        sprintf(address, "%08llX(%2d):", insn.address, insn.size);

        char bytes[64], *p = bytes;

        for (size_t i = 0; i < insn.size; ++i)
        {
            p += sprintf(p, "%02X", size_t(insn.bytes[insn.size - i - 1]));
        }

        if (use_underscore)
        {
            static const char u[] = "................................................................";
            sprintf(out, "%s<font color=\"#EEEEEE\">%s</font>%s <i>%s %s</i><font color=\"#EEEEEE\">%s</font>", address, &u[32 + strlen(bytes)], bytes, insn.mnemonic, insn.op_str, &u[1 + strlen(insn.mnemonic) + strlen(insn.op_str)]);
        }
        else
        {
            sprintf(out, "%s %32s %-16s %s", address, bytes, insn.mnemonic, insn.op_str);
        }

        return out;
    }
}


class qt_Instruction
{
    u32                                 addr_;
    u32                                 data_;
    size_t                              size_;
    const allegrex_instruction mutable *insn_;
    size_t                              addr_x86_64_;
    size_t                              size_x86_64_;

public:
    qt_Instruction(u32 addr = 0, u32 data = 0, size_t size = 0, size_t addr_x86_64 = 0, size_t size_x86_64 = 0)
        : addr_(addr)
        , data_(data)
        , size_(size)
        , insn_(nullptr)
        , addr_x86_64_(addr_x86_64)
        , size_x86_64_(size_x86_64)
    {
        assert(size >= 0);
    }

    ~qt_Instruction()
    {
    }

    u32 addr() const
    {
        return addr_;
    }

    size_t addr_x86_64() const
    {
        return addr_x86_64_;
    }

    void setAddr(u32 addr)
    {
        addr_ = addr;
    }

    void setAddr_x86_64(size_t addr)
    {
        addr_x86_64_ = addr;
    }

    u32 data() const
    {
        return data_;
    }

    void setData(u32 data)
    {
        data_ = data;
    }

    bool checkData() const
    {
        return data_ == *p32u32(addr_);
    }

    size_t size() const
    {
        return size_;
    }

    size_t size_x86_64() const
    {
        return size_x86_64_;
    }

    void setSize(size_t size)
    {
        assert(size > 0);
        size_ = size;
    }

    void setSize_x86_64(size_t size)
    {
        assert(size > 0);
        size_x86_64_ = size;
    }

    u32 endAddr() const
    {
        return addr_ + size_;
    }

    const allegrex_instruction *insn() const
    {
        if (insn_)
        {
            return insn_;
        }
        return insn_ = allegrex_decode_instruction(data_, 1);
    }
    
    QString toString() const
    {
        if (auto opcd = insn())
        {
            return allegrex_disassemble_instruction(opcd, data_, addr_, false);
        }
        return QString();
    }

    bool operator < (const qt_Instruction &rhs) const
    {
        return addr() < rhs.addr();
    }
};

typedef std::map< u32, qt_Instruction > qt_Instructions;

