/* vim:set et ts=4 sts=4:
 *
 * ibus-pinyin - The Chinese PinYin engine for IBus
 *
 * Copyright (c) 2008-2010 Peng Huang <shawn.p.huang@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "PYHalfFullConverter.h"

namespace PY {

const guint
HalfFullConverter::m_table[][3] = {
    { 0x0020, 0x3000, 1 },
    { 0x0021, 0xFF01, 94 },
    { 0x00A2, 0xFFE0, 2 },
    { 0x00A5, 0xFFE5, 1 },
    { 0x00A6, 0xFFE4, 1 },
    { 0x00AC, 0xFFE2, 1 },
    { 0x00AF, 0xFFE3, 1 },
    { 0x20A9, 0xFFE6, 1 },
    { 0xFF61, 0x3002, 1 },
    { 0xFF62, 0x300C, 2 },
    { 0xFF64, 0x3001, 1 },
    { 0xFF65, 0x30FB, 1 },
    { 0xFF66, 0x30F2, 1 },
    { 0xFF67, 0x30A1, 1 },
    { 0xFF68, 0x30A3, 1 },
    { 0xFF69, 0x30A5, 1 },
    { 0xFF6A, 0x30A7, 1 },
    { 0xFF6B, 0x30A9, 1 },
    { 0xFF6C, 0x30E3, 1 },
    { 0xFF6D, 0x30E5, 1 },
    { 0xFF6E, 0x30E7, 1 },
    { 0xFF6F, 0x30C3, 1 },
    { 0xFF70, 0x30FC, 1 },
    { 0xFF71, 0x30A2, 1 },
    { 0xFF72, 0x30A4, 1 },
    { 0xFF73, 0x30A6, 1 },
    { 0xFF74, 0x30A8, 1 },
    { 0xFF75, 0x30AA, 2 },
    { 0xFF77, 0x30AD, 1 },
    { 0xFF78, 0x30AF, 1 },
    { 0xFF79, 0x30B1, 1 },
    { 0xFF7A, 0x30B3, 1 },
    { 0xFF7B, 0x30B5, 1 },
    { 0xFF7C, 0x30B7, 1 },
    { 0xFF7D, 0x30B9, 1 },
    { 0xFF7E, 0x30BB, 1 },
    { 0xFF7F, 0x30BD, 1 },
    { 0xFF80, 0x30BF, 1 },
    { 0xFF81, 0x30C1, 1 },
    { 0xFF82, 0x30C4, 1 },
    { 0xFF83, 0x30C6, 1 },
    { 0xFF84, 0x30C8, 1 },
    { 0xFF85, 0x30CA, 6 },
    { 0xFF8B, 0x30D2, 1 },
    { 0xFF8C, 0x30D5, 1 },
    { 0xFF8D, 0x30D8, 1 },
    { 0xFF8E, 0x30DB, 1 },
    { 0xFF8F, 0x30DE, 5 },
    { 0xFF94, 0x30E4, 1 },
    { 0xFF95, 0x30E6, 1 },
    { 0xFF96, 0x30E8, 6 },
    { 0xFF9C, 0x30EF, 1 },
    { 0xFF9D, 0x30F3, 1 },
    { 0xFFA0, 0x3164, 1 },
    { 0xFFA1, 0x3131, 30 },
    { 0xFFC2, 0x314F, 6 },
    { 0xFFCA, 0x3155, 6 },
    { 0xFFD2, 0x315B, 9 },
    { 0xFFE9, 0x2190, 4 },
    { 0xFFED, 0x25A0, 1 },
    { 0xFFEE, 0x25CB, 1 },
};

gunichar
HalfFullConverter::toFull (gunichar ch)
{
    for (guint i = 0; i < G_N_ELEMENTS (m_table); i++) {
        if (G_UNLIKELY (ch < m_table[i][0]))
            return ch;
        if (G_UNLIKELY (ch < m_table[i][0] + m_table[i][2]))
            return ch - m_table[i][0] + m_table[i][1];
    }
    return ch;
}

gunichar
HalfFullConverter::toHalf (gunichar ch)
{
    for (guint i = 0; i < G_N_ELEMENTS (m_table); i++) {
        if (G_LIKELY (ch < m_table[i][1]))
            continue;
        if (G_LIKELY (ch >= m_table[i][1] + m_table[i][2]))
            continue;
        return ch - m_table[i][1] + m_table[i][0];
    }
    return ch;
}

};

