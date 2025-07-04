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

#include "disk/remove.h"
#include <iostream>
#include "disk/file.h"
#include "spdlog/spdlog.h"

namespace mclean
{

remove::remove(const std::vector<std::string>& contents) : m_contents(contents)
{
}

void
remove::prompt() noexcept
{

    std::cout << "\nWAIT! The following will be deleted: \n";

    for (const std::string& line : m_contents)
    {
        std::cout << line << "\n";
    }

    std::cout << "\nWAIT! You are about to delete some files/folders which may be dangerous.\nAre "
                 "you sure "
                 "you want to continue? (y/n): ";
    std::cin >> m_proceed;
    std::cout << "\n";

    if (m_proceed != 'y')
    {
        spdlog::warn("aborting...");
        exit(EXIT_SUCCESS);
    }
}

void
remove::erase_all()
{
    prompt();

    for (const std::string& path : m_contents)
    {
        file f(path);
        spdlog::warn("removing: {}", path);

        if (f.remove())
        {
            spdlog::info("successfully removed file/directory!");
        }
        else
        {
            spdlog::error("failed to remove file/directory!");
        }
    }
}

} // namespace mclean
