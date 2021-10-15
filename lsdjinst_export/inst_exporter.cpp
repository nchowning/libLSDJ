/*
 
 This file is a part of liblsdj, a C library for managing everything
 that has to do with LSDJ, software for writing music (chiptune) with
 your gameboy. For more information, see:
 
 * https://github.com/stijnfrishert/liblsdj
 * http://www.littlesounddj.com
 
 --------------------------------------------------------------------------------
 
 MIT License
 
 Copyright (c) 2018 - 2020 Stijn Frishert
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 */

#include "inst_exporter.hpp"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <lsdj/instrument.h>
#include <lsdj/project.h>
#include <lsdj/sav.h>
#include "../common/common.hpp"

namespace lsdj
{
    int InstExporter::print(const ghc::filesystem::path& path)
    {
        if (ghc::filesystem::is_directory(path))
        {
            std::cerr << "Loading multiple files from a directory is not yet supported...";
            return 1;
        }

        std::cout << "Loading " << path.string() << "..." << std::endl;

        lsdj_sav_t* sav = nullptr;
        lsdj_error_t error = lsdj_sav_read_from_file(path.string().c_str(), &sav, nullptr);
        if (error != LSDJ_SUCCESS)
        {
            std::cerr << handle_error(error);
            return 1;
        }
        assert(sav != nullptr);

        const lsdj_project_t* project = lsdj_sav_get_project_const(sav, 0);
        const lsdj_song_t* song = lsdj_project_get_song_const(project);

        for (int i = 0x1E7A;i < 0x1E7A + LSDJ_INSTRUMENT_COUNT * LSDJ_INSTRUMENT_BYTE_COUNT;i++)
            std::cout << &song->bytes[i] << std::endl;;
        // std::cout << lsdj_instrument_get_name(song, 0)[0] << std::endl;
        // for (int i = 0;i < LSDJ_INSTRUMENT_COUNT;i++)
        // {
        //     std::cout << i << " ";
        //     if (lsdj_instrument_is_allocated(song, i))
        //     {
        //         std::cout << lsdj_instrument_get_name(song, i) << std::endl;
        //     }
        //     else
        //     {
        //         std::cout << std::endl;
        //     }
        // }

        return 0;
    }
}
