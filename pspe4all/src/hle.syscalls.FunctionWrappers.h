////////////////////////////////////////////////////////////////////////////////
/// This file is auto-generated from pspe4all-nidgen version 0.3
///
#ifndef hle_syscalls_FunctionWrappers_h__
#define hle_syscalls_FunctionWrappers_h__
#include "hle.syscalls.Modules.h"

namespace hle
{
    namespace syscalls
    {
        template< void F(                                                            ) > __forceinline void FunctionWrapper$0               (Allegrex::Context &  ) { F(); }
        template< void F(u32                                                         ) > __forceinline void FunctionWrapper$0g              (Allegrex::Context & c) { F(c.gpr[4]); }
        template< void F(u32, u32                                                    ) > __forceinline void FunctionWrapper$0gg             (Allegrex::Context & c) { F(c.gpr[4], c.gpr[5]); }
        template< void F(u32, u32, u32, u32                                          ) > __forceinline void FunctionWrapper$0gggg           (Allegrex::Context & c) { F(c.gpr[4], c.gpr[5], c.gpr[6], c.gpr[7]); }
        template< s64  F(                                                            ) > __forceinline void FunctionWrapper$G               (Allegrex::Context & c) { *((u64 *)&c.gpr[2]) = (u64) F(); }
        template< s64  F(u32                                                         ) > __forceinline void FunctionWrapper$Gg              (Allegrex::Context & c) { *((u64 *)&c.gpr[2]) = (u64) F(c.gpr[4]); }
        template< s64  F(u32, u64                                                    ) > __forceinline void FunctionWrapper$GgG             (Allegrex::Context & c) { *((u64 *)&c.gpr[2]) = (u64) F(c.gpr[4], *((u64 *)&c.gpr[6])); }
        template< s64  F(u32, u64, u32                                               ) > __forceinline void FunctionWrapper$GgGg            (Allegrex::Context & c) { *((u64 *)&c.gpr[2]) = (u64) F(c.gpr[4], *((u64 *)&c.gpr[6]), c.gpr[8]); }
        template< f32  F(                                                            ) > __forceinline void FunctionWrapper$f               (Allegrex::Context & c) { c.fpr[0] = (f32) F(); }
        template< int  F(                                                            ) > __forceinline void FunctionWrapper$g               (Allegrex::Context & c) { c.gpr[2] = (u32) F(); }
        template< int  F(u64, u32, u32                                               ) > __forceinline void FunctionWrapper$gGgg            (Allegrex::Context & c) { c.gpr[2] = (u32) F(*((u64 *)&c.gpr[4]), c.gpr[6], c.gpr[7]); }
        template< int  F(u32                                                         ) > __forceinline void FunctionWrapper$gg              (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4]); }
        template< int  F(u32, u64, u32, u32                                          ) > __forceinline void FunctionWrapper$ggGgg           (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4], *((u64 *)&c.gpr[6]), c.gpr[8], c.gpr[9]); }
        template< int  F(u32, u32                                                    ) > __forceinline void FunctionWrapper$ggg             (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4], c.gpr[5]); }
        template< int  F(u32, u32, u64                                               ) > __forceinline void FunctionWrapper$gggG            (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4], c.gpr[5], *((u64 *)&c.gpr[6])); }
        template< int  F(u32, u32, u32                                               ) > __forceinline void FunctionWrapper$gggg            (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4], c.gpr[5], c.gpr[6]); }
        template< int  F(u32, u32, u32, u32                                          ) > __forceinline void FunctionWrapper$ggggg           (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4], c.gpr[5], c.gpr[6], c.gpr[7]); }
        template< int  F(u32, u32, u32, u32, u32                                     ) > __forceinline void FunctionWrapper$gggggg          (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4], c.gpr[5], c.gpr[6], c.gpr[7], c.gpr[8]); }
        template< int  F(u32, u32, u32, u32, u32, u32                                ) > __forceinline void FunctionWrapper$ggggggg         (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4], c.gpr[5], c.gpr[6], c.gpr[7], c.gpr[8], c.gpr[9]); }
        template< int  F(u32, u32, u32, u32, u32, u32, u32                           ) > __forceinline void FunctionWrapper$gggggggg        (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4], c.gpr[5], c.gpr[6], c.gpr[7], c.gpr[8], c.gpr[9], c.gpr[10]); }
        template< int  F(u32, u32, u32, u32, u32, u32, u32, u32                      ) > __forceinline void FunctionWrapper$ggggggggg       (Allegrex::Context & c) { c.gpr[2] = (u32) F(c.gpr[4], c.gpr[5], c.gpr[6], c.gpr[7], c.gpr[8], c.gpr[9], c.gpr[10], c.gpr[11]); }
    }
}
#endif