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

#ifndef _MCLEAN_DISK_SCAN_H_
#define _MCLEAN_DISK_SCAN_H_

#include <string>
#include <vector>

namespace mclean
{

class scan final
{
public:
    scan(const std::string&);
    ~scan() = default;

private:
    scan& operator=(const scan&) = delete;
    scan(const scan&)            = delete;
    scan(const scan&&)           = delete;

private:
    void parse() noexcept;

public:
    [[nodiscard]] std::vector<std::string> get_contents() noexcept;

private:
    std::string              m_fpath;
    std::vector<std::string> m_contents;
};

} // namespace mclean

#endif /* _MCLEAN_DISK_SCAN_H_ */
