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

#include "cli/parse.h"
#include <iostream>
#include "disk/file.h"
#include "spdlog/spdlog.h"
#include "version.h"

namespace mclean
{

static std::vector<parse_t> g_args = {
    {.arg = "path", .info = "--path\t\t\tspecifies the path to read the file"},
    {.arg = "help", .info = "--help\t\t\tshows information about commands"},
    {.arg = "version", .info = "--version\t\tversion number"}};

static std::optional<parse_t>
g_is_in_entry(const std::string& value)
{
    for (const auto& entry : g_args)
    {
        if (entry.arg == value)
        {
            return entry;
        }
    }
    return {};
}

parse::parse(int argc, char* argv[])
{
    m_args = std::vector<std::string>(argv + 1, argv + argc);
}

void
parse::consume() noexcept
{
    size_t max_len = m_args.size();
    for (size_t i = 0; i < max_len; i++)
    {
        std::string arg = m_args[i];
        std::string cmd;

        if (arg.rfind("--", 0) == 0)
        {
            arg.erase(0, 2);

            if (i + 1 != max_len)
            {
                cmd = m_args[i + 1];
            }

            std::map<std::string, std::string> buf;
            buf.emplace(arg, cmd);
            m_input.push_back(buf);
        }
    }

    if (m_input.empty())
    {
        spdlog::error("invalid options. no arguments provided");
        exit(EXIT_FAILURE);
    }
}

void
parse::validate() noexcept
{
    for (const auto& map : m_input)
    {
        for (const auto& [key, value] : map)
        {
            std::optional<parse_t> entry = g_is_in_entry(key);

            if (entry->arg == "help")
            {
                std::cout << "\n";

                for (const auto& p : g_args)
                {
                    std::cout << p.info << "\n";
                }

                std::cout << "\n";
                break;
            }

            if (entry->arg == "version")
            {
                std::cout
                    << "\nmclean. Copyright (C) 2025 Mustafa Malik.\n"
                       "This program comes with ABSOLUTELY NO WARRANTY.\n"
                       "This is free software, and you are welcome to redistribute it.\n\nVersion: "
                    << MCLEAN_VERSION << "\n\n";
                break;
            }

            if (entry->arg == "path")
            {
                if (value.empty())
                {
                    spdlog::error("invalid argument. no path specified.");
                    exit(EXIT_FAILURE);
                }
                m_path = value;
            }
        }
    }
}

[[nodiscard]] std::optional<std::string>
parse::get_path() const noexcept
{
    if (m_path.empty())
    {
        return {};
    }

    return file::to_absolute(m_path);
}

} // namespace mclean