// Copyright 2014-2020 Josh Pieper, jjp@pobox.com.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <optional>

#include "mjlib/base/visitor.h"

#include "base/kinematic_relation.h"
#include "base/point3d.h"
#include "base/quaternion.h"

#include "mech/hoverbot_command.h"

namespace mjmech {
namespace mech {

struct HoverbotState {
  // The joint level.
  struct Joint {
    int id = 0;

    // These are the raw values reported by the actuator and are not
    // referenced to any particular frame.
    double angle_deg = 0.0;
    double velocity_dps = 0.0;
    double torque_Nm = 0.0;

    double temperature_C = 0.0;
    double voltage = 0.0;
    int32_t mode = 0;
    int32_t fault = 0;

    double kp_Nm = 0.0;
    double ki_Nm = 0.0;
    double kd_Nm = 0.0;
    double feedforward_Nm = 0.0;
    double command_Nm = 0.0;

    template <typename Archive>
    void Serialize(Archive* a) {
      a->Visit(MJ_NVP(id));
      a->Visit(MJ_NVP(angle_deg));
      a->Visit(MJ_NVP(velocity_dps));
      a->Visit(MJ_NVP(torque_Nm));
      a->Visit(MJ_NVP(temperature_C));
      a->Visit(MJ_NVP(voltage));
      a->Visit(MJ_NVP(mode));
      a->Visit(MJ_NVP(fault));
      a->Visit(MJ_NVP(kp_Nm));
      a->Visit(MJ_NVP(ki_Nm));
      a->Visit(MJ_NVP(kd_Nm));
      a->Visit(MJ_NVP(feedforward_Nm));
      a->Visit(MJ_NVP(command_Nm));
    }
  };

  std::vector<Joint> joints;

  // And finally, the robot level.
  struct Robot {
    double voltage = 0.0;

    template <typename Archive>
    void Serialize(Archive* a) {
      a->Visit(MJ_NVP(voltage));
    }
  };

  Robot robot;

  template <typename Archive>
  void Serialize(Archive* a) {
    a->Visit(MJ_NVP(joints));
    a->Visit(MJ_NVP(robot));
  }
};

}
}

namespace mjlib {
namespace base {

}
}