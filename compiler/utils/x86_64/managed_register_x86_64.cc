/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "managed_register_x86_64.h"

#include "globals.h"

namespace art {
namespace x86_64 {


std::ostream& operator<<(std::ostream& os, const RegisterPair& reg) {
  os << X86_64ManagedRegister::FromRegisterPair(reg);
  return os;
}

bool X86_64ManagedRegister::Overlaps(const X86_64ManagedRegister& other) const {
  if (IsNoRegister() || other.IsNoRegister()) return false;
  CHECK(IsValidManagedRegister());
  CHECK(other.IsValidManagedRegister());
  if (Equals(other)) return true;
  if (IsRegisterPair()) {
    Register low = AsRegisterPairLow().AsRegister();
    Register high = AsRegisterPairHigh().AsRegister();
    return X86_64ManagedRegister::FromCpuRegister(low).Overlaps(other) ||
        X86_64ManagedRegister::FromCpuRegister(high).Overlaps(other);
  }
  if (other.IsRegisterPair()) {
    return other.Overlaps(*this);
  }
  return false;
}


void X86_64ManagedRegister::Print(std::ostream& os) const {
  if (!IsValidManagedRegister()) {
    os << "No Register";
  } else if (IsXmmRegister()) {
    os << "XMM: " << static_cast<int>(AsXmmRegister().AsFloatRegister());
  } else if (IsX87Register()) {
    os << "X87: " << static_cast<int>(AsX87Register());
  } else if (IsCpuRegister()) {
    os << "CPU: " << static_cast<int>(AsCpuRegister().AsRegister());
  } else if (IsRegisterPair()) {
    os << "Pair: " << AsRegisterPairLow() << ", " << AsRegisterPairHigh();
  } else {
    os << "??: " << RegId();
  }
}

std::ostream& operator<<(std::ostream& os, const X86_64ManagedRegister& reg) {
  reg.Print(os);
  return os;
}

}  // namespace x86_64
}  // namespace art
