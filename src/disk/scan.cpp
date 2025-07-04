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

#include "disk/scan.h"
#include <iostream>
#include "disk/file.h"
#include "spdlog/spdlog.h"

namespace mclean
{

scan::scan(const std::string& path) : m_fpath(path)
{
    if (m_fpath.empty())
    {
        spdlog::error("invalid file path provided.");
        exit(EXIT_FAILURE);
    }
}

void
scan::parse() noexcept
{
    file f(m_fpath);
    m_contents = f.read();

    if (m_contents.empty())
    {
        spdlog::error("could not parse file. empty contents.");
        exit(EXIT_FAILURE);
    }

    m_contents.erase(std::remove_if(m_contents.begin(),
                                    m_contents.end(),
                                    [](const std::string& line)
                                    { return line.empty() || line.at(0) == '#'; }),
                     m_contents.end());

    std::vector<std::string> abs;

    for (const std::string& path : m_contents)
    {
        abs.push_back(file::to_absolute(path));
    }

    m_contents = abs;
}

[[nodiscard]] std::vector<std::string>
scan::get_contents() noexcept
{
    parse();
    return m_contents;
}

} // namespace mclean
