//
// Created by yesliesnayder on 03.04.2021.
//

#include "../model/model.h"
#include "../db/TestDatabase.h"

#ifndef PSS_CONFIG_H
#define PSS_CONFIG_H

const static std::string SERVER_NAME = "Wendex.Taxi.API";

// TODO: Remove after debug
const static Model MODEL_GLOBAL(new TestDatabase());

#endif //PSS_CONFIG_H
