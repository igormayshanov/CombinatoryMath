#pragma once
#include <iostream>
#include <optional>
#include <string>

std::optional<std::ifstream> OpenFile(std::string fileName);