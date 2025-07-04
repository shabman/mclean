/**
 * This file is part of the mclean distribution (https://github.com/shabman/mclean)
 * Copyright (c) 2025 Mustafa Malik.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MCLEAN_CLI_PARSE_H_
#define _MCLEAN_CLI_PARSE_H_

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace mclean
{

typedef struct
{
    std::string_view arg;
    std::string_view info;
} parse_t;

class parse final
{
public:
    parse(int argc, char* argv[]);
    ~parse() = default;

private:
    parse& operator=(const parse&) = delete;
    parse(const parse&)            = delete;
    parse(const parse&&)           = delete;

public:
    void                                     consume() noexcept;
    void                                     validate() noexcept;
    [[nodiscard]] std::optional<std::string> get_path() const noexcept;

private:
    std::string                                     m_path;
    std::vector<std::string>                        m_args;
    std::vector<std::map<std::string, std::string>> m_input;
};

} // namespace mclean

#endif /* _MCLEAN_CLI_PARSE_H_ */
