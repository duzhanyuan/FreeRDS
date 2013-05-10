/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * FreeRDP X11 Server
 *
 * Copyright 2013 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <winpr/crt.h>

#include <freerdp/freerdp.h>
#include <freerdp/listener.h>

#include "bitmap.h"

#include "core.h"

/**
 * Custom helpers
 */

int libxrdp_set_bounds_rect(xrdpSession* session, xrdpRect* rect)
{
	rdpUpdate* update = session->client->update;

	if (rect)
	{
		rdpBounds bounds;

		bounds.left = rect->left;
		bounds.top = rect->top;
		bounds.right = rect->right;
		bounds.bottom = rect->bottom;

		update->SetBounds(session->context, &bounds);
	}
	else
	{
		update->SetBounds(session->context, NULL);
	}

	return 0;
}

/**
 * Original XRDP stubbed interface
 */

xrdpSession* libxrdp_init(tbus id, struct trans* trans)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_exit(xrdpSession* session)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_disconnect(xrdpSession* session)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_process_incomming(xrdpSession* session)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_process_data(xrdpSession* session)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_send_palette(xrdpSession* session, int* palette)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_send_bell(xrdpSession* session)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_send_bitmap(xrdpSession* session, int width, int height, int bpp, char* data, int x, int y, int cx, int cy)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_send_pointer(xrdpSession* session, int cache_idx, char* data, char* mask, int x, int y, int bpp)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_set_pointer(xrdpSession* session, int cache_idx)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_init(xrdpSession* session)
{
	rdpUpdate* update = session->context->update;

	printf("%s\n", __FUNCTION__);

	update->BeginPaint(session->context);

	return 0;
}

int libxrdp_orders_send(xrdpSession* session)
{
	rdpUpdate* update = session->context->update;

	printf("%s\n", __FUNCTION__);

	update->EndPaint(session->context);

	return 0;
}

int libxrdp_orders_force_send(xrdpSession* session)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_rect(xrdpSession* session, int x, int y,
		int cx, int cy, int color, xrdpRect* rect)
{
	OPAQUE_RECT_ORDER opaqueRect;
	rdpPrimaryUpdate* primary = session->client->update->primary;

	printf("%s\n", __FUNCTION__);

	opaqueRect.nLeftRect = x;
	opaqueRect.nTopRect = y;
	opaqueRect.nWidth = cx;
	opaqueRect.nHeight = cy;
	opaqueRect.color = color;

	libxrdp_set_bounds_rect(session, rect);
	primary->OpaqueRect(session->context, &opaqueRect);

	return 0;
}

int libxrdp_orders_screen_blt(xrdpSession* session, int x, int y,
		int cx, int cy, int srcx, int srcy, int rop, xrdpRect* rect)
{
	SCRBLT_ORDER scrblt;
	rdpPrimaryUpdate* primary = session->client->update->primary;

	printf("%s\n", __FUNCTION__);

	scrblt.nLeftRect = x;
	scrblt.nTopRect = y;
	scrblt.nWidth = cx;
	scrblt.nHeight = cy;
	scrblt.bRop = rop;
	scrblt.nXSrc = srcx;
	scrblt.nYSrc = srcy;

	libxrdp_set_bounds_rect(session, rect);
	primary->ScrBlt(session->context, &scrblt);

	return 0;
}

int libxrdp_orders_pat_blt(xrdpSession* session, int x, int y,
		int cx, int cy, int rop, int bg_color, int fg_color,
		xrdpBrush* brush, xrdpRect* rect)
{
	PATBLT_ORDER patblt;
	rdpPrimaryUpdate* primary = session->client->update->primary;

	printf("%s\n", __FUNCTION__);

	patblt.nLeftRect = x;
	patblt.nTopRect = y;
	patblt.nWidth = cx;
	patblt.nHeight = cy;
	patblt.bRop = (UINT32) rop;
	patblt.backColor = (UINT32) bg_color;
	patblt.foreColor = (UINT32) fg_color;

	patblt.brush.x = brush->x_orgin;
	patblt.brush.y = brush->y_orgin;
	patblt.brush.style = brush->style;
	patblt.brush.data = patblt.brush.p8x8;
	CopyMemory(patblt.brush.data, brush->pattern, 8);
	patblt.brush.hatch = patblt.brush.data[0];

	libxrdp_set_bounds_rect(session, rect);
	primary->PatBlt(session->context, &patblt);

	return 0;
}

