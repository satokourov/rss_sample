<?php
//==================================================
// システム：RSSシステム
// 機能    ：共通処理
// 概要    ：
//==================================================

require_once 'database.inc';
require_once 'util.inc';
require_once 'validator.inc';
require_once SMARTY_DIR . 'Smarty.class.php';

$GLOBALS['DB'] = new Database();

$GLOBALS['SMARTY'] = new Smarty();
$GLOBALS['SMARTY']->template_dir = ROOT_PATH . '/templates';
$GLOBALS['SMARTY']->compile_dir = ROOT_PATH . '/templates_c';
$GLOBALS['SMARTY']->default_modifiers = array('escape:"html"');
$GLOBALS['SMARTY']->register_modifier('disp_date', array('Util', 'toDispDate'));

if (!$GLOBALS['DB']->isValid()) {
	// DB接続失敗
	session_start();
	session_destroy();
	echo '[002] メンテナンス中です。';
	exit;
}
