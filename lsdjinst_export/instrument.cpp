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

#include "instrument.hpp"

#include <vector>

#include <lsdj/instrument.h>
#include <lsdj/sav.h>
#include "../common/common.hpp"

namespace lsdj
{
    Instrument::Instrument(const lsdj_song_t* song, uint8_t instrument)
    {
        id = instrument;
        name = get_instrument_name(song, instrument);
        allocated = lsdj_instrument_is_allocated(song, instrument);

        type = lsdj_instrument_get_type(song, instrument);
        type_name = get_instrument_type_name(type);
    }

    std::string Instrument::get_instrument_name(const lsdj_song_t* song, uint8_t instrument)
    {
        char* name = new char[LSDJ_INSTRUMENT_NAME_LENGTH + 1];
        const char* name_bytes = lsdj_instrument_get_name(song, instrument);

        for (int i = 0;i < LSDJ_INSTRUMENT_NAME_LENGTH;i++)
        {
            name[i] = name_bytes[i];
        }
        name[LSDJ_INSTRUMENT_NAME_LENGTH] = '\0';

        std::string name_string(name);
        return name_string;
    }

    std::string Instrument::get_instrument_type_name(lsdj_instrument_type_t type)
    {
        switch(type)
        {
            case LSDJ_INSTRUMENT_TYPE_PULSE:
                return "pulse";
                break;
            case LSDJ_INSTRUMENT_TYPE_WAVE:
                return "wave";
                break;
            case LSDJ_INSTRUMENT_TYPE_KIT:
                return "kit";
                break;
            case LSDJ_INSTRUMENT_TYPE_NOISE:
                return "noise";
                break;
            default:
                return "";
                break;
        }
    }
}
