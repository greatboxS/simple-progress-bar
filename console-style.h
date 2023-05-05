/**
 * @file console-style.h
 * @author greatboxs (github.com/greatboxs)
 * @brief
 * @version 0.1
 * @date 2022-02-10
 *
 * @copyright Copyright (c) 2022
 *
 * @ref https://en.wikipedia.org/wiki/ANSI_escape_code
 */

#ifndef __CONSOLE_STYLE_H__
#define __CONSOLE_STYLE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdio.h>

    typedef enum
    {
        CURSOR_UP = 0,
        CURSOR_DOWN,
        CUSOR_FORWARD,
        CURSOR_BACK,
        CURSOR_NEXTLINE,
        CURSOR_PREV_LINE,
        CURSOR_HOR_ABSOLUTE,
        CURSOR_SCROLL_UP,
        CURSOR_SCROLL_DOWN,
    } cursor_move_type;

    typedef enum
    {
        ERASE_TO_END = 0,
        ERASE_TO_BEGINING,
        ERASE_ENTIRE
    } cursor_erase_type;

    typedef enum
    {
        COLOR_8BITS = 0,
        COLOR_24BITS,
    } color_bits_type;
    /**
     * @brief
     * This color is use to set force/ back ground
     * SET_FOREGROUND_COLOR_S + standard_color
     * ESC [ 30–37 m
     *
     * For
     * ESC[38:5:⟨n⟩m Select foreground color      where n is a number from the table below
     * ESC[48:5:⟨n⟩m Select background color
     */
    typedef enum
    {
        COLOR_NONE = -1,
        BLACK = 0,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    } standard_color;
    /**
     * @brief
     * CSI n m	SGR	Select Graphic Rendition
     * Sets colors and style of the characters following this code
     *
     */
    typedef enum
    {
        STYLE_RESET = 0,
        STYLE_BOLD,
        STYLE_FAINT,
        STYLE_ITALIC,
        STYLE_UNDERLINE,
        STYLE_SLOW_BLINK,
        RAPID_BLINK,
        REVERSE_VIDEO,
        CONCEAL,
        CROSSED_OUT,
        PRIMARY_DEFAULT_FONT,
        ALTERNATIVE_FONT = 19,
        FRAKTUR_GOTHIC,
        DOUBLY_UNDERLINED,
        NORMAL_INTENSITY,
        NEITHER_ITALIC,
        NOT_UNDERLINED,
        NOT_BLINKING,
        PROPORTIONAL_SPACING,
        NOT_REVERSED,
        REVEAL,
        NOT_CROSSED_OUT,
        SET_FOREGROUND_COLOR_S = 30,
        SET_FOREGROUND_COLOR = 38, // Next arguments are 5;n or 2;r;g;b, ESC[38:5:0m  set to black color
        DEFAULT_FOREGROUND_COLOR,
        SET_BACKGROUND_COLOR_S = 40,
        SET_BACKGRND_COLOR = 48, // Next arguments are 5;n or 2;r;g;b
        DEFAULT_BACKGROUND_COLOR,
        DISABLE_PROPORTIONAL_SPACING,
        FRAMED,
        ENCIRCLED,
        OVERLINED,
        NEITHER_FRAMED_,
        NOT_OVERLINED,
        SET_UNDERLINE_COLOR = 58,
        DEFAULT_UNDERLINE_COLOR,
        IDEOGRAM_UNDERLINE,
        IDEOGRAM_DOUBLE_UNDERLINE,
        IDEOGRAM_OVERLINE,
        IDEOGRAM_DOUBLE_OVERLINE,
        IDEOGRAM_STRESS_MARKING,
        NO_IDEOGRAM_ATTRIBUTES,
        SUPERSCRIPT = 73,
        SUBSCRIPT,
        NEITHER_SUPERSCRIPT,
        SET_BRIGHT_FOREGROUND_COLOR = 97,
        SET_BRIGHT_BACKGROUND_COLOR = 107
    } sgr_style_type;

