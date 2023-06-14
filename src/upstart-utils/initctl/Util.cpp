// Copyright (c) 2017-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "Util.h"
#include "Logger.h"

string Util::exec(std::string cmd) {
  g_logger.write("[DEBUG] Exec : " + cmd);
  char buffer[128];
  string result = "";
  FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe) {
    g_logger.write("[FATAL] pipe open failed!");
    throw std::runtime_error("popen() failed!");
  }
  try {
    while (!feof(pipe)) {
      if (fgets(buffer, sizeof(buffer), pipe) != NULL)
        result += buffer;
    }
  } catch (...) {
    pclose(pipe);
    g_logger.write("[FATAL] read from pipe failed");
    return result;
  }
  pclose(pipe);
  return result;
}

