#ifndef LLVM_LIB_TARGET_MYRISCV_TARGETINFO_MYRISCVTARGETINFO_H
#define LLVM_LIB_TARGET_MYRISCV_TARGETINFO_MYRISCVTARGETINFO_H

namespace llvm {

class Target;

Target &getMyRISCV32Target();

} // end namespace llvm

#endif