#ifndef LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVMCTARGETDESC_H
#define LLVM_LIB_TARGET_MYRISCV_MCTARGETDESC_MYRISCVMCTARGETDESC_H

#define GET_REGINFO_ENUM
#include "MyRISCVGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "MyRISCVGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "MyRISCVGenSubtargetInfo.inc"

#endif