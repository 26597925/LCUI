﻿/* ***************************************************************************
 * sidebar.c -- sidebar widget
 * 
 * Copyright (C) 2015 by Liu Chao <lc-soft@live.cn>
 * 
 * This file is part of the LCUI project, and may only be used, modified, and
 * distributed under the terms of the GPLv2.
 * 
 * (GPLv2 is abbreviation of GNU General Public License Version 2)
 * 
 * By continuing to use, modify, or distribute this file you indicate that you
 * have read the license and understand and accept it fully.
 *  
 * The LCUI project is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GPL v2 for more details.
 * 
 * You should have received a copy of the GPLv2 along with this file. It is 
 * usually in the LICENSE.TXT file, If not, see <http://www.gnu.org/licenses/>.
 * ****************************************************************************/
 
/* ****************************************************************************
 * button.c -- LCUI 的侧边栏部件
 *
 * 版权所有 (C) 2015 归属于 刘超 <lc-soft@live.cn>
 * 
 * 这个文件是LCUI项目的一部分，并且只可以根据GPLv2许可协议来使用、更改和发布。
 *
 * (GPLv2 是 GNU通用公共许可证第二版 的英文缩写)
 * 
 * 继续使用、修改或发布本文件，表明您已经阅读并完全理解和接受这个许可协议。
 * 
 * LCUI 项目是基于使用目的而加以散布的，但不负任何担保责任，甚至没有适销性或特
 * 定用途的隐含担保，详情请参照GPLv2许可协议。
 *
 * 您应已收到附随于本文件的GPLv2许可协议的副本，它通常在LICENSE.TXT文件中，如果
 * 没有，请查看：<http://www.gnu.org/licenses/>. 
 * ****************************************************************************/

#include <LCUI_Build.h>
#include <LCUI/LCUI.h>
#include <LCUI/gui/widget.h>
#include <LCUI/gui/widget/textview.h>
#include <LCUI/gui/widget/sidebar.h>

typedef struct {
	wchar_t *id;
	LCUI_Widget icon;
	LCUI_Widget text;
	LCUI_Widget item;
} SideBarItem;

typedef struct {
	LinkedList items;
	LCUI_TextStyle icon_style;
	LCUI_StyleVar line_height;
} SideBar;

static const char sidebar_css[] = ToString(

sidebar {
	width: 224px;
	background-color: #fff;
}

sidebar sidebar-item {
	width: 100%;
	height: 38px;
	background-color: rgba(255,255,255,0);
	padding: 0 16px 0 7px;
	border-top: 1px solid #f3f3f3;
}

sidebar sidebar-item:hover {
	background-color: #f5f5f5;
}

);

void SideBar_SetIconStyle( LCUI_Widget sidebar, LCUI_TextStyle *ts )
{
	SideBarItem *item;
	SideBar *sb = (SideBar*)sidebar->private_data;
	sb->icon_style = *ts;
	LinkedList_ForEach( item, 0, &sb->items ) {
		TextView_SetTextStyle( item->icon, &sb->icon_style );
	}
}

void SideBar_SetLineHeight( LCUI_Widget sidebar, LCUI_StyleVar *val )
{
	SideBar *sb = (SideBar*)sidebar->private_data;
}

void SideBar_GetIconStyle( LCUI_Widget sidebar, LCUI_TextStyle *ts )
{
	SideBar *sb = (SideBar*)sidebar->private_data;
	*ts = sb->icon_style;
}

LCUI_Widget SideBar_AppendItem( LCUI_Widget sidebar, const wchar_t *id, 
				const wchar_t *icon, const wchar_t *text )
{
	int len = id ? wcslen(id):0;
	wchar_t *new_id = (wchar_t*)malloc( sizeof(wchar_t)*(len+1) );
	LCUI_Widget w = LCUIWidget_New("sidebar-item");
	SideBarItem *sbi = (SideBarItem*)w->private_data;
	SideBar *sb = (SideBar*)sidebar->private_data;
	
	if( !new_id ) {
		Widget_AddTask( w, WTT_DESTROY );
		return NULL;
	}
	id ? wcscpy( new_id, id ) : (new_id[0] = 0,NULL);
	sbi->id ? free( sbi->id ) : 0;
	sbi->id = new_id;
	Widget_Append( sidebar, w );
	TextView_SetTextStyle( sbi->icon, &sb->icon_style );
	TextView_SetTextW( sbi->icon, icon );
	TextView_SetTextW( sbi->text, text );
	Widget_Show( w );
	LinkedList_Append( &sb->items, sbi );
	return w;
}

void SideBarItem_OnInit( LCUI_Widget w )
{
	SideBarItem *sbi = Widget_NewPrivateData(w, SideBarItem);
	sbi->icon = LCUIWidget_New("textview");
	sbi->text = LCUIWidget_New("textview");
	sbi->id = NULL;
	Widget_Append( w, sbi->icon );
	Widget_Append( w, sbi->text );
}

void SideBarItem_OnDestroy( LCUI_Widget w )
{

}

void SideBar_OnInit( LCUI_Widget w )
{
	SideBar *sb = Widget_NewPrivateData( w, SideBar );
	LinkedList_Init( &sb->items, sizeof(SideBarItem) );
	memset( &sb->icon_style, 0, sizeof(LCUI_TextStyle) );
	sb->icon_style.has_family = TRUE;
	sb->icon_style.has_fore_color = TRUE;
	sb->icon_style.fore_color = RGB(0x26,0x26,0x26);
	sb->icon_style.pixel_size = 16;
}

void SideBar_OnDestroy( LCUI_Widget w )
{

}

void LCUIWidget_AddSideBar(void)
{
	LCUI_WidgetClass *wc;
	wc = LCUIWidget_AddClass("sidebar");
	wc->methods.init = SideBar_OnInit;
	wc->methods.destroy = SideBar_OnDestroy;
	wc = LCUIWidget_AddClass("sidebar-item");
	wc->methods.init = SideBarItem_OnInit;
	wc->methods.destroy = SideBarItem_OnDestroy;
	LCUI_ParseStyle( sidebar_css );
}