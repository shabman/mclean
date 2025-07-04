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
#include "disk/remove.h"
#include "disk/scan.h"
#include "platform.h"

int
main(int argc, char* argv[])
{
    mclean::parse parser(argc, argv);
    parser.consume();
    parser.validate();

    if (parser.get_path().has_value())
    {
        mclean::scan scanner(*parser.get_path());
        auto         to_remove = scanner.get_contents();

        mclean::remove remover(to_remove);
        remover.erase_all();
    }
}
