//
// Created by yesliesnayder on 03.04.2021.
//

#include "../model/model.h"
#include "../db/TestDatabase.h"
#include "../db/CSVDatabase.h"

#ifndef PSS_CONFIG_H
#define PSS_CONFIG_H

const static std::string SERVER_NAME = "Wendex.Taxi.API";

const static Model MODEL_GLOBAL(new CSVDatabase());
const static int PORT = 8080;

#endif //PSS_CONFIG_H