int libxrdp_orders_dest_blt(xrdpSession* session,
		int x, int y, int cx, int cy, int rop, xrdpRect* rect)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_line(xrdpSession* session, int mix_mode,
		int startx, int starty,	int endx, int endy, int rop,
		int bg_color, xrdpPen* pen, xrdpRect* rect)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_mem_blt(xrdpSession* session, int cache_id,
		int color_table, int x, int y, int cx, int cy, int rop, int srcx,
		int srcy, int cache_idx, xrdpRect* rect)
{
	MEMBLT_ORDER memblt;
	rdpPrimaryUpdate* primary = session->client->update->primary;

	printf("%s id: %d index: %d\n", __FUNCTION__, cache_id, cache_idx);

	memblt.nLeftRect = x;
	memblt.nTopRect = y;
	memblt.nWidth = cx;
	memblt.nHeight = cy;
	memblt.bRop = rop;
	memblt.nXSrc = srcx;
	memblt.nYSrc = srcy;
	memblt.cacheId = cache_id;
	memblt.cacheIndex = cache_idx;
	memblt.colorIndex = color_table;

	libxrdp_set_bounds_rect(session, rect);
	primary->MemBlt(session->context, &memblt);

	return 0;
}

int libxrdp_orders_text(xrdpSession* session,
		int font, int flags, int mixmode,
		int fg_color, int bg_color,
		int clip_left, int clip_top,
		int clip_right, int clip_bottom,
		int box_left, int box_top,
		int box_right, int box_bottom,
		int x, int y, char* data, int data_len,
		xrdpRect* rect)
{
	GLYPH_INDEX_ORDER glyph_index;
	rdpPrimaryUpdate* primary = session->client->update->primary;

	printf("%s\n", __FUNCTION__);

	glyph_index.cacheId = font;
	glyph_index.flAccel = flags;
	glyph_index.ulCharInc = mixmode;
	glyph_index.fOpRedundant = 0;
	glyph_index.backColor = bg_color;
	glyph_index.foreColor = fg_color;
	glyph_index.bkLeft = clip_left;
	glyph_index.bkTop = clip_top;
	glyph_index.bkRight = clip_right;
	glyph_index.bkBottom = clip_bottom;
	glyph_index.opLeft = box_left;
	glyph_index.opTop = box_top;
	glyph_index.opRight = box_right;
	glyph_index.opBottom = box_bottom;
	glyph_index.x = x;
	glyph_index.y = y;
	glyph_index.cbData = data_len;
	CopyMemory(glyph_index.data, data, data_len);

	libxrdp_set_bounds_rect(session, rect);
	primary->GlyphIndex(session->context, &glyph_index);

	return 0;
}

int libxrdp_orders_send_palette(xrdpSession* session, int* palette, int cache_id)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_send_raw_bitmap(xrdpSession* session,
		int width, int height, int bpp, char* data,
		int cache_id, int cache_idx)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_send_bitmap(xrdpSession* session,
		int width, int height, int bpp, char* data,
		int cache_id, int cache_idx)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_send_font(xrdpSession* session,
		xrdpFontChar* font_char, int font_index, int char_index)
{
	rdpSecondaryUpdate* secondary = session->client->update->secondary;

	printf("%s\n", __FUNCTION__);

	if (secondary->glyph_v2)
	{
		CACHE_GLYPH_V2_ORDER cache_glyph_v2;

		cache_glyph_v2.flags = 0;
		cache_glyph_v2.cacheId = font_index;
		cache_glyph_v2.cGlyphs = 1;
		cache_glyph_v2.glyphData[0].cacheIndex = char_index;
		cache_glyph_v2.glyphData[0].x = font_char->offset;
		cache_glyph_v2.glyphData[0].y = font_char->baseline;
		cache_glyph_v2.glyphData[0].cx = font_char->width;
		cache_glyph_v2.glyphData[0].cy = font_char->height;
		cache_glyph_v2.glyphData[0].aj = (BYTE*) font_char->data;
		cache_glyph_v2.unicodeCharacters = NULL;

		secondary->CacheGlyphV2(session->context, &cache_glyph_v2);
	}
	else
	{
		CACHE_GLYPH_ORDER cache_glyph;

		cache_glyph.cacheId = font_index;
		cache_glyph.cGlyphs = 1;
		cache_glyph.glyphData[0].cacheIndex = char_index;
		cache_glyph.glyphData[0].x = font_char->offset;
		cache_glyph.glyphData[0].y = font_char->baseline;
		cache_glyph.glyphData[0].cx = font_char->width;
		cache_glyph.glyphData[0].cy = font_char->height;
		cache_glyph.glyphData[0].aj = (BYTE*) font_char->data;
		cache_glyph.unicodeCharacters = NULL;

		secondary->CacheGlyph(session->context, &cache_glyph);
	}

	return 0;
}

