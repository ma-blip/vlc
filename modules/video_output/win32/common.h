/*****************************************************************************
 * common.h: Windows video output header file
 *****************************************************************************
 * Copyright (C) 2001-2009 VLC authors and VideoLAN
 *
 * Authors: Gildas Bazin <gbazin@videolan.org>
 *          Damien Fouilleul <damienf@videolan.org>
 *          Martell Malone <martellmalone@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/*****************************************************************************
 * event_thread_t: event thread
 *****************************************************************************/
#include "events.h"

#define RECTWidth(r)   (LONG)((r).right - (r).left)
#define RECTHeight(r)  (LONG)((r).bottom - (r).top)

/*****************************************************************************
 * vout_sys_t: video output method descriptor
 *****************************************************************************
 * This structure is part of the video output thread descriptor.
 * It describes the module specific properties of an output thread.
 *****************************************************************************/
typedef struct vout_display_sys_win32_t
{
    bool                 b_windowless;    /* the rendering is done offscreen */

    /* */
    event_thread_t *event;

    /* */
    HWND                 hwnd;                  /* Handle of the main window */
    HWND                 hvideownd;        /* Handle of the video sub-window */
    struct vout_window_t *parent_window;         /* Parent window VLC object */
    HWND                 hparent;             /* Handle of the parent window */
    HWND                 hfswnd;          /* Handle of the fullscreen window */

    /* current size of the display */
    UINT display_width, display_height;

    /* size of the overall window (including black bands) */
    RECT         rect_parent;

# if !defined(NDEBUG) && defined(HAVE_DXGIDEBUG_H)
    HINSTANCE     dxgidebug_dll;
# endif

    bool         place_changed;

    /* Misc */
    bool is_first_placement;
    bool is_on_top;

    /* Coordinates of dest images (used when blitting to display) */
    vout_display_place_t  place;

    vout_display_cfg_t vdcfg;

    bool use_desktop;     /* show video on desktop window ? */

    bool (*pf_GetDisplayDimensions)(void *opaque, UINT *w, UINT *h);
    void *opaque_dimensions;
} vout_display_sys_win32_t;


/*****************************************************************************
 * Prototypes from common.c
 *****************************************************************************/
int  CommonInit(vout_display_t *, vout_display_sys_win32_t *, bool b_windowless, const vout_display_cfg_t *);
#if !VLC_WINSTORE_APP
void CommonClean(vlc_object_t *, vout_display_sys_win32_t *);
#endif /* !VLC_WINSTORE_APP */
void CommonManage(vout_display_t *, vout_display_sys_win32_t *);
int  CommonControl(vout_display_t *, vout_display_sys_win32_t *, int , va_list );

void UpdateRects (vout_display_t *, vout_display_sys_win32_t *, bool is_forced);

/*****************************************************************************
 * Constants
 *****************************************************************************/
#define IDM_TOGGLE_ON_TOP  (WM_USER + 1)