/**
 * @brief SIMPLE PROGRESS BAR
 *
 * @param fd            out stream
 * @param width         progress bar width
 * @param prefix        prefix string
 * @param percent       update percent
 * @param background    background color
 * @param forceground   forceground color
 * @param c             rogress bar print character
 */
#define PROGRESS_BAR_UPDATE(fd, prefix, width, percent, background, forceground, c) \
    int value = percent * width / 100;                                              \
    fprintf(fd, "[%s] ", prefix);                                                   \
    for (int i = 0; i < width; i++)                                                 \
    {                                                                               \
        if (i < value)                                                              \
        {                                                                           \
            if (background != -1)                                                   \
                console_set_background(fd, background, COLOR_8BITS);                \
            if (forceground != -1)                                                  \
                console_set_forceground(fd, forceground, COLOR_8BITS);              \
            fprintf(fd, "%c", c);                                                   \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            console_reset_style(fd);                                                \
            fprintf(fd, " ");                                                       \
        }                                                                           \
    }                                                                               \
    console_reset_style(fd);                                                        \
    fprintf(fd, " [%d%]\n", percent);                                               \
    console_cursor_move(fd, CURSOR_PREV_LINE, 1);                                   \
    console_erase_line(fd, ERASE_ENTIRE);

/**
 * @brief Default block grogress bar
 *
 */
#define BLOCK_PROGRESS_BAR_UPDATE(fd, prefix, width, percent) \
    PROGRESS_BAR_UPDATE(fd, prefix, width, percent, (SET_BACKGROUND_COLOR_S + WHITE), (SET_FOREGROUND_COLOR_S + BLACK), " ")
    //--------------------------------------------

    /**
     * @brief           move cursor in terminal
     *
     * @param fd        out stream
     * @param cursor_dir cursor move type defined in cursor_move_type
     * @param n         number of  character to be move over
     */
    void console_cursor_move(FILE *fd, int cursor_dir, int n);

    /**
     * @brief       erase out stream display
     *
     * @param fd    out stream
     * @param type  0 - cursor to end | 1 - begining to cursor | 2 -  entire display
     *              defined in cursor_erase_type
     */
    void console_erase_display(FILE *fd, int type);

    /**
     * @brief       erase out stream line
     *
     * @param fd    out stream
     * @param type  0 - cursor to end | 1 - begining to cursor | 2 -  entire display
     *              defined in cursor_erase_type
     */
    void console_erase_line(FILE *fd, int type);

    /**
     * @brief               set out stream color and style
     *
     * @param fd            out stream
     * @param type
     * @param control       CSI (Control Sequence Introducer) sequences
     *                      https://en.wikipedia.org/wiki/ANSI_escape_code#CSIsection
     *
     * @param color_bits_type COLOR_8BITS/ COLOR_24BITS
     */
    void console_set_style(FILE *fd, int type, int control, int color_bits_type);

    /**
     * @brief       set background color to out stream
     *
     * @param fd    out stream
     * @param color SET_BACKGROUND_COLOR_S + standard_color,
     *              e.g: (SET_BACKGROUND_COLOR_S + WHITE) set background to white
     * @param type  COLOR_8BITS/ COLOR_24BITS
     */
    void console_set_background(FILE *fd, int color, int type);

    /**
     * @brief       set forceground color to out stream
     *
     * @param fd    out stream
     * @param color SET_FORCEGROUND_COLOR_S + standard_color,
     *              e.g: (SET_FORCEGROUND_COLOR_S + WHITE) set background to white
     * @param type  COLOR_8BITS/ COLOR_24BITS
     */
    void console_set_forceground(FILE *fd, int color, int type);

    /**
     * @brief       reset all style of out stream
     *
     * @param fd    out stream
     */
    void console_reset_style(FILE *fd);

#ifdef __cplusplus
}
#endif

#endif // __CONSOLE-STYLE_H__