int libxrdp_reset(xrdpSession* session, int width, int height, int bpp)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_send_raw_bitmap2(xrdpSession* session,
		int width, int height, int bpp, char* data, int cache_id, int cache_idx)
{
	int bytesPerPixel;
	CACHE_BITMAP_V2_ORDER cache_bitmap_v2;
	rdpSecondaryUpdate* secondary = session->client->update->secondary;

	printf("%s id: %d index: %d\n", __FUNCTION__, cache_id, cache_idx);

	cache_bitmap_v2.bitmapBpp = bpp;
	cache_bitmap_v2.bitmapWidth = width;
	cache_bitmap_v2.bitmapHeight = height;
	cache_bitmap_v2.bitmapDataStream = (BYTE*) data;
	cache_bitmap_v2.cacheId = cache_id;
	cache_bitmap_v2.cacheIndex = cache_idx;
	cache_bitmap_v2.compressed = FALSE;
	cache_bitmap_v2.flags = 0;

	bytesPerPixel = (bpp + 7) / 8;
	cache_bitmap_v2.cbUncompressedSize = width * height * bytesPerPixel;
	cache_bitmap_v2.bitmapLength = width * height * bytesPerPixel;

	secondary->CacheBitmapV2(session->context, &cache_bitmap_v2);

	return 0;
}

int libxrdp_orders_send_bitmap2(xrdpSession* session,
		int width, int height, int bpp, char* data, int cache_id, int cache_idx, int hints)
{
	wStream* s;
	wStream* ts;
	int e, lines;
	int bytesPerPixel;
	CACHE_BITMAP_V2_ORDER cache_bitmap_v2;
	rdpSecondaryUpdate* secondary = session->client->update->secondary;

	printf("%s id: %d index: %d\n", __FUNCTION__, cache_id, cache_idx);

	cache_bitmap_v2.bitmapBpp = bpp;
	cache_bitmap_v2.bitmapWidth = width;
	cache_bitmap_v2.bitmapHeight = height;
	cache_bitmap_v2.cacheId = cache_id;
	cache_bitmap_v2.cacheIndex = cache_idx;
	cache_bitmap_v2.compressed = TRUE;
	cache_bitmap_v2.flags = CBR2_NO_BITMAP_COMPRESSION_HDR;

	e = width % 4;

	if (e != 0)
		e = 4 - e;

	s = Stream_New(NULL, 16384);
	ts = Stream_New(NULL, 16384);

	lines = freerdp_bitmap_compress(data, width, height, s, bpp, 16384, height - 1, ts, e);
	Stream_SealLength(s);

	cache_bitmap_v2.bitmapDataStream = Stream_Buffer(s);
	cache_bitmap_v2.bitmapLength = Stream_Length(s);
	cache_bitmap_v2.cbCompMainBodySize = Stream_Length(s);

	bytesPerPixel = (bpp + 7) / 8;
	cache_bitmap_v2.cbUncompressedSize = width * height * bytesPerPixel;

	secondary->CacheBitmapV2(session->context, &cache_bitmap_v2);

	Stream_Free(s, TRUE);
	Stream_Free(ts, TRUE);

	return 0;
}

int libxrdp_orders_send_bitmap3(xrdpSession* session,
		int width, int height, int bpp, char* data, int cache_id, int cache_idx, int hints)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_query_channel(xrdpSession* session, int index,
		char* channel_name, int* channel_flags)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_get_channel_id(xrdpSession* session, char* name)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_send_to_channel(xrdpSession* session, int channel_id,
		char* data, int data_len, int total_data_len, int flags)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_send_brush(xrdpSession* session, int width, int height,
		int bpp, int type, int size, char* data, int cache_id)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_send_create_os_surface(xrdpSession* session, int id,
		int width, int height, xrdpList* del_list)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_orders_send_switch_os_surface(xrdpSession* session, int id)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_window_new_update(xrdpSession* session, int window_id,
		struct rail_window_state_order* window_state, int flags)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_window_delete(xrdpSession* session, int window_id)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_window_icon(xrdpSession* session, int window_id,
		int cache_entry, int cache_id, struct rail_icon_info* icon_info, int flags)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_window_cached_icon(xrdpSession* session, int window_id,
		int cache_entry, int cache_id, int flags)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_notify_new_update(xrdpSession* session,
		int window_id, int notify_id, struct rail_notify_state_order* notify_state, int flags)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_notify_delete(xrdpSession* session, int window_id, int notify_id)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int libxrdp_monitored_desktop(xrdpSession* session, struct rail_monitored_desktop_order* mdo, int flags)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}
