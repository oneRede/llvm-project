#include "MyRISCVTargetMachine.h"
#include "MyRISCV.h"
#include "TargetInfo/MyRISCVTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

using namespace llvm;

namespace {

class MyRISCVPassConfig : public TargetPassConfig {
public:
  MyRISCVPassConfig(MyRISCVTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  bool addInstSelector() override {
    addPass(createMyRISCVISelDag(getMyRISCVTargetMachine()));
    return false;
  }

private:
  MyRISCVTargetMachine &getMyRISCVTargetMachine() const {
    return getTM<MyRISCVTargetMachine>();
  }
};

StringRef computeDataLayout(const Triple &TT) {
  assert(TT.isArch32Bit() && "Only RV32 is currently supported!");
  return "e-m:e-p:32:32-i64:64-n32-S128";
}

Reloc::Model getEffectiveRelocModel(std::optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

} // end anonymous namespace

MyRISCVTargetMachine::MyRISCVTargetMachine(const Target &T, const Triple &TT,
                                           StringRef CPU, StringRef FS,
                                           const TargetOptions &Options,
                                           std::optional<Reloc::Model> RM,
                                           std::optional<CodeModel::Model> CM,
                                           CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        getEffectiveRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      Subtarget(TT, CPU, CPU, FS, *this),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

TargetPassConfig *MyRISCVTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new MyRISCVPassConfig(*this, PM);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMyRISCVTarget() {
  RegisterTargetMachine<MyRISCVTargetMachine> X(getMyRISCV32Target());
}