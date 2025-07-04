/*
 * This file is part of the ligen2 distribution (https://github.com/shabman/ligen)
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

#ifndef _LIGEN2_DISK_FILE_H_
#define _LIGEN2_DISK_FILE_H_

#include <fstream>
#include <string>
#include <vector>

namespace mclean
{

class file final
{
public:
    explicit file(const std::string&);
    ~file();

private:
    file& operator=(const file&) = delete;
    file(const file&)            = delete;
    file(const file&&)           = delete;

public:
    [[nodiscard]] std::vector<std::string> read();
    [[maybe_unused]] bool                  write(const std::vector<std::string>&);
    [[maybe_unused]] bool                  remove();
    [[nodiscard]] static std::string       fext(const std::string&) noexcept;
    [[nodiscard]] static std::string       to_absolute(const std::string&) noexcept;

private:
    std::fstream             m_stream;
    std::string              m_path;
    std::vector<std::string> m_contents;
};

} // namespace mclean

#endif /* _LIGEN2_DISK_FILE_H_ */