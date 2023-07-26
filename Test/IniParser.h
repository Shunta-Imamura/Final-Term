#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> parseIniFile(const std::string& filename);

#endif // INI_PARSER_H
