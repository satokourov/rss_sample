<?php
//==================================================
// システム：RSSシステム
// 機能    ：RSSデータの検索・一覧処理
// 概要    ：
//==================================================

require_once 'common.inc';
require_once 'models/index.inc';

$err = null;

// Cookieの情報を取得
$search_cond['date']           = $_COOKIE['date'];
$search_cond['link']           = $_COOKIE['link'];
$search_cond['user_id']        = $_COOKIE['user_id'];
$search_cond['server_num']     = $_COOKIE['server_num'];
$search_cond['from_entry_num'] = $_COOKIE['from_entry_num'];
$search_cond['to_entry_num']   = $_COOKIE['to_entry_num'];
$search_cond['title']          = $_COOKIE['title'];

if ( $_POST['reset'] == '1' ) {

	//検索条件とCookieを削除
	$search_cond = array();
	setcookie('date', '', time() - 1800);
	setcookie('link', '', time() - 1800);
	setcookie('user_id', '', time() - 1800);
	setcookie('server_num', '', time() - 1800);
	setcookie('from_entry_num', '', time() - 1800);
	setcookie('to_entry_num', '', time() - 1800);
	setcookie('title', '', time() - 1800);
} elseif ( $_POST['sc'] == '1' ) {

	// 検索文言のチェック
	$err = checkSearchData($_POST);
	$_POST['server_num'] = ( empty($_POST['server_num']) ) ? NULL : $_POST['server_num'];
	$_POST['from_entry_num'] = ( empty($_POST['from_entry_num']) ) ? NULL : $_POST['from_entry_num'];
	$_POST['to_entry_num'] = ( empty($_POST['to_entry_num']) ) ? NULL : $_POST['to_entry_num'];

	// エントリーNoのFrom～To値の確認
	if ( !empty($_POST['from_entry_num']) && !empty($_POST['to_entry_num']) && ($_POST['from_entry_num'] > $_POST['to_entry_num']) ) {
		list($_POST['to_entry_num'], $_POST['from_entry_num']) = array($_POST['from_entry_num'], $_POST['to_entry_num']);
	}

	//検索条件を取得
	$search_cond['date']           = $_POST['date'];
	$search_cond['link']           = $_POST['link'];
	$search_cond['user_id']        = $_POST['user_id'];
	$search_cond['server_num']     = $_POST['server_num'];
	$search_cond['from_entry_num'] = $_POST['from_entry_num'];
	$search_cond['to_entry_num']   = $_POST['to_entry_num'];
	$search_cond['title']          = $_POST['title'];
	$search_cond['limit']          = 10;
	$search_cond['page']           = 1;

	//検索条件をCookieに保存
	setcookie('date', $search_cond['date'], time() + SEARCH_DATA_RETENTIONS);
	setcookie('link', $search_cond['link'], time() + SEARCH_DATA_RETENTIONS);
	setcookie('user_id', $search_cond['user_id'], time() + SEARCH_DATA_RETENTIONS);
	setcookie('server_num', $search_cond['server_num'], time() + SEARCH_DATA_RETENTIONS);
	setcookie('from_entry_num', $search_cond['from_entry_num'], time() + SEARCH_DATA_RETENTIONS);
	setcookie('to_entry_num', $search_cond['to_entry_num'], time() + SEARCH_DATA_RETENTIONS);
	setcookie('title', $search_cond['title'], time() + SEARCH_DATA_RETENTIONS);
}

if ($_POST['limit'] != '') {
	$search_cond['limit'] = $_POST['limit'];
	$search_cond['page'] = 1;
} elseif ($_GET['page'] != '') {
	$search_cond['page'] = $_GET['page'];
}

// 件数
$data_cnt = getRssList($search_cond, true);
// データ一覧
$pager = Util::pager($data_cnt, $search_cond['page'], $search_cond['limit']);
$search_cond['limit']  = $pager['limit'];
$search_cond['offset'] = $pager['offset'];
$data_list = getRssList($search_cond, false);

$GLOBALS['SMARTY']->assign('search_cond', $search_cond);
$GLOBALS['SMARTY']->assign('pager', $pager);
$GLOBALS['SMARTY']->assign('data_list', $data_list);
$GLOBALS['SMARTY']->assign('err', $err);
$GLOBALS['SMARTY']->display('index.tpl');

//--------------------------------------------------
// 概要：検索条件の入力チェック
// 引数：data データ
// 返値：エラーがあればエラー配列、それ以外はnull
//--------------------------------------------------
function checkSearchData(&$data) {
	$err = null;

	if ( ($errmsg = Validator::date($data['date'], '日付')) != '' && !empty($data['date']) ) {
		$err[] = $errmsg;
	}
	if ( ($errmsg = Validator::number($data['server_num'], 'サーバ番号')) != '' && !empty($data['server_num']) ) {
		$err[] = $errmsg;
	}
	if ( ($errmsg = Validator::number($data['from_entry_num'], 'エントリーNo')) != '' && !empty($data['from_entry_num']) ) {
		$err[] = $errmsg;
	}
	if ( ($errmsg = Validator::number($data['to_entry_num'], 'エントリーNo')) != '' && !empty($data['to_entry_num']) ) {
		$err[] = $errmsg;
	}

	return $err;
}
