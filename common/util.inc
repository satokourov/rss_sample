<?php
//==================================================
// システム：RSSシステム
// 機能    ：共通関数定義
// 概要    ：
//==================================================

require_once 'define.inc';

//--------------------------------------------------
// 概要：Utilクラス
// 備考：
//--------------------------------------------------
class Util {

	//--------------------------------------------------
	// 概要：ページャ情報を取得(ページ番号、ページ数等)
	// 引数：count 全データ数(ページ数ではない)
	//       page 選択するページ
	//       limit 1ページに表示するデータ数
	//       pagenum 一度に表示するページ番号の数
	// 返値：$pager['count']    データ数
	//       $pager['page']     現在のページ
	//       $pager['max_page'] ページ数
	//       $pager['limit']    一度に表示するデータ数
	//       $pager['offset']   0から始まる表示するデータの開始位置
	//       $pager['start']    表示するページの開始番号
	//       $pager['end']      表示するページの終了番号
	// 備考：SQLでLIMIT等を使用するときはこの関数の返値を使用すること
	//--------------------------------------------------
	function pager($count, $page, $limit, $pagenum = 10) {
		$count = (int)$count;
		$page = (int)$page;
		$limit = (int)$limit;
		if ($count < 0) $count = 0;
		if ($page < 1) $page = 1;
		if ($limit < 10) $limit = 10;
		if ($limit > 100) $limit = 100;

		// ページ数
		$max_page = (int)ceil((float)$count / $limit);
		if ($max_page < 1) $max_page = 1;
		if ($page > $max_page) $page = $max_page;

		// 選択できるページ範囲を設定
		$start = $page - (int)($pagenum / 2);
		if ($start < 1) $start = 1;
		$end = $start + ($pagenum - 1);
		if ($end > $max_page) $end = $max_page;
		$start = $end - ($pagenum - 1);
		if ($start < 1) $start = 1;

		$pager = array(
			'count' => $count
			, 'page' => $page
			, 'max_page' => $max_page
			, 'limit' => $limit
			, 'offset' => $limit * ($page - 1)
			, 'start' => $start
			, 'end' => $end
		);
		return $pager;
	}

	//--------------------------------------------------
	// 概要：SQL文のLike検索用の文字列に変換して返す
	// 引数：data データ配列
	//       name 値の添え字
	//       id キーの添え字
	// 返値：データ配列
	//--------------------------------------------------
	function convLikeSQL($str) {
		return '%' . str_replace('%', '\%', str_replace('_', '\_', str_replace("\\", "\\\\", $str))) . '%';
	}
};
