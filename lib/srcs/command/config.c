#include "command.h"

command_std_format_t available_cmd[NONE] = {
  {START_SIMULATION, "START_SIMULATION", 0, command_start_simulation},
  {END_SIMULATION, "END_SIMULATION", 0},
  {CAR_FORWARD, "CAR_FORWARD", 2}
};