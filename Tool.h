/*
 * CLCL
 *
 * Tool.h
 *
 * Copyright (C) 1996-2019 by Ohno Tomoaki. All rights reserved.
 *		https://www.nakka.com/
 *		nakka@nakka.com
 */

#ifndef _INC_TOOL_H
#define _INC_TOOL_H

/* Include Files */
#include "General.h"
#include "Data.h"

/* Define */
// ツールを実行するタイミング
// When to run the tool
#define CALLTYPE_MENU					1				// 動作メニュー / Operation menu
#define CALLTYPE_VIEWER					2				// ビューアのメニュー / Viewer menu
#define CALLTYPE_VIEWER_OPEN			4				// ビューアを開いた時 / when viewer is opened
#define CALLTYPE_VIEWER_CLOSE			8				// ビューアを閉じる時 / when viewer is closed
#define CALLTYPE_ADD_HISTORY			16				// データが履歴に追加される時 / when data is added to history
#define CALLTYPE_ITEM_TO_CLIPBOARD		32				// データをクリップボードに送る時 / when sending data to the clipboard
#define CALLTYPE_START					64				// 起動時 / at startup
#define CALLTYPE_END					128				// 終了時 / when finished
// option only
#define CALLTYPE_MENU_COPY_PASTE		256				// コピーと貼り付けを送る / send copy and paste
// execute only
#define CALLTYPE_HISTORY				512				// 履歴からの呼び出し / call from history
#define CALLTYPE_REGIST					1024			// 登録アイテムからの呼び出し / call from registered item

// ツール戻り値
// tool return value
#define TOOL_ERROR						0				// ツールのエラー / tool error
#define TOOL_SUCCEED					1				// ツールの正常終了 / tool successfully completed
#define TOOL_CANCEL						2				// 以降の処理をキャンセル / cancel further processing
#define TOOL_DATA_MODIFIED				4				// データ変更あり / data changed


// ツール呼び出し方法 (旧ver)
// Tool calling method (old ver)
#define OLD_CALLTYPE_VIEWER				0
#define OLD_CALLTYPE_ADD_HISTORY		1
#define OLD_CALLTYPE_ITEM_TO_CLIPBOARD	2
#define OLD_CALLTYPE_NOITEM				4
#define OLD_CALLTYPE_MENU				8
#define OLD_CALLTYPE_START				16
#define OLD_CALLTYPE_END				32

// 旧ツールの関数形式
// Function format of old tool 
typedef int (__cdecl *OLD_TOOL_FUNC)(HWND, void *, int, int);
typedef int (__cdecl *OLD_GET_FUNC)(int, TCHAR *, TCHAR *, long *);

/* Struct */
// ツール情報
// Tool information
typedef struct _TOOL_INFO {
	TCHAR *title;
	TCHAR *lib_file_path;
	TCHAR *func_name;
	TCHAR *cmd_line;
	int call_type;						// CALLTYPE_
	int copy_paste;

	// hot key
	int id;
	UINT modifiers;
	UINT virtkey;

	HANDLE lib;
	FARPROC func;
	OLD_TOOL_FUNC old_func;

	int old;

	LPARAM lParam;						// ツールに対応するlong値 / Long value corresponding to the tool
} TOOL_INFO;

// ツール取得情報
// Tool acquisition information
typedef struct _TOOL_GET_INFO {
	DWORD struct_size;					// 構造体のサイズ / Structure size

	TCHAR title[BUF_SIZE];
	TCHAR func_name[BUF_SIZE];
	TCHAR cmd_line[BUF_SIZE];
	int call_type;						// CALLTYPE_
} TOOL_GET_INFO;
typedef struct _TOOL_GET_INFO_A {
	DWORD struct_size;					// 構造体のサイズ / Structure size

	char title[BUF_SIZE];
	char func_name[BUF_SIZE];
	char cmd_line[BUF_SIZE];
	int call_type;						// CALLTYPE_
} TOOL_GET_INFO_A;

// ツール実行情報
// Tool execution information
typedef struct _TOOL_EXEC_INFO {
	DWORD struct_size;					// 構造体のサイズ / Structure size

	int call_type;						// CALLTYPE_
	TCHAR *cmd_line;					// ツール設定で指定したコマンドライン / Command line specified in tool settings
	LPARAM lParam;						// ツールに対応するlong値 / long value corresponding to the tool
} TOOL_EXEC_INFO;

// ツール用アイテム情報
// Item information for tools
typedef struct _TOOL_DATA_INFO {
	DWORD struct_size;					// 構造体のサイズ / Structure size

	struct _DATA_INFO *di;				// アイテム情報 / Item information

	struct _TOOL_DATA_INFO *child;
	struct _TOOL_DATA_INFO *next;
} TOOL_DATA_INFO;

/* Function Prototypes */
int tool_title_to_index(const TCHAR *title);
BOOL tool_initialize(TCHAR *err_str);
TOOL_DATA_INFO *tool_data_copy(DATA_INFO *di, const BOOL next_copy);
void tool_data_free(TOOL_DATA_INFO *tdi);
int tool_execute(const HWND hWnd, TOOL_INFO *ti, const int call_type, DATA_INFO *di, TOOL_DATA_INFO *tdi);
int tool_execute_all(const HWND hWnd, const int call_type, DATA_INFO *di);

#endif
/* End of source */
