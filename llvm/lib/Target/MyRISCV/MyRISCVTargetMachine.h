#ifndef LLVM_LIB_TARGET_MYRISCV_MYRISCVTARGETMACHINE_H
#define LLVM_LIB_TARGET_MYRISCV_MYRISCVTARGETMACHINE_H

#include "MyRISCVSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

namespace llvm {

class MyRISCVTargetMachine : public CodeGenTargetMachineImpl {
  MyRISCVSubtarget Subtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  MyRISCVTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT);
  const MyRISCVSubtarget *getSubtargetImpl(const Function &F) const override {
    return &Subtarget;
  }

  const MyRISCVSubtarget *getSubtargetImpl() const { return &Subtarget; }

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

} // end namespace llvm

#endif