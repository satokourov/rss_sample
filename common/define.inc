<?php
//==================================================
// システム：RSSシステム
// 機能    ：共通定数定義
// 概要    ：
//==================================================

// 環境依存設定読み込み
$GLOBALS['ENVIRONMENT'] = @file_get_contents(dirname(__FILE__) . '/define/environment');
if ($GLOBALS['ENVIRONMENT'] != '') {
	$GLOBALS['ENVIRONMENT'] = dirname(__FILE__) . '/define/' . trim($GLOBALS['ENVIRONMENT']) . '.inc';
	if (is_file($GLOBALS['ENVIRONMENT'])) {
		require_once $GLOBALS['ENVIRONMENT'];
	} else {
		$GLOBALS['ENVIRONMENT'] = '';
	}
}
if ($GLOBALS['ENVIRONMENT'] == '') {
	// 環境依存設定が読み込めなかった場合
	echo '[001] メンテナンス中です。';
	exit;
}
unset($GLOBALS['ENVIRONMENT']);

// DSN
define('DB_DSN', 'mysql://' . DB_USERNAME . ':' . DB_PASSWORD . '@' . DB_HOST . '/' . DB_NAME . '?charset=utf8');

// Smartyへのパス
define('SMARTY_DIR', ROOT_PATH.'/library/Smarty/libs/');

// エラーログ出力先
ini_set('error_log', ROOT_PATH . '/log/php_' . date('Ym') . '.log');

//バッチログ出力先
define('B_LOG', ROOT_PATH . '/log/batch_' . date('Ymd') . '.log');

// セッションファイル保存先
session_save_path(ROOT_PATH . '/sess');

// RSSのURL
define('RSS_URL', 'http://*****.com/newentry.rdf');

// 検索情報保持期間
define('SEARCH_DATA_RETENTIONS', 60 * 60 * 24 * 30);
