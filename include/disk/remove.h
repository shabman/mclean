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

#ifndef _MCLEAN_DISK_REMOVE_H_
#define _MCLEAN_DISK_REMOVE_H_

#include <string>
#include <vector>

namespace mclean
{

class remove final
{
public:
    remove(const std::vector<std::string>&);
    ~remove() = default;

private:
    remove& operator=(const remove&) = delete;
    remove(const remove&)            = delete;
    remove(const remove&&)           = delete;

public:
    void prompt() noexcept;
    void erase_all();

private:
    char                     m_proceed;
    std::vector<std::string> m_contents;
};

} // namespace mclean

#endif /* _MCLEAN_DISK_REMOVE_H_ */
