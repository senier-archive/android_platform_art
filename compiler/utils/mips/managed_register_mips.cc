/*
 * Copyright (C) 2011 The Android Open Source Project
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

#include "managed_register_mips.h"

#include "globals.h"

namespace art {
namespace mips {

bool MipsManagedRegister::Overlaps(const MipsManagedRegister& other) const {
  if (IsNoRegister() || other.IsNoRegister()) return false;
  CHECK(IsValidManagedRegister());
  CHECK(other.IsValidManagedRegister());
  if (Equals(other)) return true;
  if (IsRegisterPair()) {
    Register low = AsRegisterPairLow();
    Register high = AsRegisterPairHigh();
    return MipsManagedRegister::FromCoreRegister(low).Overlaps(other) ||
        MipsManagedRegister::FromCoreRegister(high).Overlaps(other);
  }
  if (IsOverlappingDRegister()) {
    if (other.IsDRegister()) return Equals(other);
    if (other.IsFRegister()) {
      FRegister low = AsOverlappingDRegisterLow();
      FRegister high = AsOverlappingDRegisterHigh();
      FRegister other_freg = other.AsFRegister();
      return (low == other_freg) || (high == other_freg);
    }
    return false;
  }
  if (other.IsRegisterPair() || other.IsOverlappingDRegister()) {
    return other.Overlaps(*this);
  }
  return false;
}


void MipsManagedRegister::Print(std::ostream& os) const {
  if (!IsValidManagedRegister()) {
    os << "No Register";
  } else if (IsCoreRegister()) {
    os << "Core: " << static_cast<int>(AsCoreRegister());
  } else if (IsRegisterPair()) {
    os << "Pair: " << AsRegisterPairLow() << ", " << AsRegisterPairHigh();
  } else if (IsFRegister()) {
    os << "FRegister: " << static_cast<int>(AsFRegister());
  } else if (IsDRegister()) {
    os << "DRegister: " << static_cast<int>(AsDRegister());
  } else {
    os << "??: " << RegId();
  }
}

std::ostream& operator<<(std::ostream& os, const MipsManagedRegister& reg) {
  reg.Print(os);
  return os;
}

std::ostream& operator<<(std::ostream& os, const RegisterPair& reg) {
  os << MipsManagedRegister::FromRegisterPair(reg);
  return os;
}

}  // namespace mips
}  // namespace art
