#pragma once
#include <string>
#include <vector>

namespace Error {
    void LogError(const std::vector<std::string>& logs, bool closeAfterError = false);
}
